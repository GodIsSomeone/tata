先倒序，然后判断是否相等，相等则为TRUE；否则为FALSE

```
class Solution {
 public:
	 bool isPalindrome(int x) {
		 if (x<0)
		 {
			 return false;
		 }
		 if (x<10 && x>=0)
		 {
			 return true;
		 }
		 int revX = reverse(x);
		 if (revX == x)
		 {
			 return true;
		 }
		 else
		 {
			 return false;
		 }
	 }
     int reverse(int x) {
         if (x>INT_MAX || x<INT_MIN)
         {
             return 0;
         }
         long long ret = 0;
         int temp = 0;
         while (x)
         {
             temp = x%10;
             ret = 10*ret +temp;
             x = x /10;
         }
         return (ret > INT_MAX || ret < INT_MIN) ? 0 : ret;
     }
 };

 int main(){
     int i = 121;
     cout << Solution().isPalindrome(i)<<endl;
     return 0;
 }
```
