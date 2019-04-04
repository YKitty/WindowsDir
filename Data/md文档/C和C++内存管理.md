# C/C++内存管理

---

## 1. C/C++内存分布

> 看一段代码和问题；
>
> ```c++
> int globalVar = 1;
> static int staticGlobalVar = 1;
> void Test()
> {
> static int staticVar = 1;
> int localVar = 1;
> int num1[10] = {1, 2, 3, 4};
> char char2[] = "abcd";
> char* pChar3 = "abcd";
> int* ptr1 = (int*)malloc(sizeof (int)*4);
> int* ptr2 = (int*)calloc(4, sizeof(int));
> int* ptr3 = (int*)realloc(ptr2, sizeof(int)*4);
> free (ptr1);
> free (ptr3);
> }
> 1. 选择题：
> 选项: A.栈 B.堆 C.数据段（静态区） D.代码段（常量区）
> globalVar在哪里？__C__ staticGlobalVar在哪里？__C__
> staticVar在哪里？__C__ localVar在哪里？_A___
> num1 在哪里？__A__
> char2在哪里？__A__ *char2在哪里？__D_
> pChar3在哪里？__A__ *pChar3在哪里？_D___
> ptr1在哪里？_A___ *ptr1在哪里？_B___
> 2. 填空题：
> sizeof(num1) = __40__;
> sizeof(char2) = __5__; strlen(char2) = __4__;
> sizeof(pChar3) = __4||8__; strlen(pChar3) = __4__;
> sizeof(ptr1) = __4||8__; sizeof(ptr2) = __4||8__;
> //对于是指针变量的话，如果是32位机下就是4个字节，64位机下就是8个字节
> ```
>
> ![](C:\Users\0\Pictures\typora\QQ截图20181112165439.png)
>
> **【说明】**：
>
> - **栈**又叫做**堆栈**，**非静态局部变量/函数参数/返回值**等等，栈是**向下增长**的
> - **内存映射段**是**高效的I/O映射方式**，用于装载一个**共享的动态内存库**。用户可使用系统接口创建**共享内存**，做进程间通信。
> - **堆**用于程序运行时**动态内存分配**，堆是**向上增长**的。
> - **数据段（静态区）**--存储**全局数据和静态数据**
> - **代码段（常量区）**--**可执行的代码和只读常量**



## 2. C语言中动态内存管理方式

> ```c++
> void Test
> {
> 	int* p1 = (int*)malloc(sizeof(int) * 10);
> 	if (!p1)
>     {
>     	perror("malloc error!\n");
>     	exit(EXIT_FAILURE)；
>     }
>     
>     free(p1);
>     int* p2 = (int*)calloc(sizeof(int) * 10);
>     int* p3 = (int*)realloc(p2, sizeof(int) * 20);
>     
>     //这里还需要free(p2)吗?
>     //不需要，因为p3对于p2所指向的内存重现开辟已经将p2指向的内存空间释放，即已经隐式的执行了free(p2)
>     free(p3);
> }
> 
> ```
>
> **【面试题】**：**malloc与calloc以及realloc的区别**
>
> - malloc是只分配内存空间不进行初始化
> - calloc是分配空间并且初始化为0
> - realloc是对已经分配好的空间进行修改大小



## 3. C++内存管理

> **通过new和delete操作符进行动态内存管理**



### 3.1 new/delete操作内置类型

> ```c++
> void Test
> {
> 	//动态申请一个int类型的空间
> 	int* ptr1 = new int;
> 	
> 	//动态申请一个int类型的空间并且进行初始化
> 	int* ptr2 = new int(10);
> 	
> 	//动态申请10个int类型的空间
> 	int* ptr3 = new int[10];
> 	
> 	delete ptr1;
> 	delete ptr2;
> 	delete[] ptr3;
> }
> ```
>
> ![1541238440273](C:\Users\0\AppData\Local\Temp\1541238440273.png)
>
> **【注意】**：**申请和释放单个元素空间，使用new和delete操作符，申请和释放连续的空间，使用new[]和delete[]**



