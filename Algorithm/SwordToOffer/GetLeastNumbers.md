找到最小的K个数
先排序，然后把数据插入进去

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
