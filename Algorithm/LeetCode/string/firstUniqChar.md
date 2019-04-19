#### 第一个不重复的字母

用无序图来维护每一个字符及其个数
```
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map <char, int> umap;
        for (auto ch:s)
        {
            umap[ch]++;
            //cout << ch << " , " << umap[ch] << endl;
        }
        for (int i = 0; i<= s.length(); i++)
        {
            if (umap[s[i]] == 1)
            {
                return i;
            }
        }
        return -1;
    }
};
```
