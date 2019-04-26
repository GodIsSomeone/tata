#include "master.h"

/*
归并排序：采用分治法。先分，再合，合的过程中进行比较。  
归并排序是稳定排序，它也是一种十分高效的排序，能利用完全二叉树特性的排序一般性能都不会太差  
归并排序的最好，最坏，平均时间复杂度均为O(nlogn)  
空间复杂度为O(N)  
稳定  
*/
void merge_sort_recursive(int *arr, int *reg, int start, int end)
{
    if (start >= end)
    {
        return;
    }

    int len = end - start, mid = (len >> 1) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    /*左边递归*/
    merge_sort_recursive(arr, reg, start1, end1);
    /*右边递归*/
    merge_sort_recursive(arr, reg, start2, end2);

    /*合并*/
    int k = start;
    while (start1 <= end1 && start2 <= end2)
    {
        reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    }

    while (start1 <= end1)
    {
        reg[k++] = arr[start1++];
    }

    while (start2 <= end2)
    {
        reg[k++] = arr[start2++];
    }

    /*赋值操作*/
    for (k = start; k <= end; k++)
    {
        arr[k] = reg[k];
    }
}

void merge_sort(int *arr, const int length)
{
    /*避免在递归中，频繁开辟空间*/
    int *reg = new int[length];
    merge_sort_recursive(arr, reg, 0, length - 1);

    printArray(arr, length);
    delete[] reg;
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