### 3.2 new/delete操作自定义类型

> ```c++
> /new和delete操作自定义类型
> #include <cstdlib>
> #include <iostream>
> using namespace std;
> 
> class Test
> {
> public:
>   Test ()
>     : _data(0)
>   {
>     cout << "Test():" << this << endl; 
>   }
> 
>   ~Test ()
>   {
>     cout << "~Test():" << this << endl;
>   }
> 
> private:
>   int _data;
> };
> 
> void TestMallocAndFree()
> {
>   //申请一个int类型的空间
>   int* p1 = (int*)malloc(sizeof(int));
>   free(p1);
> 
>   //申请10个int类型的空间
>   int* p2 = (int*)malloc(sizeof(int) * 10);
>   free(p2);
> }
> 
> void TestNewAndDelete()
> {
>   //申请一个Test类型的空间
>   Test* p1 = new Test;
>   delete(p1);
> 
>   //申请10个Test类型的空间
>   Test* p2 = new Test[10];
>   delete[] p2;
> }
> 
> int main()
> {
>   TestMallocAndFree();
>   TestNewAndDelete();
>   return 0;
> }
> ```
>
> **【输出结果】**
>
> ``` c++
> Test():0x1eaec20
> 
> ~Test():0x1eaec20
> 
> Test():0x1eaec78
> 
> Test():0x1eaec7c
> 
> Test():0x1eaec80
> 
> Test():0x1eaec84
> 
> Test():0x1eaec88
> 
> Test():0x1eaec8c
> 
> Test():0x1eaec90
> 
> Test():0x1eaec94
> 
> Test():0x1eaec98
> 
> Test():0x1eaec9c
> 
> ~Test():0x1eaec9c
> 
> ~Test():0x1eaec98
> 
> ~Test():0x1eaec94
> 
> ~Test():0x1eaec90
> 
> ~Test():0x1eaec8c
> 
> ~Test():0x1eaec88
> 
> ~Test():0x1eaec84
> 
> ~Test():0x1eaec80
> 
> ~Test():0x1eaec7c
> 
> ~Test():0x1eaec78
> ```
>
> - **可以看出，对于malloc和free函数，不调用构造函数和析构函数；而对于new要调用构造函数，对于delete要调用析构函数**
>
> **【注意】**：**在申请自定义空间的时候，new会调用构造函数，delete会调用析构函数，而malloc和free则不会**



##4. operator new 和 operator delete函数 

