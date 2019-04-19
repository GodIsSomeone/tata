#### 查找统一结构的字符串，比如abb类型的

```
class Solution {
public:
    /*从a开始，统一字符标准*/
    string toPattern(string word) {
        map<char, char> M;
        int curr = 97;
        for (char& c : word)
        {
            if (M.count(c) == 0)
            {
                M[c] = (char)curr++;
            }
        }
        for (int i = 0; i < word.length(); i++) 
        {
            word[i] = M[word[i]];
        }

        return word;
    }

    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        string p = toPattern(pattern);
        vector<string> res;
        for (string& w : words) if (toPattern(w).compare(p) == 0) res.push_back(w);
        return res;
    }
    
};
```
