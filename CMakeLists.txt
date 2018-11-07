cmake_minimum_required(VERSION 2.8.3)
project(ros_qt_gui)

## Compile as C++11, supported in ROS Kinetic and newer
#add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
    roscpp
    rviz
    roslib
    std_msgs
    message_generation
)


find_package(Qt5 REQUIRED COMPONENTS
    PrintSupport
    Gui
    Core
)
find_package(Qt5Widgets REQUIRED)

 add_message_files(
   FILES
   IMU.msg
   EMG.msg
 )

add_service_files(
   FILES
   service.srv
#   Service2.srv
 )

generate_messages(
   DEPENDENCIES
   std_msgs  # Or other packages containing msgs
 )

set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(qt_src
    src/mainwindow.cpp
    src/gui_myrviz.cpp
    src/ros_node.cpp
    src/qcustomplot.cpp
    src/data_plot.cpp
    src/ros_service_pub.cpp
    src/mymessagebox.cpp
 )
set(qt_hdr
    include/mainwindow.h
    include/gui_myrviz.h
    include/ros_node.h
    include/qcustomplot.h
    include/data_plot.h
    include/ros_service_pub.h
    include/mymessagebox.h
   )


QT5_WRAP_CPP(qt_moc_srcs ${qt_hdr})
QT5_WRAP_UI(uis_h ${PROJECT_SOURCE_DIR}/ui/mainwindow.ui)
#set(CMAKE_AUTOUIC ON)



catkin_package(
 # INCLUDE_DIRS include
  LIBRARIES ros_qt_gui
  CATKIN_DEPENDS roscpp  rviz roslib  std_msgs message_runtime
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/ui
  ${PROJECT_SOURCE_DIR}
)

add_library(mainwindow 
   ${qt_hdr}
   ${uis_h}
   ${qt_src}
)
target_link_libraries (mainwindow Qt5::Widgets Qt5::PrintSupport)

add_executable(main_gui src/main.cpp)

#add_executable(main_gui src/main.cpp ${uis_h} ${qt_hdr} ${qt_src} )
#add_dependencies(main ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(main_gui
                 mainwindow
                   ${catkin_LIBRARIES}
                   ${Qt5Widgets_LIBRARIES}    )
add_dependencies(main_gui ros_qt_gui_gencpp)


