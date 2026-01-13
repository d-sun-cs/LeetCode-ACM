cmake_minimum_required(VERSION 3.12)
project(LeetCode-ACM)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用测试
enable_testing()

# 找到所有以数字命名的题号目录
file(GLOB PROBLEM_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "[0-9]*")

# 对每个题号目录进行处理
foreach(PROBLEM_DIR ${PROBLEM_DIRS})
    set(PROBLEM_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${PROBLEM_DIR})
    
    # 检查该目录是否存在main.cpp
    if(EXISTS "${PROBLEM_PATH}/main.cpp")
        # 添加可执行文件（问题的代码）
        add_executable(${PROBLEM_DIR} ${PROBLEM_PATH}/main.cpp)
        
        # 设置该目标的输出目录为题号文件夹
        set_target_properties(${PROBLEM_DIR} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${PROBLEM_PATH}
        )
        
        # 为每个问题创建测试executable（而非自定义目标）
        if(EXISTS "${PROBLEM_PATH}/input.txt" AND EXISTS "${PROBLEM_PATH}/output.txt")
            add_executable(test_${PROBLEM_DIR} test.cpp)
            
            # 通过编译定义传递问题号和项目源目录
            target_compile_definitions(test_${PROBLEM_DIR} PRIVATE 
                "PROBLEM_NUMBER=\"${PROBLEM_DIR}\""
                "PROJECT_SOURCE_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\""
            )
            
            # 测试程序输出到build/bin目录
            set_target_properties(test_${PROBLEM_DIR} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
            )
            
            # 设置测试程序依赖问题程序
            add_dependencies(test_${PROBLEM_DIR} ${PROBLEM_DIR})
            
            # 注册为可运行的测试
            add_test(
                NAME test_${PROBLEM_DIR}
                COMMAND test_${PROBLEM_DIR}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            )
        endif()
    endif()
endforeach()

