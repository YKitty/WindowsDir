#复习C&&C++&&数据结构

## 宏和函数的对比

1. 宏对于类型没有要求，函数对于类型有着要求
2. 宏有可能造成代码冗余，但是对于函数没有代码冗余
3. 宏的执行速度快，函数的执行速度慢，有可能调用函数的代码都有可能大于函数实现的功能的代码长度
4. 宏有可能产生副作用，但是对于函数不会产生副作用。也就是对于宏来说的话，相当于是传地址，在宏里面可以改变外面的参数，但是对于函数来说不会产生副作用

## 对于 #include “ filename.h”和#include <filename.h>的区别

- 对于**#include“filename.h”**是先在源文件所在的目录下查找，然后在标准位置查找头文件
- 对于**#include<filename.h>**是直接在标准位置查找头文件，找不到就会提示编译错误

## 对于malloc，calloc以及realloc之间的区别

malloc在堆上申请空间，不进行初始化，申请成功返回首地址，申请失败返回NULL

函数原型：void* malloc(size_t size)

calloc和malloc一样只是进行了初始化

函数原型：void* calloc(size_t num, size_t size)

realloc对于已经在堆上申请的地址进行改变

函数原型：void* realloc(void* ptr, size_t size)

**改变之后还会将原有内存中的数据移动到新的空间**

有着两种情况：一种是在原有空间之后有足够大的空间

一种是在原有空间之后没有足够大的空间

## 对于整形提升

整形提升分

- int转换为char：int为四个字节，将int进行截取，只让一个字节的数据赋值给char，会造成数据的缺失
- char转换为int：一个字节转换为四个字节
  - 对于char（signed char）将增加的三个字节，用符号位来进行补充
  - 如果char的符号位是1，那就是增加了0Xffffff
  - 如果符号位是0，就是增加了0X000000
  - 对于unsigned char直接将增加的三个字节用0补充

## 对于二叉数的面试题

- 二叉树的遍历（递归和非递归）

  - 前序遍历

  1. 递归：先输出再次对于左子树和右子树进行递归的遍历

     终止条件：root=NULL

  2. 非递归：将左路结点全部进行压栈，在压栈的时候同时，进行输出。压栈完成之后，对于栈顶元素进行出栈，然后再次对于该节点的右子树进行同样的处理（左路结点进行压栈，对于右路结点进行处理）

  - 中序遍历

  1. 递归：先进行对于左子树的遍历，在进行输出，在对于右子树进行遍历，

     终止条件：root=NULL

  2. 非递归：将左路结点全部进行压栈，但是不进行输出，在进行出栈的时候，进行输出，同时对于右子树进行同样的处理

  - 后序遍历

  1. 递归：先对于左子树和右子树进行遍历，然后在进行输出

     终止条件：root=NULL

  2. 非递归：对于后序遍历的时候，也是先将左路结点全部进行压栈处理，但是对于是否对于右子树进行输出，有着条件判断，当右子树为NULL或者访问的上一个结点就是右子树的结点就进行输出，否则就需要对于右子树也进行左路结点全部进行压栈

- 对于二叉树的非递归的镜像

  - 对于非递归的方法来说和，非递归的后序遍历二叉树的结点一样，要从右子树开始进行镜像的交换



## kill

kill命令：可以向用户态的进程发送信号

kill命令内部是一个调用kill()系统调用

kill发送一个信号该信号被系统将进程的task_struct（进程控制块）中的进程的未决信号集的对于这一信号的位图置为1，当该进程检测到该信号到来之后，就执行该信号的默认动作

``` Linux
//向进程号为1234的进程发送一个SIGTERM（15）信号，
//kill掉一个进程，但是有可能该进程不能被杀掉，因为对于该信号进程可以忽略或者阻塞该信号
kill 1234;

//对于kill -9进程不会忽略或者阻塞该信号，遇到该信号会直接执行该信号的默认动作
```

对于SIGTERM信号，进程不会立即处理该信号，而是要等到进程继续执行之前