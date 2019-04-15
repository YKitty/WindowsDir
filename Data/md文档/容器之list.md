# 容器之list

---

- 对于list首先要知道其本质是一个**双向循环带头结点的链表**

## 1. 对于list的一些常用接口

### 1.1 构造部分

> - list（）， 直接构造一个空的list
> - list（int n，int value），构造n个value的list
> - list（iterator begin(), iterator end()），使用[begin(), end())半开半闭的区间进行构造
> - list（const list<T> & d），拷贝构造



### 1.2 迭代器部分

> - begin（），返回list首个元素的迭代器
> - end（），返回list最后一个元素的下一个位置的迭代器
>
>  



### 1.3 容量部分

> - bool empty（）const， 检测list是否为空，为空返回true，否则返回false
> - int size（）const，返回list中结点的个数
>
>  



### 1.4 对于list操作部分

> - void push_back(const T& d）， 尾插一个结点
> - void pop_back()， 尾删一个结点
> - void push_front(const T& d)， 头插一个结点
> - void pop_front()， 头删一个结点
> - void insert(iterator pos, const T& d)，在pos前面插入一个结点
> - void erase(iterator pos)， 删除pos位置的结点
> - void swap(list& x)， 交换两个list
> - void clear()， 将list中的数据进行清空



## 2. 迭代器失效

> 对于list进行**插入操作**的时候**不会造成迭代器失效**，因为插入产生的迭代器失效是由于增容所导致的，对于list不存在增容的情况所以不会产生迭代器失效的问题。
>
> 对于list进行**删除操作**的时候会**导致迭代器失效**，会将当前迭代器所指向的结点删除，所以该迭代器是会失效的



## 3. 对于list的自我实现

> 首先对于list其实现的时候，**list是一个模板**，可以产生各种类型的list，只要对list进行显示实例化，实例化后的list才是一个类型。例：list<int>，list<string>等等
>
> 由于其是一个模板，所以对于**声明与定义不可以分开**，分开的话有可能导致链接错误
>
> 所以只有一个文件，
>
> - list.h（list的实现，声明与定义都在这里）

### 3.1 list.h

``` c++
#ifndef __LIST_H__
#define __LIST_H__ 

#include <iostream>

namespace Mylist
{
  //双向循环带头结点
  //对于struct内部默认都是public类型的访问权限
  //struct要将其当做一个类，来看，
  //如果new一个该类的话，就会调用构造函数
  template <class T>
  struct ListNode
  {

    //对于T()，这是一个匿名对象，T也是一个类
    ListNode (const T& d = T())
      : _data(d)
      , _next(nullptr)
      , _prev(nullptr)
    {
    }

    T _data;
    //struct ListNode* _next;
    //struct ListNode* _prev;
    ListNode<T>* _next;
    ListNode<T>* _prev;

  };
  
  //迭代器本质上还是一个指针，只不过对于该指针的操作不一样了
  template <class T>
  struct ListIterator 
  {
    typedef ListNode<T> Node;
    typedef ListIterator<T> Self;
    ListIterator (Node* node)
      : _node(node)
    {
    }

    ListIterator (const Node& d)
      : _node(d._node)
    {
    }

    T operator* ()
    {
      return _node->_data;
    }

    //后置++
    //拷贝一份当前迭代器，然后返回拷贝好的迭代器
    Self operator++ (int)
    {
      Self temp(*this);
      _node = _node->_next;

      return temp;
    }

    //前置++
    Self& operator++ ()
    {
      _node = _node->_next;

      return *this;
    }

    bool operator!= (const Self& it)
    {
      //两个不相等返回true，相等返回false
      return _node != it._node;
    }


    Node* _node;
  };


  template <class T>
  class mylist 
  {
    typedef ListNode<T> Node;
  public:

    typedef ListIterator<T> iterator;
    
    iterator begin()
    {
      return iterator(_head->_next);
    }

    iterator end()
    {
      //返回的时候要返回最后一个元素的下一个位置
      return iterator(_head);
    }

    //开辟头结点并且在Node中默认初始化
    mylist ()
      : _head(new Node)
    {
      _head->_next = _head;
      _head->_prev = _head;
    }
    
    template <class Iterator>
    mylist (Iterator First, Iterator end)
      : _head(new Node)
    {
      _head->_next = _head;
      _head->_prev = _head;
      while (First != end)
      {
        push_back(*First);
        //++First;
        First++;
      }
    }

    mylist (int n, const T d = T())
      : _head(new Node)
    {
      _head->_next = _head;
      _head->_prev = _head;
      for (int i = 0; i < n; i++)
      {
        push_back(d);
      }
    }

    ~mylist ()
    {
      clear();
      delete _head;
      _head = nullptr;
    }

    //mylist (const mylist<T>& ml)
    //  : _head(new Node)
    //{
    //  _head->_next = _head;
    //  _head->_prev = _head;
    //  Node* ret = ml._head->_next;
    //  while (ret != ml._head)
    //  {
    //    push_back(ret->_data);
    //    ret = ret->_next;
    //  }
    //}

    //现代写法
    mylist (mylist<T>& ml)
      : _head(new Node)
    {
      _head->_next = _head;
      _head->_prev = _head;
      mylist<T> temp(ml.begin(), ml.end());
      swap(temp);
    }

    //mylist<T>& operator= (const mylist<T>& ml)
    //{
    //  Node* ret = ml._head->_next;
    //  while (ret != ml._head)
    //  {
    //    push_back(ret->_data);
    //    ret = ret->_next;
    //  }
    //}
    
    //现代写法
    //直接拷贝不管是不是自己给自己拷贝
    //mylist<T>& operator= (mylist<T> ml)
    //{
    //  swap(ml);

    //  return *this;
    //}
    
    //拷贝的时候判断一下是不是自己给自己拷贝
    mylist<T>& operator= (mylist<T>& ml)
    {
      if (this != &ml)
      {
        mylist<T> temp(ml);//拷贝构造
        swap(temp);
      }

      return *this;
    }
    

    bool empty()
    {
      return size() == 0 ? true : false;
    }

    size_t size()
    {
      size_t num = 0;
      Node* ret = _head->_next;
      while (ret != _head)
      {
        num++;
        ret = ret->_next;
      }

      return num;
    }

    void push_back(const T& d)
    {
      Node* tail = _head->_prev;
      Node* newNode = new Node(d);

      //head tail newNode 
      tail->_next = newNode;
      newNode->_prev = tail; 
      newNode->_next = _head; 
      _head->_prev = newNode;
    }

    void pop_back()
    {
      Node* tail = _head->_prev;
      Node* front = tail->_prev;

      //head front tail
      front->_next = _head;
      _head->_prev = front;
      delete tail;
    }

    void push_front(const T& d)
    {
      Node* first = _head->_next;
      Node* newNode = new Node(d);

      //_head newNode first 
      _head->_next = newNode;
      newNode->_prev = _head;
      newNode->_next = first;
      first->_prev = newNode;
    }

    void pop_front()
    {
      Node* del = _head->_next->_next;
      Node* first = _head->_next;

      //_head first del 
      _head->_next = del;
      del->_prev = _head;
      delete first;
    }

    void insert(iterator pos,const T& d)
    {
      Node* front = pos._node->_prev;
      Node* posNode = pos._node;
      Node* newNode = new Node(d);

      //front newNode pos 
      front->_next = newNode;
      newNode->_prev = front;
      newNode->_next= posNode;
      posNode->_prev = newNode;
    }

    void erase(iterator pos)
    {
      Node* front = pos._node->_prev;
      Node* posNode = pos._node;
      Node* back = posNode->_next;

      //front pos back 
      front->_next = back;
      back->_prev = front;
      delete posNode;
    }
    
    void clear()
    {
      Node* ret = _head->_next;
      while (ret != _head)
      {
        Node* tmp = ret->_next;
        delete ret;
        ret = tmp;
      }

      _head->_next = _head;
      _head->_prev = _head;
    }

    void swap(mylist<int>& ml)
    {
      //对于系统自己实现的swap,只是浅拷贝，对于交换指针，已经够了
      std::swap(_head, ml._head);
    }

  private:
    Node* _head;
  };

}

#endif //__LIST_H__
```

