# Spring Boot复习

- [1. 前三的开发语言](#1-前三的开发语言)
- [2. 主流的开发框架](#2-主流的开发框架)
- [3. Spring的概述](#3-spring的概述)
- [4. Maven简介](#4-maven简介)
- [5. 依赖注入](#5-依赖注入)
    - [5.1 配置类](#51-配置类)
    - [5.2 运行](#52-运行)
- [6. Enable*注解的工作原理](#6-enable注解的工作原理)
- [7. Spring MVC概述](#7-spring-mvc概述)
    - [7.1 MVC逻辑关系](#71-mvc逻辑关系)
    - [7.2 Spring MVC常用注解](#72-spring-mvc常用注解)
    - [7.3 Spring Boot原理剖析](#73-spring-boot原理剖析)
- [8. Starter pom](#8-starter-pom)
- [9. Docker](#9-docker)
    - [9.1 概念](#91-概念)
    - [9.2 作用](#92-作用)
    - [9.3 优势](#93-优势)
        - [9.3.1 具体的优势](#931-具体的优势)
- [10. Spring Data JPA](#10-spring-data-jpa)
    - [10.1 概念](#101-概念)
    - [10.2 定义数据访问层](#102-定义数据访问层)
    - [10.3 如何配置](#103-如何配置)
- [11. Spring Boot下的Spring Data JPA](#11-spring-boot下的spring-data-jpa)
    - [11.1 使用](#111-使用)
    - [11.2 特点](#112-特点)

------------------

## 1. 前三的开发语言

TIOBE前三的**开发语言**：**Java，C，C++**

## 2. 主流的开发框架

主流的**开发框架**：**SSM，SSH，Spring Boot**

- SSM：**Spring+SpringMVC+MyBatis**框架集由Spring、MyBatis两个开源框架整合而成（SpringMVC是Spring中的部分内容） 
- SSH：SSH是 **struts+spring+hibernate**的一个集成框架，Web应用程序开源框架。分为四层：**表示层，业务逻辑层，数据持久层以及与域模块层**
- Spring Boot：目的解决Spring应用的**简化初始化搭建以及开发过程**。该框架使用特定的方式来进行配置。

## 3. Spring的概述

Spring框架是一个**轻量级的企业级的开发的一站式解决方案**。所谓解决方案就是可以**基于Spring解决Java EE开发的所有问题。**Spring框架主要提供了**IOC容器，AOP，数据访问，Web开发，消息，测试**等相关技术支持。

Spring使用简单**POJO**（即**无任何限制的普通Java对象**）来进行企业级开发。每一个被**Spring管理的Java对象称之为Bean**；而Spring提供一个**IOC容器**用来**初始化对象**，解决对象间的**依赖管理和对象的使用**。

## 4. Maven简介

Apache Maven是一个**软件项目管理工具**。基于**项目对象模型（Project Object Model，POM）**的概念，Maven可用来管理**项目的依赖、编译、文档**等信息。

使用Maven管理项目时，项目依赖的**jar包**将**不再包含在项目**内，而是集中放置在**用户目录下的.m2文件夹**下。

## 5. 依赖注入

### 5.1 配置类

1. @Configuration声明当前类是一个配置类
2. 使用@ComponentScan，自动扫描包名下所有使用@Service、@Component、@Repository和@Controller的类，并注册为Bean

### 5.2 运行

1. 使用AnnotationConfigApplicationContext作为容器，接受输入一个配置类作为参数
2. Context.getBean(UseFunctionService)获得声明配置的UseFunctionService的Bean

## 6. Enable*注解的工作原理

**第一部分：**

- @EnableAspectJAutoProxy开启对AspectJ自动代理的支持
- @EnableAsync开启异步方法的支持
- @EnableScheduling开启计划任务的支持

**第二部分：**

- @EnableWebMvc开启Web MVC的配置支持

**第三部分：**

- @EnableConfigurationProperties开启对@ConfigurationProperties注解配置Bean的支持
- @EnableJpaRepositories开启对Spring Data JPA Repository的支持
- @EnableTransactionManagement开启注解式事务的支持
- @EnableCaching开启注解式的缓存支持

**作用：**通过简单的@Enable*开启一项项功能的支持，从而避免自己配置大量的代码，大大降低使用难度。

**原理：**所有的注解都有一个**@Import注解**，@Import是用来导入配置类的，这也就意味着这些自动开启的实现其实也就是**导入一些自动配置的Bean。**

**导入的配置方式：**

- 直接导入配置类
- 依据条件选择配置
- 动态注册Bean

## 7. Spring MVC概述

### 7.1 MVC逻辑关系

**Spring MVC和三层架构的关系**

MVC：Model + View + Controller（数据模型+视图+控制器）

三层架构：Presentation tier + Application tier + Data tier（展现层 + 应用层 + 数据访问层）

实际上MVC对应的不是三层架构的三层。**MVC只存在三层架构的展现层**，M是数据模型，是包含数据的对象。在Spring MVC中有一个专门的Model类，用来和V之间的数据交互、传值；V指的是视图页面，包含JSP、freeMarker、Velocity、Thymeleaf、Tile等；C当然就是控制器（Spring MVC的注解@Controller的类）

### 7.2 Spring MVC常用注解

1. **@Controller**

@Controller注解在类上表明这个类是**Spring MVC里的Controller**，将其声明为Spring的一个Bean，Dispatcher Servlet会自动扫描注解了此注解的类，并将Web请求映射到**注解了@RequestMapping的方法上**

2. **@RequestMapping**

@RequestMapping注解是用来**映射Web请求（访问路径和参数）、处理类和方法**的。@RequestMapping可以**注解在类或者方法上**。注解在方法上的@RequestMapping路径会继承注解在类上的路径，@RequestMapping支持Servlet的request和response作为参数，也支持对request和response媒体类型进行配置

3. **@ResponseBoby**

@ResponseBoby支持**将返回值放在response体内**，而不是返回一个页面。此注解可**放置在返回值前或者方法上**

4. **@RequestBoby**

@RequestBoby允许**request的参数在request体**中，而不是直接链接在地址后面。此注解**放置在参数前**

5. **@PathVariable**

@Path Variable用来**接收路径和参数**，如/news/001，可接收001作为参数，此注解**放置在参数前**

6. **@RestController**

@RestController是一个**组合注解**，**组合了@Controller和@ResponseBoby**，这就意味着当你只**开发一个和页面交互数据的控制的时候，需要使用此注解**。若没有此注解想要实现上述功能，则需自己在代码中加@Controller和@ResponseBoby两个注解

### 7.3 Spring Boot原理剖析

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/%E5%85%B6%E4%BB%96/Spring%20Boot/Spring%20MVC%E5%8E%9F%E7%90%86%E5%89%96%E6%9E%90.jpg)

## 8. Starter pom

Spring Boot为我们提供了简化企业级开发绝大多数场景的starter pom，只要使用了应用场景所需要的starter pom，相关的技术配置将会消除，就可以得到Spring Boot为我们提供的自动配置的Bean。

|             名称              |                             描述                             |
| :---------------------------: | :----------------------------------------------------------: |
|      spring-boot-starter      | Spring Boot核心starter，包含自动配置、日志、yaml配置文件的支持 |
| spring-boot-starter-actuator  |                准生产特性，用来监控和管理应用                |
|    spring-boot-starter-aop    |           使用spring-aop和AspectJ支持面向切面编程            |
|   spring-boot-starter-batch   |                     对Spring Batch的支持                     |
| spring-boot-starter-data-jpa  |   对JPA的支持，包含spring-data-jpa、spring-orm和Hibernate    |
|   spring-boot-starter-jdbc    |                      对JDBC数据库的支持                      |
| spring-boot-starter-thymeleaf |      对Thymeleaf模板引擎的支持，包含于Spring整合的配置       |
|    spring-boot-starter-web    |        对Web项目开发的支持，包含Tomcat和spring-webmvc        |

## 9. Docker

### 9.1 概念

Docker是一个**轻量级容器技术**，类似于虚拟机技术（xen，kvm，vmware，virtualbox）。Docker是**直接运行在当前操作系统（Linux）之上**，而不是运行于虚拟机中，但也实现了虚拟机技术的**资源隔离**，**性能远远高于虚拟机技术。**

### 9.2 作用

DOcker支持**将软件编译成一个镜像**（image），在这**镜像里做好对软件的各种配置**，然后发布这个镜像，使用者可以使用运行这个镜像，**运行中的镜像称之为容器**（container），容器的启动是非常快的，一般都是**以秒为单位。**

### 9.3 优势

具有五大优势。**持续集成、版本控制、可移植性、隔离性和安全性**

- 持续控制

如果你需要在一个产品发布周期中完成一次升级，你可以很容易地将需要变更的东西放到Docker容器中，测试它们，并且使你已经存在的容器执行相同的变更 

- 版本控制

Docker容器还可以像**git仓库一样**，可以让你提交变更到Docker镜像中并通过**不同的版本来管理**它们。

举例：设想如果你因为完成了一个组件的升级而导致你整个环境都损坏了，Docker可以让你轻松地回滚到这个镜像的前一个版本。这整个过程可以在几分钟内完成，如果和虚拟机的备份或者镜像创建流程对比，那Docker算相当快的，它可以让你快速地进行复制和实现冗余。此外，启动Docker就和运行一个进程一样快。 

- 可移植性

所有**主流的云计算提供商**，包括亚马逊AWS和谷歌的GCP，都将Docker融入到他们的平台并**增加了各自的支持** 

- 隔离性

Docker可以确保你的**应用程序与资源是分隔开的** 

- 安全性

Docker确保运行在容器中的应用程序和其他容器中的应用程序是完全分隔与隔离的，在通信流量和管理上赋予你完全的控制权。Docker容器不能窥视运行在其他容器中的进程。从体系结构角度来看，**每个容器只使用着自己的资源（从进程到网络堆栈）。** 

#### 9.3.1 具体的优势

1）**标准化应用发布**，docker容器包含了运行环境和可执行程序，可以跨平台和主机使用；

2）**节约时间**，快速部署和启动，VM启动一般是分钟级，docker容器启动是秒级；

3）**方便构建基于SOA架构或微服务架构的系统**，通过服务编排，更好的松耦合；

4）**节约成本**，以前一个虚拟机至少需要几个G的磁盘空间，docker容器可以减少到MB级；

5）**方便持续集成**，通过与代码进行关联使持续集成非常方便；

6）可以作为**集群系统的轻量主机或节点**，在IaaS平台上，已经出现了CaaS，通过容器替代原来的主机。

## 10. Spring Data JPA

### 10.1 概念

**JPA即Java Persistence API**。JPA是一个基于O/R映射的标准规范。所谓规范即**只定义标准规则而不提供实现**，软**件提供商按照标准规范来实现，而使用者只需按照标准规范中定义的方式来使用**，而不用和软件提供商的实现打交道。JPA的主要实现由**Hibernate、EclipseLink和OpenJPA**等，这样意味着我们使用JPA来开发，无论是那一个开发方式都一样的。**黑盒使用**

Spring Data JPA是Spring Data的一个子项目，他通过提供基于JPA的Repository极大地减少了JPA作为数据访问方案的代码量。

### 10.2 定义数据访问层

使用Spring Date JPA简历数据访问层十分简单，只需要定义一个继承JpaRepository的接口即可。

### 10.3 如何配置

使用Spring Data JPA可通过@EnableJPARespositories注解来开启Spring Data JPA的支持，@EnableJpaRepositories接收的value参数用来扫描数据访问层所在包下的数据访问的接口定义。

## 11. Spring Boot下的Spring Data JPA

### 11.1 使用

Spring Boot**自动开启了对Spring Boot JPA的支持**，即我们**无须在配置类中显示声明@EnableJPARespositories**。在Spring Boot下使用Spring Data JPA，在项目的**Maven依赖里添加spring-boot-starter-data-jpa，然后只需定义DataSource、实体类和数据访问层，并在需要使用数据访问的地方注入数据访问层的Bean即可，无须任何额外配置。**

### 11.2 特点

Spring Data JPA是Spring基于ORM框架、JPA规范封装的一套JPA应用框架。

- 可使开发者**用极简的代码即可实现对数据的访问和操作**。
- 他提供了包括增删改查等在内的常用功能，且**易于扩展，学习并使用**。
- Spring Data JPA可以**极大的提高开发效率**。