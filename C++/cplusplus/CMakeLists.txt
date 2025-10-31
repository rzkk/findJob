# 指定cmake版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(cPlusPlusLearning)

# 添加编译参数 -O0  -fno-elide-constructors 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g  -fno-elide-constructors -Wall ")    
#-O2 可能会优化代码结构，
#不便于调试-fno-elide-constructors: 主要对临时变量的优化效果
# -fno-elide-constructors

# 设置代码构建级别为 Debug 方式
set(CMAKE_BUILD_TYPE Debug)

#message(${CMAKE_CXX_FLAGS})

# 包含目录 头文件目录
include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR}/src )
#include_directories( include )

#message( ${CMAKE_SOURCE_DIR})
#link_directories(/usr/lib/mylibfolder ./lib)

# 编译
# add_executable(externTest src/extern/externA.cpp src/extern/externB.cpp  )  
#add_executable(cppbaseTest src/cppbase.cpp  src/namespace/complex.cpp   src/class/myBaseCpp.cpp)  #src/inline.cpp
#add_executable(cppbaseTest src/cppbase.cpp  src/namespace/complex.cpp  )  #src/inline.cpp
# add_executable(stringTest src/string.cpp ) 
# add_executable(vectorTest src/vector.cpp ) 
#add_executable(streamTest src/Stream.cpp ) 

# function(redefine_file_macro targetname) #__FILE__输出相对路径
#     #获取当前目标的所有源文件
#     get_target_property(source_files "${targetname}"  SOURCES)
#     #遍历源文件
#     foreach(sourcefile ${source_files})
#         #获取当前源文件的编译参数
#         get_property(defs SOURCE "${sourcefile}"
#             PROPERTY COMPILE_DEFINITIONS)
#         #获取当前文件的绝对路径
#         get_filename_component(filepath "${sourcefile}" ABSOLUTE)
#         #将绝对路径中的项目路径替换成空,得到源文件相对于项目路径的相对路径
#         string(REPLACE ${PROJECT_SOURCE_DIR}/ "" relpath ${filepath})
#         #将我们要加的编译参数(__FILE__定义)添加到原来的编译参数里面
#         list(APPEND defs "__FILE__=\"${relpath}\"")

#         #add_compile_definitions(__FILE__="${relpath}")
#         #target_compile_definitions(${targetname} PRIVATE __FILE__="${relpath}")
#         #重新设置源文件的编译参数
#         set_property(
#             SOURCE "${sourcefile}"
#             PROPERTY COMPILE_DEFINITIONS ${defs}
#             )
#     endforeach()
# endfunction()



# add_executable(log4cppTest 
#                     src/log4cpp/log4cppTest.cpp 
#                     src/log4cpp/myLogger.cpp ) 
# target_link_libraries(log4cppTest log4cpp pthread)

# redefine_file_macro(log4cppTest)


#  add_library(LineImpl SHARED src/LineImpl.cpp)
#  link_directories(build)
#  add_executable(operatorTest src/operatorTest.cpp  src/CowString.cpp)
#  target_link_libraries(operatorTest LineImpl pthread)


# add_executable(myStringTest 
#     src/myStringTest.cpp 
#     src/myString.cpp)

# add_executable(smartPtr  src/smartPtr.cpp)
# add_executable(moveTest  src/moveTest.cpp)

#add_executable(associativeTest src/associative.cpp)

#add_executable(inheritanceTest src/inheritance.cpp)
# add_executable(raii src/RAII.cpp)

# add_executable(templateTest 
#             src/template.cpp 
#             src/template/add.tcc
#             )
# add_executable(SsoStringTest src/SsoString.cpp)

  # add_executable(stlTest  src/stl2.cpp)
 # add_executable(myVectorTest  src/myVector.cpp)
  # add_executable(stlTest  src/stl.cpp)
# add_executable(Test  src/test.cpp)

# add_executable(test  src/test.cpp)
add_executable(leetcode  src/leetcode.cpp)