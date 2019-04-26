#include "master.h"

/*
快速排序：找到一个标志位，使得左边的数据都小于这个标志数据，右边的数据都大于这个标志数据。  
然后对左边的数据，和右边的数据进行处理。
时间复杂度，在最坏情况下：O(n^2)，平均时间复杂度：O(NlogN,2为底)，平均复杂度，1.3NlogN  
空间复杂度，在最坏情况下：O(n)，平均时间复杂度：O(logN,2为底)  
不稳定  
*/

void QuickHelp(int arr[], int begin, int end)
{
    if (begin < end)
    {
        int flag = begin;
        int right = end;
        int x = arr[begin];

        /*找到标志位flag,使得左边的都小于x，右边的都大于x*/
        while (flag < right)
        {
            while (flag < right && arr[right] >= x)
                right--;

            /*把小于X的放在左边*/
            arr[flag] = arr[right];

            while (flag < right && arr[flag] < x)
                flag++;

            /*把大于X的放在右边*/
            arr[right] = arr[flag];
        }

        arr[flag] = x;
        QuickHelp(arr, begin, flag - 1);
        QuickHelp(arr, flag + 1, end);
    }
    return;
}

void QuickSort(int arr[], int size)
{
    checkParam(arr, size);
    QuickHelp(arr, 0, size - 1);
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
