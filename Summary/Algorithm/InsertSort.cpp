#include "master.h"

/*
插入排序，与冒泡和选择相比，插入排序不交换值，只是选择合适的位置。  
维护前面的顺序数组  
时间复杂度为O(n^2)，最好最坏都是如此  
空间复杂度为O(1)  
链表稳定  
*/

void InsertSort(int arr[], int size)
{
    checkParam(arr, size);

    for (int i = 1; i < size; i++)
    {
        int cur = arr[i];
        int j = i - 1;

        /*维护已经排好序的数组*/
        while (j >= 0 && arr[j] > cur)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = cur;
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
