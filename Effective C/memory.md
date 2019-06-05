### C++里可能出现的内存问题大致有这么几个方面  

1. 缓冲区溢出（buffer overrun）.  

    使用vector<char>/string来管理缓冲区，自动记住用缓冲区的长度，并通过成员函数，而不是裸指针来修改缓冲区。  

2. 空悬指针，野指针。  

    用shared_ptr/weak_ptr

3. 重复释放（delete两次）。  

    用scoped_ptr，只在对象析构的时候释放一次。  

4. 内存泄漏（memory leak）。  

    用scoped_ptr，对象析构的时候自动释放。  

5. 不配对的new delete。  

    尽量避免自己new，使用vector。  

6. 内存碎片（memory fragmentation）。