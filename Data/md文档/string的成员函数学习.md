# string的学习

----

## #string如何使用

**首先要学会对于string在C++程序里面，如何来使用**

> ``` c++
> //第一种使用方法：
> //这种是只在使用string的时候采用
> std::string;
> 
> //第二种使用方法：
> //这是将命名空间std进行全部的展开
> using namespace std;
> 
> //第三种使用方法：
> //这是只将命名空间std里面的string展开使用
> using std::string;
> ```
>
> 可以看出对于**string**这个**容器**，在**命名空间std**中包含着，所以要使用string必须使用std命名空间

## #对于成员函数该如何使用

> **必须要包含头文件string**

## #成员函数

## 1. operator=：字符串赋值

> **operator=**是**赋值运算符**，有着**三种重载**形式
>
> ``` c++
> //对于一个引用
> string& operator=(const string& str);
> 
> //对于c语言的字符串
> string& operator=(const char* str);
> 
> //对于一个字符
> string& operator=(const char);
> ```
>
> **【解释】**:
>
> ​	**字符串赋值：**为字符串分配一个新值，替换当前内容
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> using namespace std;
> 
> int main()
> {
>   string s1, s2, s3;
>   s1 = "hello world";//字符串
>   s2 = 'x';//字符
>   s3 = s2;//引用
> 
>   //注意
>   //string s = "hello world";//这是进行拷贝构造，不是运用了string容器的赋值运算符
> 
>   cout << s1 << endl;
>   cout << s2 << endl;
>   cout << s3 << endl;
>   return 0;
> }
> ```



## 2. Iterators：迭代器（指针）

### 2.1 begin：返回迭代器到字符串的开头

> **begin**是**返回到字符串开头的迭代器**，有着**两种重载**形式
>
> ``` c++
> //非const类型的迭代器
> iterator begin();
> 
> //const类型的迭代器
> const_iterator begin() const;
> 
> 返回值：
> 	如果字符串对象是const限定的，则该函数返回一个const_iterator，否则，返回的是一个iterator
> 	成员类型iterator和const_iterator随机访问迭代器类型（分别指向一个字符和一个const字符）
> ```
>
> **【作用】：**
>
> ​	**返回迭代器到开头：**返回迭代器的指针到字符串的开头
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str("hello world");
>   //it相当于是一个char*指针
>   for (std::string::iterator it = str.begin(); it != str.end(); it++)
>   {
>     std::cout << *it << " ";
>   }
>   std::cout << '\n';
>   return 0;
> }
> ```
>



### 2.2 end：返回迭代器到字符串的结尾

> **end**是**返回到字符串结尾的迭代器**，有着**两种重载**形式
>
> ```c++
> //非const类型的迭代器
> iterator end();
> 
> //const类型的迭代器
> const_iterator end() const;
> 
> 返回值：
> 	如果字符串对象是const限定的，则该函数返回一个const_iterator，否则，返回的是一个iterator
> 	成员类型iterator和const_iterator随机访问迭代器类型（分别指向一个字符和一个const字符）
> ```
>
> **【作用】：**
>
> ​	**返回迭代器到结尾：**
>
> ​	返回迭代器的指针到字符串的结尾。该尾部是最后一个字符的下一个位置，也就是该迭代器不可以被解引用。
>
> ​	如果该对象是一个空的字符串的话，那么该函数返回与string::begin()相同的值



### 2.3 rbegin：返回反向迭代器以反向开始 

