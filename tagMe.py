#!/home/users/liuyuanzhe/.jumbo/bin/python
#coding=utf-8

import os
import sys, getopt
import commands

VERSION = "1.0 liuyuanzhe123@126.com"

def cscope():
    #find查找指定格式的源文件, 生成cscope.files
    extension = ("php", "py", "c", "cpp", "cc", "sh", "h")
    cur_dir = "."
    cmd = "find " + cur_dir
    
    type_args = ""
    if (len(extension) > 0):
        type_args = " -name '*." + extension[0]+"'"
        for i in range(1, len(extension)):
            ext = extension[i]
            type_args += " -o -name '*." + extension[i]+"'"
    else:
        print "no given extension, please check"

    cmd = cmd + type_args + " >cscope.files"
    #print cmd
    os.system(cmd)
    #查找软连接目录下的文件追加到cscope.files
    (status, link_dir) = commands.getstatusoutput("find . -type l")
    #小技巧：查找软连接目录中的文件需要目录名以/结尾。 如：find ./handler/ -name "*.php"
    link_dir = link_dir.replace('\n', "/ ")

    if (0 != len(link_dir)):
        cmd = "find " + link_dir + type_args + ">>cscope.files"
        #print cmd
        os.system(cmd)

    #cscopes根据cscope.files生成cscope.out等数据文件
    cmd = "cscope -bq"
    os.system(cmd)

def ctags():
    tags_cmd = "ctags -R"
    os.system(tags_cmd)
def version():
    print VERSION

def usage():
    print """Usage: tagMe.py -[c|v|h]
        -c clean tags and cscope.*
        -h help
        -v version
    """
def clean_tags():
    remove_list = "tags cscope.*"
    os.system("rm -f "+remove_list)

def make_ctags_cscope():
    clean_tags()
    cscope()
    ctags()

def main():
    if (len(sys.argv) == 1):
        make_ctags_cscope()
        print "generate tags ok!"
    else:
        try:
            opts, args = getopt.getopt(sys.argv[1:], "cvh")
            for opt, value in opts:
                if ("-c" == opt):
                    clean_tags()
                    print "clean tags ok!"
                elif ("-v" == opt):
                    version()
                elif ("-h" == opt):
                    usage()
                else:
                    print "Unknow options"
                    usage()
        except getopt.GetoptError as err:
            print err
            usage()
            sys.exit(-1)



if  __name__ == "__main__":
    main()

