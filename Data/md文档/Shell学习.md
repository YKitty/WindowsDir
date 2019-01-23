# Shell学习

## # 符号

## 1. 初识

### 1.1 Shell定位

Shell就是用C编写的程序，是用户是用Linux的桥梁。Shell就是Linux内核的一个外壳，调用内核的接口



### 1.2 Shell和Bash

Shell如果是人的话，那么Bash就是好人或者坏人。也就是说Shell是内核程序的总称，Bash就是其中的一个



### 1.3 Shell的开发环境

Shell编程就和java，php，python一样，只要有一个能编写代码的文本编译器和一个能解释执行的脚本解释器就可以了

**【种类】：**

- /usr/bin/sh或/usr/bin/sh
- /bin/bash
- /usr/bin/csh
- /usr/bin/ksh
- /sbin/sh

**Bash是大多数Linux系统默认的Shell**



### 1.4 Shell特点

- **解释非编译型**
- **弱类型**
- **执行模式：交互式/批处理式**

弱类型：Shell中没有类型也不需要类型。Shell脚本把所有的变量中的内容全部看成是字符串

交互式：输入一台命令进行回车

批处理式：将多条命令放在一个文件中执行

举例：

交互式：对于每天工作之前都要执行100条命令。

批处理式：对于交互式是要自己每天敲100条命令。而对于批处理式则只需要第一次输入100条命令对于以后就不需要每天敲这么多的命令了，只需要执行就可以了。起到了一劳永逸的效果

**【重点】：批处理式可以提高效率**



### 1.5 知识点

- Shell是不能挂掉的，如果他挂掉了，就会导致外壳程序挂掉了，从而执行不了其他的命令了。
- Shell执行任务：创建子进程->子进程执行命令->父进程等待->子进程返回结果
- windows中的界面就相当于是Linux下的Shell
- Shell是外壳程序
- Shell是一个二进制解释器和python一样。
  - /bin/bash
  - /usr/bin/python
- 父进程也是一个bash，是交互式bash
- 子进程是一个bash，子进程在执行Shell脚本的时候要遵循Shell的执行原理
- 原则上Shell脚本当中的内容按行读取，原则上每一行都可以被当做一条命令

**【注意】：**子bash在执行的时候是如何执行的

1. fork创建子进程，子进程读取脚本文件当中的第一行，然后exec到解释器
2. 然后读取一行执行一行

**对于每一个进程都有着自己的工作目录**

### 1.5 Shell脚本

``` Shell
#!/bin/bash

echo 'hello world'
```

对于**第一行的#!这是一个约定的标志，他告诉系统要用什解释器来执行，即用哪一种Shell。通常叫做”Shebang“**

**echo命令用于向窗口输出文本**



### 1.6 执行的两种方式

- 第一种：作为可执行程序

``` Shell
# chmod u+x test.sh
# ./test.sh
hello world
```

**【注意】：**

一定要写成**./test.sh而不是test.sh**,对于运行其他的二进制程序也是一样的，**直接写test.sh**。Linux系统会**去PATH里寻找有没有叫test.sh**的，而只有**/bin，/sbin，/usr/bin等在PATH里**，你的**当前目录通常不在PATH里**，所以写成test.sh是会找不到文件的。如果使用**/test.sh意思就是告诉系统在当前目录下查找二进制文件**

- 第二种：作为解释器参数

``` Shell
# /bin/bash test.sh
hello world
```

这种方式就是**直接运行解释器，其参数就是Shell脚本的文件名**。采用这种方式运行的脚本**不需要在第一行指定解释器信息，写了的话也会将其当成注释**

Shell脚本中用#表示注释，相当于C语言的//注释。但如果#位于第一行的话，就会例外，这个时候表示**该脚本使用后面所指定的解释器/bin/bash解释执行**

### 1.7 解释执行的本质原理

- 第一种执行方式：chmod + x test.sh。

对于执行一个程序的时候，操作系统只认识二进制文件。但是对于执行test.sh文件。fork出一个子进程，然后exec执行test.sh，但是test.sh不是二进制文件，所以不能直接执行test.sh文件。但是对于文件中第一行有这解释器,所以exec是直接执行这个解释器，然后将test.sh文件中的内容作为这个解释器的参数来进行执行。对于这种情况该文本文件要有可执行的权限

