cmake_minimum_required(VERSION 3.0)
project(Appraise_sys)

#添加当前文件的所有.c文件给变量src_list
AUX_SOURCE_DIRECTORY(./src src_list)

#将部分代码进行静态链接
#add_library(archive ${src_list})
#add_executable(Appraise_sys AppraiseSystem.c)

#链接
ADD_EXECUTABLE(Appraise_sys ${src_list})

#将静态部分链接进来
#target_link_libraries(Appraise_sys archive)