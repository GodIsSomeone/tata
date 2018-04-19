CORE文件的GDB调试过程。

1.首先检查程序运行环境，检查环境变量是否正确。cat /proc/进程号/environ
2.调试core文件：gdb -c 可执行程序  core
3.bt full，查看具体的堆栈信息。
4.info register 获取所有register的值
5.layout asm 显示汇编代码
6.p打印，n下一步，s步入，c继续。
还有很多，需要不断总结。
