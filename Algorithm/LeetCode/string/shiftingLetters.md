字母移动，移动的规则是迭代移动

```
class Solution {
public:
    string shiftingLetters(string S, vector<int>& shifts) {
        int sum = 0;
        for (int i = shifts.size()-1; i >= 0; i--)
        {
            sum = (sum + shifts[i]) % 26;
            S[i] = 'a' + ((int)S[i] - (int)'a' + sum) % 26;
        }
        return S;
    }
};

```
