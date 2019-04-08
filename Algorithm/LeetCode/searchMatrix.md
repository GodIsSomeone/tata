```

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int length = matrix.size();
        if (0 == length)
        {
            return false;
        }
        int xlen = matrix[0].size();
        if (0 == xlen) return false;
        int low = 0;
        int high = length - 1;
        while (low<=high)
        {
            int mid = low + (high - low) / 2;
            if (matrix[mid][0] = target)
            {
                return true;
            }
            else if (matrix[mid][0] > target)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }

        if (!low)
        {
            return false;
        }

        
        int left = 0;
        int right = xlen - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (matrix[low][left] == target)
            {
                return true;
            }
            else if (matrix[low][left] > target)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        return false;
    }

```
