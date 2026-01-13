#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

// 获取问题号：优先使用编译时定义，否则使用命令行参数
std::string getProblemNumber(int argc, char* argv[]) {
    #ifdef PROBLEM_NUMBER
    return PROBLEM_NUMBER;
    #else
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <problem_number>" << std::endl;
        exit(1);
    }
    return argv[1];
    #endif
}

int main(int argc, char* argv[]) {
    std::string problem_num = getProblemNumber(argc, argv);
    
    // 获取项目根目录
    #ifdef PROJECT_SOURCE_DIR
    std::string base_dir = PROJECT_SOURCE_DIR;
    #else
    std::string base_dir = ".";
    #endif
    
    std::string problem_dir = base_dir + "/" + problem_num;
    
    // 构造文件路径
    std::string executable_path = problem_dir + "/" + problem_num;
    std::string input_path = problem_dir + "/input.txt";
    std::string expected_path = problem_dir + "/output.txt";
    std::string output_path = problem_dir + "/my_output.txt";

    // 检查文件存在
    if (!fs::exists(executable_path)) {
        std::cerr << "❌ Problem " << problem_num << ": Executable not found at " << executable_path << std::endl;
        return 1;
    }

    if (!fs::exists(input_path)) {
        std::cerr << "❌ Problem " << problem_num << ": input.txt not found" << std::endl;
        return 1;
    }

    if (!fs::exists(expected_path)) {
        std::cerr << "❌ Problem " << problem_num << ": output.txt not found" << std::endl;
        return 1;
    }

    // 运行可执行文件，重定向输入和输出
    std::string cmd = executable_path + " < " + input_path + " > " + output_path + " 2>&1";
    int result = system(cmd.c_str());

    if (result != 0) {
        std::cerr << "❌ Problem " << problem_num << ": Execution failed (exit code: " << result << ")" << std::endl;
        return 1;
    }

    // 读取期望输出和实际输出
    std::ifstream expected_file(expected_path);
    std::ifstream actual_file(output_path);

    if (!expected_file || !actual_file) {
        std::cerr << "❌ Problem " << problem_num << ": Failed to open output files" << std::endl;
        return 1;
    }

    // 读取整个文件内容进行比较
    std::stringstream expected_content, actual_content;
    expected_content << expected_file.rdbuf();
    actual_content << actual_file.rdbuf();

    // 获取文件内容
    std::string expected_str = expected_content.str();
    std::string actual_str = actual_content.str();

    // 移除尾部空白和换行符
    auto trim_trailing = [](std::string& s) {
        while (!s.empty() && (s.back() == '\n' || s.back() == '\r' || s.back() == ' ' || s.back() == '\t')) {
            s.pop_back();
        }
    };

    trim_trailing(expected_str);
    trim_trailing(actual_str);

    bool output_matches = (expected_str == actual_str);

    if (output_matches) {
        std::cout << "✅ Problem " << problem_num << ": Accepted!" << std::endl;
        return 0;
    } else {
        std::cerr << "❌ Problem " << problem_num << ": Wrong Answer" << std::endl;
        std::cerr << "\n--- Expected Output ---" << std::endl;
        std::cerr << expected_str << std::endl;

        std::cerr << "\n--- Your Output ---" << std::endl;
        std::cerr << actual_str << std::endl;

        return 1;
    }
}
