#include "master.h"

/*
冒泡排序的主要思想是一趟比较，相邻元素之间进行对比，遍历一遍，可以将一个最值元素沉底。
时间复杂度为O(n^2)，最好最坏都是如此
空间复杂度为O(1)
比较稳定
*/

void BubbleSort(int arr[], int size)
{
    checkParam(arr, size);
    for (int i = 0; i < size; i++)
    {
        /*相邻元素进行比较，每次都找一个最值，放到队尾*/
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] < arr[j + 1])
                swapElement(arr[j], arr[j + 1]);
        }
    }
    printArray(arr, size);
}


int main()
{
    int arr[10] = {23, 12, 31, 45, 32, 1, 4, 13, 45, 90};
    //BubbleSort(arr,10);
    //QuickSort(arr,10);
    //heap_sort(arr,10);
    //shell_sort(arr,10);
    //SelectSort(arr,10);
    //InsertSort(arr,10);
    merge_sort(arr, 10);
    system("pause");
    return 0;
}
