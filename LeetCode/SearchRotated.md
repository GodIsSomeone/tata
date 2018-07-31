Search in Rotated Sorted Array


```

    int search(vector<int>& nums, int target) {
        int length = nums.size();
        if (!length) return -1;
        int low = 0;
        int high = length - 1;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (nums.at(mid) == target)
            {
                return mid;
            }
            if (nums.at(mid)<nums.at(high))
            {
                if (nums.at(mid)<target && target<=nums.at(high))
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }
            else
            {
                if (nums.at(mid) > target && target>=nums.at(low))
                {
                    high = mid - 1;
                }
                else
                {
                    low = mid + 1;
                }
            }
        }
        return -1;
    }

```
