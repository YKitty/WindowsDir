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

**如果在代码块中，出现了空语句情况，什么都不写，shell会直接报错，那怎么解决呢？**

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



### 2.5 case和esac

case可类比C语言的switch/case语句，esac表示case语句块的结束。C语言的case只能匹配整形或字符型常量表达式。而Shell脚本的case可以匹配字符串和Wildcard，每个匹配分支可以有若干条命令，**末尾必须以;;结束**，**执行时找到第一个匹配的分支并执行相应的命令，然后直接跳到esac之后**，不需要像C语言一样用break跳出。

```shell
[yk@localhost 3_lesson]$ ./test.sh 
restart
restart
[yk@localhost 3_lesson]$ ./test.sh 
Restart
restart
[yk@localhost 3_lesson]$ ./test.sh 
hello
start
[yk@localhost 3_lesson]$ ./test.sh 
-s
stop
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 

str='hello'
read mystr 
case $mystr in 
#case $1 in 
  "$str" )
    echo "start"
    ;;
  'stop'| "-s" )
    echo "stop"
    ;;
   [Rr]estart )
    echo "restart"
    ;;
  'down' )
    echo "down"
    ;;
  'up' )
    echo "up"
    ;;
  * )
    echo "default"
    ;;
esac
```

`$1`是一个特殊变量，再执行脚本是自动取值为第一个命令行参数。

尝试关闭ssh服务：

``` shell
sudo /etc/init.d/sshd stop
```

断开连接之后，一般就连不上Linux服务器了。一般只能在Linux终端上重启了，成功之后就可以重新连接

``` shell
sudo /etc/init.d start
```

**系统服务的脚本目录/etc/init.d**



## 3. 循环语句

### 3.1 类C循环

Shell脚本的for循环结构和C语言很不一样，但是也有类似C语言的写法

``` shell
for i in {1,2,3,4}
do 
  echo $i
done

for ((i = 0; i <= 10; i++))
do 
  echo "hello$i"
done
```

对于`(())`这个结构，在这个结构中，所有的运算和C都是一样的

对于for...in...就相当于C++的foreach循环



### 3.2 for in 循环

该循环的强大之处是可以遍历字符，然后还可以进行全排列

``` shell
#遍历两个范围
for i in {1..4} {a..f}
do 
  echo "$i"
done 

#全排列
for i in {1..3}{a..d}
do 
  echo "$i"
done 

#遍历字符
for i in {a..z}
do 
  echo "$i"
done 

for i in {1..10}
do 
  echo "$i"
done
```



### 3.3 while循环

``` shell
i=0
while [ $i -le 10 ]
do 
  echo "hello $i"
  let i++
done
```

**【注意】：对于while循环一定要注意索引的自增以及对于判断条件一定要初始化**



### 3.4 until循环

这是一种shell特有的循环

``` shell
i=10
until [ $i -le 0 ]
do 
  echo "hello $i"
  let i--
done
```

**直到循环**



### 3.5 死循环

- **for死循环**

``` shell
for (( ; ; ))
do 
  echo "hello"
done
```



- **while死循环**

``` shell
while :
do 
  echo "hello"
done
```



- **until死循环**

``` shell
until false
do 
  echo "hello"
done

until /bin/false
do 
  echo "hello"
done
```



### 3.6 命令行循环

``` shell
[yk@localhost 3_lesson]$ i=0;while [ $i -le 10 ];do echo "hello";let i++;done
hello
hello
hello
hello
hello
hello
hello
hello
hello
hello
hello
```



### 3.7 练习

- 求1~100的和

``` shell
sum=0
for ((i = 1;i <= 100; i++))
do 
  let sum+=$i;
done 
echo "$sum"
```



- 打印出加的结果

``` shell
sum=0
for ((i = 1;i <= 100; i++))
do
  if [ -z $str ];then
    str=$i
  else
    str=$str'+'$i
  fi 
  let sum+=$i;
done 
echo "$str""=$sum"
```



- 求1~100的奇数和

``` shell
sum=0
for ((i = 1; i <= 100; i += 2))
do 
  let sum+=$i
done  
echo "$sum"
```



## 4. 位置参数和特殊变量

### 4.1 特殊变量

