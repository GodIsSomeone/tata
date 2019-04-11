## 找到最小的K个数
1. 先排序，然后把数据插入进去

```
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> vRet;
        if(input.size()<1 || k > input.size()) return vRet;
        sort(input.begin(), input.end());
        for(int i=0;i<k;i++) vRet.push_back(input[i]);
        return  vRet;
    }
};
```
2. 利用快速排序的思想，快而不排，找到第N大的数，然后数组遍历一遍就可以了
```
static inline void checkParam(int arr[], int size)
{

    if (arr == nullptr || size == 0)
        return;
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "第" << i << "个: " << arr[i] << endl;
    }
    return;
}

int quickGet(int arr[], int begin, int end)
{
    int ret = 0;
    if(begin<end)
    {
        int flag = begin;
        int right = end;
        int cur = arr[begin];
        while (flag < right)
        {
            while(right > flag && arr[right] >= cur) 
                right--;
            if(right>flag)
            {
                arr[flag] = arr[right];
                flag++;
            } 
            while(flag < end && arr[flag] < cur) 
                flag++;
            if(right > flag)
            {
                arr[right] = arr[flag];
                right--;
            }
        }
        arr[flag] = cur;
        ret = flag;
    }
    return ret;
}

void maxK(int arr[], int size, int k)
{
    checkParam(arr, size);
    if (k == 0)
        return ;
    int arrK[k];
    int index = quickGet(arr, 0, size - 1);
    while(index!=k)
    {
        if(index<k)
            index = quickGet(arr,index+1,size-1);
        else
            index = quickGet(arr,0,index-1);
    }
    int j =0;
    for(int i=0;i<k;i++)
    {
        if(arr[i]<arr[index])
        {
            arrK[j] = arr[i];
            j++;
        }
    }

    printArray(arrK, k);
    return ;
}
```

3. 冒泡法也可以这么改编，只需要遍历k次就行了，找出前k个小的数
```
void maxKbyBubble(int arr[], int size, int k)
{
    int arrK[k];
    for(int i=0;i<k;i++)
    {
        for(int j=0;j<size-1-i; j++)
        {
            if(arr[j]<arr[j+1])
            {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
        arrK[i] = arr[size-1-i];
    }

    printArray(arrK, k);
    return;
}
```