> **new和delete**是用户在进行**动态内存申请和释放的操作符**，**operator new**和**operator delete**是系统提供的**全局函数**，**new**在**底层调用operator new**全局函数来**申请空间**，**delet**e在**底层调用operator delete**全局函数来**释放空间**。
>
> ```c++
> //operator new:该函数实际通过malloc来申请空间，当malloc申请成功时直接返回；申请失败，尝试执行空间不足应对措施，如果改为应对措施用户设置了，那就继续申请，否则抛异常
> 
> void* __CRTDECL operator new(size_t size) _THROW!(_STD bad_alloc)
> {
>     //try to allocate size bytes
>     void* p;
>     while ((p = malloc(szie)) == 0)
>         if (_callnewh(szie) == 0)
>         {
>             //report no memory
>             static const std::bad_alloc nomem;
>             _RAISE(nomem);
>         }
>     
>     return (p);
> }
> 
> //operator delete:该函数最终是通过free来释放空间的
> 
> void operator delete(void *pUserData)
> {
> 	_CrtMemBlockHeader * pHead;
>     
> 	RTCCALLBACK(_RTC_Free_hook, (pUserData, 0));
>     
> 	if (pUserData == NULL)
> 		return;
>     
> 	_mlock(_HEAP_LOCK); /* block other threads */
> 
> 	__TRY
> 		/* get a pointer to memory block header */
> 		pHead = pHdr(pUserData);
>     
> 		/* verify block type */
> 		_ASSERTE(_BLOCK_TYPE_IS_VALID(pHead->nBlockUse));
>     
> 		_free_dbg( pUserData, pHead->nBlockUse );
> 	__FINALLY
> 		_munlock(_HEAP_LOCK); /* release other threads */
> 	__END_TRY_FINALLY
>         
> 	return;
> }
> ```
>
> 通过上述两个全局函数得到，**operator new实际也是通过malloc来申请空间的**，如果malloc申请的空间成功就直接返回，否则执行用户提供的空间不足应对措施，如果用户提供该措施就继续申请，否则就抛异常。**operator delete最终也是通过free来释放空间的。**
>
> **【注意】**：operator new和operator delete用户也可以自己实现，用户实现即**可实现成全局函数，也可实现成类的成员函数**，但是**一般情况下不需要实现，除非有特殊要求**。比如需要跟踪内存的申请与释放时。
>
> ```c++
> //自己实现operator new和operator delete函数
> 
> #include <cctype>
> #include <iostream>
> using namespace std;
> 
> void* operator new(size_t size, const char* strFileName, const char* strFuncName, size_t lineNo)
> {
>     void* p = ::operator new(size);//调用全局的new来进行动态内存空间的分配
>     cout<<strFileName<<"--"<<lineNo<<"-- "<<strFuncName<<" new:"<<size<<" "<<p<<endl;
>     return p;
> 
> }
> 
> void operator delete(void* p, const char* strFileName, const char* strFuncName, size_t lineNo)
> {
>     cout<<strFileName<<"--"<<lineNo<<"-- "<<strFuncName<<" delete:"<<p<<endl;
>     ::operator delete(p);//调用全局的delete来进行动态内存空间的删除
> 
> }
> 
> #define _DEBUG 1
> #ifdef _DEBUG
> #define new new(__FILE__, __FUNCTION__, __LINE__)
> #define delete(p) operator delete(p, __FILE__, __FUNCTION__, __LINE__)
> #endif
> 
> int main()
> {
>     int* p = new int;
>     delete(p);
>     return 0;
> }
> ```
>
> 输出结果：
>
> ``` c++
> operatorNewAndDelete.cpp--30-- main new:4 0x144cc20
> 
> operatorNewAndDelete.cpp--31-- main delete:0x144cc20
> 
> ```
>
> 



## 5. new和delete的实现原理

### 5.1 内置类型

> 如果申请的是内置类型的空间，new和malloc，delete和free基本类似，不同的地方是：new和delete申请和释放的是单个元素的空间，new[]和delete[]申请和释放的是连续空间，而且new在申请失败时会抛异常，malloc会返回NULL。



### 5.2 自定义类型

> - new的实现原理
>   1. 调用operator new函数申请空间
>   2. 在申请的空间上执行构造函数，完成对象的构造
> - delete的实现原理
>   1. 在空间上执行析构函数，完成对象中资源的清理工作
>   2. 调用operator delete函数释放对象的空间
> - new T[N]的原理
>   1. 调用operator new[]函数，在operator new[]中实际调用operator new函数完成N个对象空间的申请
>   2. 在申请的空间上执行N次构造函数
> - delete[]的原理
>   1. 在释放的对象空间上执行N次析构函数，完成N个对象中资源的处理
>   2. 调用operator delete[]释放空间，实际在operator delete[]中调用operator delete来释放空间



## 6. 定位new表达式

