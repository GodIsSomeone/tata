class Solution {
    public:
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
    int i = 1534236469;
    cout << Solution().reverse(i)<<endl;
    return 0;
}
