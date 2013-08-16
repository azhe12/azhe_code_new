#!/bin/bash
usage()
{
	echo -e "Usage: textToxml input-file. \noutput: input-file.xml" 1>&2
}
set -x
if [ -z $1 ];then
	usage
	exit 1
fi
INPUT_FILE=$1
OUTPUT_XML=$1.xml
TMP_XML=$(mktemp).xml
SED_SCRIPT=$(mktemp).sed

cat <<EOF >$SED_SCRIPT
s:__TABLE_START__:<?xml version="1.0" ?>\n<rt5501>:
s:SECTION_START:\t<mode>:
s:SECTION_END:\t</mode>:
s:MODE \(.*\):\t\t<id>\1</id>:
s:\(^0x.*\), \(0x.*\),#*\(.*\):\t\t<register><!--\3-->\n\t\t\t<addr>\1</addr>\n\t\t\t<value>\2</value>\n\t\t</register>:
s:\(^#.*\):<!--\1-->:
s:__TABLE_END__:</rt5501>:
EOF

sed -f $SED_SCRIPT $INPUT_FILE >$TMP_XML

sed 's;<!---->;;g' $TMP_XML >$OUTPUT_XML
rm -rf $TMP_XML $SED_SCRIPT

exit 0