> **定位new表达式**是在**已分配**的**原始内存空间**中**调用构造函数** **初始化一个对象**
>
> **使用格式：**
> **new （place_address）type**或者**new （place_address）type（initializer -list）**
>
> place_address 必须是一个指针，initializer -list是类型的初始化列表
>
> **使用场景：**
>
> 定位new表达式在实际中一般是配合**内存池**使用，因为**内存池**分配出来的**内存没有初始化**。所以如果是自定义类型的对象，需要使用new的定位表达式进行显式的调用构造函数初始化。
>
> ```c++
> //定位new表达式
> 
> #include <cstdlib>
> #include <iostream>
> using namespace std;
> 
> class Test
> {
> public:
>   Test (int a = 0)
>     : _data(a)
>   {
>     cout << _data << "Test():" << this << endl;
>   }
> 
>   ~Test ()
>   {
>     cout << "~Test():" << this << endl;
>   }
> 
> private:
>   int _data;
> };
> 
> int main()
> {
>   Test* ptr = (Test*)malloc(sizeof(Test));
>   
>   //定位new表达式,调用Test构造函数
>   new(ptr)Test(13);
> 
>   return 0;
> }
> ```
>
> ```c++
> 输出结果：
> 13Test():0x13b2c20
> ```



### 内存池

> **内存池是一种分配方式**，通常我们使用**malloc，new**等API分配内存，这样的缺点在于：由于所申请的内存块大小不定，当频繁使用时会**造成**大量的**内存碎片**并进而**降低性能**。
>
> - 内存池则是在真正使用内存之前，先申请分配一定数量的、大小相等(一般情况下)的内存块留作备用。当有新的内存需求时，就从内存池中分出一部分内存块，若内存块不够再继续申请新的内存。这样做的一个显著优点是，使得内存分配效率得到提升。 



## 7. 常见面试题

### 7.1 malloc、free和new、delete的区别

> 共同点：
>
> ​	都是从堆上申请空间，并且需要用户手动释放
>
> 不同点：
>
> 1. **malloc和free**是**函数**，而**new和delete**是**操作符**
> 2. **malloc**申请的**空间不能初始化**，**new**可以**初始化**
> 3. **malloc申请空间**时，需要手**动计算空间大小并且传递**，**new**只需要其后**跟上空间类型的**即可
> 4. **malloc**申请的**返回值为void***，在使用时必须要进行**强转**，new不需要，因为**new**后面**跟的是空间的类型**
> 5. **malloc申请空间失败**时，**返回值是NULL**，因此必须进行**判空处理**，new不需要，但是**new需要捕获异常**
> 6. **malloc、free**只能**申请内置类型**的空间，**不能申请自定义类型**的空间，因为其**不会调用构造函数与析构函数** **（malloc可以与定位new表达式连用申请自定义类型的空间）**
> 7. **malloc**申请的**空间 ** **一定在堆上**，**new不一定**，因为**operator new函数可以重新实现**
> 8. **new、delete**比malloc、free的**效率低**一点，因为new、delete底层**封装了malloc、free**



### 7.2 请设计一个类，该类只能在堆上创建空间

> - 方法一：构造函数私有化
>   - 将类的构造函数私有化，拷贝构造函数声明成私有，防止别人调用拷贝构造函数，在栈上生成对象
>   - 提供一个静态的成员函数，在该静态的成员函数内部完成在堆上开辟空间
>
> ``` c++
> //只能从堆上开辟对象
> //必须把构造函数，拷贝构造函数以及赋值运算符重载都给封起来（即私有化）
> 
> #include <iostream>
> using namespace std;
> 
> class HeapType
> {
> public:
>   //静态成员函数没有this
>   static HeapType* GetHeapObject()
>   {
>     return new HeapType;
>   }
> 
> private:
>   HeapType () //构造函数初始化
>   {
> 
>   }
>   
>   //只声明不实现，因为实现可能很麻烦，而你本身不需要
>   //只声明为私有
>   //(声明成公有或私有编译器编译器都可能在类外给你实现)
>   //HeapType (const HeapType& ht);
>   HeapType (const HeapType& ht) = delete;//声明函数但是不需要实现该函数
>   //HeapType (const HeapType& ht)//拷贝构造函数私有化
>   //{}
> };
> 
> int main()
> {
> 
>   return 0;
> }
> ```



### 7.3 请设计一个类，该类只能在栈上创建对象

