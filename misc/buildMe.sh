#!/bin/bash
#set -x
PROGRAM=$(basename $0)
ERROR_CODE=0
flag_repo=0
flag_setup_env=0
flag_build=0
time_now()
{
	echo -n $(date '+%s')
}

repo_code()
{
	case $1 in
		z4td|cp5dtg|cp5dug|cp5dtu)
			repo init -u ssh://10.33.8.6:29419/manifest.git -b htc -m jb-mr0-rel_shep_sprd8825_dsda_sense50.xml; repo sync
			;;
		*)
			warning "unrecognize project $1"
			;;
	esac
}

setup_env()
{
	case $1 in
		cp5dug)
			export HTCFW_ENABLED=true; export HTC_BUILD_STUBS_FLAG=true; source build/envsetup.sh ; partner_setup cp5dug CP5DUG_Generic_WWE_DEBUG 
			;;
		z4td)
			export HTCFW_ENABLED=true; export HTC_BUILD_STUBS_FLAG=true; source build/envsetup.sh ; partner_setup z4td Z4TD_Generic_WWE_DEBUG
			;;
		*)
			warning "unrecognize project $1"
			;;
	esac
}
build()
{
	case $1 in
			cp5dug)
				. setup_env cp5dug;make -j4 PRODUCT-cp5dug-userdebug
				;;
			z4td)
				. setup_env z4td;make -j4 PRODUCT-z4td-userdebug
				;;
			*)
				warning "unrecognize project $1"
				;;
	esac
}

usage()
{
	cat <<EOT 1>&2
		Usage: $PROGRAM [--repo|--setup|--build|--help] project
EOT
}

usage_exit()
{
	usage
	((ERROR_CODE+=1))
}
warning()
{
	echo $@ 1>&2
	((ERROR_CODE+=1))
}
START_TIME=$(time_now)

test $# -lt 2 && usage

for arg in $@
do
	case $arg in
		--help)
			usage
			;;
		--repo)
			flag_repo=1
			shift
			;;
		--setup)
			flag_setup_env=1
			shift
			;;
		--build)
			flag_build=1
			shift
			;;
		--*)
			warning "unknow agrument"
			usage_exit;
			;;
		*)
			break
	esac
done
test $ERROR_CODE = 0 && test $# != 1 && warning "support only project at same time"

PROJECT=$@
test $ERROR_CODE = 0 && test $flag_repo = 1 && repo_code $PROJECT
test $ERROR_CODE = 0 && test $flag_setup_env = 1 && setup_env $PROJECT
test $ERROR_CODE = 0 && test $flag_build = 1 && build $PROJECT
ELAPSE_TIME=$(($(time_now) - $START_TIME))

echo "\
/*************************** \
Done! Elipse:  $(($ELAPSE_TIME / 60))m $(($ELAPSE_TIME % 60))s \
****************************/"
#set +x