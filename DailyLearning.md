

1.值得推荐的C/C++框架和库
https://www.ezlippi.com/blog/2014/12/c-open-project.html

2.C++并发教程
https://chenxiaowei.gitbooks.io/cpp_concurrency_in_action/content/


3.CPU工作模式及调频
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


4.linux 的日常

errno

文件相关操作，解压。压缩。打包。删除
pstack +进程号 查看相关依赖库

5.linux火焰图：http://www.cnblogs.com/happyliu/p/6142929.html

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



8.数据结构  https://hit-alibaba.github.io/interview/basic/algo/Tree.html



https://blog.csdn.net/ebowtang/article/details/50668895


