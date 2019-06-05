# 80-20法则：一个典型的程序有80%的执行时间花费在20%的代码身上。  

## 让自己习惯C++

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

## 构造、析构和赋值运算

### 条款五  了解C++ 默默编写并调用哪些函数。  

+ C++会默认 为类构建default构造、析构（非virtual，除非base class自身有virtual析构函数）、copy assignment构造、copy构造函数。且这些函数都是public和inline。  

+ default构造函数和析构函数主要是给编译器一个地方用来防止藏身幕后的代码，像是调用base classes 和no-static成员变量的构造函数和析构函数。  

+ 至于copy构造函数和copyassignment操作符，编译器创建的版本只是单纯地将来源对象的每一个non-static成员变量拷贝到目标对象。

+ 编译器并不是任何情况下都默认生成这些函数，要看具体的情况。  

### 条款六  不想用默认的，就要说啊，不要当渣男。

+ 把copy构造函数和copyassignment操作符都声明为private，并不实现。  

+ 或者使用uncopyable这样的base class也是一种做法。继承一个base class，其copy函数是private。不过有点微妙，需要细心一点研究。  

### 条款七  为多态基类声明virtual析构函数。

+ 盲目继承，会造成内存泄漏，比如继承no-virtual的类String。相同的分析适用于任何不带virtual析构函数的class，包括所有STL容器。

	```
	class myString: public string{};
	myString ms= new myString("hello");
	string *ps;
	ps = ms;
	delete ps; //未定义！显示中*ps的myString资源会泄漏，因为myString析构函数并没有被调用。
	```

+ class的设计目的如果不是作为base class使用，或者不是为了具备多态性（polymorphically），就不该声明为virtual析构函数。

### 条款八  别让异常逃离析构函数。析构函数吞下异常，然后记下来。不要轻易终止程序。  

+ 析构函数绝对不要吐出异常。如果一个被析构函数调用的函数可能跑出异常，析构函数应该捕捉任何异常，然后吞下他们（不传播）或结束程序。  

	```
	class DBConn{     // 这个class用来管理DBConnection对象
		public:
		~DBConn()     // 确保数据库连接总是会被关闭；
		{
			try{
				db.close();
			}
			catch(){
				// 制作运转记录，记下对close的调用失败；或吞下异常
				abort();	//close()抛出异常的处理，
			}
		}
		private:
		DBConnection db;
	};
	```

+ 如果客户需要对某个操作函数运行期间跑出的异常做出反应，那么class应该提供一个普通函数执行该操作，而不是在析构中。  

	```
	class DBConn{     // 这个class用来管理DBConnection对象
		public:
		void close()//供客户使用的新函数
		{
			db.close();
			closed = true;
		}
		~DBConn()     // 确保数据库连接总是会被关闭；
		{
			if(!closed)  // 判断是否关闭
			{
				try{
					db.close();
				}
				catch(){
					// 制作运转记录，记下对close的调用失败；或吞下异常
					abort();	//close()抛出异常的处理，
				}
			}
		}
		private:
		DBConnection db;
		bool closed;
	};
	```
​
### 条款九  不要在构造函数中调用虚函数  

+ base class 构造期间virtual函数绝不会下降到derived class阶层。在base class构造期间，virtual函数不是virtual函数。  

+ 其实b在base class构造（析构也是这样）期间，b的类型是base class，而不是derived class。  

	```
	class A{
		public:
		A()
		{
			//do sth;
			······
			// final
			print();     //调用A的方法，而不是B的。
		}
		virtual void print() const;
	};

	class B:public A{
		virtual void print() const;
	};

	//先调用A的构造，print，不会调用B的print
	//因为A构造函数的执行的时候，B的成员变量尚未初始化。要求使用对象内部尚未初始化的成分是危险的。
	B b;
	```

+ 解决办法：不要使用virtual函数从上向下调用，在构造期间，你可以用参数传递。  

	```
	class A{
		public:
		explict A(string& loginfo)
		{
			//do sth;
			······
			// final
			print(loginfo);     //调用A的方法，而不是B的。
		}
		void print(string& loginfo) const;
	};

	class B:public A{
		public:
		B(param):A(createlogstring(param))
		{···}
		private:
		string createlogstring(param);
	};
	```

### 条款十  operator= 的时候返回*this  

