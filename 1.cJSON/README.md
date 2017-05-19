
#cJSON
An ultra-lightweight, portable, single-file, simple-as-can-be ANSI-C compliant JSON parser, under MIT license.

git repository: https://github.com/DaveGamble/cJSON

directory structure:
cJSON:   cJSON Library Source Code
include: headers
lib:     static lib and shared lib
test:    my test 

##在test目录执行测试需,设置../lib目录为环境变量
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../lib
