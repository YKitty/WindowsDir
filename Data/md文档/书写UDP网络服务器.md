# 书写UDP网络服务器

----

## # 前序：

> **UDP是不面向连接的，是面向数据报的，是不可靠**

## # 套接字

> 就是**IP地址+端口号 **
>
> **IP地址**：4字节
>
> **端口号**：2字节，也就是说范围是0~65536
>
> IP地址的理解：
>
> - **IP地址用来标识一个主机**
>
> 端口号的理解：
>
> - 端口号就是用来告诉操作系统要对于那一个进程进行操作，也就是说**端口号就是用来标识一个进程**
> - **一个端口号只可被一个进程所占用**，但是**一个进程可以拥有多个端口号**，也就是**进程和端口号是一对多的关系**
>
> 所以**套接字就可以准确的标识一台主机上的一个进程**，从而完成**计算机之间的通信**
>
> **计算机之间的通信：**
>
> - **主机A的某个进程与主机B上的另一个进程进行通信**



##  # 网络字节序转换

> 对于数据在网络中传输的时候有着自己遵循的传输规则**大端传输**
>
> 对于主机上的数据的传输序列有着两种：
>
> - 大端：即高位字节序放在低地址上
> - 小端：即低位字节序放在低地址上
> - 传输：**均是先传输低地址上的数据然后是高地址上的数据**
>
> 所以对于主机上的数据传输的时候传输到网络上的时候有可能导致数据错误（例如主机上是小端的时候，所以需要进行转换）
>
> 转换函数：
>
> ``` c++
> #include <arpa/inet.h>
> 
> uint32_t htonl(uint32_t hostlong);
> uint16_t htons(uint16 hostshort);
> uint32_t ntohl(uint32_t netlong);
> uint16_t ntohs(uint16_t netshort);
> ```
>
> h：表示主机host name
>
> n：表示网络network
>
> l：表示4字节long
>
> s：表示2字节short



## #地址转换函数

> - 字符串转化为in_addr
>   - `in_addr_t inet_addr(const char* strptr)`
> - in_addr转化为字符串
>   - `char* inet_ntoa(struct in_addr inaddr)`
>   - 具有不可重入性，也就是不可多次调用，因为该函数自己在静态区开辟一块空间用来存放IP地址字符串的



## 1. 对于socket函数的使用

### 1.1 函数原型

``` c++
int socket(int domain, int type, int protocol);

domain: 领域
	AF_INET：IPV4
	AF_INET6：IPV6
type: 类型
	SOCK_STREAM
	SOCK_DGARM
protocol: 协议
```

### 1.2 函数的作用

>  在通信领域中创建一个未被绑定的套接字，并且返回一个文件描述符，可以在以后对套接字进行操作的函数调用中使用



## 2. 对于bind函数的使用

### 2.1 函数原型

``` c++
int bind(int socket, const struct sockaddr* address, socklen_t address_len);
```

### 2.2. 函数的作用

> 该函数采用先前**创建好的套接字来对于IP地址以及端口号进行绑定**，也就是表示该套接字可以标识出在一个网络中一台确定的主机并且主机中的进程



## 3. 对于recvfrom函数的使用

## 3.1 函数原型

``` c++
ssize_t recvfrom(int socket, void* restrict buffer, size_t length, 
                 int flags, struct sockaddr* restrict address, 
                socklen_t* restrict address_len);

socket：要接受那一个套接字的消息
buffer：用来接收消息的缓存区
length：接收的消息的长度
flags：类型
address：空指针或者存储发送信息的sockaddr结构
addless_len：指定地址参数指向的sockaddr结构的长度
```

### 3.2 函数的作用

> 用来接收从socket套接字发送来的消息。该套接字的sockaddr结构也知道



## 4. 对于sendto函数的使用

### 4.1 函数原型

``` c++
ssize_t recvfrom(int socket, const void* message, size_t length, 
                 int flags, const struct sockaddr* dest_addr, 
                socklen_t* dest_len);
```

### 4.2 函数的作用

> 该函数是socket套接字从dest_addr出接收消息