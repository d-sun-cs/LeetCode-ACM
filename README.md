# LeetCode ACM Online Judge 测试框架

## 项目结构简化说明

### 核心文件
- **CMakeLists.txt** - CMake构建配置，自动发现所有题号目录
- **test.cpp** - 通用的测试程序，自动对比程序输出和预期输出
- **每个题号目录/**
  - `main.cpp` - 你的解答代码
  - `input.txt` - 测试输入
  - `output.txt` - 预期输出

## 使用方式

### 1. 在VS Code中运行测试（推荐）

在CMake的活动任务栏中，可以点击运行特定问题的测试目标：
- `test_23` - 运行问题23的测试
- `test_42` - 运行问题42的测试
- 任何新增的数字目录都会自动识别

### 2. 从命令行运行测试

```bash
cd build
cmake --build . --target test_23  # 测试问题23
cmake --build . --target test_42  # 测试问题42
```

## 工作流程

1. **创建新问题**
   ```bash
   mkdir 50
   cat > 50/main.cpp << 'EOF'
   #include <iostream>
   using namespace std;
   int main() {
       int a, b;
       cin >> a >> b;
       cout << a + b << endl;
       return 0;
   }
   EOF
   
   # 准备测试数据
   echo "1 2" > 50/input.txt
   echo "3" > 50/output.txt
   ```

2. **在VS Code中点击运行 `test_50`**
   
   CMake会自动：
   - 编译 `50/main.cpp`
   - 运行程序，将 `input.txt` 作为输入
   - 对比输出与 `output.txt`
   - 在输出窗口显示测试结果

3. **查看结果**
   - ✅ 表示通过
   - ❌ 表示失败（会显示预期输出和实际输出）

## 系统工作原理

```
CMakeLists.txt
├── 编译 test_runner (test.cpp)
├── 为每个题号目录编译 <题号> (main.cpp)
└── 为每个题号创建 test_<题号> 目标
    └── 运行: test_runner <题号>
        ├── 执行 <题号>/<题号> 程序，输入 input.txt
        ├── 捕获输出到 my_output.txt
        └── 对比 my_output.txt 和 output.txt
```

## 优势

✅ 无需运行脚本，点击即测  
✅ 自动编译和测试  
✅ 新增题目自动检测  
✅ 清晰的输出结果  
✅ 支持VS Code native集成
