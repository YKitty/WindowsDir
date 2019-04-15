# 自己实现sleep函数

----

## 1. 首先需要了解sleep函数是什么

> - 现象：就是让进程停止多少秒。sleep（5），就是使进程停止五秒。



## 2. 实现所需的东西：

> - 采用了alarm、sigprocmask、sigsuspend、sigaction等系统调用接口，还有sigemptyset、sigfullset、sigaddset、sigdelset、sigismember等信号集函数
> - 对于信号集函数：
>   - 除了sigmember函数外，其余四个函数都是成功返回0，出错返回-1.sigismember是一个布尔函数，用于判断一个信号集的有效信号中是否包含某种信号，若包含则返回1，不包含返回0，出错返回-1.



## 3.实现

> ``` c++
> #include <iostream>
> #include <signal.h>
> #include <unistd.h>
> 
> using namespace std;
> 
> void handler(int signo)
> {
>   //cout << "catch a signal, signo:" << signo << endl;
> }
> 
> int mysleep(int secs)
> {
>   int unslept = 0;
>   struct sigaction act;
>   struct sigaction oact;
>   
> 
>   act.sa_handler = handler;
>   act.sa_flags = 0;
>   sigemptyset(&act.sa_mask);
> 
> 
>   sigaction(SIGALRM, &act, &oact);
>   alarm(secs);
>   pause();//将进程挂起
> 
>   unslept = alarm(0);//对闹钟进行清空并且知道该闹钟是不是，被提前唤醒
>   sigaction(SIGALRM, &oact, NULL);//将对于信号14的处理改变为最初的默认处理，而不是执行自定义处理函数
>   return ret;
> }
> 
> int main()
> {
>   while (1)
>   {
>     if(mysleep(1) == 0)
>     {
>       cout << "1 seconds over" << endl;        
>     }
>     else
>     {
>       cout << "sleep mistake" << endl;
>     }
>   }
>   return 0;
> }
> ```
>
> 【问题】：
>
> - 信号处理函数sig_alrm函数啥都没干，为什么还要注册他作为SIGALRM信号的处理函数？不注册信号处理函数可以吗？（SIGALRM会终止进程？）
>   - 注册sig_alrm函数是为了对于SIGALRM信号要递达的的时候的处理动作是捕捉，从而可以让挂起的进程终止。从而实现了mysleep
>   - 不注册信号处理函数不可以，如果默认处理动作不是捕捉的话，那么就有可能导致该进程一直挂起，或者直接终止，从而无法实现mysleep的功能
> - 为什么在mysleep函数返回前要恢复SIGALRM信号原本的sigaction？（想想不恢复怎么样）
>   - 如果不恢复原本的信号处理动作这样就会导致，执行对于该信号的处理动作发生改变
>   - 如果再来一个SIGALRM信号的话，就会导致默认处理动作不一致，从而出现错误
>   - 例子：
>     - 对于mysleep函数来说，main函数只是一个调用者。只是想睡一觉，没让你在其睡觉的时候让你把他打的鼻青脸肿的
> - mysleep函数的返回值表示什么含义？什么情况下返回非0值？
>   - mysleep返回值表示的是对于上一个alarm函数是否提前取消闹钟了。如果提前结束的话，那么就会返回上一个alarm函数剩余的秒数，否则返回0。
>
> 【注意】：
>
> - 该种方法存在着巨大的问题，那就是该进程的原子性问题，因为将alarm函数与pause函数是分为两步操作的，不是原子操作，比如：alarm函数设定闹钟之后，
>   - 内核调度优先级更高的进程取代当前进程执行，并且优先级更高的进程有很多个，每个都要执行很长的时间
>   - secs秒之后闹钟超时了，内核发送SIGALRM信号给这个进程，处于未决状态
>   - 优先级更高的进程执行完了，内核要调度回这个进程执行。SIGALRM信号递达，执行处理函数sig_alrm之后再次进入内核
>   - 返回这个进程的主控制流程，alarm（secs）返回，调用pause挂起等待
>   - 可是SIGALRM信号已经处理完了，还等待什么呢？
> - 这样就会出错了