**有很多的特殊变量是被shell自动赋值的**

- `$0`：相当于C语言main函数的argv[0]，还有`$1、$2、$3`相当于argv[1],argv[2]等等
- `$#`：相当于C语言的argc-1
- `$@`：表示参数列表
- `$?`：上一条命令的Exit Status
- `$$`：当前Shell的进程号

``` shell
[yk@localhost 3_lesson]$ ./test.sh 1 2 3 4
$0 -> ./test.sh
$1 -> 1
$2 -> 2
$3 -> 3
$# -> 4
$@ -> 1 2 3 4
$$ -> 11788
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 

echo "\$0 -> $0"
echo "\$1 -> $1"
echo "\$2 -> $2"
echo "\$3 -> $3"
echo "\$# -> $#"
echo "\$@ -> $@"
echo "\$$ -> $$"
```



### 4.2 位置参数（shift）

**位置参数可以使用shift命令左移。比如`shift 3`表示原来的`$4`变成了`$1`，原来的`$1`,`$2`,`$3`都被丢弃了。`$0`不移动。不带参数的shift命令相当于`shift 1`**

``` shell
[yk@localhost 3_lesson]$ ./test.sh 1 2 3 4
##############shift before###############
$0 -> ./test.sh
$1 -> 1
$2 -> 2
$3 -> 3
$# -> 4
$@ -> 1 2 3 4
$$ -> 11983
##############shift after###############
$0 -> ./test.sh
$1 -> 2
$2 -> 3
$3 -> 4
$# -> 3
$@ -> 2 3 4
$$ -> 11983
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 

echo "##############shift before###############"
echo "\$0 -> $0"
echo "\$1 -> $1"
echo "\$2 -> $2"
echo "\$3 -> $3"
echo "\$# -> $#"
echo "\$@ -> $@"
echo "\$$ -> $$"

shift #shift 1
echo "##############shift after###############"
echo "\$0 -> $0"
echo "\$1 -> $1"
echo "\$2 -> $2"
echo "\$3 -> $3"
echo "\$# -> $#"
echo "\$@ -> $@"
echo "\$$ -> $$"
```



### 4.3 如何遍历命令行参数

- **使用shift**

``` shell
while [ $# -gt 0 ]
do 
  echo "$1"
  shift
done
```



- **使用for in**

``` shell
for i in $@
do 
  echo "$i"
done
```



## 5. 函数

### 5.1 定义（function）

和C语言类似，Shell也有函数的概念，但是特殊的是，**函数定义中没有返回值也没有参数列表**

``` shell
function myfun()
{
    echo "hello"
}
```

【**注意】：函数体的做花括号和后面的命令之间必须有空格或者换行；如果将最后一条命令和右花括号写在了同一行，命令末尾必须有；号**

在定义函数myfun()的时候并**不执行函数体中的命令**，就像定义变量一样，只是**给myfun()这个名字一个定义**，到后面调用的时候（**注意函数调用不写括号**）才执行函数体中的命令

``` shell
[yk@localhost 3_lesson]$ ./test.sh 
hello
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 


function myfun()
{
  echo "hello"
}
```

Shell脚本中函数先定义后调用，一般把函数定义都写在脚本前面，把函数调用和其他命令写在脚本后面。



### 5.2 函数传参

传参时，将shell函数当成迷你脚本

shell函数没有参数列表并不表示不能传参数，事实上，函数就像是迷你脚本，调用函数是可以传任意个参数，在函数内部使用`$1`,`$2`等变量来提取参数

``` shell
[yk@localhost 3_lesson]$ ./test.sh 
hello
1
2
3
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 


function myfun()
{
  echo "hello"
  echo "$1"
  echo "$2"
  echo "$3"
}
```

**对于`$0`并不作为函数参数进行传参任务**



### 5.3 函数返回值

- **使用return返回**

函数调用或者返回是，将shell函数当成命令。只要是命令那么函数的调用成功与否，可以通过`$?`来判定。一般函数中可以使用return命令返回，如果return后面跟一个数字则表示函数的ExitStatus。

``` shell
[yk@localhost 3_lesson]$ ./test.sh 
1
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 


function fun()
{
  return 1;
}

fun 
echo $?
```



