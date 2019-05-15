# 复习STL以及学习set&&map

----

## 六大组件

- 容器 80%  
  - 序列式容器：vector/list/string 扩展：deque
  - vector的缺点：增容，插入删除
  - 优点：随机访问
  - list的优点：插入删除方便）O(1)时间复杂度
  - 缺点：不能随机访问
  - deque：中控，一段一段的buffer
  - 看起来效率极高但是其实效率低下
- 算法 10%
- 迭代器  5%
  - **一种设计模式**
- 适配器 2%  stack/queue/priority_queue
  - 对一个类再次进行封装
- 仿函数 2%
  - 是一个类，重载了operaotor()
  - 函数对象，一个类的对象就像是一个函数一样
- 空间配置器 1%

### 容器：

关联式容器和序列式容器的不同之处在于关联式容器在进行插入数据的时候，不能随便来进行插入，首先要找到一个可以插入这个数据的位置，然后才能进行插入。

**数据与数据之间是相关联的。**

#### 序列式容器

**【注意】：vector/list/string**

- vector和array的优缺点：

array开辟的空间在栈上，但是栈的空间不够大有可能导致栈溢出，栈的空间大小一般都是8M~10M

- bitset位图

现场实现位图，底层要自己写

位图和布隆过滤器

布隆过滤器的最大缺点：不准确

#### 关联式容器

**【注意】：map/set/unordered_map/unordered_set**



**二叉搜索树->极端情况下效率变低**

**平衡树：**

- AVL树：高度平衡搜索二叉树，控制左右高度差绝对值不超过1，每一个子树也都是一个AVL树（严格平衡）

平衡因子：右子树的高度减去左子树的高度

- 红黑树：颜色控制最长路径不超过最短路径的2倍（近似平衡）

时间复杂度都是O(log2N)



## set

**对于数据元素不能进行改变**

**作用：**

1. key的模型，判断在不在？进行数据的查找
   1. 优势，效率高，时间复杂度O(logN)
2. 排序+去重



## multiset

**和set基本一样只是不进行去重**

**作用：**

1. 用来排序
2. 允许重复



## map和multimap

**multimap就是少了去重，允许key重复**

**map和multimap都会进行排序**

multimap没有operator[]，因为对于一个key有着多个value

## 对于Map[]的实现原理

**[]是key和value的映射**，以前的vector，string，deque是下标和元素的映射

返回的是**value的引用**

``` c++
mapped_type& operator[] (const key_type& k);
//返回值是value的引用

key_type是插入的键值对的key
mapped_type是插入的键值对的value
//首先调用insert成员函数
(*((this->insert(make_pair(k,mapped_type()))).first)).second
```





对于map中的成员函数的insert的返回值是pair<iterator，bool>

返回值是一个键值对，

第一个是一个迭代器：该迭代器如果元素存在的话，返回已经存在的该key的迭代器：如果不存在的话，将其插入然后返回一个指向插入的键值对的迭代器

第二是是一个布尔类型：如果插入的元素不存在的话，bool为真，如果插入的元素已经存在的话bool是false为假

``` c++
//统计一个单词出现的次数
//第一种，使用find来统计次数
//第二种，使用insert来统计次数
//第三种，使用operator[]来统计次数

std::string str[] = { "sort", "find", "end"};
typedef std::map<std::string, int> CountMap;
typedef std::map<std::string, int>::iterarotr CountMapIterator;
CountMap count_map;

//第三种方法，operator[]
for (const auto& e : str_array)
{
	count_map[e]++;    
}
```



对于字典的修改

``` C++
可以直接使用operator[]对于字典进行插入的修改

dict["sort"] = "字典"；
dict["bug"] = "幺蛾子"；
dict["xust"] = "西安科技大学"；
dict["left"] = "左边"；//插入pair<"left", "左边">
dict["left"] = "剩余"；//修改了left的value，修改为剩余

multimap不适合于统计次数
map可以统计次数
```



迭代器有着三种：
单向：forward_list

双向：list，map

随机：vector，string，deque



benchmark对于性能进行测试

``` C++
void benchmark
{
	
}
```



多节哈希