> **rbegin**是**返回反向迭代器以反向开始**，有着两种重载形式
>
> ``` c++
> //非const类型的反向迭代器
> reverse_iterator rbegin();
> 
> //const类型的反向迭代器
> const_reverse_iterator rbegin() const;
> 
> 返回值：
> 	如果字符串对象是const限定的，则该函数返回一个const_reverse_iterator否则返回reverse_iterator
> 	成员类型const_reverse_iterator和reverse_iterator是反向随机访问迭代器类型（分别指向一个字符和一个const字符）
> ```
>
> **【作用】：**
>
> ​	**返回反向迭代器以反向开始**
>
> ​	返回指向字符串最后一个字符的反向迭代器。（即，它的反向开头）
>
> ​	反向迭代器向后迭代：增加他们将他们移向字符串的开头
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str = "hello world";
>   for (std::string::reverse_iterator it = str.rbegin(); it != str.rend(); it++)
>   {
>     std::cout << *it << " ";
>   }
>   std::cout << '\n';
>   return 0;
> }
> ```



### 2.4 rend：返回反向迭代器以反向结束

> **rend**是**返回反向迭代器以反向结束**，有着两种重载形式
>
> ```c++
> //非const类型的反向迭代器
> reverse_iterator rend();
> 
> //const类型的反向迭代器
> const_reverse_iterator rend() const;
> 
> 返回值：
> 	如果字符串对象是const限定的，则该函数返回一个const_reverse_iterator否则返回reverse_iterator
> 	成员类型const_reverse_iterator和reverse_iterator是反向随机访问迭代器类型（分别指向一个字符和一个const字符）
> ```
>
> **【作用】：**
>
> ​	**返回反向迭代器以反向结束**
>
> ​	返回指向字符串第一个字符前面的理论字符的反向迭代器。（被认为是它的反向结束）



## 3. Capacity：容量

### 3.1 size：返回字符串的长度(size == length)

> ``` c++
> //const类型的成员函数，不能改变this指向的成员变量，除非将该成员变量使用mutable修饰
> size_t size() const;
> ```
>
> **【作用】：**
>
> ​	**以字节为单位返回字符串的长度**
>
> ​	返回字符串的实际容量的字节数，不一定等于其存储容量。返回的是size_t(unsigned int)类型无符号的整数类型
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str("hello world");
>   std::cout << "the size of str: " << str.size() << "byte!\n";
>   std::cout << "the length of str: " << str.length() << "byte!\n";
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> the size of str: 11byte!
> the length of str: 11byte!
> ```



### 3.2 max_size：字符串所能达到的最大长度

> ``` c++
> //返回字符串所能达到的最大长度，是由系统决定的
> size_t max_size() const;
> ```
>
> **【作用】：**
>
> ​	**返回字符串所能达到的最大长度**
>
> ​	这是由于已知的系统或者库实现限制的，字符串可以达到的最大长度，但不保证该对象能够达到该长度
>
> ​	返回的是size_t类型的数，无符号的整数（unsigned int）
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str("hello world");
>   std::cout << "max_size: " << str.max_size() << "bytes \n";
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> max_size: 4611686018427387897bytes 
> ```



### 3.3 capacity：返回当前为字符串分配的储存空间的大小

> ``` c++
> //返回当前为字符串分配的储存空间的大小，以字节为单位
> size_t capacity() const;
> ```
>
> **【作用】：**
>
> ​	**返回为当前字符串已分配的字节的大小**
>
> ​	此容量不一定等于字符串长度。他可以是相等或者更大，具有额外的空间。
>
> ​	注意：当此容量用完并且需要更多的空间的时候由对象自动扩展（重新分配储存空间）
>
> ​	返回的类型是size_t类型，无符号的整数类型（unsigned int）
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str("hello world");
>   std::cout << "the capacity for str: " << str.capacity() << "bytes\n";
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> the capacity for str: 15bytes
> //对于"hello world"是11个字节，但是容量却是15个字节
> ```



### 3.4 resize：重新调整字符串的大小

