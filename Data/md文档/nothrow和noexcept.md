# nothrow和noexcept

## 1. 使用std::nothrow

new (std::nothrow) 在分配内存失败的时候会返回一个空指针，而不是触发std::bad_alloc，可以方便进行NULL检查

``` c++
#include <iostream>

int main()
{
	char* p = NULL;
	int i = 0;//记录申请多少内存

	do
	{
		//每次申请1M
		p = new (std::nothrow) char[1024 * 1024];
		i++;
	} while (p);

	if (NULL == p)
	{
		std::cout << "new " << i - 1 << "M memory\n" << "第 " << i << "次内存分配失败" << std::endl;
	}
	char* ptr = nullptr;

	ptr = new (std::nothrow) char[2047 * 1024 * 1024];
	if (ptr == nullptr)
	{
		std::cout << "new (std::nothrow) char[2047M] error" << std::endl;
	}
	else
	{
		std::cout << "new (std::nothrow) char[2047M] sucessed" << std::endl;
	}


	return 0;
}
```

插图：nothrow

![](C:\Users\0\Pictures\C++\test nothrow.png)

可以看到在进行申请大的内存的时候申请不到的话，就会返回一个nullptr，从而知道new失败了，而不是抛异常，直接让程序退出

从此也可以看到，对于**堆上的内存一般就是1900M左右**



# 如何让函数不抛出异常

## noexcept修饰符

noexcept修饰符可以修饰函数，不让函数抛出异常，如果函数抛出异常程序就直接终止

作用：防止程序不该出现异常的地方出现异常是就终止函数。

对于delete函数，析构函数默认都是noexcept

``` C++
#include <iostream>

void Exception() noexcept 
{
    throw 1;
}

int main()
{
    Exception();
    return 0;
}
```

结果：

![](C:\Users\0\Pictures\C++\noexcept.png)

对于该函数声明为不可以抛出异常但是却抛出了异常，terminate调用中断，直接终止程序

