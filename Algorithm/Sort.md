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

        for (int i = 0; i< length; i++)
        {
            for (int j= length-1; j>i; j--)
            {
                if (arr[j]<arr[j-1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j - 1];
                    arr[j - 1] = temp;
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
            int tar = arr[i];//保存当前变量

            int j = i - 1;
            if (arr[i] < arr[i-1])
            {
                for ( ; j>0; j--)
                {
                    arr[j + 1] = arr[j];
                }
                arr[j+1] = tar;
            }
        }
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

    void HeapSort(int arr[], int length) {

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

int main() {
    int a[] = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
    int length = sizeof(a) / sizeof(a[0]);
    CSort().BubbleSort(a,length);
    CSort().InsortSort(a,length);
    CSort().HeapSort(a, length);
    return 0;
}
```
