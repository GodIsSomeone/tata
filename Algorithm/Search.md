```

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <xutility>
#include <string>
#include<algorithm>
#include <list>
#include <queue>
using namespace std;

class CSort
{
public:
    void printArray(int arr[], int length) {
        for (int i = 0; i < length; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    /*
    第i轮：
    倒叙比较，最后一个如果小，则冒泡交换，否则，下一个比较
    */
    void BubbleSort(int arr[], int length)
    {
        if (arr == NULL || length == 0) return ;

        for (int i = 0; i< length-1; i++)
        {
            for (int j= 0; j < length-1-i; j++)
            {
                if (arr[j] > arr[j+1])
                {
                    swap(arr[j], arr[j+1]);
                }
            }
        }
        printArray(arr, length);
    }

private:
};

class CSearch
{
public:
    /*递归方法*/
    int recursionHelper(int arr[], int value, int low, int high) 
    {
        /*当有多个相同的值的时候，得到的下标不一样*/
        /*插入查找法*/
        //int mid = low + (value - arr[low]) / (arr[high] - arr[low])*(high - low);
        if (low>high)
        {
            return -1;
        }
        /*一般查找法*/
        int mid = low + (high - low) / 2;

        if (arr[mid] == value)
            return mid;
        if (arr[mid] > value)
            return recursionHelper(arr, value, low, mid - 1);
        if (arr[mid] < value)
            return recursionHelper(arr, value, mid + 1, high);
    }
    int commonHelper(int arr[], int value, int low, int high) 
    {
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (arr[mid] == value)
            {
                return mid;
            }
            else if (arr[mid] < value)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        /*没有找到*/
        if (low > high)
        {
            return -1;
        }
    }
    /*有序数组*/
    int BinarySearch(int arr[], int length, int value)
    {
        if (arr == NULL || length == 0) return -1;
        int low = 0;
        int high = length - 1;
        int ret = commonHelper(arr, value, low, high);
        ret = ret > 0 ? ret+1 : -1;
        return ret;
    }

private:
};


int main() {
    int a[] = { 3, 5, 4, 0, 8, 6, 1, 8, 8};
    //{ 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
    int length = sizeof(a) / sizeof(a[0]);
    CSort().BubbleSort(a,length);
//     CSort().InsortSort(a,length);
//     CSort().HeapSort(a, length);
//     CSort().SelectSort(a, length);
//     CSort().QuickSort(a, length);
//     CSort().printArray(a, length);
    cout<< CSearch().BinarySearch(a, length, 8) << endl;
    return 0;
}



```
