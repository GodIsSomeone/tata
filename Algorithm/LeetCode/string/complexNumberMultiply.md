#### 复数的计算

```
class Solution {
public:
    pair<int, int> extract(string a)
    {
        int i = 0;
        while (i < a.size() && a[i] != '+')
        {
            i++;
        }
        int x = stoi(a.substr(0, i));
        int y = stoi(a.substr(i+1));
        return make_pair(x, y);
    }

    string complexNumberMultiply(string a, string b) {
        if (a=="")
        {
            return b;
        }
        if (b == "")
        {
            return a;
        }
        auto a1 = extract(a);
        auto b1 = extract(b);
        int x = a1.first * b1.first - a1.second * b1.second;
        int y = a1.first * b1.second + a1.second * b1.first;
        string s = to_string(x) + "+" + to_string(y) + "i";
        return s;
    }
};
```