- 第二种执行方式：bash test.sh

Shell直接fork出一个子Shelll去执行解释器。然后对于后面的脚本文件中内容按行读取逐行解释

- Shell脚本是非编译性的解释性的弱类型语言，它的执行并不是自己亲自执行，而是由现将其解释器跑起来，然后再有解释器读取脚本文件中的内容，按行读取，逐行解释



### 1.8 内建命令

例：

``` Shell
# pwd
# cd ..
# pwd
```

发现执行完了之后，但是对于当前目录没有改变。但是再执行的时候还是输出了上一结构的目录

对于这个执行，因为没有影响到交互式bash（即父进程），所以对于目录没有发生该变。**影响的只是子进程的工作目录。没有影响到父进程的工作目录**

在**交互式bash**当中执行的**没有产生子进程**去执行的叫做内建命令。这种命令执行之后，**直接影响到了父进程的工作目录**

在**执行shell脚本文件时，是创建出来的子进程来执行的，所以不会影响到交互式的bash**

**【注意】：**

cd命令在执行的时候不需要创建子进程，cd叫做内置命令。直接由Shell执行。（一般不会出错，所以可以由shell直接执行不害怕会出错）

echo也是内置命令。

如果使用**.或者source**来修饰脚本，脚本的执行影响到了父Bash。这种情况下也不会创建子Shell，而是直接在交互式Shell下逐行解释脚本中的命令。



## 2. Shell变量

**Shell是弱类型，原则上不是特别强调Shell变量，或者Shell变量可以放很多常见的内容。Shell变量不需要提前定义，需要的时候直接使用即可。**



### 2.1 赋值和命名规则

``` Shell
myint=10
```

**【注意】：**变量和等号之间不能有空格！否则会被Shell解释成命令和命令行参数。

**变量名命名规则：**

- 首个字符必须是字母
- 中间不能有空格，可以使用下划线
- 不能使用标点符号
- 不能使用bash里的关键字（使用help命令查看）



###  2.2 使用变量

使用一个已经赋值过的变量只需要**在前面加上$符号**就可以了

$符号的意思就是取出变量里面的内容

例：

``` Shell
mystr="yk"
echo $mystr
echo ${mystr}
```

对于变量名外面的花括号是可选的，加不加都行，加花括号是为了帮助解释器识别变量的边界。

比如下面这种情况：

``` Shell
mystr="yk"
echo ${mystr}itty
```

如果不加花括号的话，写成"echo $mystritty",对于解释器来说就会把mystritty整体当成一个变量而这个变量为空。输出结果就不是我们所想的那样了就会出错了。

**【强烈推荐】：给所有的变量都加上花括号，这是一个好习惯**

对于**已定义的变量，可以被重新定义**，如：

``` Shell
mystr="yk"
echo $mystr
mystr="yq"
echo $mystr
```

这样写是合法的，但是注意，对于第二次赋值的时候，不能写 `$ mystr="yq"`，**当变量作为右值的时候，才需要带上  `$`符号**



### 2.3 只读变量

使用**readonly命令可以将白能量定义为只读变量，只读变量的值不能被改变**



### 2.4 删除变量

**使用unset命令可以删除变量**

**对于删除变量也就是将变量的内容置为空**

**【注意】：unset不能删除只读变量**



### 2.5 变量类型

- **本地变量：**局部变量在脚本或者命令行中定义，仅在当前Shell实例中有效，其他Shell启动的程序不能访问局部变量

  这是因为对于不同的Shell都是父Shellfork出来的，都各自有着自己的工作目录所以不可以访问其他人的变量

- **环境变量：**所有的程序，包括Shell启动的程序，都能访问环境变量，有些程序需要环境变量保证正常运行。

  必要的时候Shell脚本也可以定义环境变量，使用export命令创建环境变量

- **Shell变量：**Shell变量是由Shell程序设置的特殊变量。Shell变量中有一部分是环境变量，有一部分是局部变量

举例：