> 有着**两种重载**形式：
>
> ``` c++
> void resize(size_t n);
> void resize(size_t n, char n);
> ```
>
> **【作用】：**
>
> ​	**调整字符串的大小**
>
> ​	将字符串的长度调整为n个字符的长度。
>
> ​	如果**当前字符串的长度大于n**的话，则将**原先的字符串缩减到n个字符的长度**，并且在后面加上'\0'
>
> ​	如果**当前字符串的长度小于n**的话
>
> ​	    第一种：使用**单个参数**的函数（   **void resize(size_t n)** ），那就对于原先的字符串在后面**添加空字符（null charactets）**
>
> ​	    第二种：使用**两个参数**的函数（  **void resize(size_t n, char c)** ），那就给原先的字符串在后面**添加上字符c**
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str1("hello world");//11
>   std::string str2("hello world");
>   std::string str3("hello world");
>   
>   std::cout << str1 << '\n';
>   str1.resize(3);
>   std::cout << str1 << '\n';
> 
>   std::cout << str2 << '\n';
>   str2.resize(15);
>   std::cout << str2 << '\n';
> 
>   std::cout << str3 << '\n';
>   str3.resize(15, 'h');
>   std::cout << str3 << '\n';
> 
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> hello world//old.str1
> hel//new.str1
> hello world//old.str2
> hello world//new.str2（在原先的字符串后面不上空字符）
> hello world///old.str3
> hello worldhhhh//new.str3（在原先的字符串后面补上字符‘c’）
> ```



### 3.5 reserve：请求更改字符串的容量(只可增大)

> ``` c++
> //缺省成员函数，如果不传值的话，默认将容量改为0
> void reserve(size_t n = 0);
> ```
>
> **【作用】：**
>
> ​	**可以看出对于reserve函数，只有将其的capacity增加的时候才可以使用，将其调整为n个字符的大小；对于其他的情况，容器会自己自由的优化，并使字符串的容量大于n，或者不改变字符串的容量**
>
> ​	**生成的字符串的容量可能等于或者大于n，这是容器自己计划的字符串的长度**
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str1("hello world");
>   std::string str2("hello world");
>   std::string str3("hello world");
>  
>   std::cout << str1 << '\n';
>   std::cout << "the capacity of str1: " << str1.capacity() << '\n';
>   str1.reserve(4);
>   std::cout << str1 << '\n';
>   std::cout << "the capacity of str1: " << str1.capacity() << '\n';
>   
>   std::cout << str2 << '\n';
>   std::cout << "the capacity of str2: " << str2.capacity() << '\n';
>   str2.reserve(20);
>   std::cout << str2 << '\n';
>   std::cout << "the capacity of str2: " << str2.capacity() << '\n';
>   
>   
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> hello world
> the capacity of str1: 11
> hello world
> the capacity of str1: 11
> hello world
> the capacity of str2: 11
> hello world
> the capacity of str2: 22
> ```



### 3.6 clear：删除字符串，将该字符串变为一个空的字符串

> ``` c++
> //清空字符串
> void clear();
> ```
>
> **【作用】：**
>
> ​	**清空字符串的内容，将字符串变为空字符串**
>
> **【注意】：**
>
> ​	**对于该成员函数，没有参数，没有返回值**
>
> 例1：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str("hello world");
>   std::cout << str << '\n';
>   str.clear();
>   std::cout << str << '\n';
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> hello world
> 
> //对于上面的空行也是输出，表示对于str字符串已经进行删除了
> ```
>
> 
>
> 例2：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
> 	char c;
> 	std::string str;
> 	std::cout << "Please type some lines of text. Enter a dot (.) to finish:\n";
> 	do {
> 		c = std::cin.get();//每次只能给c中赋一个字符
> 		str += c;//这是给str后面追加字符。如果每次都是从最开始输出，表示clear成员函数起作用了
> 		if (c == '\n')
> 		{
> 			std::cout << str;
> 			str.clear();
> 		}
> 	} while (c != '.');
> 	return 0;
> }
> ```





### 3.7 empty：检测该字符串是不是空字符串

