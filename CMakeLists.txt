cmake_minimum_required(VERSION 3.16)
project(reactor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)   # runs moc for you on Q_OBJECT classes
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets PrintSupport)

add_executable(reactor src/reactor.cpp src/main.cpp src/plots.cpp src/constants.h src/lib/qcustomplot.h src/lib/qcustomplot.cpp)
target_link_libraries(reactor PRIVATE Qt6::Widgets Qt6::PrintSupport)
