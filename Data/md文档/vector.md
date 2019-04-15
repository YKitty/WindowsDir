# vector

> - vector是表示可变大小数组的序列容器
> - vector采用连续存储空间来存储元素。所以可以采用下标的方式vector的元素进行访问，和数组一样的高效。但是其又不像数组，它的大小是可以动态改变的，而且它的大小会被容器自己处理
> - 本质：对于vector使用动态分配数组来存储其元素。当新元素插入到数组中时，如果空间不够的话，就会开辟空间。
> - vector分配空间策略：vector会分配一些额外的空间以适应可能的增长，储存空间比实际要存储的空间更大。
> - 与其他的动态序列容器相比（deques，lists and forward_lists）：vector在访问元素时很高效，在末尾添加和删除元素相对高效。对于其他不在末尾的删除和插入操作，效率更低。



## #vector如何使用

**首先要学会对于vector在C++程序里面，如何来使用**

> ```c++
> //第一种使用方法：
> //这种是只在使用vector的时候采用
> std::vector;
> 
> //第二种使用方法：
> //这是将命名空间std进行全部的展开
> using namespace std;
> 
> //第三种使用方法：
> //这是只将命名空间std里面的vector展开使用
> using std::vector;
> ```
>
> 可以看出对于vector这个**容器**，在**命名空间std**中包含着，所以要使用vector必须使用std命名空间



## #对于成员函数该如何使用

> **必须要包含头文件vector**



## #成员函数

----

## 1. vector的构造函数

> ``` c++
> //无参构造
> vector ();
> 
> //构造并初始化n个val
> vector (size_type n, const value_type& val = value_type());
> 
> //使用迭代器的范围构造
> vector (Inputiterator first, Inputiterator last);
> 
> //拷贝构造
> vector (const vector& x);
> ```
>
> 



## 2. vector迭代器

> ``` c++
> //获取第一个数据位置的iterator
> begin (); 
> 
> //获取最后一个数据的下一个位置的iterator
> end ();
> 
> //获取最后一个数据位置的reverse_iterator
> rbegin ();
> 
> //获取第一个数据前一个位置的reverse_iterator
> rend ();
> 
> //获取第一个数据位置的const_iterator
> cbegin ();
> 
> //获取最后一个数据下一个未知的const_iterator
> cend ();
> ```
>
> 



## 3. vector容量

> ``` c++
> //获取数据个数
> size ();
> 
> //获取数据容量
> capacity ();
> 
> //判断是否为空
> empty ();
> 
> //改变vector的size，如果大于原先的size，后面填充val
> resize (size_type n, value_type val = val_type());
> 
> //改变vector的容量
> reserve (size_type n);
> ```
>
> - 对于capacity这个开辟容量在不同的编译器下每一次开辟的大小是不一样的。vs下是1.5倍增长的，g++是按照2倍增长的。vs是PJ版本的，g++是SGI版本的
>
> - reserve是只负责开辟空间的，如果知道了需要用多少空间的话，reserve可以缓解vector增容的代价缺陷问题
>
> - resize在开辟空间的时候还会进行初始化，影响size
>
>   



## 4. vector的增删改查 

> ``` c++
> //尾插
> void push_back (const value_type & val);
> 
> //尾删
> void pop_back ();
> 
> //查找（这个是算法模块实现的，不是vector的成员接口）
> Inputiterator find(Inputiterator first, Inputiterator last, const T& val);
> 
> //在position前面插入val
> iterator insert (iterator position, const value_type& val);
> 
> //删除position位置的数据
> iterator erase(iterator position);
> 
> //交换两个vector的数据空间
> void swap(vector& x);
> 
> //像数组一样访问
> reference operator[] (size_type n);
> ```
>
>  



## 迭代器失效

> - 对于迭代器如何失效呢。其实就是**iterator指针指向的位置的数据已经被释放了，或者该指针已经失效了**
>
>   - iterator指向的位置数据已经被释放了
>
>   - 发生的例子：
>
>   - ``` c++
>     #include <iostream>
>     #include <vector>
>     
>     int main()
>     {
>         std::vector<int> v;
>         v.push_back(1);
>         v.push_back(2);
>         v.push_back(3);
>     	std::vector<int>::iterator pos = find(v.begin(), v.end(), 3);
>         //删除pos位置的数据，导致pos迭代器失效
>         v.erase(pos);
>         std::cout << *pos << '\n';
>         
>         //在pos位置插入数据导致迭代器失效
>         //增容后，原先的空间已经被释放了
>         v.insert(pos, 4);
>         //出错访问一个，已经被释放的空间
>         std::cout << *pos << '\n';
>         return 0;
>     }
>     ```
>
>   - 
>
>     - 运行环境：g++，按二倍增容的
>     - 对于一个vector初始化了四个数据，那么下一次要插入数据的时候，就会产生增容
>     - 如果我们使用insert插入一个数据之后，再次使用insert刚才里面的参数，就会产生内存访问出错的情况，因为开辟空间的时候，旧的空间要进行释放，导致丢的iterator指向的是一个已经失效的位置
>
>   - 如果删除一个位置的数据之后，再次使用以前的迭代器访问数据的时候，就会出现错误。
>
> - 常见的迭代器失效的场景
>
> ``` c++
> int array[5] = { 1, 2, 3, 4, 5 };
>   std::vector<int> v(array, array + 4);
>   for (auto e : v)
>   {
>     std::cout << e << '\n';
>   }
> 
>   std::vector<int>::iterator it = v.begin();
>   //导致迭代器失效
>   //while (it != v.end())
>   //{
>   //    if (*it % 2 == 0)
>   //        v.erase(it);
>   //    else
>   //        it++;
>   //}
>   
>   //更新迭代器，不会失效
>   while (it != v.end())
>   {
>     if (*it % 2 == 0)
>     {
>       it = v.erase(it);
>     }
>     else 
>     {
>       it++;
>     }
>   }
>   for (auto e : v)
>   {
>     std::cout << e << '\n';
>   }
> 
> ```
>
> 