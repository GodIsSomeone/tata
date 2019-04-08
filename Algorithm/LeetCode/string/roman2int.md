罗马数字转阿拉伯数字
```
class Solution {
public:
    int romanToInt(string s) {
        int nRet = 0;
        int last = 0;
        map<char, int> roman;
        roman['I'] = 1;
        roman['V'] = 5;
        roman['X'] = 10;
        roman['L'] = 50;
        roman['C'] = 100;
        roman['D'] = 500;
        roman['M'] = 1000;

        for (auto iter = s.rbegin(); iter != s.rend(); iter++)
        {

            if (roman[*iter] < last)
            {
                nRet -= roman[*iter];
            }
            else
            {
                nRet += roman[*iter];
            }
            last = roman[*iter];
        }
        return nRet;
    }
};
```

### 遍历string
1. 直接读下标
2. 迭代器，可以正读或者倒着读。
