class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() <= 1) {
            return s;
        }

        string ret;
        int start = 0, end = 0;
        for (int i = 1; i < s.size(); ++i) {
            // 偶数回文遍历的方式，abba这类回文从中心向两边遍历
            start = i - 1;
            end = i;

            while (start >= 0 && end < s.size() && s[start] == s[end]) {
                start--;
                end++;
            }

            int paliStart = start+1, paliEnd = end-1;
            int paliLen = paliEnd - paliStart + 1;
            if (paliLen > ret.size()) {
                ret = s.substr(paliStart, paliLen);
            }

            // 奇数回文遍历方式 abcba这种方式，中心点start=i-1, end = i+1
            start = i - 1;
            end = i + 1;
            while (start >= 0 && end < s.size() && s[start] == s[end]) {
                start--;
                end++;
            }

            paliStart = start + 1;
            paliEnd = end - 1;
            paliLen = paliEnd - paliStart + 1;
            if (paliLen > ret.size()) {
                ret = s.substr(paliStart, paliLen);
            }
        }

        return ret;
    }
};

int main(){
    string s = "asdsa";
    cout << Solution().longestPalindrome(s)<<endl;
    return 0;
}
