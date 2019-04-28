#include "master.h"

/*
堆排序：大顶堆（升序，小到大），小顶堆（降序，大到小）。  
大顶堆：arr[i] >= arr[2i+1] && arr[i] >= arr[2i+2]  
小顶堆：arr[i] <= arr[2i+1] && arr[i] <= arr[2i+2]  
然后对左边的数据，和右边的数据进行处理。
时间复杂度：平均 O(NlogN,2为底)  
空间复杂度：O(1)  
不稳定  
*/

void create_heap(int array[], int begin, int end)
{
    int son = begin * 2 + 1;
    int dad = begin;
    while (son <= end)
    {
        if (son + 1 <= end && array[son] < array[son + 1])
        {
            son++;
        }

        if (array[dad] > array[son])
            return;
        else
        {
            std::swap(array[dad], array[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}
void heap_sort(int array[], int length)
{
    //参数判断
    //1.构建大顶堆
    for (int i = length / 2 - 1; i >= 0; i--)
    {
        //从最后一个非叶子结点从下至上，从右至左调整结构
        create_heap(array, i, length - 1);
    }

    //2.调整堆结构+交换堆顶元素与末尾元素
    for (int i = length - 1; i > 0; i--)
    {
        std::swap(array[0], array[i]); //将堆顶元素与末尾元素进行交换
        create_heap(array, 0, i - 1);  //重新对堆进行调整
    }

    printArray(array, length);
}

int main()
{
    int arr[10] = {23, 12, 31, 45, 32, 1, 4, 13, 45, 90};
    //BubbleSort(arr,10);
    //QuickSort(arr,10);
    heap_sort(arr,10);
    //shell_sort(arr,10);
    //SelectSort(arr,10);
    //InsertSort(arr,10);
    //merge_sort(arr, 10);
    system("pause");
    return 0;
}
