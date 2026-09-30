cmake_minimum_required(VERSION 3.16)
project(reactor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)   # runs moc for you on Q_OBJECT classes

find_package(Qt6 REQUIRED COMPONENTS Widgets PrintSupport)

add_executable(reactor reactor.cpp main.cpp plots.cpp third_party/qcustomplot/qcustomplot.cpp)
target_link_libraries(reactor PRIVATE Qt6::Widgets Qt6::PrintSupport)