> ``` c++
> //布尔类型的函数，使用const进行修饰表示不能修改成员变量
> bool empty() const;
> ```
>
> **【作用】：**
>
> ​	**测试字符串是否为空**
>
> ​	返回字符串是否为空
>
> ​	此函数不会以任何方式修改字符串的内容
>
> **【返回】：**
>
> ​	如果字符串的长度为0，返回真，否则返回假
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string context;
>   std::string line;
>   do
>   {
>     getline(std::cin, line);
>     context += line + '\n';
>   }while (!line.empty());//直到line为空
>   std::cout << context;
>   return 0;
> }
> ```
>
> 测试代码：解释
>
> ​	该程序读取用户写入的数据到字符串内容中，直到输入空行，也就是字符串为空的时候。



## 4. Element access（元素访问） 

### 4.1 operator[]：获取字符串的字符(可以获取'\0')

> 该成员函数具有两个重载形式：
>
> ``` c++
> //返回pos下标出字符的引用
> char& operator[](size_t pos);
> 
> //使用const修饰该成员函数表示改类中的成员变量不可以被修改
> const char& operator[](size_t pos) const;
> ```
>
> **【作用】**
>
> ​	**获取字符串的字符**
>
> ​	返回对字符串以pos为下标处的字符的引用
>
> **【注意】**
>
> ​	**如果pos等于字符串长度的话，并且字符串是const限定的话，，则该函数返回对字符'\0'的引用**
>
> **【返回值】**
>
> ​	**如果字符串是const限定的话，则返回const char&，否则返回一个char&**
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str("hello world");
>   
>   //记得对于string的成员函数的返回值都是size_t类型
>   for (size_t i = 0; i < str.size(); i++)  
>   {
>     std::cout << str[i] << " ";
>   }
>   std::cout << '\n';
> 
>   return 0;
> }
> ```
>
> 输出:
>
> ``` c++
> h e l l o   w o r l d 
> ```

### 4.2 at：获取字符串中的字符(只能获取有效位置字符)

> 该函数具有两种重载形式：
>
> ``` c++
> //返回非const字符串中的字符
> char& at(size_t pos);
> 
> //返回const字符串中的字符
> const char& at(size_t pos) const;
> ```
>
> **【作用】：**
>
> ​	**返回字符串中的字符**
>
> ​	该函数会返回字符串中pos位置字符的引用，并且自动检查pos是不是字符串的有效位置，即pos是否小于字符串的长度，如果不是有效位置的话，则会抛出out_of_range异常。
>
> **【返回值】：**
>
> ​	如果该字符串是const字符串，则返回const char&，否则返回char&
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str("hello world");
>   for (size_t i = 0; i <= str.size(); i++)
>   {
>     std::cout << str.at(i) << " ";
>   }
>   std::cout << '\n';
> 
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> terminate called after throwing an instance of 'std::out_of_range'
>   what():  basic_string::at: __n (which is 11) >= this->size() (which is 11)
> h e l l o   w o r l d Aborted (core dumped)
> ```
>
> **【注意】：**
>
> ​	对于访问字符串中的位置的话，就会抛出异常



## 5. Modifiers：修饰符

### 5.1 operator+=：对字符串进行追加

> 对于该成员函数具有三种重载形式：
>
> ``` c++
> //string
> //在原先的字符串后面追加一个字符串对象
> string& operator+=(const string& str);
> 
> //c-string
> //在原先的字符串后面追加一个c字符串
> string& operator+=(const char* str);
> 
> //character
> //在原先的字符串后面追加一个字符
> string& operator+=(const char c);
> ```
>
> **【作用】：**
>
> ​	**追加字符串**
>
> ​	通过在原先字符串的末尾追加字符串以来扩展字符串
>
> **【返回值】：**
>
> ​	***this**（表示返回当前对象的引用）
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str1("hello");
>   std::string str2(" world!");
> 
>   str1 += str2; //string
>   str1 += "I come!"; //c-string 
>   str1 += '\n';//character
> 
>   std::cout << str1; 
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> hello world!I come!
> ```



### 5.2 append：追加字符串

