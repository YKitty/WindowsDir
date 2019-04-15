# Java（继承总结）

```java
class Shape
{
    protected string name;
    public Shape(string name)
    {
        this.name = name;
    }
}

class Circle extends shape
{
	private double radious;
	public Circle()
    {
    	radious = 0;
    }
    
    public Circle(double radious)
    {
    	this.radious = radious;
    }
    
    public Circle(double radious, string name)
    {
    	this.radious = radious;
    	this.name = name;
    }
    
    public Print()
    {
    	System.out.println("name = " + name);
    	System.out.println("radious = " + radious);
    }
}

public class test
{
    public static viod main(String[] args)
    {
        Circle circle = new(23.46, "circle");
        circle.Print();
    }
}
```

> 错误：对于构造的时候，对派生类进行构造，派生类隐性的调用super(),对基类进行无参构造，可是基类没有无参构造函数，所以出现错误。
>
> 改正：
>
> - 给基类加一个无参构造
>
> ```java
> public shape
> {
> 	name = "Peter";
> }
> ```
>
> - 显性的对基类进行初始化
>   - 在派生类构造器的第一句加上super(name);就可以调用基类的带参构造了



> 注意：
>
> - 子类不可继承父类的构造器
> - 若父类的构造器带参，子类一定要调用super。从而到基类，在基类中进行构造
>
> 类中有构造器则系统不再创建构造器



```java
class Draw
{
    public Draw(String type)
    {
        System.out.println(type + "draw cons");
    }
}

class Shape
{
    private Draw draw = new Draw("Shape");
    public shape()
    {
        System.out.println("Shape cons");
    }
}

class Circle extends Shape
{
	private Draw draw = new Draw("Circle");
	public Circle()
    {
    	System.out.println("Circle cons");
    }
}

public class test
{
    public static void main(String[] args)
    {
        Circle circle = new Circle();
    }
}
```

> 正确输出：
>
> - Shape draw cons
> - Shape cons
> - Circle draw cons
> - circle cons



> 总结:
>
> - 子对象：类A中含有类B对象，然后把类B的对象称为类A的子对象
> - 子对象的目的：调用子对象的方法
> - 含有子对象的类的构造器的执行顺序：
>   - 先调用子对象构造器，然后执行构造器的其他语句
> - 如果派生类中子对象
>   - 调用基类构造
>   - 调子对象构造器
>   - 执行派生类其他构造器语句
> - 派生类构造器：
>   - super语句
>   - 子对象初始化
>   - 执行构造器的剩下语句
> - 派生类和基类中相同的成员变量，则基类的成员变量将会被隐藏起来，基类的对象还是存在的
> - 访问基类变量：
>   - 共有,受保护的：用super，必须是super.变量名(引用基类的变量)
>   - 私有：用基类的公有方法，用this.变量名，调用变量



继承的优点：

- 提高代码的可复用
- 使类和类之间产生联系——多态性



