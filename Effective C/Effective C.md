### 条款一  C++是一个语言联邦  

#### 建议

   + c++是有兄弟的：C，Object-Oriented c++(c with class),template c++,STL  
   + c++高效编程守则视状况而变化，取决于你使用c++的哪一部分。

### 条款二  尽量使用const, enum, inline代替define。  

+ 宁可**编译器**替换**预处理器**比较好。因为define不被视为语言的一部分。  

	```
	define NUM 3
	```

	define在预处理器中已经替换成为具体的值，当编译遇到一个常量错误的时候,你可能会感到困惑，因为错误信息提到的可能是3，而不是NUM。  
	而且当NUM的定义不是你所设计的时候，你可能会因为去查找3这个值所引发的错误到底是为什么而头大！这个问题也可能出现在记号调试器（symbolic debugger）中，原因相同：你所使用的名称可能并未进入记号表（symbol table）  
	另一个原因是：const可以成为作用域中的一个成员，define并不能行，且不能提供任何封装性。  
	还有一个原因是#define的函数  

	```
    #define MAX(a,b) func((a)>(b)?(a):(b))
    int a=5,b=0;
    MAX(++a,b);		     //a被累加二次
    MAX(++a,b+10);	    //a被累加一次
    ```

	在这里，调用f之前，a的递增次数不定！  
	建议用内联模板  

#### 建议  

   + 对于单纯常量，最好以const对象或者enum替换#define  
   + 对于形似函数的宏，最好改用inline函数替换  

### 条款三  尽量使用const。  

+ const在常量中的运用。

	```
	char greet[] = "hello";
	const char* p = greet; //const data,non-const pointer;
	char* const p = greet; //non-const data,const pointer;
	const char* const p = greet; //const data,const pointer;
	```
	
	迭代器中:
	
	```
	vector<int>vec;
	const vector<int>::iterator iter = vec.begin();
	*iter = 10;		 //没问题，改变iter所指的实体；
	++iter;          //错误！iter是const
	
	//其实看过const_iterator的实现就知道，他就是对实体对象的一个const
	vector<int>::const_iterator citer = vec.begin();
	*citer = 10;		 //错误！*citer是const；
	++citer;            //没问题！改变citer
	```
	
+ const在函数中的运用

   > const Rational operator*（const Rational &lhs）；

	避免用户XJBY。

+ const成员函数
	
	第一，他们使得class接口比较容易理解，可以知道哪个函数可以改动对象内容，哪个函数不行。  
	第二，他们使得“操作const对象”成为可能。  

+ 编译器强制实施bitwise constness，但你编写程序时应该使用概念上的常量性

+ 当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可避免代码重复。但是要做好类型转换，否则会出现自己调用自己的现象。  

	```
	const char& operator[] (int position) const
	{
	    return m_text[position];
	}
	
	/*  返回类型是个reference to char，不是char  */
	char &operator[](int position)
	{
	    return m_text[position];
	    /*调用const operator[]*/
	    /*
	    return const_cast<cahr&>(const TextBlock&)(*this)[position]);
	    */
	}
	```

#### 建议

   + const真的是一个磨人的小妖精

### 条款四  确定对象在使用前已经初始化。  

+ 为内置型对象进行手工初始化，因为C++不保证初始化它们。  

+ 构造函数最好使用成员初始化列表（member initialization list）,而不要在构造函数本体内使用赋值操作（assignment）。初值列列出的成员变量，其**排列次序**应该和它们在class中的声明次序相同。  
	**C++规定，对象的成员变量的初始化动作发生在进入构造函数本体之前**。构造函数体内的“=”叫做“赋值”，初始化发生的时间更早，发生于这些成员的default构造函数被自动调用之时。  
	**赋值构造的实质**是：先设定初值，再为它们赋予新值。  
	**成员列表初始化**：避免上述问题，同时避免调用copy构造函数，高效很多  
	
+ 为免除“跨编译单元之初始化次序”问题，请以local static对象替换non-local static对象。（不是很明白）

#### 建议

   + 记得初始化！
   + 可以使用初始化列表

### 条款五  了解C++ 默默编写并调用哪些函数。  

	C++会默认为类构建default构造、析构（非virtual）、copy assignment构造、copy构造函数。  
    
### 条款六  不想用默认的，就要说啊，不要当渣男。

   把五种的函数声明为private，并不实现。
    
### 条款七  为多态基类声明virtual析构函数。


​       
### 条款八  别让异常逃离析构函数。析构函数吞下异常，然后记下来。不要轻易终止程序。    


​       
### 条款九  不要在构造函数中调用虚函数     


### 条款十  operator= 的时候返回*this      


### 条款十一  operator= 的时候处理自我复制，判断如果等同this ,return       


### 条款十二  copy对象的时候不要忘记七每一个成分       


### 条款十三  以对象管理资源，防止资源泄漏，使用RAII管理资源，使用智能指针shared_ptr       


### 条款十四  在资源管理类中，小心copy的行为       


### 条款十五  在原始资源类中，提供对原始资源的访问。


### 条款十六  成对使用new和delete，并采用相同的形式       
new [] ,delete []; new ,delete.    
     
### 条款二十  传递const引用，而不是value       
value涉及到构造析构对象，要消耗更多，const引用，没有创建任何对象，所以消耗没那么多    
```
class Person
{
public:
    Person(int a = 0) : m_a(a)
    {
    }
    virtual ~Person()
    {
        cout << "Calling Person destructor" << endl;
    }
public:
    int m_a;
};
class Student:public Person
{
public:
    Student() {}
    ~Student() {

        cout << "Calling Student destructor" << endl;
    }

private:

};
//如果是(Student stu)，则需要构造两次，析构两次。
bool isStudent(const Student& stu)//只需要构造一次，析构一次
{
    return true;
}

//***************************************************************
int main( )
{
    Student stu;
    cout << isStudent(stu) << endl;

    return 0;
}
```
在底层中，引用其实是用指针来完成的。但是并非都是如此，如果参数是内置的类型或者STL的迭代器或者函数对象，比如int，
那么直接传值并不会造成过多的构造和虚构。
    
### 条款二十二  将 成员变量声明为private       

### 条款二十七  尽可能延后变量的定义        


### 条款二十八  尽量减少类型转换       

### 条款三十    inline函数，限制在频繁调用的小型函数。避免代码膨胀。   


### 条款三十一  public继承,是一个is-a的关系。因为基类身上的每一件事情一定也适用于继承类身上，因为每一个继承类对象也是一个基类对象。   


### 条款三十二  。   

​    
