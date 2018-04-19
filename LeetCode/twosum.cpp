class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int length = nums.size();

        vector<int>retPos(2,0);

        for (int i = 0; i<length; i++)
        {
            int num1 = nums[i];
            for (int j = i+1; j<length; j++)
            {
                int num2 = nums[j];
                if (target == num1 + num2)
                {
                    retPos[0] = i;
                    retPos[1] = j;
                    return retPos;
                }
            }
        }
        return retPos;
    }
};

int main(){
    vector<int> nums;
    nums.push_back(0);
    nums.push_back(4);
    nums.push_back(3);
    nums.push_back(0);
    vector<int> ret(2);
    ret = Solution().twoSum(nums,0);
    for (int i = 0; i<2; i++)
    {
        cout<<ret[i]<<endl;
    }
    return 0;
}
