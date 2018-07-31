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

    void InsortSort(int arr[], int length)
    {
        if (arr == NULL || length == 0) return;
        for (int i = 1; i < length; i++)
        {
            int cur = arr[i];
            int j = i - 1;
            for (; j >= 0 && cur < arr[j]; j--)
            {
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = cur;
        }
        printArray(arr, length);
    }

    void SelectSort(int arr[], int length)
    {
        if (arr == NULL || length == 0) return;
        for (int i = 0; i < length; i++)
        {
            int min = i;
            for (int j =i+1;j<length;j++)
            {
                if (arr[min] > arr[j])
                {
                    min = j;//寻找最小值的下标
                }
            }
            swap(arr[min], arr[i]);
        }
        printArray(arr, length);
    }

    /*快速排序*/
    void QuickHelp(int arr[], int begin, int end)
    {
        if (begin < end)
        {
            int left = begin, right = end, x = arr[begin];
            while (left < right)
            {
                while (left < right && arr[right] >= x) // 从右向左找第一个小于x的数  
                {
                    right--;
                }
                if (left < right)
                {
                    arr[left] = arr[right];
                    left++;
                }
                while (left < right && arr[left] < x) // 从左向右找第一个大于等于x的数  
                {
                    left++;
                }
                if (left < right)
                {
                    arr[right] = arr[left];
                    right--;
                }
            }
            arr[left] = x;
            QuickHelp(arr, begin, left - 1); // 递归调用  
            QuickHelp(arr, left + 1, end);
        }
    }

    void QuickSort(int arr[], int length)
    {
        if (arr == NULL || length == 0) return;
        /*创建大堆，并交换根节点的位置*/
        QuickHelp(arr, 0, length-1);
        printArray(arr, length);
    }

    void MaxHeap(int arr[], int start, int end) {
        int leaf = start*2+1;
        while (leaf <= end)
        {
            /*找出最大的叶子节点*/
            if (leaf + 1 <= end && arr[leaf] < arr[leaf + 1]) //变成>号，则为倒序排列
            {
                leaf++;
            }
            /*如果根节点比子节点都大，则直接return*/
            if (arr[start] >arr[leaf]) //变成<号，则为倒序排列
            {
                return;
            }
            else
            {
                swap(arr[start], arr[leaf]);
                start = leaf;
                leaf = start * 2 + 1;
            }
        }
    }

    void HeapSort(int arr[], int length) 
    {

        if (arr == NULL || length == 0) return;
        /*创建大堆，并交换根节点的位置*/
        for (int i = length / 2 - 1; i >= 0; i--)
        {
            MaxHeap(arr, i, length - 1);
        }
        for (int i = length - 1; i > 0; i--)
        {
            swap(arr[0], arr[i]);
            MaxHeap(arr, 0, i - 1);
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