- **echo方式**

**也就是采用命令代换的方式**

``` shell
[yk@localhost 3_lesson]$ ./test.sh 
sucess
0
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 


function fun()
{
  echo "sucess"
  return 1;
}
```

这种方式也就是函数内部只能有一条string输出



## 6. shell脚本的调试方法

shell脚本本身，调试没有C/C++那么多的调试方法和工具，一般我们常规的方法，shell都支持。但主要通过调试选项来进行

- -n：读一遍脚本中的命令但不执行，用于检测脚本中的语法错误
- -v：一边执行脚本，一边将执行过的脚本命令打印到标准错误输出
- -x：提供跟踪执行信息，将执行的每一条命令和结果都打印出来

使用这些选项一般有三种方法：

一是在命令行使用

``` shell
bash test.sh -x
```

二是在脚本开头提供参数

``` shell
#!/bin/bash -x
```

三是在脚本中用set命令启用或禁用参数

``` shell
[yk@localhost 3_lesson]$ ./test.sh 
sucess
+ echo 0
0
[yk@localhost 3_lesson]$ cat test.sh  
#!/bin/bash 


function fun()
{
  echo "sucess"
  return 1;
}

set +x
ret=$(fun)
echo "$ret"
set -x
echo $?
```



## 7. 数组

数组中可以存放多个值。Bash Shell只支持一维数组，初始化是不需要定义数组大小。并且没有限定数组的大小。与大部分编程语言类似，数组元素的下标由0开始。获取数组中的元素要利用下标，下标可以是整数或算术表达式，其值应大于或等于0

**Shell数组用括号来表示，元素用”空格“分割开，可以不适用连续的下标，而且下标没有限制**

获取单个元素：

**`${arr[index]}`**

``` shell
[yk@localhost 3_lesson]$ ./test.sh 
0: 1
1: 2.23
2: hello
3: b
1 2.23 hello b
1 2.23 hello b
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 

arr=(1 2.23 "hello" 'b')

echo "0: ${arr[0]}"
echo "1: ${arr[1]}"
echo "2: ${arr[2]}"
echo "3: ${arr[3]}"

echo ${arr[*]}
echo ${arr[@]}
```

获取全部元素：

**`${arr[@]}`,` ${arr[*]}`**

获取数组长度：

**`${#arr[@]}`,` ${#arr[*]}`**

``` shell
echo ${#arr[*]}
echo ${#arr[@]}
```

遍历数组：

``` shell
arr=(1 2.23 "hello" 'b')

i=0
while [ $i -lt ${#arr[@]} ]
do 
  echo "$i:  ${arr[$i]}"
  let i++
done

#建议使用for in比较简单
for i in ${arr[@]}
do 
  echo $i
done 
```



## 8. shell和文件

大多数UNIX系统命令从你的终端接收输入并将产生的输出发送回到你的终端。。一个命令通常从一个叫标准输入
的地方读取输入，默认情况下，这恰好是你的终端。同样，一个命令通常将其输出写入到标准输出，默认情况下，这也是你的终端

C/C++当中，读取文件需要相关函数来进行完成，但shell就简单多了



### 8.1 shell输出重定向

``` shell
[yk@localhost 3_lesson]$ cat file1
0hello
1hello
2hello
3hello
4hello
5hello
6hello
7hello
8hello
9hello
10hello
[yk@localhost 3_lesson]$ cat file
hello world
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 

#循环结果和单个字符串进行输出重定向
echo "hello world" > file
for (( i = 0; i <= 10; i++ ))
do 
  echo "${i}hello"
done > file1 
```



### 8.2 追加重定向

``` shell
[yk@localhost 3_lesson]$ cat file
hello world
hello world two
[yk@localhost 3_lesson]$ cat file1
0hello
1hello
2hello
3hello
4hello
5hello
6hello
7hello
8hello
9hello
10hello
0hello world
1hello world
2hello world
3hello world
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 


echo "hello world two" >> file
for (( i = 0; i <= 3; i++ ))
do 
  echo "${i}hello world"
done >> file1 
```



### 8.3 输入重定向

- **read每次只能读取一行内容**