``` Shell
[yk@localhost 2_lesson]$ a=10
[yk@localhost 2_lesson]$ vim test.sh 
[yk@localhost 2_lesson]$ ./test.sh 

[yk@localhost 2_lesson]$ echo $a
10
[yk@localhost 2_lesson]$ export a
[yk@localhost 2_lesson]$ ./test.sh 
10
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

echo $a
```

**【注意】：使用printenv可以查看当前Shell进程的环境变量**

用export可以将本地变量导出为环境变量，定义和导出环境变量通常可以一步完成。

``` Shell
export mystr="yk"
```

或者两步完成

``` Shell
mystr="yk"
export mystr
```

**【注意】：使用unset可以删除已定义的环境变量或者本地变量**

``` Shell
unset mystr
```



### 2.6 字符串操作

字符串是shell编程中最常用最有用的类型了，字符串可以用单引号，也可以使用双引号，也可以不使用引号

- **单引号**

``` shell
str='this is a string'
```

**单引号字符串的限制：**

1. **单引号里的任意字符都会原样输出，单引号字符串里的变量是无效的**
2. 单引号字符串中**不能出现单独一个的单引号**（对单引号使用转义符也不可以），但**可成对出现，作为字符串拼接使用**



- **双引号**

``` shell
mystr="yk"
echo "hello, I know your \"$mystr\"!"
```

输出：

``` shell
hello, I know you are "yk"!
```

**双引号的优点：**

1. **双引号里可以有变量**
2. **双引号里可以出现转义字符**



- **拼接字符串**

原则上，只要将信息写在一起就完成了string的拼接

``` shell
your_name="runoob"
# 使用双引号拼接
greeting="hello, "$your_name" !"
greeting_1="hello, ${your_name} !"
echo $greeting  $greeting_1
# 使用单引号拼接
greeting_2='hello, '$your_name' !'
greeting_3='hello, ${your_name} !'
echo $greeting_2  $greeting_3
```

输出结果：

``` shell
hello, runoob ! hello, runoob !
hello, runoob ! hello, ${your_name} !
```



- **获取字符串长度**

``` shell
string="abcd"
echo ${#string}#输出4
```



- **提取字符串长度**

**从字符串第2个字符开始截取4个字符**

``` shell
string="runoob is a great site"
echo ${string:1:4} # 输出 unoo
```



- **查找字符串**

查找字符 **i** 或 **o** 的位置(哪个字母先出现就计算哪个)

``` shell
string="runoob is a great site"
echo `expr index "$string" io` # 输出 4
```

**注意：** 以上脚本中 ` 是反引号，而不是单引号 '，不要看错了哦。

 

## 3. 文件名代换

这些用于匹配的字符称为通配符，

- 通配符*：匹配0个或者多个任意字符
- ？：匹配一个任意字符
- [若干字符]：匹配方括号中任意一个字符的一次出现

例:

``` shell
[yk@localhost 2_lesson]$ for i in {1..20};do touch file$i;done[yk@localhost 2_lesson]$ ls
api.sh  file12  file16  file2   file5  file9
file1   file13  file17  file20  file6  file.sh
file10  file14  file18  file3   file7  lable.sh
file11  file15  file19  file4   file8  test.sh
[yk@localhost 2_lesson]$ ls file*
file1   file12  file15  file18  file20  file5  file8
file10  file13  file16  file19  file3   file6  file9
file11  file14  file17  file2   file4   file7  file.sh
[yk@localhost 2_lesson]$ ls file?
file1  file2  file3  file4  file5  file6  file7  file8  file9
[yk@localhost 2_lesson]$ ls file[123]
file1  file2  file3
[yk@localhost 2_lesson]$ ls file[1-5]
file1  file2  file3  file4  file5
```

**【注意】：**文件名代换所匹配的文件名是由** 	**。比如上述的ls file[1-5]命令。如果当前目录下有file1~file5，则传给ls命令的参数实际上是这5个文件名，而不是一个匹配字符串



## 4. 命令代换和算术代换

- **命令代换**

**由反引号``括起来的也是一条命令，Shell先执行该命令，然后将输出结果立刻代换到当前命令行中**

例：

``` shell
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

