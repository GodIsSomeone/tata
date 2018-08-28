## 条款一  C++是一个语言联邦 包括C，Objective-C，STL，template C++。     

   
## 条款二  尽量使用const, enum, inline代替define。    

      
## 条款三  尽量使用const。      

    
## 条款四  确定对象在使用前已经初始化。        

     
## 条款五  了解C++ 默默编写并调用哪些函数。    
    C++会默认为类构建default构造、析构、copy assignment构造、copy构造函数。
    
## 条款六  不想用默认的，就要说啊，不要当渣男。

   把五种的函数声明为private，并不实现。
    
## 条款七  为多态基类声明virtual析构函数。

     
       
## 条款八  别让异常逃离析构函数。析构函数吞下异常，然后记下来。不要轻易终止程序。    

     
       
## 条款九  不要在构造函数中调用虚函数     

     
## 条款十  operator= 的时候返回*this      

     
## 条款十一  operator= 的时候处理自我复制，判断如果等同this ,return       

     
## 条款十二  copy对象的时候不要忘记七每一个成分       

     
## 条款十三  以对象管理资源，防止资源泄漏，使用RAII管理资源，使用智能指针shared_ptr       

     
## 条款十四  在资源管理类中，小心copy的行为       

    
## 条款十五  在原始资源类中，提供对原始资源的访问。

     
## 条款十六  成对使用new和delete，并采用相同的形式       
new [] ,delete []; new ,delete.    
     
## 条款二十  传递const引用，而不是value       
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
    
## 条款二十二  将 成员变量声明为private       
      
## 条款二十七  尽可能延后变量的定义        

     
## 条款二十八  尽量减少类型转换       
