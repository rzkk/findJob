cmake_minimum_required(VERSION 3.15)

project(systemLearning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g  -fno-elide-constructors -Wall ")

# 包含目录 头文件目录
include_directories( ${CMAKE_SOURCE_DIR}/include )
# include_directories( ${CMAKE_SOURCE_DIR}/src )
link_directories(${CMAKE_SOURCE_DIR}/src)

# set(CMAKE_BUILD_TYPE Debug)
add_definitions(-DDEBUG)

# add_executable(fileTest  src/file.cpp  ) 
#target_link_options(shellTest PRIVATE -static)
#target_include_directories(shellTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
# target_link_libraries(shellTest add)
#target_link_directories(shellTest PRIVATE ${CMAKE_SOURCE_DIR}/src)
# target_compile_definitions(fileTest PRIVATE -DDEBUG)


# add_executable(pipRead   src/pipeRead.cpp  ) 
# add_executable(pipwrite  src/pipeWrite.cpp  ) 

# add_executable(zhenzhen   src/chat/azhen.cpp  ) 
# add_executable(qiangqiang src/chat/aqiang.cpp  ) 

#  add_executable(processTest  src/process.cpp  ) 
# add_executable(test  src/test.cpp  ) 
add_executable(threadTest  src/thread.cpp  ) 
target_link_libraries(threadTest pthread)
