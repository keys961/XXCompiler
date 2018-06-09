# README

## XXCompiler - Project of Compiler Principle

[![Build Status](https://travis-ci.com/keys961/XXCompiler.svg?token=An2HsiQKwhJSHUQB4Xqh&branch=master)](https://travis-ci.com/keys961/XXCompiler)

BY
- @keys961(Front-End) 
- @KRCheung(Middle-End)
- @437367125(Back-End)

### 声明

- 源码实现了类PASCAL语言的编译器
- 生成的目标代码（中间代码）参考了MIPS汇编，并实现了栈结构（函数调用）
- 程序不能保证所有情况都运行正确，但是**可以保证我们提供的test cases都能生成正确的结果**

### 编译并生成可执行程序

- 首先需要保证你的电脑中有：
  - `cmake`：3.5以上版本
  - `gcc & g++`：5以上版本（5以下版本不能通过编译），推荐5.4以上版本
- 步骤
  1. 在源码根目录，键入命令`cmake .`
  2. 然后键入命令`make`，该目录下就会生成可执行文件（Windows和*nix系统均可）

### 如何使用程序

以*nix系统为例，格式如下

```bash
./Compiler src_file [-options] dst_file
```

其中

- `src_file`：代码源文件

- `dst_file`：目标代码文件，程序会自动加上后缀`.asm`

- `[-options]`：可选选项，如下所示，选项顺序没有要求

  - `-l`：打印词法分析结果到标准输出流
  - `-g`：打印语法分析结果到标准输出流
  - `-a`：打印抽象语法树到标准输出流
  - `-s`：打印符号表到标准输出流
  - `-c`：打印类型检查详细结果到标准输出流

  例如，我们要打印词法分析结果，语法分析结果和抽象语法树到控制台，可以这么做：

  `./Compiler test1.p -lga  test_out`

  程序会打印词法分析结果，语法分析结果和抽象语法树到控制台，并生成目标代码文件`test_out.asm`