> ``` c++
> //只能从栈上开辟对象
> //每次调用构造函数开辟对象
> 
> #include <iostream>
> using namespace std;
> 
> class StackType
> {
> public:
>   static StackType GetSatckObject ()
>   {
>     StackType obj;
>     //不会返回obj对象，因为obj是局部变量
>     //返回的话就会调用拷贝构造函数
>     return obj;
>   }
> 
>   void Print ()
>   {
>     cout << "Print():" << this << endl;
>   }
> 
> private:
>   StackType ()//构造函数私有化
>   {
> 
>   }
> };
> 
> int main()
> {
>   StackType::GetSatckObject();//匿名对象
>   
>   StackType obj = StackType::GetSatckObject();//将匿名对象给一个对象
>   obj.Print();
> 
>   return 0;
> }
> ```
>
>  
>
> ``` c++
> //只能从栈上开辟对象
> //只需要为该类定制一个operator new和operator delete就可以了
> 
> #include <iostream>
> using namespace std;
> 
> class StackType
> {
> public:
>   //不封构造函数
>   StackType ()
>   {
> 
>   }
> 
>   void Print ()
>   {
>     cout << "Print():" << this << endl;
>   }
> 
> private:
>   //为该类定制一个operator new和operator delete
>   void* operator new (size_t size) = delete;
>   void operator delete (void* p) = delete;
> };
> 
> int main()
> {
>   
>   StackType obj;//将匿名对象给一个对象
>   obj.Print();
> 
>   return 0;
> }
> ```



### 7.4 单例模式

> #### 设计模式： 
>
> ​	设计模式是一套被反复使用，多数人知晓的，经过分类的，代码设计经验的总结
>
> #### 目的：
>
> ​	为了代码的可重用性，让代码更容易被他人理解，保证代码的可靠性。设计模式使代码编写真正工程化。
>
> #### 单例模式：
>
> ​	一个类只能创建一个对象，即单例模式，该模式可以保证系统中该类只有一个实例，并提供一个访问它的全局访问点，该实例被所有程序模块共享。
>
> 单例模式有两种实现方式：
>
> - 饿汉模式
>
>   就是说一开始就把这一个对象给你创建出来不管你用不用，也就是先吃饱
>
> ``` c++
> /单例模式：只有一个对象
> //饿汉模式：饿(一上来就吃)
> //直接把对象创建出来
> 
> #include <iostream>
> using namespace std;
> 
> //类内都是声明
> class Singleton
> {
> public:
>   static Singleton* GetInstance()
>   {
>     return &_sInstance;
>   }
>   
>   void Print()
>   {
>     cout << "Print():" << this << endl;
>   }
> 
> private:
>   Singleton()//构造函数私有化
>   {}
> 
>   //加上delete是为了防止友元
>   //即在类外对这个函数进行定义(实现)
>   Singleton(const Singleton& sl) = delete;//拷贝构造函数初始化
>   Singleton& operator=(const Singleton& d) = delete;//赋值运算符重载
>   static Singleton _sInstance;//声明一个对象，类外定义
> };
> 
> Singleton  Singleton::_sInstance;//定义(创建)这个对象
> 
> int main()
> {
>   Singleton* b = Singleton::GetInstance();
>   b->Print();
>   return 0;
> }
> ```
>
> - 懒汉模式
>
>   就是需要的时候在创建这一个对象
>
> ``` c++
> //单例模式：只有一个对象
> //懒汉模式：第一次使用对象创建对象
> 
> #include <iostream>
> #include <mutex>
> using namespace std;
> 
> //类内都是声明
> class Singleton
> {
> public:
>   static Singleton* GetInstance()
>   {
>     //二重锁，防止每一个线程过来的时候，都要加锁，解锁，浪费资源
>     if (_spInstance == nullptr)
>     {
>       //添加锁是一重锁，只是每次让一个线程执行该段代码
>       _smutex.lock();
>       if (_spInstance == nullptr)
>       {
>         _spInstance = new Singleton;
>       }
>       _smutex.unlock();
>     }
> 
>     return _spInstance;
>   }
>   
>   void Print()
>   {
>     cout << "Print():" << this << endl;
>   }
> 
>   //内部嵌套一个可以清理开辟的空间的类
>   class CGarbo
>   {
>   public:
>     ~CGarbo()
>     {
>       if (_spInstance != nullptr)
>       {
>         delete _spInstance;
>       }
>     }
>   };
> 
> private:
>   Singleton()//构造函数私有化
>   {}
> 
>   //加上delete是为了防止友元
>   //即在类外对这个函数进行定义(实现)
>   Singleton(const Singleton& sl) = delete;//拷贝构造函数初始化
>   Singleton& operator=(const Singleton& d) = delete;//赋值运算符重载
>   static CGarbo _sGarbo;
>   static Singleton* _spInstance;//声明一个对象的指针，类外定义
>   static mutex _smutex;
> };
> 
> Singleton*  Singleton::_spInstance = nullptr;//定义(创建)这个对象
> Singleton::CGarbo Singleton::_sGarbo;//在进程结束时，这个对象也会销毁，调用析构函数，释放堆空间
> mutex Singleton::_smutex;
> 
> int main()
> {
>   Singleton* b = Singleton::GetInstance();
>   b->Print();
>   return 0;
> }
> ```
>
> 