> 该成员函数具有五个重载函数：
>
> ``` c++
> //string
> //在其后面追加字符串对象str
> string& append(const string& str);//string
> 
> //substring
> //在其后面追加字符串对象str的子串，从subpos处，向后追加sublen个字符,如果subpos大于字符串str的长度的话则会抛出out_of_range异常
> string& append(const string& str, size_t subpos, size_t sublen);//substring(子串)
> 
> //c-string
> //在其后面追加c字符串
> string& append(const char* str);//c-string
> 
> //buffer
> //在其后面追加字符数组str的前n个字符
> string& append(const char* str, size_t n);//buffer
> 
> //fill(填充)
> //在其后面追加n个连续的字符c
> string& append(size_t n, char c);//fill
> ```
>
> **【作用】**
>
> ​	**追加字符串**
>
> ​	在当前字符串的末尾追加字符串来扩展字符串
>
> **【返回值】**
>
> ​	***this**（表示返回当前对象的引用）
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str1("hello");
>   std::string str2("world!I come....");
> 
>   str1.append(str2);//string
>   str1.append(str2, 1, 2);//substring
>   str1.append("haha");//c-string 
>   str1.append("haha", 2);//buffer
>   str1.append(5, 'x');//fill
> 
>   std::cout << str1;
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> helloworld!I come....orhahahaxxxxx
> ```



### 5.3 push_back：在尾部插入一个字符 

> ``` c++
> //在尾部插入字符c
> void push_back(const char c);
> ```
>
> **【作用】：**
>
> ​	**给字符串追加字符**
>
> ​	在字符串的尾部插入字符c，使字符串的长度增加1
>
> **【返回值】：**
>
> ​	**无返回值**
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str("I love yo");
>   str.push_back('u');
>   std::cout << str << '\n';
> 
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> I love you
> ```
>
>



### 5.4 assign：重新给字符串赋值 

> 该成员函数有五个重载形式：
>
> ``` c++
> //string
> //将其内容替换为字符串对象str
> string& assign(const string& str);
> 
> //substring(子串)
> //将其内容替换为字符串对象str的子串，从subpos处，向后替换sublen个字符,如果subpos大于字符串str的长度的话则会抛出out_of_range异常
> string& assign(const string& str, size_t subpos, size_t sublen);
> 
> //c-string
> //将其内容替换为c字符串
> string& assign(const char* str);
> 
> //buffer
> //将其内容替换为字符数组str的前n个字符
> string& assign(const char* str, size_t n);
> 
> //fill
> //将其内容替换为n个连续的字符c
> string& assign(size_t n, char c);
> ```
>
> **【作用】：**
>
> ​	**替换字符串的内容**
>
> ​	为字符串分配一个新值，替换其内容
>
> **【返回值】：**
>
> ​	***this**（表示返回当前对象的引用）
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str1("hello world!");
>   std::string str2("I love you!");
> 
>   str1.assign(str2);
>   std::cout << str1 << '\n';//I love you!
> 
>   str1.assign(str1, 0, 5);
>   std::cout << str1 << '\n';//I lov
> 
>   str1.assign("hello world!");
>   std::cout << str1 << '\n';//hello world!
> 
>   str1.assign("hello world!", 5);
>   std::cout << str1 << '\n';//hello
> 
>   str1.assign(10, 'h');
>   std::cout << str1 << '\n';//hhhhhhhhhh
> 
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> I love you!
> I lov
> hello world!
> hello
> hhhhhhhhhh
> ```



### 5.5 insert：插入字符串

> 该成员函数具有五个重载形式：
>
> ``` c++
> //string
> //在pos位置处插入字符串对象str
> string& insert(size_t pos, const string& str);
> 
> //substring
> //在pos位置处插入字符串对象str的子串，从subpos处，向后替换sublen个字符,如果subpos大于字符串str的长度的话则会抛出out_of_range异常
> string& insert(size_t pos, const string& str, size_t subpos, size_t sublen);
> 
> //c-string
> //在pos位置处插入c字符串
> string& insert(size_t pos, const char* str);
> 
> //buffer
> //在pos位置处插入字符数组str的前n个字符
> string& insert(size_t pos, const char* str, size_t n);
> 
> //fill
> //在pos位置处插入n个连续的字符c
> string& insert(size_t pos, size_t n, char c);
> void insert(iterator it, size_t n, char c);
> //对于该迭代器不支持反向迭代器，因为反向迭代器的类型是reverse_iterator
> 
> //character
> //采用迭代器插入一个字符c
> iterator insert(iterator it, char c);
> ```
>
> **【作用】：**
>
> ​	**插入字符串**
>
> ​	在pos处插入字符串
>
> ​	如果pos大于字符串的长度话，就出抛出out_of_range异常
>
> **【返回值】：**
>
> ​	对于返回引用的，返回***this**（表示返回的当前对象的引用）
>
> ​	对于迭代器返回的话，返回的是刚开始插入的时候迭代器指向的位置
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str1("hello world!");
>   std::string str2("I love you!");
> 
>   str1.insert(0, str2);
>   std::cout << str1 << '\n';//I love you!hello world!
> 
>   str1.insert(str1.size(), str2, 0, std::string::npos);
>   std::cout << str1 << '\n';//I love you!hello world!I love you!
> 
>   str1.insert(str1.size(), "haha");
>   std::cout << str1 << '\n';//I love you!hello world!I love you!haha
> 
>   str2.insert(str2.size(), "haha", 2);
>   std::cout << str2 << '\n';//I love you!ha
> 
>   str2.insert(str2.size(), 2, 'X');
>   std::cout << str2 << '\n';//I love you!haXX
> 
>   str2.insert(str2.end(), 2, 'X');
>   std::cout << str2 << '\n';//I love you!haXXXX
>   
>   std::string::iterator it = str2.insert(str2.begin() + 1, 'F');
>   std::cout << *it << '\n';
> 
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> I love you!hello world!
> I love you!hello world!I love you!
> I love you!hello world!I love you!haha
> I love you!ha
> I love you!haXX
> I love you!haXXXX
> F
> ```



