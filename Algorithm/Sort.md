##各种排序算法
```

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
    /*归并排序*/
    void merge_sort_recursive(int* arr, int* reg, int start, int end) 
    {
        if (start >= end)
        {
            return;
        }

        int len = end - start, mid = (len >> 1) + start;
        int start1 = start, end1 = mid;
        int start2 = mid + 1, end2 = end;

        merge_sort_recursive(arr, reg, start1, end1);
        merge_sort_recursive(arr, reg, start2, end2);

        int k = start;
        while (start1<=end1 && start2 <=end2)
        {
            reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
        }

        while (start1<=end1)
        {
            reg[k++] = arr[start1++];
        }

        while (start2 <= end2)
        {
            reg[k++] = arr[start2++];
        }
        for (k=start;k<=end;k++)
        {
            arr[k] = reg[k];
        }
    }

    void merge_sort(int* arr, const int len) 
    {
        int *reg = new int[len];
        merge_sort_recursive(arr, reg, 0, len - 1);
        delete[] reg;
    }


private:
};


int main() {
    int a[] = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
    int length = sizeof(a) / sizeof(a[0]);
    CSort().BubbleSort(a,length);
    CSort().InsortSort(a,length);
    CSort().HeapSort(a, length);
    CSort().SelectSort(a, length);
    CSort().QuickSort(a, length);
    return 0;
}


```
