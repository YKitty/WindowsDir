# String

----

## 迭代器

``` c++
#include <iostream>
using namespace std;

void test()
{
  string num("1234");
  string::iterator it = num.begin();
  while (it != num.end())
  {
    cout << *it << " ";
    ++it;
  }
  cout << endl;
}

int main()
{
  test();
  return 0;
}
```

优势：给出统一的方式访问容器，屏蔽了底层复杂的细节

typedef实现的。（底层类似于指针）

不仅可以实现读，还可以实现写

**左闭右开**

- iterator
- rbegin（），最后一个位置，++rbegin的时候是向前面加
- rend（），第一个位置的前一个位置
- const_iterator只能读不能写
- reverse_iterator反向
- 

