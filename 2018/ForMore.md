# 一些零碎的知识点 
## new 和 malloc的区别
1.new需要调用构造函数，malloc只是申请一块内存。<br>
2.new不需要指定内存，malloc需要指定内存<br>
3.new出来的类型固定，malloc出来的是void*<br>
4.malloc出来的是在堆上内存，new出来的是自由存储区<br>
5.new内存分配失败时，会抛出bac_alloc异常。malloc分配内存失败时返回NULL。<br>
