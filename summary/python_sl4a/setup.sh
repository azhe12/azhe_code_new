set -x
PORT_HOST=9999

usage()
{
    echo "Usage: . setup.sh [-start|stop] [-p port]"
    echo "port default is 45001"
    echo "Example: . setup.sh 45002"
}

#start sl4a server Port:45001
start_sl4a()
{
    adb shell "am start -a com.googlecode.android_scripting.action.LAUNCH_SERVER \
                        -n com.googlecode.android_scripting/.activity.ScriptingLayerServiceLauncher \
                        --ei com.googlecode.android_scripting.extra.USE_SERVICE_PORT ${PORT_DEVICE}"
    
    adb forward tcp:${PORT_HOST} tcp:${PORT_DEVICE}
    export AP_PORT=${PORT_HOST}
}

end_sl4a()
{
    adb shell am force-stop  com.googlecode.android_scripting
}


n=0
start=0
stop=0
#while getopts sp:
while [ $# -gt 0 ]
do
    case $1 in
    -s|--start)
        start=1
        ;;
    -e|--end)
        end=1
        ;;
    -p|--port)
        port=$2
        shift
        ;;
    --)
        break
        ;;
    -*)
        echo "$0: $1: unrecognized option >&2"
        usage
        break
        ;;
    *)
        echo "$0: $1: unrecognized option >&2"
        usage
        ;;
    esac
    shift
done

PORT_DEVICE=${port:-45001}
[ $start = 1 ] && start_sl4a
[ $end = 1 ] && end_sl4a

set +x
