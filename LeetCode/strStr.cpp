class Solution {
public:
    int strStr(string haystack, string needle) {
        //if (needle.length() == 0 || needle == "") return 0;
        //if (haystack.length() < needle.length())  return -1;
        return haystack.find(needle);
    }
};
int main()
{
    string haystack = "hello";
    string needle = "lo";
    cout << Solution().strStr(haystack, needle) << endl;

    return 0;
}


find  和   find_first_of的区别
find完全匹配，find_first_of部分匹配
