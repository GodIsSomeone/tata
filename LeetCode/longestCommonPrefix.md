最长的公共前缀        

``` 
class Solution {
 public:
     string longestCommonPrefix(vector<string>& strs) {
         if (strs.size() == 0)
         {
             return "";
         }
         string resPrefix = strs[0];
         for (int i=1; i<strs.size(); i++)
         {
             while (strs[i].find(resPrefix) != 0)
             {
                 resPrefix = resPrefix.substr(0,resPrefix.length()-1);
                 if ("" == resPrefix)
                 {
                     return resPrefix;
                 }
             }
         }
         return resPrefix;
     }
 };

 int main(){
     vector<string> strs;
     strs.push_back("hello");
     strs.push_back("helloworld");
     cout << Solution().longestCommonPrefix(strs)<<endl;
     return 0;
 }
 ```     
 
