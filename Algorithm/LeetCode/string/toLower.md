大小写转换
```
class Solution {
  public:
  string toLowerCase(string str) {
    /*针对每一个元素进行操作*/
    for(auto &c:str ) // &c  使用引用
    {
      c = tolower(c);
    }
    /*使用算法*/
    transform(str.begin(), str.end(), str.begin(), ::tolower); /*include 头文件 algorithm.h*/
    
    return str;
  }
};
```
