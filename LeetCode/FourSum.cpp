class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        if (nums.size()<4)
        {
            return res;
        }
        for (int h = 0; h<nums.size() - 3; h++)
        {
            if (h>0 && nums[h] == nums[h - 1]) continue;
            if (nums[h] + nums[h + 1] + nums[h + 2] + nums[h + 3]>target) break;
            if (nums[h] + nums[nums.size() - 3] + nums[nums.size() - 2] + nums[nums.size() - 1]<target) continue;

            for (int i = h + 1; i < nums.size() - 2; i++)
            {
                if (i>h + 1 && nums[i] == nums[i - 1]) continue;
                if (nums[h] + nums[i] + nums[i + 1] + nums[i + 2]>target) break;
                if (nums[h] + nums[i] + nums[nums.size() - 2] + nums[nums.size() - 1]<target) continue;

                int j = i + 1;
                int k = nums.size() - 1;
                while (j < k)
                {
                    if (nums[h] + nums[i] + nums[j] + nums[k] == target)
                    {
                        vector<int> temp;
                        temp.push_back(nums[h]);
                        temp.push_back(nums[i]);
                        temp.push_back(nums[j]);
                        temp.push_back(nums[k]);
                        res.push_back(temp);
                        cout << nums[h] << "," << nums[i] << "," << nums[j] << "," << nums[k] << endl;
                        while (j < k && nums[j] == nums[j + 1])
                        {
                            j++;
                        }
                        while (j < k && nums[k] == nums[k - 1])
                        {
                            k--;
                        }
                        j++;
                        k--;
                    }
                    else if (nums[h] + nums[i] + nums[j] + nums[k] < target)
                    {
                        j++;
                    }
                    else
                    {
                        k--;
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums;
    nums.push_back(-3);
    nums.push_back(-1);
    nums.push_back(-2);
    nums.push_back(0);
    nums.push_back(0);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    Solution().threeSum(nums, 0);
    //cout << Solution().threeSum(nums)<<endl;
    return 0;
}
