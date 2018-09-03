
```
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        if (!digits.length())
        {
            return res;
        }
        string constStr[10] = { "0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        res.push_back("");
        for (int i = 0; i<digits.length(); i++)
        {
            vector<string> tempV;
            int num = digits[i] - '0';
            string tempstr = constStr[num];
            for (int j = 0; j<tempstr.length(); j++)
            {
                for (int k=0; k<res.size(); k++)
                {
                    tempV.push_back(res[k] + tempstr[j]);
                }
            }
            res = tempV;
        }
        return res;
    }

};

int main() {
    string str = "";
    vector<string> vstr = Solution().letterCombinations(str);
    for (int i = 0; i<vstr.size(); i++)
    {
        cout << vstr[i] << endl;
    }
    return 0;
}
```
