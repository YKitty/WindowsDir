# mysql

----

## 1.mysql的基本使用

mysql中对于关键字是不区分大小写的

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
> ![](C:\Users\0\Pictures\mysql\查看有哪些库.png)
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
> - DML（增删查改）
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
> 14. 查看当前处于那一个数据库下
>
> ``` C++
> //查看正处于那一个数据库
> select database();
> ```
>
> 15. 查看数据库支持的字符集校验规则
>
> ``` C++
> //查看校验规则
> show collation;
> ```
>
> 



### 校验规则对数据库的影响

校验规则使用utf8_general_ci不区分大小写

校验规则使用utf8_bin区分大小写

影响：

1. 查询结果：对于不区分大小写的，如果表中有a A，查询a的话，两个的都会显示出来。而如果区分大小写的话，查询a就只会显示a

![](C:\Users\0\Pictures\mysql\不区分大小写.png)

![](C:\Users\0\Pictures\mysql\区分大小写.png)

1. 排序结果：不区分大小写的，存储顺序是啥就输出啥，区分大小写的，大写字母在前面小写字母在后面

![](C:\Users\0\Pictures\mysql\不区分大小写的排序结果.png)

![](C:\Users\0\Pictures\mysql\区分大小写的查询结果.png)



### 显示创建数据库的语句

``` sql
show create database first_class;
```

![](C:\Users\0\Pictures\mysql\创建数据库的语句.png)

### 数据库中的``

【注意】：``是防止使用的数据库名刚好是关键字

### 修改数据库

修改数据库一般修改的都是数据库的字符集，校验规则

``` sql
alter database first_class charset=gbk
```

![](C:\Users\0\Pictures\mysql\修改字符集.png)

将数据库的字符集改为gbk

### 数据库删除

这是一个级联删除，也就是数据库中的数据和文件夹都会删除

``` sql
drop database 
```

![](C:\Users\0\Pictures\mysql\删库到跑路.png)

### 数据库的备份和恢复

#### 备份

``` sql
mysqldump -P3306 -u root -p 密码 -B 数据库名 > 数据库备份的文件
```

``` sql
mysqldump -u root -p first_class > mysql.sql
```

![](C:\Users\0\Pictures\mysql\备份.png)

![](C:\Users\0\Pictures\mysql\mysql_sql.png)

在备份的时候，必须在bash下进行操作

#### 还原

``` sql
mysql -u root -p < mysql.sql
```

### 查看链接状况

``` sql
show pprocesslist
```

![](C:\Users\0\Pictures\mysql\查看链接状况.png)

是为了告诉我们当前有哪些用户连接到了我们的mysql，如果查出那个用户不是你正常登录的，很有可能你的数据库被入侵了。

当以后发现你的数据库比较慢的时候，可以使用这个指令来查看数据库的连接情况

## 表的操作

### 创建表并且查看如何创建

![](C:\Users\0\Pictures\mysql\查看表的创建过程.png)

### 查询表中的数据

**`select * from student`**

![](C:\Users\0\Pictures\mysql\查询表中的数据.png)

按照判断条件查找

**`select * from student where name='张三'`**

![](C:\Users\0\Pictures\mysql\判断查找.png)

按照升序查找

**`select * from student order by id`**

### 修改表中的数据

**`update date set t1='1970-1-2'`**

![](C:\Users\0\Pictures\mysql\修改表之后时间戳会发生变化.png)

**【注意】：修改了表中的是数据之后，时间戳就会发生变化**

### 修改表中的数据类型

**`alter table person modify age smallint`**

![](C:\Users\0\Pictures\mysql\修改表的字段.png)

### 修改字段的名字

**`ALTER TABLE table_name CHANGE oldname newname int`**

## 视图的操作

### 创建一个视图

视图可以使用一个或者多个基本表来进行创建

**`CREATE VIEW view_name AS SELECT `**

### 查看视图信息

有着三种方式：

**`DESC view_name`**

**`SHOW TABLE STATUS LIKE view_name`**

**`SHOW CREATE VIEW view_name`**

### 查看所有的视图信息

