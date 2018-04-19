class Solution {
 public:
     int threeSumClosest(vector<int>& nums, int target) {
         sort(nums.begin(), nums.end());
         int mintarget = nums[0]+nums[1]+nums[2]-target;
         int closet = nums[0] + nums[1] + nums[2];
         if (nums.size() == 3)
         {
             return closet;
         }
         for (int i = 0; i < nums.size(); ++i)
         {
             int j = i + 1;
             int k = nums.size() - 1;
             while (j < k)
             {
                 int sum = nums[i] + nums[j] + nums[k];
                 
                 if (abs(mintarget) > abs(target-sum))
                 {
                     mintarget = target - sum;
                     closet = sum;
                 }
                 
                 if (sum < target)
                 {
                     ++j;
                 }
                 else
                 {
                     --k;
                 }
             }
         }
         return closet;
     }
 };

 int main(){
     vector<int> nums;
     nums.push_back(1);
     nums.push_back(1);
     nums.push_back(1);
     nums.push_back(1);
//      nums.push_back(-1);
//      nums.push_back(-4);
     
     cout << Solution().threeSumClosest(nums, 0) <<endl;
     return 0;
 }
