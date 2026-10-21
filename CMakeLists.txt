cmake_minimum_required(VERSION 3.16)
project(reactor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)   # runs moc for you on Q_OBJECT classes
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets PrintSupport)

option(SANITIZE "Build with ASan/UBSan" OFF)
if(SANITIZE)
  add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer -g)
  add_link_options(-fsanitize=address,undefined)
endif()

add_executable(reactor src/sim.cpp src/sim.h src/physics.cpp src/main.cpp src/plots.cpp src/constants.h src/lib/qcustomplot.h src/lib/qcustomplot.cpp)
target_link_libraries(reactor PRIVATE Qt6::Widgets Qt6::PrintSupport)
