# CacheSim

jiangxinnju@163.com

http://github.com/jiangxincode

## 版本改动

### Version 0.01-0.11:

* 完成基本结构，能够实现直接映射，回写方法的Cache模拟。

### Version 0.12:

* 优化了程序结构，将所有的全局数据变量、结构的定义声明等全部放到了base.cpp/base.h中；将所有的函数的定义和声明放到了functions.cpp/functions.h中。

### Version 0.13:

* 大幅度优化了程序，改善了程序结构，修复了大量隐含bug，并将一直可能隐含bug，但还没有时间解决的部分全部做了标记；改善了提示信息，便于调试。

### Version 0.14:※

* 能够正确实现全相联，随机替换策略、回写法。

### Version 0.15:

* 大幅度优化了程序，改善了程序结构。特别是其中关于条件编译的部分。

### Version 0.16:

* 更改了部分变量的命名，使其更加容易阅读。删除了部分无用文件。

### Version 0.17:※

* 能够正确实现组相联，随机替换策略、回写法

### Version 0.18

* 优化了程序，加快了运行速度

### Version 0.19

* 实现了LRU的基本框架，但是发现了严重bug，肯能会产生回退。

### Version 0.20

* 消除了Version 0.19中的严重bug，消除了部分冗余代码。

### Version 0.21

* 编码全部设置为UTF-8