class A
{
public:
    A(int);
    A(A const &rhs);
    virtual ~A();
    /* 如果基类只是一个接口类，此行还可以直接改为virtual  A* clone() =0; */
    virtual A* clone() 
    {  
        return  new A (*this);
    }
private: 
};

class B:public A
{
public:
    B(int);
    B(B const &rhs);
    virtual ~B();
    virtual B* clone()
    {
        //return new B();    //利用虚函数机制实现了虚构造的目的；
        return new B(*this); //利用虚函数机制实现了虚复制构造的目的；
    }
};