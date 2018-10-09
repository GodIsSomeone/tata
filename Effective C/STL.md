## 条款1：选择合适的容器。根据具体需求选择合适的容器
  1. 标准STL序列容器：vector、string、deque、list
  2. 标准STL关联容器：set、multiset、map、multimap
  3. 非标准序列容器slist、rope
  4. 非标准关联容器hash_set、hash_multiset、hash_map、hash_multimap。
  
## 条款2：小心对“容器无关代码”的幻想。没有完美的容器，能够实现所有的操作。使用typedef定义相关容器，可以节省很多没必要的代码修改.
```
class Widget {...};
typedef vector<Widget> WidgetContainer;
typedef WidgetContainer::iterator WCIterator;
WidgetContainer cw;
Widget bestWidget;
...
WCIterator i=find(vw.begin(), vw.end(), bestWidget);
```

## 条款3：容器内的对象拷贝操作要正确且轻量。
容器可以存储对象。当向容器添加对象（insert或push_back），添加到容器的对象是指定对象的拷贝；同理，取出对象时也是通过拷贝。存储在容器里的对象，
还可能会对它拷贝。例如，从序列容器插入或删除元素，会引起元素的移动，移动是通过拷贝进行的（条款 14、15）。如果使用了排序算法（条款 31）
next_permutation、previous_permutation、remove、unique等或同类算法（条款 32），rotate或reverse等，对象也会拷贝（移动）。
解决办法就是建立指针容器，这样拷贝更快，且没有分割问题。

## 条款4：用empty来代替检查size()是否为0
因为empty的典型实现是一个返回size是否为0的内联函数。因为对于所有标准容器，empty是一个常数时间操作，但对于list，size的花费为线性时间，
因为是list特有的splice有很多要处理的东西。
```
list<int> list1; 
list<int> list2; 
... 
list1.splice(                   
    list1.end(), list2,         
    find(list2.begin(), list2.end(), 5),        //list2中第一次出现5和第一次出现10的元素插入到list1的结尾
    find(list2.rbegin(), list2.rend(), 10).base()   
    );   
 /*因为在插入之前谁都不知道最后list到底有多少元素，size到底是多少。list中如果把size设计成常数时间操作，
 那么list成员函数在更新list时也要更新size的大小，包括splice。这时splice就是线性时间操作了。
 size和splice不能都是常数时间操作，必须有一个让步。*/
```

## 条款5：尽量使用区间成员函数，而不是对单个元素进行操作。
尽量避免手写显式循环操作，区间成员函数就是对区间直接进行操作的函数！！！

相比单元素遍历操作，使用区间成员函数的优势在于： 
1）更少的函数调用 
2）更少的元素移动 ，单元素操作，每次都要移动，而区间函数，只是移动一次，一步到位。
3）更少的内存分配 ，同上，依旧需要处理内存分配问题。

总结
```
/*区间构造*/
container（begin(),end()）;
/*插入*/
insert(pos,begion(),end());
/*清除*/
erase(begin(),end());
/*区间赋值*/
assign(begin(),end());
```

## 条款6：c++的解析方式是SB的，所以尽量使用安全的形式去解析。一步一步的来，简单清晰。
没办法，这就是作者的愿意，他解析了半天，举了很多的例子，但是我感觉他就是想这么说明的，因为那种赋值方式是极为容易出现错误的。

## 条款7：对于new出的指针，记得在结束的时候记得delete掉
吾日三省吾身，初始化了吗？内存清空了吗？头发掉了吗？
具体细节还要继续看。第一遍不深究。

## 条款8：不要建立auto_ptr指针的容器。
因为拷贝一个auto_ptr会拿走他的值，原有的容器内就变成空了。智能指针并不适用于这种情况。

## 条款9：仔细选择删除方式


## 条款12：STL中的线程安全
使用代码块{...........}在代码块中调用锁，资源初始化之后释放，

# string 和 vector
## 条款13：尽量使用vector和string代替动态分配的数组

## 条款14：使用reserve重新避免不必要的内存分配。
string和vector的内存重新分配方法，申请一块新的地址，大小以2的倍数增长。拷贝内容，销毁原有内存。
使用reserve将内存设置的足够大，避免内存重新分配，带来较大的开销。

## 条款15：小心string实现的多样化。（还需要再详细看看）
包括string实现的多样化，配置器、大小、内容引用等因素。

## 条款16：将string和vector数据传给遗留的API   
v.begin()返回的是迭代器类型，&v[0]是指针，二者不能通用。等同于&（*v.begin()）

## 条款17：使用swap清除不必要内存。
```
void testVec() 
{
    vector<int> vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++)
    {
        vec.push_back(i);
    }
    vector<int> vecCpy(vec);
    for (int i = 0; i < 2000; i++)
    {
        vec.push_back(i);
    }
    cout << "cap: " << vec.capacity() << ", " << vecCpy.capacity() << endl;

    vec.swap(vecCpy);
    cout << "cap: " << vec.capacity() << ", " << vecCpy.capacity() << endl;

    return;
}
```

## 条款18：避免使用vector<bool>.
vector<bool>并不是容器，只不过是披着vector的皮而已。
  vector<bool>不满足vector的一些必要条件，比如bool *p= &v[0]是错误的。
  替代品：deque<bool>,bitset
  ```
  // bitset::count
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<8> foo (std::string("10110011"));

  std::cout << foo << " has ";
  std::cout << foo.count() << " ones and ";
  std::cout << (foo.size()-foo.count()) << " zeros.\n";

  return 0;
}
  ```
# 关联容器

## 条款19： 等价和相等之间的区别。
通过自定义，等价和相等之间是不同的。set中是通过less的手段进行比较的。
## 条款20： 为指针的关联容器指定比较类型。
## 条款21： 永远让比较函数返回false
```
bool fncomp(int lhs, int rhs) { return lhs < rhs; }

struct classcomp {
    bool operator() (const int& lhs, const int& rhs) const
    {
        return lhs < rhs;
    }
};

int main()
{
    set<int> first;                           // empty set of ints

    int myints[] = { 10,20,30,40,50 };
    set<int> second(myints, myints + 5);        // range

    set<int> third(second);                  // a copy of second

    set<int> fourth(second.begin(), second.end());  // iterator ctor.

    set<int, classcomp> fifth;                 // class as Compare

    bool(*fn_pt)(int, int) = fncomp;
    set<int, bool(*)(int, int)> sixth(fn_pt);  // function pointer as Compare

    return 0;
}
```

## 条款22：避免原地直接修改map和set的键


## 条款23：考虑用有序vector代替关联容器
感觉是在说尽量自己写compare函数，提交效率，减少内存占用。

## 条款24：map::operator[] 和map::insert之间的选择
处于对效率的考虑，当map添加一个元素的时候，insert比operator[]更好；从效率和美学考虑，当更新map中的元素时，operator[]更好