# 对于pthread_cancel函数以及取消点的理解

## 1.pthread_cancel函数做了什么

> pyhread_cancel函数只是给线程发送了一个**请求**该请求是希望可以将该线程终止。
>
> - 所以对于该请求的话，只是对于线程的一个建议
> - 线程也可能就不会立即终止，会继续运行，直到运行到取消点的时候该线程才会退出



## 2. 取消点的理解

> - 取消点是线程检查他是否被取消的一个位置
>
> 取消点是如何出现的呢？
>
> - 对于取消点对于使用某些函数就会出现取消点
> - 例如：sleep，wait，waitpid，waitid，send等函数
> - 如图：这些函数都可以作为取消点
>
> ![](C:\Users\0\Pictures\typora\QQ截图20181119155942.png)
>
> ![](C:\Users\0\Pictures\typora\QQ截图20181119160003.png)



## 3.pthread_setcancelstate

> - 这个函数可以设置取消的状态，有两种状态PTHREAD_CANCEL_ENABLE（可取消状态）和PTHREAD_CANCEL_DISABLE（不可取消状态）。
>
> ``` c++
> #include <pthread.h>
> 
> pthread_setcancelstate(int state, int* oldstate);
> 
> 参数：
> 	state：将当前状态改为state
> 	oldstate：将该线程原先的状态放到oldtype所指向的空间里面
> 返回值：
> 	成功返回0，失败返回错误码
> ```
>
> 这两步是一个原子操作。
>
> - 对于**pthread_cancel函数默认**的是**PTHREAD_CANCEL_ENABLE可取消状态**。，当状态设为**PTHREAD_CANCEL_DISABLE**时，对于pthread_cancel的调用并**不会杀死线程**。相反，该取消请求对于这个**线程还处于挂起状态（也就是未决**），直到线程的**取消状态变为PTHREAD_CANCEL_ENABLE时**，线程将在**下一个取消点上对所有的挂起请求进行处理**。



## 4. pthread_setcanceltype

> 设置取消的类型。
>
> ``` c++
> #include <thread.h>
> 
> int pthread_testcanceltype(int type, int* oldtype);
> 
> 参数：
> 	type：将取消的类型设置为type
> 	oldtype：将该线程的取消类型放到oldtype所指向的空间里面
> 返回值：
> 	成功返回0，失败返回错误码
> ```
>
> - 我们默认的取消类型是推迟取消。也就是会运行到取消点再取消
> - 对于可以设置的取消类型有PTHREAD_CANCEL_DEFERRED（推迟取消），也就是默认的取消类型。
> - PTHRAED_CANCEL_ASYNCHRONOUS（异步取消），采用异步取消之后，线程可以在任意时间取消，不是非得到取消点才可以取消。



## 5. pthread_testcancel

> - 对于一个线程没有调用上面说的可以产生取消点函数，那么该线程就**没有取消点**，也就无法被取消，**取消请求**也就会**一直挂起**，**不会被线程处理。**
> - 所以如果要**对线程进行取消请求的话，可以自己给线程加上取消点**
> - **pthread_testcancel函数**就可以在程序**自己加上取消点。**
>
> ``` c++
> #include <thread.h>
> 
> void pthread_testcancel(void);
> ```
>
> **调用pthread_testcancel函数，如果有某个取消请求正处于挂起状态的话，而且取消并没有被设置为无效，那么该线程就会立即被取消。但是，如果取消被设置为无效的话，那么pthread_testcancel函数调用就没与效果**了。



