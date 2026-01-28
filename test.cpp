#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// 获取问题号：由 CMake 在编译时定义
std::string getProblemNumber()
{
#ifdef PROBLEM_NUMBER
    return PROBLEM_NUMBER;
#else
#error "PROBLEM_NUMBER must be defined by CMake"
#endif
}

// 按分隔符将内容分割成多个部分
// 格式：开头没有---，之后每组用---隔开，结尾有---
std::vector<std::string> splitByDelimiter(const std::string &content, const std::string &delimiter)
{
    std::vector<std::string> parts;
    size_t start = 0;
    size_t end = content.find(delimiter);

    auto trim = [](std::string &s)
    {
        while (!s.empty() && (s.front() == '\n' || s.front() == '\r' || s.front() == ' ' || s.front() == '\t'))
        {
            s.erase(0, 1);
        }
        while (!s.empty() && (s.back() == '\n' || s.back() == '\r' || s.back() == ' ' || s.back() == '\t'))
        {
            s.pop_back();
        }
    };

    while (end != std::string::npos)
    {
        std::string part = content.substr(start, end - start);
        trim(part);
        parts.push_back(part);
        start = end + delimiter.length();
        end = content.find(delimiter, start);
    }

    return parts;
}

int main()
{
    std::string problem_num = getProblemNumber();

    // 获取项目根目录（源码）和二进制目录（可执行文件所在），由 CMake 在编译时定义
#ifdef PROJECT_SOURCE_DIR
    std::string source_root = PROJECT_SOURCE_DIR;
#else
#error "PROJECT_SOURCE_DIR must be defined by CMake"
#endif

#ifdef BIN_DIR
    std::string bin_dir = BIN_DIR; // e.g. ${CMAKE_BINARY_DIR}/bin
#else
#error "BIN_DIR must be defined by CMake"
#endif

    // 源码中题目目录
    std::string problem_dir = source_root + "/" + problem_num;

    // 构造文件路径（可执行文件统一放在 build/bin 下）
    std::string executable_path = bin_dir + "/" + problem_num;
    std::string input_path = problem_dir + "/input.txt";
    std::string expected_path = problem_dir + "/output.txt";
    std::string temp_input_path = bin_dir + "/temp_input.txt";
    std::string temp_output_path = bin_dir + "/temp_output.txt";

    // 检查文件存在
    if (!fs::exists(executable_path))
    {
        std::cerr << "❌ Problem " << problem_num << ": Executable not found at " << executable_path << std::endl;
        return 1;
    }

    if (!fs::exists(input_path))
    {
        std::cerr << "❌ Problem " << problem_num << ": input.txt not found" << std::endl;
        return 1;
    }

    if (!fs::exists(expected_path))
    {
        std::cerr << "❌ Problem " << problem_num << ": output.txt not found" << std::endl;
        return 1;
    }

    // 读取所有输入和期望输出
    std::ifstream input_file(input_path);
    std::ifstream expected_file(expected_path);

    std::stringstream input_buffer, expected_buffer;
    input_buffer << input_file.rdbuf();
    expected_buffer << expected_file.rdbuf();

    // 分割输入和期望输出
    std::vector<std::string> test_inputs = splitByDelimiter(input_buffer.str(), "---");
    std::vector<std::string> expected_outputs = splitByDelimiter(expected_buffer.str(), "---");

    if (test_inputs.size() != expected_outputs.size())
    {
        std::cerr << "❌ Problem " << problem_num << ": Number of test cases mismatch" << std::endl;
        return 1;
    }

    int passed = 0;
    int failed = 0;

    for (size_t i = 0; i < test_inputs.size(); i++)
    {
        // 将当前测试用例写到临时输入文件（放在 bin 目录）
        {
            std::ofstream temp_input(temp_input_path);
            temp_input << test_inputs[i] << std::endl;
        }

        // 运行可执行文件（从统一的 bin 目录中执行）
        std::string cmd = executable_path + " < " + temp_input_path + " > " + temp_output_path + " 2>&1";
        int result = system(cmd.c_str());

        if (result != 0)
        {
            std::cerr << "❌ Problem " << problem_num << " Test Case " << (i + 1) << ": Execution failed (exit code: " << result << ")" << std::endl;
            failed++;
            continue;
        }

        // 读取实际输出
        std::ifstream actual_file(temp_output_path);
        std::stringstream actual_buffer;
        actual_buffer << actual_file.rdbuf();
        actual_file.close();

        std::string actual_str = actual_buffer.str();

        // 移除尾部空白
        while (!actual_str.empty() && (actual_str.back() == '\n' || actual_str.back() == '\r' || actual_str.back() == ' ' || actual_str.back() == '\t'))
        {
            actual_str.pop_back();
        }

        std::string expected_str = expected_outputs[i];

        if (expected_str == actual_str)
        {
            std::cout << "✅ Problem " << problem_num << " Test Case " << (i + 1) << ": Accepted!" << std::endl;
            passed++;
        }
        else
        {
            std::cerr << "❌ Problem " << problem_num << " Test Case " << (i + 1) << ": Wrong Answer" << std::endl;
            std::cerr << "Expected: [" << expected_str << "]" << std::endl;
            std::cerr << "Got: [" << actual_str << "]" << std::endl;
            failed++;
        }
    }

    // 清理临时文件
    fs::remove(temp_input_path);
    fs::remove(temp_output_path);

    std::cout << "\n"
              << passed << "/" << test_inputs.size() << " test cases passed" << std::endl;

    return (failed == 0) ? 0 : 1;
}
