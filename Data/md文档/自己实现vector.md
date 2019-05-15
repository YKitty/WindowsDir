# 自己实现vector

``` c++
#ifndef __VECTOR_H__
#define __VECTOR_H__ 

#include <iostream>
#include <cassert>
#include <cstring>

namespace Myvector
{
  //<模板>，T为模板参数
  template <class T>
  class myvector 
  {
  public:
    typedef T* iterator;
    typedef const T* const_iterator;

    iterator begin()
    {
      return _start;
    }

    iterator end()
    {
      return _finish;
    }
    
    const_iterator begin() const
    {
      return _start;
    }

    const_iterator end() const
    {
      return _finish;
    }

    myvector ()
      : _start(nullptr)
      , _finish(nullptr)
      , _endofstorage(nullptr)
    {}
    
    myvector (size_t n, T d)
      : _start(nullptr)
      , _finish(nullptr)
      , _endofstorage(nullptr)
    {
      while (n--)
      {
        push_back(d);
      }
    }
    
    myvector (iterator left, iterator right)
      : _start(nullptr)
      , _finish(nullptr)
      , _endofstorage(nullptr)
    {
      right--;
      while (right >= left)
      {
        insert(begin(), right[0]);
        right--;
      }
    }

    ~myvector ()
    {
      if (_start)
      {
        delete[] _start;
        _start = _finish = _endofstorage = nullptr;
      }
    }

    myvector (const myvector<T>& mv)
      : _start(nullptr)
      , _finish(nullptr)
      , _endofstorage(nullptr)
    {
        int len = mv._finish - mv._start;
        T* tmp = new T[len];
        for (size_t i = 0; i < len; i++)
        {
          tmp[i] = mv._start[i];
        }
        _start = tmp;
        _finish = tmp + len;
        _endofstorage = tmp + len;
    }

    myvector<T>& operator=(const myvector<T>& mv)
    {
      size_t lenSelf = _finish - _start;
      size_t  len = mv._finish - mv._start;
      if (lenSelf < len)
      {
        reserve(len);
      }
      //这只是浅拷贝
      //memcpy(tmp, mv._start, sizeof(T) * len);
      for (size_t i = 0; i < len; i++)
      {
        //每一次增加数据的时候,_finish应该向后走
        _start[i] = mv._start[i];
        _finish++;
      }
    }
    
    size_t capacity()
    {
      return _endofstorage - _start;
    }

    T& operator[](size_t pos)
    {
      assert(pos < size());

      return _start[pos];
    }

    const T& operator[](size_t pos) const 
    {
      assert(pos < size());

      return _start[pos];
    }

    size_t size()
    {
      return _finish - _start;
    }

    //T()表示直接对于这个T类型的数据进行初始化，一般也就是赋值为0
    void resize(size_t n, const T& d = T())
    {
      size_t begin = size();
      if (n <= size())
      {
        _finish = _start + n;
      }
      else 
      {
        reserve(n);
        for (size_t i = begin; i < n; i++)
        {
          _start[i] = d;
          //每一次增加一个元素的时候finish就要增加1
          _finish++;
        }
      }
    }

    void reserve(size_t n)
    {
      if (n > capacity())
      {
        size_t len = _finish - _start;
        T* tmp = new T[n];
        for (size_t i = 0; i < len; i++)
        {
          tmp[i] = _start[i];
        }

        _start = tmp;
        _finish = _start + len;
        _endofstorage = _start + n;
      }
    }

    void push_back(T d)
    {
      insert(_finish, d);
    }

    void insert(iterator pos, const T& d)
    {
      assert(pos <= _finish);
      //开始先记录下来pos的偏移量
      int offset = pos - _start;

      if (_finish == _endofstorage)
      {
        size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
        reserve(newcapacity);
        //如果增容的话，pos的位置发生改变
        pos = _start + offset;
      }

      //这里的pos一直没有改变，依旧是刚开始增容的那个
      for (iterator i = _finish - 1; i >= pos; i--)
      {
        i[1] = i[0]; 
      }

      pos[0] = d;
      _finish++;
      
      //pos加1，是为了可以让该指针依旧指向刚进来的那个位置
      pos++;
    }
    
    void erase(iterator pos)
    {
      assert(pos < _finish);
      
      for (iterator i = pos; i != _finish - 1; i++)
      {
        i[0] = i[1];
      }
      _finish--;
    }

    void pop_back()
    {
      if (_start == nullptr)
      {
        return;
      }
      else 
      {
        erase(_finish - 1);
      }
    }

  private:
    T* _start;//开始处的地址
    T* _finish;//最后一个数据的下一个地址
    T* _endofstorage;//容量的下一个地址
  };
}


#endif //__VECTOR_H__
```