``` shell
[yk@localhost 3_lesson]$ ./test.sh 
hello world
[yk@localhost 3_lesson]$ cat file
hello world
hello world two
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 

read line < file
echo "$line"
```



- **采用read读取多行内容**

``` shell
[yk@localhost 3_lesson]$ ./test.sh 
hello world
hello world two
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 

while read line
do 
  echo "$line"
done < file
```



- **采用read读取整个文件并且进行备份**

``` shell
[yk@localhost 3_lesson]$ cat file.bak 
hello world
hello world two
[yk@localhost 3_lesson]$ cat file
hello world
hello world two
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 


while read line
do 
  echo "$line"
done < file >> file.bak
```

【注意】：默认情况下，我们把stdout > file,file < stdin

|      命令       |                     说明                      |
| :-------------: | :-------------------------------------------: |
| command > file  |              将输出重定向到file               |
| command > file  |              将输入重定向到file               |
| command >> file |        将输出以追加的方式重定向到file         |
|    n > file     |       将文件描述符为n的文件重定向到file       |
|    n >> file    | 将文件描述符为n的文件以追加的方式重定向到file |
|     n >& m      |              将输出文件m和n合并               |
|     n <& m      |              将输入文件m和n合并               |
|     << tag      | 将开始标记tag和结束标记tag之间的内容作为输入  |



如果我们希望重定向stderr可以这样，

``` shell
[yk@localhost 3_lesson]$ find a 2> file
[yk@localhost 3_lesson]$ cat file
find: ‘a’: No such file or directory
```

如果我们希望stderr追加到file文件末尾

``` shell
[yk@localhost 3_lesson]$ find a 2> file
[yk@localhost 3_lesson]$ find b 2>> file
[yk@localhost 3_lesson]$ cat file
find: ‘a’: No such file or directory
find: ‘b’: No such file or directory
```

2表示标准错误文件（stderr）

如果我们希望将stdout和stderr合并后重定向到file

``` shell
command > file 2>&1

command > file 2>>&1
```

如果希望对 stdin 和 stdout 都重定向，可以这样写： 

``` shell
command < file1 >file2
```

command 命令将 stdin 重定向到 file1，将 stdout 重定向到 file2



### 8.4 Here Document

Here Document是Shell中一种特殊的重定向方式，用将输入重定向到一个交互式的Shell脚本或者程序。

``` shell
commmand << delimiter
	document
deli
```

它的作用是将两个delimiter之间的内容（document）作为输入传递给command

- 结尾的delimiter一定要顶格写，前面不能有任何的字符，后面也不能有任何的字符，包括空格和tab缩进
- 开始的deliemiter前后的空格会被忽略掉

例：

``` shell
[yk@localhost 3_lesson]$ ./here.sh 
2
[yk@localhost 3_lesson]$ cat here.sh 
#!/bin/bash

wc -l  << EOF
  欢迎来到
  ahahhaha
EOF
```



### 8.5 /dev/null文件

如果希望执行某个命令，但又不希望在屏幕上显示输出结果，那么可以将输出重定向到 /dev/null： 

``` shell
command > /dev/null
```

/dev/null 是一个特殊的文件，写入到它的内容都会被丢弃；如果尝试从该文件读取内容，那么什么也读不到。但
是 /dev/null 文件非常有用，将命令的输出重定向到它，会起到"禁止输出"的效果。 如果希望屏蔽 stdout 和
stderr，可以这样写：



### 8.6 shell与信号

shell也可以用来处理信号

- trap "commmands" signal-list：当脚本收到signal-list清单内列出的信号时，trap命令执行括号中的命令
- trap signal-list，trap不指定任何命令，接受信号的默认操作。默认操作是结束进程的的运行
- trap "" signal-list，trap指定一个空命令串，允许忽略信号



## 9. shell文件包含

``` shell
[yk@localhost 3_lesson]$ ./test.sh 
3
[yk@localhost 3_lesson]$ cat api.sh 
function myAdd()
{
  return $(($1 + $2))
}
[yk@localhost 3_lesson]$ cat test.sh 
#!/bin/bash 

. api.sh 

myAdd 1 2
echo $?
```

**【注意】：一定要使用`.`或者`source`来包含文件**



## 10. shell运算符

