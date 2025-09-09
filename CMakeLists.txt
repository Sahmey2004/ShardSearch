# /shardsearch/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(shardsearch CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core library of search code
add_library(ir
  src/ir/tokenize.cpp
  src/ir/index.cpp
  src/ir/bm25.cpp
)
target_include_directories(ir PUBLIC src)

# Small demo apps we can run at each step
add_executable(tokenize_demo src/demos/tokenize_demo.cpp)
target_link_libraries(tokenize_demo PRIVATE ir)

add_executable(index_demo src/demos/index_demo.cpp)
target_link_libraries(index_demo PRIVATE ir)

add_executable(searchd src/main.cpp)
target_link_libraries(searchd PRIVATE ir)