**`SELECT * FROM information_schema.VIEWS`**

对于这个数据库中的这个表，里面有着所有关于视图的信息

### 修改，更新以及删除视图

和表的操作一样，使用

**`ALTER、UPDATE、DELETE`**



## 类型

### 字符串类型

enum和set：都是一个集合

对于enum只能是这个集合中的一个数值

对于set可以是这个集合中的多个

**底层都是使用数字来实现的，对于enum最大是65535，对于set最大是64**

### 对于set的查找

![](C:\Users\0\Pictures\mysql\set.png)

对于这样的set里面有hello和hello,world。如何查找出只要具有hello就显示出来呢

![](C:\Users\0\Pictures\mysql\find_in_set.png)

使用普通的查找，只能找到一个记录，但是使用find_in_set就可以查找出全部的数据了

对于find_in_set就是在一个集合中，查找出该元素，找到就返回下标，否则返回0

![](C:\Users\0\Pictures\mysql\example find_in_set.png)

## 表的约束

对于表的约束，真正约束的是数据类型。

作用：从业务逻辑角度保证数据的正确性

主要约束：null/not null，default，comment（列描述）,zerofill，primary key，auto_increment，unique_key

### 默认约束

**`DEFAULT`**指定某列的默认值

比如：一个字段是性别的时候，对于这个字段来说，男生出现的次数高。所以就会将这个字段的默认值设置为男

### 主键约束

**该列唯一，不可以为空**

主键约束有着好两种：

- 单字段主键
  - id int PRIMARY KEY;
  - PRIMARY KEY(id);
- 多字段主键
  - PRIMARY KEY(id, name);
  - 多字段主键，对于id以及name都有着限制

### 唯一性约束

要求**该列唯一，可以为空**，但是对于只能有一个，不能有多个

与主键约束的区别就是，这个可以为空，但是主键不可以为空

### 空属性

一般都是null都是默认的，但是对于数据为空就无法进行运算，所以要设置为不为空

### comment（列注释）

只是对于一个字段进行描述，只有在show create table tablename的时候才可以看到

### zerofill（宽度）

这个只是和int(10)进行搭配使用，对于int后面的数字代表的是一个数字显示的时候得宽度。

![](C:\Users\0\Pictures\mysql\zerofill.png)

可以看到进行输出的时候，对于int类型是按照宽度5进行输出的，宽度不够5的，进行0填充

### AUTO_INCREMENT

一般使用与主键，这是为了对于主键进行自增，当插入数据的时候，不进行插入主键的时候，主键的数据可以自己依次每次增加一，不会为空

一般AUTO_INCREMENT修饰的都是int类的数据

作用：每次插入新的记录的时候，系统自动生成字段的主键值

要求：一个表中只能有一个字段使用AUTO_INCREMENT约束，并且该字段必须是主键的一部分。

## 增删改查

### order by以及limit，offset

**`order by desc`**：结果按照降序排列

**`order by asc`**：结果按照升序排列

**`order by desc limit 2 offset 0`**：结果按照降序排列之后，取出两条记录

![](C:\Users\0\Pictures\mysql\order and limit.png)

## 删除表中的记录

### delete

**`delete from person where id = 3`**

![](C:\Users\0\Pictures\mysql\删除表中的记录.png)

### 删除整个表

**`delete from for_test_delete`**

并且删除之后，这个表的auto_increment还是会保留原来的

![](C:\Users\0\Pictures\mysql\for_test_delete.png)

**`truncate`**

1. truncate是直接对整个表进行操作，不能像delete对部分数据进行操作
2. 实际上truncate是不会对数据进行操作，所以比delete快
3. 这个会重置auto_increment，但是delete不会重置suto_increment
4. 这两个都不会将表结构删除，但是drop会将表结构删除

## 联表查询

### 内联

**`from 表1， 表2 where 条件`**

**`from 表1， join 表2 on 条件`**

不带条件，结果就是一个笛卡尔积

表1 ：m行

表2 ： n行

结恭共有：m*n行

### 外联

**左联**

**`from 表1 left join 表2 on 条件`**

**右联**

**`from 表1 right join 表2 on 条件`**