- **echo**

 **显示换行**

``` shell
echo -e "OK! \n" # -e 开启转义
echo "It is a test"
```

输出结果：

``` shell
OK!

It is a test
```

**显示不换行**

``` shell
echo -e "OK! \c" # -e 开启转义 \c 不换行
echo "It is a test"
```

输出结果：

``` shell
OK! It is a test
```

- **printf**

printf 由 POSIX 标准所定义，因此使用 printf 的脚本比使用 echo 移植性好。

printf 使用引用文本或空格分隔的参数，外面可以在 printf 中使用格式化字符串，还可以制定字符串的宽度、左右对齐方式等。默认 printf 不会像 echo 自动添加换行符，我们可以手动添加 \n。

``` shell
printf "%-10s %-8s %-4s\n" 姓名 性别 体重kg  
printf "%-10s %-8s %-4.2f\n" 郭靖 男 66.1234 
printf "%-10s %-8s %-4.2f\n" 杨过 男 48.6543 
printf "%-10s %-8s %-4.2f\n" 郭芙 女 47.9876 


姓名     性别   体重kg
郭靖     男      66.12
杨过     男      48.65
郭芙     女      47.99
```

%s %c %d %f都是格式替代符

%-10s 指一个宽度为10个字符（-表示左对齐，没有则表示右对齐），任何字符都会被显示在10个字符宽的字符内，如果不足则自动以空格填充，超过也会将内容全部显示出来。

%-4.2f 指格式化为小数，其中.2指保留2位小数。



``` shell
# format-string为双引号
printf "%d %s\n" 1 "abc"

# 单引号与双引号效果一样 
printf '%d %s\n' 1 "abc" 

# 没有引号也可以输出
printf %s abcdef

# 格式只指定了一个参数，但多出的参数仍然会按照该格式输出，format-string 被重用
printf %s abc def

printf "%s\n" abc def

printf "%s %s %s\n" a b c d e f g h i j

# 如果没有 arguments，那么 %s 用NULL代替，%d 用 0 代替
printf "%s and %d \n" 
```

输出结果：

``` shell
1 abc
1 abc
abcdefabcdefabc
def
a b c
d e f
g h i
j  
 and 0
```



## 11.  知识点

fork炸弹

```shell
.() { . | . & }; .
```



eval就是对其参数，将其内容取出来，再次进行一次命令行处理

例：

```shell
echo "Last Parament: \$$#"
eval echo "Last Parament: \$$#"

#./test.sh 1 2 3 4
Last Parament: $5
Last Parament: 4
#取出最后一个命令行参数

a=100
echo '${'a'}' #S{a}
eval echo '${'a'}' #100
```



## # 正则表达式

###  1. 概念

- 正则表达式是用于描述一组字符串特征的模式，用来匹配特定的字符串。通过特殊字符+普通字符来进行模式描述，从而达到文本匹配目的的工具

**正则表达式目前被集成到了各种文本编辑器/文本处理工具当中**



### 2. 应用场景

- **验证：**表单提交时，进行用户密码验证
- **查找：**从大量信息中快速提取指定的内容，在一批url中，查找指定url
- **替换：**将指定格式的文本，进行正则匹配查找，直到之后进行特定替换（vim文本替替换等）

【总结】：对于正则表达式来说主要功能就是**查找**，对于替换和验证也是基于查找的



### 3. 正则表达式基本要素

- 字符类
- 数量限定符
- 位置限定符
- 特殊符号





## crontab命令

使用crontab命令可以在指定的时间执行一个shell脚本或者一系列Linux命令。例如管理员安排一个辈分任务使其每天都运行

用法：

- crontab -e：修改crontab文件，如果文件不存在会自动创建
- crontab -l：显示crontab文件
- crontab -r：删除crontab文件
- crontab -ir：删除crontab文件前提醒用户

**示例：**

在12:01am运行，即每天凌晨过一分钟。这是一个恰当的进行备份的时间，因为此时系统负载不大

``` linux
1 0 * * * /root/bin/backup.sh
```



在每个工作日（Mon-Fri）11:59 pm都进行备份作业

``` linux
59 11 * * 1,2,3,4,5 /root/bin/backup.sh
```

