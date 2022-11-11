#----------------------------------------------------------------------------
# Setup the project
#设置项目名称
cmake_minimum_required(VERSION 3.16...3.21)
project(M1)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
# 找到Geant4安装目录，即Geant4Config.cmake所在目录
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
# 自动配置Geant4头文件

include(${Geant4_USE_FILE})


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
# 定位项目的源文件和头文件
# 将用户自定义头文件和Geant4头文件一并添加到头文件目录，即-I路径
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR})
#将用户自定义源文件 ，头文件，一并添加到CMake全局变量中                   
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#添加可执行文件，并链接到Geant4的库
add_executable(M1 M1.cc ${sources} ${headers})

# 将可执行文件dnaphysics链接到Geant4库
target_link_libraries(M1 ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build M1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#复制所有脚本到build目录，因为可执行文件依赖于一些宏命令等，拷贝后可直接运行
# 将目录下以*.mac、*.in和*.C结尾的文件添加到全局变量MAC_FILES中
set(EXAMPLEM1_SCRIPTS
init_vis.mac
vis.mac 
  )
#下面这俩我不知道要不要加


# 将遍历到的文件路径${_script}拷贝到指定路径${PROJECT_BINARY_DIR}/. 并执行指定操作
# 这里的操作是只复制：COPYONLY
foreach(_script ${EXAMPLEM1_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
#add_custom_target(M1 DEPENDS exampleM1)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#将可执行二进制文件dnaphysics安装到'bin'目录
install(TARGETS M1 DESTINATION bin)
