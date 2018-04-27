// CTread.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
#include <condition_variable>       // std::condition_variable

using namespace std;

mutex g_mutex;
bool g_Flag = false;
condition_variable cv;

void print_fun(int i) 
{
    unique_lock <mutex> lock(g_mutex);
    while (!g_Flag) { cv.wait(lock); }

    cout << "Thread" << i << endl;
}

void startThread() 
{
    unique_lock <mutex> lock(g_mutex);
    g_Flag = true;
    cv.notify_all();
}

int main()
{
    thread threads[10];
    for (int i = 0; i < 10; i++) 
    {
        threads[i] = thread(print_fun, i);
    }
    
    cout << "10 Theads ready" << endl;
    startThread();
    for (auto& th:threads)
    {
        th.join();
    }

    return 0;
}
