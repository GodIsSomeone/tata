#include "master.h"

/*
选择排序：与冒泡排序对比，交换次数很少，走一趟只需要一次交换  
因为选择排序走一趟的目的是为了找到一个最值，然后进行交换。  
时间复杂度为O(n^2)，最好最坏都是如此  
空间复杂度为O(1)  
数组不稳定（涉及插入），链表稳定  
*/

void SelectSort(int arr[], int size)
{
    checkParam(arr, size);

    for (int i = 0; i < size; i++)
    {
        /*找到最值的下标*/
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        /*最后才交换位置*/
        swapElement(arr[min], arr[i]);
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
