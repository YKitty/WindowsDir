# mysql

----

## 1.mysql的基本使用

**对于无法使用中文，可以在创建表的最后面加上` CHARSET utf8`**

> 1. 连接到mysql
>
> ``` c++
> mysql [-h 主机] -u 用户 -p
> ```
>
> 2. 创建库
>
> ``` c++
> create database msg;
> //创建了库，msg
> ```
>
> 3. 查看已经有哪些库
>
> ``` c++
> show databases;
> ```
>
> 4. 使用库
>
> ``` c++
> -- 使用库
> use msg;
> ```
>
> 5. 创建表
>
> ``` c++
> -- 创建表
> create table teacher(
> 	name varchar(32),
> 	age int 
> )CHARSET utf8;
> //创建了表，teacher
> 
> create table student(
> 	name varchar(32),
> 	age int 
> )CHARSET utf8;
> //创建了表，teacher
> ```
>
> 6. 删除表
>
> ``` c++
> drop table teacher;
> //将表teacher删除
> ```
>
> 7. 查看当前库里有哪些表
>
> ``` c++
> show tables;
> ```
>
> 8. 向表中插入数据
>
> ``` c++
> insert into teacher(name, age)  values('范冰冰', 58);
> insert into teacher(age, name)  values(78, '冯小刚');
> 
> insert into student(name, age) values('王也'， 90)；
> insert into student(name, age) values('王爽'， 60)；
> ```
>
> 9. 查询
>
> ``` c++
> select name, age from teacher;
> select * from teacher
> ```
>
> 10. 删除一条记录
>
> ``` c++
> delete from teacher where age = '78';
> ```
>
> 11. 删除表
>
> ``` c++
> drop table teacher;
> //删除表teacher
> ```
>
> 12.查看表有哪些列
>
> ``` c++
> desc teacher;
> ```
>
> 13.如何查看表存放在哪里呢
>
> ``` c++
> cd /var/lib/mysql/
>     
> //必须要root权限
> ```
>
> 14. SQL的分类：
>
> - DDL
>   - create,drop,alter
> - DML
>   - insert,delete,update
> - DQL
>   - select
> - DCL(控制语句)
>   - grant,revoke,commit



创建学生表，要求有学号，姓名，成绩，并且插入两条记录

``` c++
create table student(
	id int,
    name varchar(30),
    score float
)CHARSET utf8;
//utf8表示支持中文
```



## 2. 库的操作

> 1. 创建库的语法
>
> ``` c++
> create database [if not exists] db_name [createspecification],...
> ```
>
> ``` c++
> create_specification:
> 	[DEFAULT] CHARACTER SET charset_name  (char set)
> 	[DEFAULT] COLLATE collation_name
> ```
>
> 2. 创建库
>
> ``` c++
> create database company1;
> ```
>
> 3. 查看创建数据库的系统给定的语句
>
> ``` c++
> show create database company1\G
> 
> Create Database: CREATE DATABASE `msg` /*!40100 DEFAULT CHARACTER SET latin1 */
> 【注意】：/*!40100 DEFAULT ...*/
> 	表示mysql>=4.01版本才可以执行这句话
> ```
>
> ![](C:\Users\0\Pictures\mysql\1541753312617.png)
>
> **40100表示！后面的语句必须是在40100版本以上的数据库才可以执行**
>
> 当我们创建数据库的时候没有指定字符集和校验规则是，系统使用默认。
>
> 字符集：utf8
>
> 校验规则：utf8_general_ci
>
> 4. 查看数据库版本
>
> ``` c++
> select version();
> ```
>
> 5. 创建库使用utf8字符集
>
> ``` c++
> create database company2 charset=utf8;
> ```
>
> 6. 创建库，使用utf8字符集，并制定校验规则
>
> ``` c++
> create database company3 charset=utf8 collate utf8_general_ci;
> ```
>
> 7. 查询字符集和校验规则
>
> ``` c++
> show charset;
> ```
>
> ![](C:\Users\0\Pictures\mysql\QQ截图20181109171421.png)
>
> 8. 修改默认的字符集
>
> ``` c++
> //root用户下
> vim /etc/my.cnf
> 
> [client]
> default-character-set=utf8
> 
> [mysqld]
> default-character-set=utf8
> ```
>
> 9. 校验规则
>
> ``` c++
> utf8_general_ci;//不区分大小写
> utf8_bin;//区分大小写
> ```
>
> 10. 创建库1（utf8_general_ci），库2（utf8_bin）
>
> ``` c++
> create database k1 collate utf8_general_ci;
> create database k2 collate utf8_bin;
> 
> use k1;
> create table ttt(name char(1), id int) charset = utf8;
> insert into ttt values('a', 1),('b', 2),('c', 3),('d', 4);
> //查询数据，按照name列排序
> select name, id from ttt order by name;
> 
> use k2;
> create table ttt(name char(1), id int) charset = utf8;
> insert into ttt values('a', 1),('B', 2),('C', 3),('d', 4);
> //查询数据，按照name列排序
> select name, id from ttt order by name;
> ```
>
> 11. 数据库的删除
>
> ``` c++
> drop database 库名；//实际工作中禁止使用
> ```
>
> 12. 查看当前mysql数据库的连接情况(查看有哪些客户端连接我的数据库)
>
> ``` c++
> show processlist
> ```
>
> 13. 数据库的备份和恢复
>
> ``` c++
> //备份数据
> mysqldump -u root -p msg;
> mysqldump -u root -p msg > msg.bk
> //备份就是把以前使用的mysql语句存储起来
> 
> //恢复数据
> mysql -u root -p
> create database msg;
> use msg;
> source ./msg.bk;
> ```
>
> 









































































































## 特殊的使用

### 1.   \G

采用\G之后表示一次输出一行，一行一行的输出

例：![](C:\Users\0\Pictures\mysql\QQ截图20181109164409.png)



![](C:\Users\0\Pictures\mysql\QQ截图20181109164459.png)



``` c++
show create database company1\G;
//将信息进行一行一行的输出
```

### 2. 查看版本信息

``` c++
select version();
```

![](C:\Users\0\Pictures\mysql\QQ截图20181109165122.png)



### 3. 如何查看终端是什么？

``` c++
echo $LANG

en_US.UTF-8//终端类型
```



