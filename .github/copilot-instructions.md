# LeetCode ACM Testing Framework

## Project Architecture

This is a **CMake-based LeetCode solution framework** with automated testing. Each problem lives in a numbered directory (`4/`, `23/`, `42/`, etc.) containing:
- `main.cpp` - Solution with `main()` that reads stdin and writes stdout
- `input.txt` - Test inputs separated by `---` delimiters (no leading `---`, ends with `---`)
- `output.txt` - Expected outputs, same delimiter format

The build system automatically discovers all problem directories and generates executables + test targets.

## 🤖 AUTOMATIC WORKFLOW: Adding New Problems from LeetCode Images

**When user provides a LeetCode problem screenshot:**

1. **Automatically identify the problem number** from the top-left corner of the image (e.g., "84. 柱状图中最大的矩形" → problem number is `84`)

2. **Create directory structure automatically:**
   ```bash
   mkdir <problem_number>
   touch <problem_number>/main.cpp
   touch <problem_number>/input.txt
   touch <problem_number>/output.txt
   ```

3. **Generate test files (input.txt/output.txt) based on the problem description in the image:**
   
   **Test generation rules:**
   - 用空格与换行组织数据，**不用** `[` 和 `,` 之类的符号分隔
   - 对于数组输入要单独给出一行长度数值，其他信息也要合理组织
   - 每组数据先给出数据内容，再用短横线 `---` 隔开
   - **文件开头没有** `---`，但**结尾必须有** `---`
   - **必须包含原题的所有示例数据**
   - **额外添加至少8-10组扩展测试数据**，覆盖边界情况和典型场景：
     - 边界值（如空数组、单元素、最小/最大值）
     - 特殊模式（递增、递减、全相同）
     - 中等规模的普通测试用例

4. **Make `main.cpp` a basic template:** 

  ```cpp
  #include<iostream>

  using namespace std;
  
  int main() {
    return 0;
  }
  ```

  - If the problem description includes a special test-case format (like operation sequences for Problem 295), include a concise C-style comment block (`/* ... */`) immediately above the `main` function that documents the exact input/output format. Do not include any guidance about implementing the solution — only describe the IO layout and example input/output.

5. **Run CMake to register the new problem:** `cd build && cmake ..`

6. **Report completion** with links to the created files

## Build System (CMake)

**Key CMake features:**
- Auto-discovers all `[0-9]*` directories with `main.cpp`
- Compiles each problem to `build/bin/<problem_number>`
- Generates test executables `test_<problem_number>` that:
  - Run the solution with each test case from `input.txt`
  - Compare actual output with `output.txt`
  - Report ✅/❌ with diff on failure

**Compilation standards:** C++23 with standard library features like `std::format`.

## Developer Workflows

### Adding a New Problem
```bash
mkdir <problem_number>
cd <problem_number>
# Create main.cpp with your solution
# Create input.txt and output.txt with test cases
cd ../build && cmake ..
```

### Building & Testing
From VS Code, use CMake targets:
- Build: Select `test_<number>` target and build
- Run: Execute `test_<number>` to run all test cases for that problem

From terminal:
```bash
cd build
cmake --build . --target test_<number> && ./bin/test_<number>
```

### Test Data Format
Each file uses `---` as test case separator:
```
<test_case_1_data>
---
<test_case_2_data>
---
```

**Important:** No `---` before first case, but required after last case.

## Code Conventions

### Input/Output Pattern
Solutions use **ACM-style I/O** (not LeetCode function signatures):
1. Read problem size/dimensions first (e.g., array length, number of lists)
2. Read data structures element-by-element using `cin`
3. Output results directly to `cout` (match expected format exactly)

**Example:** [4/main.cpp](4/main.cpp) reads two array sizes then elements:
```cpp
int m, n;
cin >> m;
vector<int> nums1(m);
for (int i = 0; i < m; i++) cin >> nums1[i];
```

### Data Structure Patterns
- **Arrays:** Input size on first line, elements space-separated on subsequent lines
- **Linked Lists:** [23/main.cpp](23/main.cpp) - Read list count, then for each list: length + values
- **Output format:** Space-separated values or formatted decimals (e.g., `format("{:.5f}", result)`)

### Common Includes
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>  // INT_MIN, INT_MAX
#include <format>   // C++23 formatting
using namespace std;
```

## Test Runner Implementation

[test.cpp](test.cpp) is a generic test harness compiled per-problem with:
- `PROBLEM_NUMBER`, `PROJECT_SOURCE_DIR`, `BIN_DIR` defined via CMake
- Splits test files by `---` delimiter
- Executes problem binary with piped input/output
- String-matches trimmed outputs

**Note:** The test runner uses filesystem operations and expects all binaries in `build/bin/`.

## Quick Shortcut: send an image + a single dot

When the user sends a LeetCode problem screenshot followed by a single `.` (dot) message, the agent MUST perform the following steps automatically and silently (no problem-solving hints or explanations):

- Detect the problem number from the top-left corner of the image (e.g. "84. ..." → `84`).
- Create the problem directory and three files if they do not exist:
  ```bash
  mkdir -p <problem_number>
  touch <problem_number>/main.cpp
  touch <problem_number>/input.txt
  touch <problem_number>/output.txt
  ```
- Populate `main.cpp` with the minimal template exactly as below (do NOT add solution logic):
  ```cpp
  #include <iostream>
  using namespace std;

  int main() {
      return 0;
  }
  ```
  - If a problem has special-case test instructions, add a brief `/* ... */` comment block immediately above `main` describing the input/output layout and any operation codes. Keep it concise and factual (no implementation hints).
- Generate `input.txt` and `output.txt` using the Test generation rules in this document:
  - Keep LeetCode example data
  - Add 4–6 extra cases covering edge cases (empty, single element, increasing, decreasing, identical elements, moderate random)
  - Use the `---` delimiter format (no leading `---`, end with `---`)
  - For arrays, put length on its own line followed by elements on the next line
- Run `cd build && cmake ..` to register the new problem in the build system.

DO NOT provide any hints about solving the problem, algorithms, or implementation suggestions in the response. The agent's reply after creating files should be minimal and may only confirm file creation or list created file paths if a confirmation is required by the environment. The intent: the user will implement the solution themselves.