### 7.5 内存泄露

#### 7.5.1 什么是内存泄露

> **内存泄露是指因为疏忽或错误造成程序未能释放已经不再使用的内存的情况，内存泄露并不是指内存在物理上的消失，而是应用程序分配某段内存后，因为设计错误，失去了对该段内存的控制，因而造成了内存的浪费。**
>
> ```c++
> void Test
> {
> 	//1.内存申请了空间忘记释放
> 	int* p1 = (int*)malloc(sizeof(int));
> 	int* p2 = new int;
> 	
> 	//2.异常安全问题
> 	int* p3 = new int[10];
> 	
> 	Func();//这里Func函数抛异常导致delete[] p3未执行，p3未被释放
> 	
> 	delete[] p3;
> }
> ```
>
>



#### 7.5.2 内存泄露的分类

> C/C++程序中一般我们关心两个方面的内存泄露：
>
> - 堆内存泄露（Heap Leak）
>   - 堆内存指的是程序执行中依据需要分配通过malloc、calloc、realloc、new等从堆中分配的一块内存，用完后必须通过调用相应的free或者delete删掉。假设程序的设计错误导致这部分内存没有被释放，那么以后这部分空间将不能在被使用，就会产生Heap Leak。
> - 系统资源泄露
>   - 指程序使用系统分配的资源，比如方套接字、文件描述符、管道等没有使用对应的函数释放掉，导致系统资源的浪费，严重可导致系统效能减少，系统执行不稳定。



#### 7.5.3 如何避免内存泄露

> - 工程前期良好的设计规范，养成良好的习惯，申请的内存空间记着匹配的去释放。ps：这个理想状态。但是如果碰上了异常时，就算注意释放了，可能还会出问题。需要下一条智能指针来管理才有保证
> - 采用RAII思想或者智能指针来管理资源
> - 有些公司内部规范使用内部实现的私有内存管理库，这套库自带内存泄露检测功能选项
> - 出问题了使用内存泄露工具检测。ps：不过很多工具都不靠谱，或者收费昂贵
>
> 总结一下：
>
> 内存泄露非常常见，解决问题的两种方案：
>
> - 1. 事前预防性。如智能指针等
> - 2. 事后查错型。如泄露检测工具



## 扩展：互斥锁(mutex lock)【C++】

> 在编程引入了对象互斥锁的概念，来保证共享数据操作的完整性。每个对象都对应于可称为“互斥锁”的标记，这个标记用来保证在任一时刻，只能有一个线程访问该对象。
>
> ```  c++
> #include <mutex>
> 
> Member functions
> lock 	locks the mutex,blocks if the mutex is not available
> try_lock	tries to lock the mutex,returns if the mutex is not available
> unlock  	unlocks the mutex
> ```
>
> 

