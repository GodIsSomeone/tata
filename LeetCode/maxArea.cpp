 class Solution {
 public:
	 int maxArea(vector<int>& height) 
	 {
		 int size = height.size();
		 int x = 0;
		 int y = 0;
		 int width = 0;
		 int area = 0;
		 int temp = 0;
		 for (int i = 0; i < size; i++)
		 {
			 x = height[i];
			 if (!x)
			 {
				 continue;
			 }
			 for (int j = i+1; j < size; j++)
			 {
				 y = height[j];
				 if (!y)
				 {
					 continue;
				 }
				 width = (x < y) ? x : y;
				 temp = width *(j - i);
				 if (temp>area)
				 {
					 area = temp;
				 }
			 }
		 }
		 return area;
	 }
 };

 int main(){
	 vector<int> height;
	 height.push_back(1);
	 height.push_back(2);

     cout << Solution().maxArea(height)<<endl;
     return 0;
 }