> - 出现这个问题的根本原因是**系统运行的时序**并不想我们写程序所设想的那样。虽然alarm（secs）紧接着的下一行就是pause（），但是无法保证pause（）一定会在调用alarm（secs）之后的secs秒之内被调用。由于**异步事件在任何时间都有可能发生**（这里的异步事件指出现更高优先级的进程），如果我们写程序是考虑不周密，就有可能**由于时序问题而导致错误，这就叫做竞态条件。**
>
> ##### 解决方法
>
> - 第一种，**在调用pause之前屏蔽SIGALRM信号使它不能提前递达就可以了**
>
>   - 1. 屏蔽SIGALRM信号
>     2. alarm（secs）
>     3. 解除对SIGALRM信号的屏蔽
>     4. pause（）
>
> - **从解除信号屏蔽到调用pause（）之间存在间隙，SIGALRM仍有可能在这个间隙递达。要消除这个间隙，我们把解除屏蔽移到pause后面可以吗？**
>
>   - 屏蔽SIGALRM信号
>   - alarm（secs）
>   - pause（）
>   - 解除对SIGALRM信号的屏蔽
>
> - 这样就更不行了，**还没有解除SIGALRM信号的屏蔽就解除pause（），pause（）这样就根本不可能等到SIGALRM信号**。要是**“解除SIGALRM信号”和“pause的挂起等待信号”这两步合成一个原子操作**就好了。这正是**sigsuspend函数**的功能。
>
> - ``` c++
>   #include <signal.h>
>   
>   int sigsuspend(const sigset_t* sigmask);
>   
>   参数：
>   	sigmask：该信号集里面就是该进程的信号屏蔽字
>   ```
>
> - 功能：
>   	和pause一样，**sigsuspend没有成功返回值**，只有**执行了信号处理函数**之后sigsuspend才返回，返回值为-1，errno设置为EINTR。调用sigsuspend是，**进程的信号屏蔽字有sigmask参数指定**，可以通过指定的**sigmask来临时解除对某个信号的屏蔽**，然后挂起等待，**当sigsuspend返回时进程的信号屏蔽字恢复为原来的值**，如果原来对该信号是屏蔽的，从sigsuspend返回后仍然是屏蔽的。

> 优化：
>
> ``` c++
> #include <iostream>
> #include <signal.h>
> #include <unistd.h>
> 
> using namespace std;
> 
> void handler(int signo)
> {
>   //cout << "catch a signal, signo:" << signo << endl;
> }
> 
> int mysleep(int secs)
> {
>   int unslept = 0;
>   struct sigaction act;
>   struct sigaction oact;
>   sigset_t newmask, oldmask, sigmask;
>   
>   //设定对于SIGALRM信号采取自定义的函数处理
>   act.sa_handler = handler;
>   act.sa_flags = 0;
>   sigemptyset(&act.sa_mask);
>   sigaction(SIGALRM, &act, &oact);
> 
>   //对于该进程屏蔽SIGALRM信号
>   sigemptyset(&newmask);
>   sigaddset(&newmask, SIGALRM);
>   sigprocmask(SIG_BLOCK, &newmask, &oldmask);
>   
>   //调用alarm函数，并且解除对于SIGALRM信号的屏蔽，并且把进程挂起 
>   alarm(secs);
>   sigmask = oldmask;
>   //确保SIGALRM信号集里面没有SIGALRM信号，防止该信号被继续屏蔽
>   //因为sigmask是该进程的信号屏蔽字进行一个指定
>   sigdelset(&sigmask, SIGALRM);
>   sigsuspend(&sigmask);
>   
> 
>   unslept = alarm(0);//确保停留了secs秒
> 
>   //将对于SIGALRM信号的处理改为原先该进程对于其的处理
>   sigaction(SIGALRM, &oact, NULL);//将对于信号14的处理改变为最初的默认处理，而不是执行自定义处理函数
>   
>   //将进程的信号屏蔽字，也改为原先进程的信号屏蔽字
>   sigprocmask(SIG_SETMASK, &oldmask, NULL);
>   return unslept;
> }
> 
> int main()
> {
>   while (1)
>   {
>     if (mysleep(1) == 0)
>     {
>       cout << "1 seconds over" << endl;
>     }
>     else
>     {
>       cout << "mysleep mistake" << endl;
>     }
>   }
>   return 0;
> }
> ```
>
> 对于此次优化，最主要的就是将alarm（）函数和pause（）函数和在了一起，使其变成了一个原子操作。
>
> 流程：
>
> - 调用sigprocmask（SIG_BLOCK， &newmask， &oldmask），屏蔽SIGALRM信号
> - 调用sigsuspend（&sigmask）；解除对SIGALRM信号的屏蔽，然后挂起等待
> - SIGALRM信号递达后suspend（）返回，自动恢复原来的屏蔽字，也就是再次屏蔽SIGALRM信号
> - 调用sigprocmask(SIG_SETMASK，&oldmask， NULL)；再次解除对SIGALRM的屏蔽







