#include "master.h"

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

/*
希尔排序：插入排序的一种更高效的改进版本。希尔排序是非稳定排序算法。  
设定分组，组内进行插入排序，逐渐减少分组。 
时间复杂度，在最坏情况下：O(n^2)，平均时间复杂度：O(N logN logN,2为底)   
空间复杂度：O(1)  
不稳定  
*/

void shell_sort(int array[], int length)
{
    /*步长设定为gap ， 每次除以2，逐渐缩小分组*/
    for (int gap = length >> 1; gap > 0; gap >>= 1)
    {
        cout << "gap : " << gap << endl;

        /*分组，插入排序*/
        for (int i = gap; i < length; i++)
        {
            int temp = array[i];
            int j = 0;
            for (j = i - gap; j >= 0 && array[j] > temp; j -= gap)
            {
                array[j + gap] = array[j];
            }

            array[j + gap] = temp;
        }
    }

    printArray(array, length);
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
