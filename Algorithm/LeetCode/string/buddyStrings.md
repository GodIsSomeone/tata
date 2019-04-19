#### 仅交换两个字母。使得A==B

```
class Solution {
public:
    bool buddyStrings(string A, string B) {

        //参数判断，长度是否相等
        if (A.size() != B.size()) return false;

        //使用无序set保存A，如果长度相等且A==B,则相等
        unordered_set<char> uSet(A.begin(), A.end());
        int ASetLen = uSet.size();
        if (A == B && ASetLen < B.size()) return true;

        vector<int> pos; //维护不相等的字符位置
        for (int i=0; i<A.size(); i++)
        {
            if (A.at(i) != B.at(i)) pos.push_back(i);
            if (pos.size() > 2) return false;
        }

        if (pos.size() != 2) return false;

        return A.at(pos[0]) == B.at(pos[1]) && A.at(pos[1]) == B.at(pos[0]);
    }
};
```
