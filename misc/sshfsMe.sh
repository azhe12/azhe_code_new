#!/bin/bash
#set -x
flag_sshfs=0
flag_ssh=1
usage()
{
	echo "Usage:$(basename $0) [--sshfs] clientname" 1>&2
}
for arg in $@
do
	case $arg in
		--sshfs)
			flag_sshfs=1
			flag_ssh=0
			;;
		-*)
			echo "unreconize ssh client" 1>&2
			usage
			exit 1
			;;
		*)
			break
			;;
	esac
	shift
done

test !$# = 1 && usage && exit 1
CLIENT=$1

#sshfs
if [ $flag_sshfs = 1 ];then
	case $CLIENT in
		display)
			echo "sshfs connect: display"
			set -x
			sudo sshfs -o cache=yes,allow_other display@10.33.138.156:/home/display /home/azhe/share/display/
			set +x
			;;
		azhe_htc)
			echo "sshfs connect: azhe-htc"
			set -x
			sudo sshfs -o cache=yes,allow_other azhe@10.33.137.177:/home/azhe /home/azhe/share/azhe_htc
			set +x
			;;
		*)
			echo "unrecognize client $CLIENT" 1>&2
			exit 1
			;;
	esac
else #ssh
	case $CLIENT in
		display)
			echo "ssh connect: display"
			set -x
			ssh display@10.33.138.156
			set +x
			;;
		azhe_htc)
			echo "ssh connect: azhe_htc"
			set -x
			ssh azhe@10.33.137.177
			set +x
			;;
		*)
			echo "unrecognize client $CLIENT" 1>&2
			exit 1
			;;
	esac
fi

set +x
