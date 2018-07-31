```

    int searchInsert(vector<int>& nums, int target) {
        int length = nums.size();
        int low = 0;
        int high = length - 1;
        while (low<=high)
        {
            int mid = low + (high - low) / 2;
            if (nums.at(mid) == target)
            {
                return mid;
            }
            else if (nums.at(mid) < target)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }

            /*看到了一种运行速度更快的，直接用逼近的原则求结果*/
            /*
            if (nums.at(mid) >= target)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
            */
        }
        return low;
    }

```