echo `date +%Y`
[yk@localhost 2_lesson]$ ./test.sh 
2019
```

**命令代换也可以使用$()来表示：**

例：

``` shell
[yk@localhost 2_lesson]$ ./test.sh 
2019
2019
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

echo `date +%Y`
echo $(date +%Y)
```

- **算术代换**

**`(())`中的shell变量取值将转化成整数，常用于算术计算**

例：

``` shell
[yk@localhost 2_lesson]$ ./test.sh 
520
521
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

myint=520
echo $myint 
((myint++))
echo $myint
```

**如果要对运算结果进行赋值或者作为右值**

例：

``` shell
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

myint=520
echo $myint 
ret=$((myint++))
echo $myint
```

**【注意】：`(())`中只能用+-*/和()运算符，并且只能做整数运算**



## 5. 转义字符

和C语言类似，**\在shell中被用作转义字符**，用于除去紧跟其后的的单个字符的特殊意义（回车除外），换句话说，**紧跟其后的字符取字面值**。另外，**\后面还可以紧跟其后的普通字符去特殊含义**

举例：**创建和删除一个文件名为`$ $`(中间有空格的文件**

``` shell
[yk@localhost 2_lesson]$ ll
total 16
-rw-rw-r--. 1 yk yk   52 Jan 23 00:42 api.sh
-rwxrw-r--. 1 yk yk  527 Jan 23 02:14 file.sh
-rw-rw-r--. 1 yk yk  178 Jan 23 00:42 lable.sh
-rwxrw-r--. 1 yk yk 1429 Jan 23 05:05 test.sh
[yk@localhost 2_lesson]$ touch \$\ \$
[yk@localhost 2_lesson]$ ll
total 16
-rw-rw-r--. 1 yk yk    0 Jan 23 05:10 $ $
-rw-rw-r--. 1 yk yk   52 Jan 23 00:42 api.sh
-rwxrw-r--. 1 yk yk  527 Jan 23 02:14 file.sh
-rw-rw-r--. 1 yk yk  178 Jan 23 00:42 lable.sh
-rwxrw-r--. 1 yk yk 1429 Jan 23 05:05 test.sh
[yk@localhost 2_lesson]$ rm \$\ \$
[yk@localhost 2_lesson]$ ll
total 16
-rw-rw-r--. 1 yk yk   52 Jan 23 00:42 api.sh
-rwxrw-r--. 1 yk yk  527 Jan 23 02:14 file.sh
-rw-rw-r--. 1 yk yk  178 Jan 23 00:42 lable.sh
-rwxrw-r--. 1 yk yk 1429 Jan 23 05:05 test.sh
```

另外还有一个字符虽然不具有特殊含义，但是要用做文件名也是很麻烦的，就是`-`号。如果要创建一个文件名以`-`号开头的文件，即使加上`\`还是会出错。因为各种UNIX命令都把`-`号开头的命令行参数当做命令的选项，而不会是当做文件名。如果非要处理以`-`号开头的文件名。有以下两种办法：

``` shell
[yk@localhost 2_lesson]$ touch -- -file
[yk@localhost 2_lesson]$ touch ./-file.bak
[yk@localhost 2_lesson]$ ll
total 16
-rw-rw-r--. 1 yk yk   52 Jan 23 00:42 api.sh
-rw-rw-r--. 1 yk yk    0 Jan 23 05:17 -file
-rw-rw-r--. 1 yk yk    0 Jan 23 05:17 -file.bak
-rwxrw-r--. 1 yk yk  527 Jan 23 02:14 file.sh
-rw-rw-r--. 1 yk yk  178 Jan 23 00:42 lable.sh
-rwxrw-r--. 1 yk yk 1429 Jan 23 05:05 test.sh
[yk@localhost 2_lesson]$ rm -- -file
[yk@localhost 2_lesson]$ rm ./-file
[yk@localhost 2_lesson]$ ll
total 16
-rw-rw-r--. 1 yk yk   52 Jan 23 00:42 api.sh
-rwxrw-r--. 1 yk yk  527 Jan 23 02:14 file.sh
-rw-rw-r--. 1 yk yk  178 Jan 23 00:42 lable.sh
-rwxrw-r--. 1 yk yk 1429 Jan 23 05:05 test.sh
```

**\还有一种用法就是，在\后面敲回车表示续行，Shell并不会立刻执行命令，而是把光标移到下一行，给出一个续行提示符>，等待用户继续输入，最后把所有的续行接到一起当做一个命令执行**

``` shell
[yk@localhost 2_lesson]$ while :;\
> do \
> echo "hello world";\
> sleep 1;\
> done
hello world
hello world
hello world
```



## # 语法

## 1. 条件测试

### 1.1 测试命令

shell脚本中测试使用命令来完成的，最**常见的测试命令包含`test`和`[`**，通过检查该类命令的退出码，决定条件测试是否成立。

例：

``` shell
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

read myint
test $myint -eq 100
echo $?
[yk@localhost 2_lesson]$ ./test.sh 
100
0
[yk@localhost 2_lesson]$ ./test.sh 
200
1
```

**【注意】：shell认为退出码为0，条件成立，非0，条件不成立**



### 1.2 测试类型

shell脚本测试可以用来**测试不同的类型**，应用与不同的测试场景

常见测试选项如下：

> - 整数测试：-eq -ne  -lt  -le -gt -ge
> - 字符串测试：==(=) ！= -z -n
> - 文件测试：-d -f -b -c



- **测试整数**

例：

``` shell
[yk@localhost 2_lesson]$ ./test.sh 
100
0
1
1
1
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

read myint
[ $myint -eq 100 ] 
echo $?
[ $myint -ne 100 ] 
echo $?
[ $myint -lt 100 ] 
echo $?
[ $myint -gt 100 ] 
echo $?
```

`test`和`[`都可以用来测试，两者使用稍有不同，虽然看起来很奇怪但是左方括号`[`确实是一个命令的名字，传给命令的各参数之间应该用空格隔开。比如`$myint -le 18`是命令`[`的四个参数，必须使用空格隔开，如果不使用空格隔开的话，就会把两个参数放在一起认为是一个变量就会出错。

**命令`test`和命令`[`的参数形式是相同的，只不过`test`命令不需要`]`参数**。建议使用`[`来测试



- **测试字符串**

``` shell
yk@localhost 2_lesson]$ ./test.sh 
helloworld
0
1
1
0
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 


read mystring 
[ $mystring == "helloworld" ]
echo $?
[ $mystring != "helloworld" ]
echo $?
[ -z $mystring ]
echo $?
[ -n $mystring ]
echo $?
```

**【注意】：**

**当字符串为空串的时候进行比较**

``` shell
[yk@localhost 2_lesson]$ ./test.sh #直接回车

./test.sh: line 5: [: ==: unary operator expected
2

[yk@localhost 2_lesson]$ ./test.sh 
+ read mystring

+ '[' == hello ']'
./test.sh: line 5: [: ==: unary operator expected
+ echo 2
2
```

对于直接回车不输入任何一个字符，就会导致左边是空串，就会出现错误

**【解决方法】：**

``` shell
yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

read mystring

[ "$mystring" == "hello" ]
echo $?
```

**只需要加上双引号就可以，就表示这是一个字符串，如果这个为空的话，这个也是一个空的字符串。但是不能使用单引号，因为单引号对于变量是无效的**



- **测试文件**

``` shell
[yk@localhost 2_lesson]$ ./test.sh 
0
0
0
0
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 


[ -c /dev/tty ]
echo $?
[ -b /dev/sda ]
echo $?
[ -f ./test.sh ]
echo $?
[ -d / ]
echo $?
```



## 2. 多条件测试

### 2.1 逻辑与或非

**和C语言类似，测试条件还可以做与、或、非逻辑运算**

例：**逻辑反**

``` shell
[yk@localhost 2_lesson]$ ./test.sh 
hello
1
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

read mystring
[ ! "$mystring" == "hello" ]
echo $?
```

例：**逻辑与**

``` shell
[yk@localhost 2_lesson]$ ./test.sh 
100 200
0
[yk@localhost 2_lesson]$ ./test.sh 
2 200
1
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

read d1 d2 
[ $d1 -eq 100 -a $d2 -eq 200 ]
echo $?
```

例：**逻辑或**

``` shell
[yk@localhost 2_lesson]$ ./test.sh 
100 2
0
[yk@localhost 2_lesson]$ ./test.sh 
1 200
0
[yk@localhost 2_lesson]$ ./test.sh 
100 200
0
[yk@localhost 2_lesson]$ ./test.sh 
2 9
1
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

read d1 d2 
[ $d1 -eq 100 -o $d2 -eq 200 ]
echo $?
```



### 2.2 if/then/elif/else/fi

上面的若干的判断命令，只能用来判断出条件的帧或者假，但是在实际应用中，判断出真假只是第一步，我们还要根据判断结果来进行**语句分流**

在Shell中使用if、then、elif、else、fi这几条命令实现分支控制。这种流程控制语句本质上也是有若干条Shell命令组成的

``` shell
[yk@localhost 2_lesson]$ ./test.sh 
hello
hello
[yk@localhost 2_lesson]$ ./test.sh 
hasdkj
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

read mystring
if [ "$mystring" == "hello" ];then
  echo "hello"
fi
```

如果两条命令写在同一行则需要用`；`号隔开，一行只写一条命令就不需要写`;`了，另外，then后面有换行，但这条命令没有写完，Shell就会自动续行，把下一行接在then后面当做一条命令处理，和`[`命令一样，要注意命令和各参数之间必须用空格隔开。



- **循环嵌套**

``` shell
[yk@localhost 2_lesson]$ ./test.sh 
100
le 100
ge 0
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 


read myint 
if [ $myint -le 100 ];then
  echo "le 100"
  if [ $myint -le 50 ];then 
    echo "le 50"
  elif [ $myint -ge 50 ];then 
    echo "ge 0"
  else 
    echo "myint in 50 ~ 100"
  fi 
else
  echo "gt 100"
fi
```

**if命令的参数组成一条子命令，如果该子命令的退出码为0，则执行then'后面的子命令，如果退出码非0，则执行elif，else或者fi后面的命令。**fi后面的命令通常都是测试命令，但也可以是其他的命令

**【思考】：`if`的子命令除了`[`和`test`命令，还可以放其他的命令，只要该命令退出码为0,1来表明执行结果**

下面是检测文件中是否包含`222`关键字的脚本

``` shell
[yk@localhost 2_lesson]$ ./test.sh 
file
22222222222222222
yes
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

read filename
if grep '222' "$filename";then
  echo "yes"
else
  echo "no"
fi
```

用`if`来进行条件判断，直接判断`grep`的执行结果

- -E：使用扩展正则匹配
- -q：使用安静模式匹配

Shell脚本中没有{}括号，所以用fi来表示if语句块的结束



### 2.3 空代码块

**如果在代码块中，出现了空语句情况Ian，什么都不写，shell会直接报错，那怎么解决呢？**

`:`是一个特殊的命令，称为空命令，该命令不做任何事，但是退出码总是真。此外，也可以执行/bin/true或/bin/false得到真的或者假的Exit Status

``` shell
[yk@localhost 2_lesson]$ ./test.sh 
100
equal
[yk@localhost 2_lesson]$ ./test.sh 
78
equal
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 

read myint 
if /bin/true ;then
  echo "equal"
else 
  echo "noequal"
fi
```



### 2.4 ||或&&

Shell还提供了&&和||语法，和C原因类似，具有Short-circuit（懒逻辑）特性。也即使**对于&&来说只要前面的正确了就不需要关心后面的了。对于||来说前面的对了之后，还是要关系后面是否正确。**

``` shell
[yk@localhost 2_lesson]$ ./test.sh 
100
yes 100
no 200
[yk@localhost 2_lesson]$ ./test.sh 
200
[yk@localhost 2_lesson]$ cat test.sh 
#!/bin/bash 


read myint
[ $myint -eq 100 ] && echo "yes 100"
[ $myint -eq 200 ] || echo "no 200"
```

&&相当于“if...then...”，而||相当于"if not...then...".&&和||用于连接两个命令，而上面所讲的-a或-o仅用于在测试表达式中连接两个测试条件



