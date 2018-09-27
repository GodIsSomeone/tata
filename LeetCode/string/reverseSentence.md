翻转句子，保留单词原有的位置。
```
class Solution {
public:
    string reverseWords(string s) {
        string result = "";
        /*理解错了题目，我把整个string都翻转了*/
        /*
        for (string::reverse_iterator iter = s.rbegin(); iter != s.rend(); iter++)
        {
            result += *iter;
        }
        */
        /*split*/
        string item = "";
        stringstream ss(s);
        vector<string> splitStr;
        while (getline(ss, item, ' ')) {
            splitStr.push_back(item);
        }

        for(vector<string>::iterator it = splitStr.begin(); it!= splitStr.end(); it++)
        {
            for (string::reverse_iterator iter = (*it).rbegin(); iter != (*it).rend(); iter++)
            {
                result += *iter;
            }
            result += " ";
        }
        result.pop_back();
        return result;
        
    }
};
```
