#### 最后一个单词的长度
碰到空格，length归零。  
这种题做起来简直恶心死人了！~！！！！！！  
```
class Solution {
public:
    int lengthOfLastWord(string s) {
        const char* ch = s.c_str();
        int len = 0;
        while (*ch) {
            if (*ch++ != ' ')
                ++len;
            else if (*ch && *ch != ' ')
                len = 0;

        }
        return len;
    }
};
```
