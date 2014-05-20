NAME:
	CacheSim
FUNCTION:
	Simulate the functions of Cache
VERAION:
	0.13
AUTHOR:
	jiangxin
Copyright (c) 2014, jiangxin


All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of the jiangxin nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Log:
	Version 0.01-0.11:
		完成基本结构，能够实现直接映射，回写方法的Cache模拟。
	Version 0.12:
		优化了程序结构，将所有的全局数据变量、结构的定义声明等全部放到了base.cpp/base.h中；将所有的函数的定义和声明放到了functions.cpp/functions.h中。
	Version 0.13:
		大幅度优化了程序，改善了程序结构，修复了大量隐含bug，并将一直可能隐含bug，但还没有时间解决的部分全部做了标记；改善了提示信息，便于调试。
	Version 0.14:
		能够正确实现全相联，随机替换策略、回写法。
	Version 0.15:
		大幅度优化了程序，改善了程序结构。特别是其中关于条件编译的部分。