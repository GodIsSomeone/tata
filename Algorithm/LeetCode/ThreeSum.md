相比四数之和，三数相当于去掉了一个外衣
```
class Solution {
 public:
     vector<vector<int>> threeSum(vector<int>& nums) {
         sort(nums.begin(), nums.end());
         vector<vector<int>> res;
         for (int i = 0; i < nums.size(); ++i)
         {
             if (nums[i] > 0)
             {
                 break;//
             }
             if (i > 0 && nums[i] == nums[i-1])//nums的判断条件写在前面会报错。
             {
                 continue;
             }
             int target = nums[i];
             target = 0 - target;
             int j = i + 1;
             int k = nums.size() - 1;
             while (j < k)
             {
                 if (nums[j]+nums[k] == target)
                 {
                     vector<int> temp;
                     temp.push_back(nums[i]);
                     temp.push_back(nums[j]);
                     temp.push_back(nums[k]);
                     res.push_back(temp);
                     cout << nums[i] << "," << nums[j] << "," << nums[k] << endl;
                     while (j < k && nums[j] == nums[j + 1])
                     {
                         ++j;
                     }
                     while (j < k && nums[k] == nums[k - 1])
                     {
                         --k;
                     }
                     ++j;
                     --k;
                 }
                 else if (nums[j] + nums[k] < target)
                 {
                     ++j;
                 }
                 else
                 {
                     --k;
                 }
             }
         }
         return res;
     }
 };

 int main(){
     vector<int> nums;
     nums.push_back(-1);
     nums.push_back(0);
     nums.push_back(1);
     nums.push_back(2);
     nums.push_back(-1);
     nums.push_back(-4);
     Solution().threeSum(nums);
     //cout << Solution().threeSum(nums)<<endl;
     return 0;
 }
```   
