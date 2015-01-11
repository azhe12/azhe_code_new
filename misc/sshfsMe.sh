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
		--ip)
			shift
			if [ -z "$1" ];then
				echo "Please enter ip address" && exit 1
			fi
			client_ip=$1
			;;
		-*)
			echo "unreconize option" 1>&2
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
			sudo sshfs -o cache=yes,allow_other display@${client_ip:-10.33.138.156}:/home/display /home/azhe/share/display/
			set +x
			;;
		azhe_htc)
			echo "sshfs connect: azhe-htc"
			set -x
			sudo sshfs -o cache=yes,allow_other azhe@${client_ip:-10.33.137.177}:/home/azhe /home/azhe/share/azhe_htc
			set +x
			;;
		azhe_laptop)
			echo "sshfs connect: $CLIENT"
			set -x
			sudo sshfs -o cache=yes,allow_other azhe@${client_ip:-10.33.219.14}:/home/azhe /home/azhe/share/azhe_laptop
			set +x
			;;
        azhe_vm)
			echo "sshfs connect: $CLIENT"
			set -x
			sudo sshfs -o cache=yes,allow_other azhe-vt@${client_ip:-192.168.189.129}:/home/azhe-vt /home/azhe/share/azhe_vm
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
        azhe_vm)
			echo "ssh connect: $CLIENT"
			set -x
			ssh azhe-vt@192.168.189.129
			set +x
            ;;
		*)
			echo "unrecognize client $CLIENT" 1>&2
			exit 1
			;;
	esac
fi

set +x