### 5.6 erase：对字符串进行删除

> 该成员函数有着三种重载形式：
>
> ``` c++
> //sequence
> //从字符中删除一个序列
> string& erase(size_t pos = 0, size_t len = npos);
> 
> //character
> //从字符串中删除一个字符，采用迭代器删除
> iterator erase(iterator it);
> 
> //range
> //从字符串中删除一个范围的字符串，采用迭代器删除，删除的是[frist, last)，不包含最后那个位置
> iterator erase(iterator first, iterator last);
> ```
>
> **【作用】**
>
> ​	**删除字符串**
>
> ​	删除字符串的一部分，减小字符串的长度
>
> **【返回值】**
>
> ​	对于返回字符串的引用的话，返回的是*this
>
> ​	对于返回的是iterator的话，返回的是第一个删除位置的删除后的字符，如果该位置没有字符的话，返回end()（即迭代器）
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str1("hello world!");
>   std::string str2("hellok world!");
>   std::string str3("hellok world!");
>   
>   std::cout << str1 << '\n';
>   str1.erase();//默认删除全部，因为该成员函数是一个缺省函数
>   std::cout << str1 << '\n';
> 
>   str2.erase(0, 1);//ellok world!
>   std::cout << str2 << '\n';
> 
>   std::string::iterator it = str2.erase(str2.begin() + 3);
>   std::cout << "*it: "<< *it << '\n' << "str2: " << str2 << '\n';//k  ellk world!
> 
>   str3.erase(str3.begin() + 1, str3.begin() + 5);
>   std::cout << str3 << '\n';//hk world!
> 
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> hello world!
> 
> ellok world!
> *it: k
> str2: ellk world!
> hk world!
> ```



### 5.7 replace：替换字符串部分值

> 该成员函数具有九个重载的函数
>
> ``` c++
> //string
> //从pos这个位置开始删除该对象的len个字符，然后将其替换为str这个字符串对象
> string& replace(size_t pos, size_t len, const string& str);
> //将迭代器i1的这个位置到i2的这个位置的字符，替换为str这个字符串对象
> string& replace(iterator i1, iterator i2, const string& str);
> 
> //substring
> //将pos开始的这个位置的len个字符，替换为str这个字符串对象中的从subpos开始的sublen个字符
> string& replace(size_t pos, size_t len, const string& str, size_t subpos,size_t sublen);
> 
> //c-string
> //从pos这个位置开始删除该对象的len个字符，然后将其替换为str这个c字符串
> string& replace(size_t pos, size_t len, const char* str);
> //将迭代器i1的这个位置到i2的这个位置的字符，替换为str这个c字符串
> string& replace(iterator i1, iterator i2, const char* str);
> 
> //buffer
> //将pos开始的这个位置的len个字符，替换为str这个c字符串中的从0开始的n个字符
> string& replace(size_t pos, size_t len, const char* str, size_t n);
> //将迭代器i1的这个位置到i2的这个位置的字符，替换为str这个c字符串中的从0开始的n个字符
> string& replace(iterator i1, iterator i2, const char* str, size_t n);
> 
> //fill
> //将pos开始的这个位置的len个字符，替换为n个字符c
> string& replace(size_t pos, size_t len, size_t n, char c);
> //将迭代器i1的这个位置到i2的这个位置的字符，替换为n个字符c
> string& replace(iterator i1, iterator i2, size_t n, char c);
> ```
>
> **【作用】：**
>
> ​	**部分字符的替换**
>
> ​	替换以pos处开始长度为len的字符串，或者替换[i1, i2)之间的字符串
>
> **【返回值】：**
>
> ​	***this**（返回的是该对象的引用）
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> 
> int main()
> {
>   std::string str1("hello world!");
>   std::string str2("replace str!");
>   std::string str3("replace str1!");
>   std::string str4("replace str2!");
>   std::string str5("replace str3!");
>   
>   //string
>   str1.replace(0, 1, str2);
>   std::cout << str1 << '\n';//replace str!ello world!
>   str1.replace(str1.begin(), str1.begin() + 15, str2);
>   std::cout << str1 << '\n';//replace str!o world!
> 
>   //substring 
>   str2.replace(0, 1, str3, 0, 5);
>   std::cout << str2 << '\n';//replaeplace str!
> 
>   //c-string 
>   str3.replace(0, 1, "haha");
>   std::cout << str3 << '\n';//hahaeplace str1!
>   str3.replace(str3.begin(), str3.begin() + 10, "haha");
>   std::cout << str3 << '\n';//haha str1!
> 
>   //buffer
>   str4.replace(0, 1, "haha", 2);
>   std::cout << str4 << '\n';//haeplace str2!
>   str4.replace(str4.begin(), str4.begin() + 8, "haha", 4);
>   std::cout << str4 << '\n';//haha str2!
> 
>   //fill
>   str5.replace(0, 1, 5, 'X');
>   std::cout << str5 << '\n';//XXXXXeplace str3!
>   str5.replace(0, 11, 11, 'A');
>   std::cout << str5 << '\n';//AAAAAAAAAAA str3!
> 
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> replace str!ello world!
> replace str!o world!
> replaeplace str!
> hahaeplace str1!
> haha str1!
> haeplace str2!
> haha str2!
> XXXXXeplace str3!
> AAAAAAAAAAA str3!
> ```
>
>



