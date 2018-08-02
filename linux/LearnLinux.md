1. du  du命令也是查看使用空间的，但是与df命令不同的是Linux du命令是对文件和目录磁盘使用的空间的查看，还是和df命令有一些区别的。

   df -h.df命令用于显示磁盘分区上的可使用的磁盘空间。默认显示单位为KB。可以利用该命令来获取硬盘被占用了多少空间，目前还剩下多少空间等


   scp   scp -r -P 22223 root@43.224.34.73:/home/lk /root    -r  递归复制整个目录。


   history history命令用于显示指定数目的指令命令，读取历史命令文件中的目录到历史命令缓冲区和将历史命令缓冲区中的目录写入命令文件。


2.CPU工作模式及调频
http://www.simlinux.com/2017/03/24/cpu-model-freq.html CPU工作模式及调频

ondemand	按需快速动态调整CPU频率， 一有cpu计算量的任务，就会立即达到最大频率运行，等执行完毕就立即回到最低频率（阙值为 95%
performance	运行于最大频率
conservative	按需快速动态调整CPU频率， 一有cpu计算量的任务，就会立即达到最大频率运行，等执行完毕就立即回到最低频率（阙值为 75%）
powersave	运行于最小频率
userspace	运行于用户指定的频率

查看CPU当前的工作模式
cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
查看支持的CPU工作模式
cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors
调整最高性能模式
echo 'performance' |tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor


3.linux 的日常

errno

文件相关操作，解压。压缩。打包。删除
pstack +进程号 查看相关依赖库

45.linux火焰图：http://www.cnblogs.com/happyliu/p/6142929.html

   Flame Graph项目位于GitHub上：https://github.com/brendangregg/FlameGraph
   可以用git将其clone下来：git clone https://github.com/brendangregg/FlameGraph.git

 

我们以perf为例，看一下flamegraph的使用方法：

5.1 perf record -e cpu-clock -g -p 28591
   Ctrl+c结束执行程序后，在当前目录下会生成采样数据perf.data.

5.2 用perf script工具对perf.data进行解析：perf script -i perf.data &> perf.unfold

5.3 将perf.unfold中的符号进行折叠：./stackcollapse-perf.pl perf.unfold &> perf.folded

5.4 最后生成svg图： ./flamegraph.pl perf.folded > perf.svg


6.tcpdump 抓包 ：https://www.cnblogs.com/chyingp/p/linux-command-tcpdump.html


7.gdb调试  https://legacy.gitbook.com/book/wizardforcel/100-gdb-tips/details


8.时间调整： ntpdate -u 210.72.145.44 :网络时间同步命令  date -s "2015-02-04 16:30:00"