+ 这只是一个协议，并无强制性。  

	```
	class Widget
	{
		public: 
		Widget& operator+=(const Widget& rhs)
		{
			···
			return *this;
		}
		Widget& operator=(int rhs)
		{
			···
			return *this;
		}
	};
	```

### 条款十一  operator= 的时候处理自我复制，判断如果等同this ,return  

+ 确保operator=的安全，包括比较“来源对象”和“目标对象”的地址，精心周到的语句顺序，以及copy and swap  

+ 确定任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确。  

	```
	class Widget
	{
		public: 
		//*this和rhs有可能是同一个对象。如果真的是这样，delete m_pb也会把rhs干掉了！！！！
		Widget& operator=(const Widget& rhs)
		{
			delete m_pb;  //停止使用当前的bitmnap
			pb = new Bitmap(*rhs.m_pb);  // 使用rhs bitmap的副本
			return *this;
		}

		private:
		Bitmap* m_pb;
	};
	```

+ 改进一：先判断this和rhs是否会相等。缺点：new失败后抛异常，Widget会有一个指针指向一块被删除的Bitmap。这样的指针有害，无法安全的删除它们，甚至无法安全地读取。  

	```
	Widget& operator=(const Widget& rhs)
	{
		if(this == &rhs) return *this; // 判断是否相同

		delete m_pb;  //停止使用当前的bitmnap
		pb = new Bitmap(*rhs.m_pb);  // 使用rhs bitmap的副本
		return *this;
	}
	```

+ 改进二：我们需要注意在赋值之前别删除m_pb。或者使用swap的方法  

	```
	Widget& operator=(const Widget& rhs)
	{
		Bitmap* pOrig = m_pb;		 // 记住原先的pb
		pb = new Bitmap(*rhs.m_pb);  // 使用rhs bitmap的副本
		delete pOrig;                // 删除原先的pb
		return *this;
	}
	```


### 条款十二  copy对象的时候不要忘记其每一个成分  

+ 确保复制所有的local成员变量，调用所有base class内的适当copying函数  

+ 不要尝试以某个copying函数实现另一个copying函数，应该将共同机能放进第三个函数中，并由两个copying函数共同调用。  

## 资源管理

### 条款十三  以对象管理资源，防止资源泄漏，使用RAII管理资源，使用智能指针shared_ptr  

+ 为防止资源泄漏，使用RAII（resource Acquisition Is Initialization）对象，在构造函数中获得资源并在析构函数中释放资源。  

+ 两个常被使用的RAII class分别是shared_ptr和unique_ptr(auto_ptr已经废弃)。  

### 条款十四  在资源管理类中，小心copy的行为  

+ 复制RAII对象必须一并复制它所管理的资源，所以资源的copying行为决定RAII对象的copying行为。  

+ 普遍而常见的RAII class copying行为是：抑制copying、使用引用计数法。不过其他行为也都可能被实现。  

### 条款十五  在资源管理类中，提供对原始资源的访问。

+ 每一个RAII class应该提供一个“取得其所管理之资源”的办法。  

+ 对原始资源的访问可能经由显式转换或隐式转换。一般而言显式转换比较安全，但隐式转换对客户比较方便。  

```
class Font{
	operator FontHandle() const  //隐式转换函数，容易带来危险。
	{return f;}

	FontHandle get() const  //显式转换函数
	{return f;}
};
```

### 条款十六  成对使用new和delete，并采用相同的形式  

+ new [] ,delete []; new ,delete.  

### 条款十七  以独立语句将newed对象置入智能指针  

+ 以独立语句将newed对象置入智能指针内，如果不这样做，一旦new的时候抛异常，有可能导致难以察觉的资源泄漏。  

## 设计与声明

### 条款十八  让接口容易被正确使用，不易被误用  

+ 好的接口很容易被正确使用，不容易被误用。  

+ 促进正确使用：接口的一致性，内置类型的行为兼容。  

+ 阻止误用：建立新类型、限制类型上的操作，束缚对象值，以及消除客户的资源管理责任  

+ 提到了shared_ptr。没仔细看。  

### 条款十九  设计class，犹如设计type  


### 条款二十  传递const引用，而不是value  

+ 尽量用const引用替换传值，value涉及到构造析构对象，要消耗更多，const引用，没有创建任何对象，所以消耗没那么多  

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

