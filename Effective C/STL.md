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



