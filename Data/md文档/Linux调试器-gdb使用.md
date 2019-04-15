# Linux调试器-gdb使用

---

**退出**

> crtl + d或者quit命令

## 1. list/l 行号：

- 显示binFile源代码，接着上次的位置往下列，每次列10行

## 2. list/l  函数名：

- 列出某个函数的源代码

## 3. r或run：

- 运行程序

## 4. n或next：

- 单条执行

## 5. s或step：

- 进入函数调用

## 6. break/b 行号：

- 在某一行设置断点info

## 7. break函数名：

- 在某个函数开头设置断点

## 8. info break：

- 查看断点信息

## 9. finish：

- 执行到当前函数返回，然后停下来等待命令

## 10. print/p ：

- 打印表达式的值，通过表达式可以修改变量的值或者调用函数

## 11. p 变量：

- 打印变量值

## 12. set var：（set var 变量名=表达式）

- 修改变量值

## 13. continue（或c）：

- 从当前位置开始连续而非单步执行程序

## 14. run（或r）：

- 从开始连续而非单步执行程序

## 15. delete breakpoint：

- 删除所有断点

## 16. delete breakpoint n：

- 删除序号为n的断点

## 17. disable breakpoints：

- 禁用断点

## 18. enable breakpoints：

- 启用断点

## 19. info（或i）breakpoints：

- 参看当前设置了哪些断点

## 20. diaplay 变量名：

- 跟踪查看一个变量，每次停下都显示它的值

## 21. undisplay：

- 取消对先前设置的哪些变量的跟踪

## 22. until X（行号）：

- 跳至X行

## 23. breaktrace（或bt）：

- 查看各级函数调用及参数

## 24. info（或i）locals：

- 查看当前栈帧局部变量的值

## 25. quit：

- 退出gdb

