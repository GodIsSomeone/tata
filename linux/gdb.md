### CORE文件的GDB调试过程。

1. 首先检查程序运行环境，检查环境变量是否正确。cat /proc/进程号/environ  
2. 调试core文件：gdb -c 可执行程序  core  
3. bt full，查看具体的堆栈信息。  
4. info register 获取所有register的值  
5. layout asm 显示汇编代码  
6. p打印，n下一步，s步入，c继续。  
7. layout显示代码。  


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

### gdb 程序运行中的调试

1. gdb -P pid(线程ID)  

2. info thread  

3. thread + 线程号  

4. 其他和一般的GDB程序是一样的。  


http://172.16.72.143/w/pthread.html