## 子查询

出现在 where条件后

子查询返回后

​	单行单列 id = （select id from 表）

​	多行单列 id in（select id from 表）

​			id > all（select id from 表）

​			id > any（select id from 表）

​	多行多列



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

### 4. 如何查看版本是否大于4.01版本

当使用**`show create database first_class`**显示出

/*!40100 default... */这就是当前的mysql的版本大于4.01版本

## 3. 小知识点

### 1. 如何清屏

system clear或者ctrl + L

MariaDB是mysql的一个分支，害怕mysql被Oracle收购收费，又创建出一个数据库

### 2. 退不出命令行时

使用**`'\c`**

![](C:\Users\0\Pictures\mysql\退出命令行.png)

### 3. SQL分类

DDL数据定义语言，用来维护数据的结构

``` sql
create,drop,alter
```

DML数据操作语言，用来对数据进行操作

``` sql
insert,delete,update
```

DQL数据查询语言吗，是DML的一个分支

``` sql
select
```

DCL数据控制语言，主要负责权限管理和事务

``` sql
grant,revoke,commit
```

### 4. 存储引擎

存储引擎：数据库管理系统如何存储数据，如何为存储的数据建立索引和如何更新、查询数据等技术的实现方法

mysql的存储引擎就是插件式存储引擎。

查看存储引擎：

``` sql
show engines;
```

![](C:\Users\0\Pictures\mysql\存储引擎.png)

默认的是InnoDB，这是mysql5.5版本之后默认使用的存储引擎，5.5之前的使用的是MyISAM

### 5. 时间戳

获取时间戳：**`time(NULL)`**

对于Linux下时间戳的范围是1970--2037年

这是因为对于Linux下时间戳是使用的32的整数进行表示的，

对于时间戳表示的是秒数，从1970到2037的秒数，已经到达32位整数的最大值了就会发生溢出

### 6. count

count字段的时候null不计入

count*的时候null要计算进去

### 7. OLAP Online Analyze Process

在线分析报告 	出数据报告

追求数据的吞吐效率

### 8. OLTP Online Transaction Process

在线业务过程		申请账号、聊天、买东西

追求实时性

### 9. 索引

一个为了解决搜索而出现的数据结构

内部可能是搜索树或者hash

数据库中使用的搜索树不是二叉树（平衡）

B+树（B-树系列）：（B-树 B+树 B*树）

波音公司，平衡（balance），作者三个都是B开头的

**分支越多高度越低，高度越低，读取结点次数越少**

数据库索引为什么使用B+树，不用红黑树

B+数是多叉树，所以高度比二叉树更低

读取结点次数更少

而磁盘的读取成本很高，减少磁盘的读取

提高了效率



**搜索树支持范围查找，比如where a > 100 and a < 200，对于hash只支持key查找**

**有序性的优点**：**直接查找一段范围**

对于NAME LIKE '%a'进行**模糊匹配**，这个只能**使用搜索树，不能使用hash**。**利用了有序性**



**创建索引的原则**

1. 索引不是越多越好
2. 不是频繁查询的字段不需要加索引
3. 区分不是很多的字段不需要加索引
4. 尽量使用复合索引去优化

**查询调优：**

**``EXPLAIN``**

可以看到每次查询的时候，遍历了多少行数据才命中了记录

**索引类型**

- 主键索引	  	
  - 每张表中都有主键，不能为NULL，不能重复
- 唯一键
  - 不能重复
- 普通索引
  - Key | Index（使用这两个关键字都可以进行创建索引）
- 全文索引
  - FULL TEXT
  - 不支持中文，直接使用搜索引擎解决
  - 搜索引擎（Solar/Sphinx）





**扩展：**

- 数据安全
  - 数据都应该有备份
  - 不要明文存储敏感信息
  - 数据的权限信息
- 如何优化数据库
  - 建库，建表
  - 优化查询语句
- 如何建库，建表
  - 博客系统
  - 功能：用户发文章
  - 用户针对文章发评论
  - 文章列表（按发表时间倒叙）
  - 文章详情
  - 文章列表（按时间倒序）