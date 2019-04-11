### 约瑟夫环  
f [1] = 0;   
f [ i ] = ( f [i -1] + m) % i; (i>1)   


```
int josephus(int n, int k) 
{ 
    //非迭代版本
    int s = 0;
    for (int i = 2; i <= n; i++)
    {
        s = (s + k) % i;
    }
    return s;
}
int josephus_recursion(int n, int k) 
{ 
    //迭代版本
    return n > 0 ? (josephus_recursion(n - 1, k) + k) % n : 0;
}

```
