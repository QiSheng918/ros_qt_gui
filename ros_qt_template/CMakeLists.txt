cmake_minimum_required(VERSION 3.1.0) #version 3.1.0 is recommended for qt5
project(ros_qt_template)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  pcl_msgs
  rviz
  roslib
  geometry_msgs
  turtlesim
)

find_package(Qt5 REQUIRED COMPONENTS
    PrintSupport
    Gui
    Core
)
find_package(Qt5Widgets REQUIRED)



set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(  qt_srcs
      GUI/mainwindow.cpp
      GUI/gui_myrviz.cpp
      GUI/sub_node.cpp
      ./qcustomplot.cpp
      GUI/data_plot.cpp
   )
set(  qt_hdrs
      GUI/mainwindow.h
      GUI/gui_myrviz.h
      CUI/sub_node.h
      ./qcustomplot.h
      GUI/data_plot.h
   )

QT5_WRAP_CPP(qt_moc_srcs ${qt_hdrs})
QT5_WRAP_UI(uis_h GUI/mainwindow.ui)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${Qt5Widgets_INCLUDES})

catkin_package(
 # INCLUDE_DIRS include
  LIBRARIES ros_qt_template
  CATKIN_DEPENDS roscpp pcl_msgs rviz roslib geometry_msgs turtlesim
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(mainwindow GUI/mainwindow.cpp GUI/gui_myrviz.cpp GUI/sub_node.cpp ./qcustomplot.cpp GUI/data_plot.cpp)
target_link_libraries (mainwindow Qt5::Widgets Qt5::PrintSupport)

add_executable(main src/main.cpp)
target_link_libraries(main
                   mainwindow
                   ${catkin_LIBRARIES}
                   ${Qt5Widgets_LIBRARIES}    )
