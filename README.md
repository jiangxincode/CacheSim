# Cache模拟器(CacheSim)

[![Build and Release](https://github.com/jiangxincode/CacheSim/actions/workflows/BuildAndRelease.yml/badge.svg)](https://github.com/jiangxincode/CacheSim/actions/workflows/BuildAndRelease.yml)

该程序是大学时《计算机组成与系统结构》的编程实验，我早已毕业多年，但是依然收到很多人的邮件咨询，所以简单描述一下。

该程序模拟了Cache的工作原理并通过读取trace文件得到相应的命中率，能够实现直接映射、全相联、组相联三种映射方式，其中全相联和组相联能够实现随机、LRU两种替换策略。目前三种映射方式均采用回写法，但已经定义了其它写策略的接口，可以很容易扩充。程序具有比较强的鲁棒性，能够接受一定范围的错误输入，并能够比较清晰的提示用户输入。

我尽量缩减了不必要的代码，控制在1000行以内。因为纯粹是为了模拟Cache的工作原理，所以没有过多考虑性能，比如读取30万行的内存地址数据，如果采取全相联的话，需要耗费的时间还是很长的。大家可以帮忙优化下。

程序使用标准C++编写，没有使用三方依赖库，支持Windows/Linux/MacOS。程序中使用了一些C++11标准中的类，比如`bitset<T>`，所以必须在支持C++11的编译器上进行编译，但现在主流的编译器比如GCC和VS均已支持。本程序编码方式是UTF-8。

如果你只是想查看最后的数据结果，不关心每条数据的具体命中情况请保留base.h中的`#define NDEBUG // For NDEBUG pattern`，否则，程序需要很长的运行时间。

关于该程序的更多背景和说明请参考`Materials`文件夹，测试数据请参考`TestData`文件夹。

如果你对于程序中的内容有所疑问，比如无法在你的机器上正常编译或运行，可以直接在Github上提交issue，并附上你的编译环境和报错日志。

如果你觉得该程序不满足你的要求，你可以看下另一个程序：<http://pages.cs.wisc.edu/~markhill/DineroIV/>

This program is a programming experiment for my university course "Computer Organization and System Architecture." Although I graduated many years ago, I still receive numerous emails from people seeking information about it. So, let me provide a brief description.

This program simulates the operation of a cache and calculates the corresponding hit rate by reading a trace file. It can implement three mapping methods: direct-mapped, fully associative, and set associative. Among these, the fully associative and set associative mappings support two replacement strategies: random and LRU. Currently, all three mapping methods use a write-back policy, but I have defined interfaces for other write policies for easy expansion. The program is robust and can handle a certain range of input errors, providing clear prompts for users.

I have tried to keep unnecessary code to a minimum, limiting it to under 1000 lines. Since the primary purpose is to simulate cache operation, I didn't focus much on performance. For example, reading 300,000 lines of memory addresses will take a long time when using a fully associative mapping. Any optimization assistance is welcome.

The program is written in standard C++ without third-party dependencies and supports Windows, Linux, and MacOS. It uses some classes from the C++11 standard, like `bitset<T>`, so it must be compiled on a C++11-supporting compiler, which most major compilers like GCC and VS already do. The program's encoding is in UTF-8.

If you only want to view the final data results and don't care about the specific hit details, please keep the `#define NDEBUG // For NDEBUG pattern` in the base.h file; otherwise, the program will take a long time to run.

For more background and explanations about this program, please refer to the `Materials` folder, and for test data, consult the `TestData` folder.

If you have any questions about the program, such as compilation or runtime issues on your machine, you can submit an issue on GitHub with your compilation environment and error logs.

If you feel that this program doesn't meet your requirements, you can check out another program at <http://pages.cs.wisc.edu/~markhill/DineroIV/>.

## How to build

* `cmake -B build`
* `cmake --build build`

## How to get TRACE file

* cse240a Project 1: Cache Simulator: <http://cseweb.ucsd.edu/classes/fa07/cse240a/project1.html>
* Intel Pin基础: <https://www.cnblogs.com/long123king/p/3635408.html>
* pin下载: <http://software.intel.com/en-us/articles/pintool-downloads>

## License

+ The MIT License (MIT) <http://mit-license.org/>

## 版本改动

* Version 0.01-0.11:完成基本结构，能够实现直接映射，回写方法的Cache模拟。
* Version 0.12:优化了程序结构，将所有的全局数据变量、结构的定义声明等全部放到了base.cpp/base.h中；将所有的函数的定义和声明放到了functions.cpp/functions.h中。
* Version 0.13:大幅度优化了程序，改善了程序结构，修复了大量隐含bug，并将一直可能隐含bug，但还没有时间解决的部分全部做了标记；改善了提示信息，便于调试。
* Version 0.14:※能够正确实现全相联，随机替换策略、回写法。
* Version 0.15:大幅度优化了程序，改善了程序结构。特别是其中关于条件编译的部分。
* Version 0.16:更改了部分变量的命名，使其更加容易阅读。删除了部分无用文件。
* Version 0.17:※能够正确实现组相联，随机替换策略、回写法
* Version 0.18:优化了程序，加快了运行速度
* Version 0.19:实现了LRU的基本框架，但是发现了严重bug，可能会产生回退。
* Version 0.20:消除了Version 0.19中的严重bug，消除了部分冗余代码。
* Version 0.21:编码全部设置为UTF-8
* Version 0.22:删除了不必要信息，比如作者信息，退出信息;重新format代码;删除不必要的using namespace std;
* Version 0.23:merge部分文件
* Version 0.30:optimization

