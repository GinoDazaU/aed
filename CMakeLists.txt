cmake_minimum_required(VERSION 3.28)
project(Test)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)

add_executable(test ./data_structures/s7_avl/test.cpp
        data_structures/s7_avl/TreeNode.cpp)
add_executable(balance_bst_lc sem7/balance_bst_lc.cpp)