### 5.8 swap：字符串内容的交换

> ``` c++
> //交换字符串的内容
> void swap(string& str);
> ```
>
> **【作用】：**
>
> ​	**交换两个字符串对象的内容**
>
> **【返回值】：**
>
> ​	**没有返回值**
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str1("hello");
>   std::string str2("nihao");
> 
>   std::cout << "str1:" << str1 << '\n';
>   std::cout << "str2:" << str2 << '\n';
>   str1.swap(str2);
>   std::cout << "str1:" << str1 << '\n';
>   std::cout << "str2:" << str2 << '\n';
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> str1:hello
> str2:nihao
> str1:nihao
> str2:hello
> ```



## 6. String operations：字符串的操作

### 6.1 c_str：将字符串对象变成c字符串

> ``` c++
> //将字符串对象转化为等价c字符串，并且包含终止符'\n'
> const char* c_str() const;
> ```
>
> **【作用】**
>
> ​	**将字符串对象转化为c字符串**
>
> ​	返回指向数组的指针，此数组包括该字符串对象的字符序列，并且末尾的终止符'\0'
>
> **【返回值】**
>
> ​	**返回指向数组的指针**
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str = "hello world!";
>   //必须使用const char*类型来接收它
>   const char* c_str = str.c_str();
>   std::cout << c_str << '\n';
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> hello world!
> ```



