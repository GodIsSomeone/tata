CORE文件的GDB调试过程。

1.首先检查程序运行环境，检查环境变量是否正确。cat /proc/进程号/environ
2.调试core文件：gdb -c 可执行程序  core
3.bt full，查看具体的堆栈信息。
4.info register 获取所有register的值
5.layout asm 显示汇编代码
6.p打印，n下一步，s步入，c继续。
7.layout显示代码。 
        layout：用于分割窗口，可以一边查看代码，一边测试。主要有以下几种用法：
        layout src：显示源代码窗口
        layout asm：显示汇编窗口
        layout regs：显示源代码/汇编和寄存器窗口
        layout split：显示源代码和汇编窗口
        layout next：显示下一个layout
        layout prev：显示上一个layout
        Ctrl + L：刷新窗口
        Ctrl + x，再按1：单窗口模式，显示一个窗口
        Ctrl + x，再按2：双窗口模式，显示两个窗口
        Ctrl + x，再按a：回到传统模式，即退出layout，回到执行layout之前的调试窗口。

还有很多，需要不断总结。


编译过程中gcc 的选项，显示所有的warning  ： -Wall -Wextra -Wconversion

-Wall：显示所有的
-Wextra:显示某些特殊的，比如
        if(i);/*此处的分号*/
             return 1;
-Wconversion：显示一些转换的warning 

-Wall选项意思是编译后显示所有警告。

-W选项类似-Wall，会显示警告，但是只显示编译器认为会出现错误的警告。

在编译一些项目的时候可以-W和-Wall选项一起使用。
之前看了一篇国外程序员写的博客，说编译时不使用-W -Wall选项的是stupid的，所以编译时还是尽量带上吧。




gdb 程序运行中的调试
1.gdb -P pid(线程ID)

2.info thread

3.thread + 线程号

4.其他和一般的GDB程序是一样的。