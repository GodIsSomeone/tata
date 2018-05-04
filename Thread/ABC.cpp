#include<thread>  
#include<mutex>  
#include<condition_variable>  
using namespace std;
mutex m;
condition_variable cond;
int LOOP = 10;
int flag = 0;

void fun(int id) {
    for (int i = 0; i<LOOP; i++) {
        unique_lock<mutex> lk(m);
        while (id != flag)//一定要用循环判断，若是if多个阻塞线程唤醒后同时处于临界区  
            cond.wait(lk);
        cout << (char)('A' + id) << " ";
        flag = (flag + 1) % 3;
        cond.notify_all();
    }
}
int main() {
    thread B(fun, 1);
    thread C(fun, 2);
    fun(0);
    //cout << endl;
    B.join();
    C.join();
    return 0;
}