### 6. 2 find：从前向后查找字符串中的内容

> 该成员函数有着四种重载形式
>
> ``` c++
> //string
> //默认从下标0处开始在该对象中查找字符串str
> size_t find(const string& str, size_t pos = 0) const;
> 
> //c-string
> //默认从下标0处开始在该对象中查找c字符串str
> size_t find(const char* str, size_t pos = 0) const;
> 
> //buffer
> //从下标pos处开始在该对象中，查找字符串str的前n个字符
> size_t find(const char* str, size_t pos, size_t n) const;
> 
> //character
> //默认从下标0处开始在该对象中，查找字符c
> size_t find(const char c, size_t pos = 0);
> ```
>
> **【作用】：**
>
> ​	**查找内容是否在字符串中**
>
> ​	在对当前对象中查找第一个匹配的内容
>
> ​	当指定pos时，忽略pos之前的任何字符
>
> **【返回值】：**
>
> ​	**成功的话，返回匹配内容第一个位置的坐标**
>
> ​	**失败的话，返回string::npos**
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str1("Everyone is very very perfect,Do you know?");
>   std::string str2("Do");
>   std::string str3("DO");
> 
>   //string
>   size_t find = str1.find(str2, 0);
>   if (find != std::string::npos)
>   {
>     std::cout << "str2:Do find!Index is " << find << '\n';
>   }
> 
>   //c-string 
>   find = str1.find("very", 17);
>   if (find != std::string::npos)
>   {
>     std::cout << "very find!Index is " << find << '\n';
>   }
> 
> 
>   //buffer
>   find = str1.find("perfect", 15, 2);
>   if (find != std::string::npos)
>   {
>     std::cout << "pe find!Index is " << find << '\n';
>   }
> 
>   //character
>   find = str1.find('e', 0);
>   if (find != std::string::npos)
>   {
>     std::cout << "e find!Index is " << find << '\n';
>   }
> 
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> str2:Do find!Index is 30
> very find!Index is 17
> pe find!Index is 22
> e find!Index is 2
> ```



### 6. 3 rfind：从后向前查找字符串内容

> 该成员函数有着四种重载形式
>
> ``` c++
> //string
> //默认从当前对象的最后一个字符处开始向前查找字符串对象str
> size_t rfind(const string& str, size_t pos = npos) const;
> 
> //c-string
> //默认从当前对象的最后一个字符处开始向前查找c字符串str
> size_t rfind(const char* str, size_T pos = npos) const;
> 
> //buffer
> //从当前对象pos处开始向前面查找字符串的前n个字符
> size_t rfind(const chat* str, size_t pos, size_t n) const;
> 
> //character
> //默认从当前对象的最后一个字符处开始向前查找字符c
> size_t rfind(const char* c, size_t pos = npos);
> ```
>
> **【作用】：**
>
> ​	**从后向前查找内容在字符串中的位置**
>
> ​	当指定pos是，忽略pos之后的所有字符
>
> **【返回值】：**
>
> ​	**成功的话，返回匹配内容第一个位置的坐标**
>
> ​	**失败的话，返回string::npos**
>
> 例：
>
> ``` c++
> #include <iostream>
> #include <string>
> 
> int main()
> {
>   std::string str1("the people is super people...");
>   std::string str2("people");
> 
>   size_t find = str1.rfind(str2, str1.size());
>   if (find != std::string::npos)
>   {
>     std::cout << "str2:people find!Index in " << find << '\n';
>     str1.replace(find, str2.size(), "man");
>     std::cout << str1 << '\n';
>   }
> 
>   return 0;
> }
> ```
>
> 输出：
>
> ``` c++
> str2:people find!Index in 20
> the people is super man...
> ```



## #成员常量

## 	npos

> ``` c++
> //对于npos是无符号字符型常数，所以npos是255
> static const szie_t npos = -1;
> ```
>
> **【作用】：**
>
> ​	**size_t的最大值**
>
> ​	此变量定义为-1，因为该变量是无符号的整数类型，所以他是此类型的最大值（2^32 - 1）