+ 在底层中，引用其实是用指针来完成的。但是并非都是如此，如果参数是内置的类型或者STL的迭代器或者函数对象，比如int，那么直接传值并不会造成过多的构造和虚构。

### 条款二十一  必须返回对象时，别妄想返回其reference

+ 绝不要返回pointer或reference指向一个local stack对象，或返回reference指向一个heap-allocated对象，或返回pointer或reference指向一个localstatic对象而有可能同时需要多个这样的对象。

### 条款二十二  将 成员变量声明为private  

+ 切记将成员变量生命为private。使得客户访问数据具有一致性，可细微划分访问控制，并提供class作者以充分的实现弹性。  

+ protected并不比public更具有封装性。  

### 条款二十三  用non-member、non-friend替换member函数  

+ 这样做可以增加封装性，报过弹性和技能扩充性  

### 条款二十四  若所有参数皆需类型转换，请为此采用non-member函数  

### 条款二十五  考虑写出一个不抛异常的swap函数  

+ 当std::swap对你的类型效率不高时，提供一个swap成员函数，并确定这个函数不抛异常  

+ 调用swap时应针对std::swap使用using声明，然后调用swap，并且不带任何命名空间资格修饰  

## 实现

### 条款二十六  尽可能延后变量定义式的出现时间  

### 条款二十七  尽量少作转型动作  

+ 尽量避免转型，特别是在注重效率的代码中避免dynamic_casts.  

+ 如果转型是必要的，试着将它隐藏于某个函数背后。客户随后可以调用该函数，而不需将转型放进他们自己的代码内  

+ 宁可使用C++style转型，不要使用旧式转型，前者很容易便是出来，而且有着不同的职责。  

### 条款二十八  避免返回handles指向对象内部成分  

### 条款二十九  为异常安全而努力是值得的  

+ 不泄露任何资源  

+ 不允许数据败坏  

+ 基本承诺：如果异常被抛出，程序内的任何事物仍然保持在有效状态下  

+ 强烈保证：如果异常被抛出，从程序状态不改变。能够以copy-and-swap实现  

+ 不抛弃保证（no throw）：承诺绝不抛出异常，因为它们总是能够完成它们原先承诺的功能  

### 条款三十    透彻学习inline函数  

+ inline只是一个申请，不是强制命令。如果无法将你要求的函数inline话，会给你一个警告信息  

+ 大多数编译器拒绝将太过复杂的函数inlining，对virtual函数也无效。因为virtual意味着“等待，直到运行期才确定调用哪个函数”。编译器很难进行替换  

+ 大部分调试器面对inline函数都束手无策  

+ 将大多数inlining限制在小型、被频繁调用的函数身上。这可使日后的调试过程和二进制升级更容易，也可使潜在的代码膨胀问题最小化，使程序的速度提升机会最大化  

### 条款三十一  将文件间的编译一寸关系降至最低  

## 继承与面向对象设计

### 条款三十二  确定你的public继承是一个is-a的关系  

+ public继承,是一个is-a的关系。因为基类身上的每一件事情一定也适用于继承类身上，因为每一个继承类对象也是一个基类对象。  


### 条款三十三  避免遮掩继承而来的名称  

+ 名字是什么？一朵玫瑰叫任何名字还是一样芬芳。  

+ 子类内的名称会遮掩父类内的名称。


### 条款三十四  区分接口继承和实现继承  

+ 声明一个纯虚函数（virtual func() = 0）的目的是为了让子类只继承函数接口  

+ 声明非纯虚函数（virtual func()）的目的，是让子类继承该函数的接口，并缺省实现。  

+ 声明non-virtual函数的目的是为了让子类继承函数的接口以及一份强制性实现  

### 条款三十五  考虑virtual函数以外的其他选择  


### 条款三十六  绝不重新定义继承而来的non-virtual函数  

+ 动态绑定（virtual）和静态绑定（non-virtual）的区别  

### 条款三十七  绝不重新定义继承而来的缺省参数值  

+ 动态绑定（virtual）和静态绑定（non-virtual）的区别  

### 条款三十八  通过复合塑模出has-a或“根据某物实现出”  

+ 复合，是类型之间的一种关系，当某种类型的对象内含有其他类型的对象，便是这种关系。  

### 条款三十九 明智而谨慎使用private继承  

+ 尽可能使用复合，必要时使用private  

