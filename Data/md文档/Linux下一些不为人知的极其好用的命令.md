# Linux下的一些不为人知的极其好用的命令

---------------

## 1. htop

替代top命令，更美观，更方便进程监控工具

需要使用yum进行下载

使用截图：

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/Linux/htop%E5%91%BD%E4%BB%A4.png)

## 2. axel

多线程下载工具，可以替代curl，wget命令

## 3. tldr

tldr：too long not read

翻译过来就是“太长不读”，tldr根据【二八原则】原理，将命令的常用场景给出示例，让人一下就懂

对于tldr有着多种客户端，可以进行使用，我使用的是web端的

## 4. iftop

和top命令差不多，只不过iftop是监控网络的工具

需要使用yum进行下载，并且在运行时，需要权限，也就是需要sudo提供权限

如图：

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/Linux/%E5%91%BD%E4%BB%A4/iftop/iftop.png)

从上图可以看出来，对于本机与那个网络IP地址进行的流量传输

## 5. dstat

对于网络进行监控

## 6. wireshark

安装：

```C++
//提供抓包功能
sudo yum install wireshark
//提供wireshark命令以及图形页面
sudo yum install wireshark-gnome
```







​	