### 条款四十  明智而谨慎使用多重继承  

+ 多重继承比单一继承复杂，可能导致新的歧义

+ virtual继承会增加大小、速度、初始化、赋值等成本，如果是virtual base class不带任何数据，将是最有实用价值的情况  

## 模板与泛型编程  

### 条款四十一  了解隐式接口和编译期多态  

+ class和template都支持接口（interface）和多态 （polymorphism）  

+ 对template参数而言，接口是隐式的（implicit），基于有效表达式。多态则是通过template具体化和函数重载解析发生于编译期  


### 条款四十二  了解typename的双重意义  

+ 在以下声明中，class和typename意义完全相同  

```
template<class T> class Widget;
template<typename T> class Widget;
```

+ 可以使用关键字typename标识嵌套从属类型名称；但不得在base class list（基类列表）或者memeber initialization list(成员初始化列表)内以它作为base class修饰符  

### 条款四十三  学习处理模板化基类内的名称  

### 条款四十四  将与参数无关的代码抽离templates  

### 条款四十五  运用成员函数模板接受所有兼容类型  

### 条款四十六  需要类型转换时请为模板定义非成员函数

### 条款四十七  使用traits classes表现类型信息  


### 条款四十八  认识template元编程  

## 定制new和delete

### 条款四十九  了解ner_handler的行为  

+ new_handler是一个typedef，定义出一个指针指向函数，该函数没有参数，也不返回任何东西。  

+ set_new_handler的参数一个指针，指向operator new无法分配足够内存时需要被调用的函数，。返回值也是个指针，指向set_new_handler被调用前正在执行的那个new_handler函数。  

	在这个例子中，当 operator new 无法为5000000000个整数分配足够空间的时候，oom() 函数会被调用，程序输出 “out of memory！！” 后夭折，如果在写出错误信息到 cerr 的过程中必须动态分配内存，则会进入上一篇中提到的 oom_malloc() 函数中的死循环，不断尝试释放、再配置、再释放、再配置......  

	```
	void oom()
	{
		cerr << "out of memory!!";
		about();
	}

	int main()
	{
		set_new_handler(oom);
		int *needBigMemory = new int [5000000000L];
		...
		return 0;
	}
	```

	当 operator new 无法满足内存申请时，它会不断调用“new-handler”函数（也就是不停在oom_malloc()函数中死循环），直到找到足够内存。由此我们必须设计良好的 new-handler 函数。具体如下：  

	1、让更多内存可被使用，这边造成了operator new内的下一次内存分配动作可能成功。实现此策略的一个做法是，程序一开始执行就分配一大块内存，而后当 new-handler 第一次被调用，将它们释还给程序使用。  

	2、安装另一个 new-handler。如果目前这个 new-handler 无法取得更多可用内存，或许它知道另外哪个 new-handle 有此能力。如此，目前这个new-handler 就可以安装另外那个 new-handler 以替换自己。下次当operator new 调用 new-handler，调用的将是最新安装的那个。(如果 new-handler 修改自己的行为，于是当它下次被调用，就会做某些不同的事。为达此目的，做法之一是令 new-handler 修改“会影响new-handler 行为”的static数据、namespace数据或global数据）  

	3、卸除 new-handler，也就是将null指针传给 set_new_handler。一旦没有安装任何 new-handler, operator new 会在内存分配不成功时抛出异常。  

	4、抛出 bad_alloc (或派生自 bad_alloc) 的异常。这样的异常不会被operator new 捕捉，因此会被传播到内存索求处。  

	5、不返回，通常调用 abort() 或 exit(0)。  


### 条款五十  了解new和delete的合理替换时机  

+ 什么时候适合重载new和delete  

### 条款五十一  编写new和delete时需遵循常规  

### 条款五十二  写了placement new , 也要写placement delete  

## 杂项讨论

### 条款五十三  不要轻视编译器的警告  

+ 严肃对待编译器发出的警告信息。努力在你的饿扁一起的最高警告级别下争取无任何警告的荣誉  
+ 不要过度依赖编译器的报警能力，因为不同编译器对待事物的态度并不相同。一旦移植到另一个编译器上，你原本依赖的警告信息有可能消失。  

### 条款五十四  让自己熟悉包括TR1在内的标准程序库  


### 条款五十四  让自己熟悉Boost  

