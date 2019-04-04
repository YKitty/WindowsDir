# HTTP的缓存机制及原理

--------------

## 前言

**Http缓存机制**是作为web性能优化的重要手段。我们要更好的了解，Http的缓存原理才能更好的懂得其实如何工作的，以及平时老说的缓存是什么，并且是如何实现的？

## HTTP报文

对于了解Http缓存之前，首先要了解一下Http的报文。这是因为对于Http得缓存就是和Http得报文有着极大的关系。

Http报文，Http报文就是浏览器以及服务器之间进行通信是发送及响应的数据块。

浏览器向服务器请求数据时，发送**请求(request)报文**；服务器向浏览器返回数据时，返回**响应(response)报文**。

报文信息主要分为四部分：

1. 首行：请求方法，Http协议版本，状态码以及状态码描述
2. 头部：key，value的键值对，用来存储记录，数据长度，数据类型，是否缓存，以及数据匹配等信息
3. 空行：分割首部和正文
4. 主体：Http请求以及响应时传输数据的地方

## 缓存规则解析

假定浏览器有着自己的一个缓存数据库，专门用来缓存信息。

在客户端第一次请求数据时，此时缓存数据库中没有对应的缓存数据，需要请求服务器，服务器返回后，将数据存储在缓存数据库中。

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/http%E7%AC%AC%E4%B8%80%E6%AC%A1%E8%AF%B7%E6%B1%82%E6%95%B0%E6%8D%AE.jpg)

HTTP缓存有着许多种，根据是否需要**重新向服务器发起请求**，我们将其分成两类：**强制缓存和对比缓存**

**已存在缓存数据，仅基于强制缓存**，请求数据的流程如下：

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/%E5%BC%BA%E5%88%B6%E7%BC%93%E5%AD%98.jpg)

**已存在缓存数据，仅基于对比缓存**，请求数据的流程如下：

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/%E5%AF%B9%E6%AF%94%E7%BC%93%E5%AD%98.jpg)

我们可以看到两类缓存规则的不同，**强制缓存**如果生效，不需要在和服务器发生交互，而**对比缓存**不管是否生效，都需要和服务端发生交互。

两类缓存可以同时存在，**强制缓存**优先级**高于**对比缓存，也就是说当执行强制缓存的规则时，如果缓存生效，直接使用缓存，不在执行对比缓存规则。

## 强制缓存

从上文得知，**强制缓存**，在缓存数据未失效的情况下，可以直接使用缓存数据，那么浏览器是**如何判断缓存数据是否失效呢？**

我们知道，在没有缓存数据的时候，浏览器向服务器请求数据时，服务器会将**数据以及缓存规则一并返回**，**缓存规则信息则包含在header中。**

对于强制缓存来说，响应header中会有两个字段来标识失效规则(Expires/Cache-Control)使用chrome的开发者工具，可以很明显的看到对于强制缓存生效是，网络请求的情况。

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/%E7%BD%91%E7%BB%9C%E8%AF%B7%E6%B1%82%E6%83%85%E5%86%B5.jpg)

### Expires

**Expires的值为服务返回的到期时间**，即下一次请求时，请求时间小于服务端返回的到期时间，直接使用缓存数据。不过Expires是HTTP 1.0的东西，现在默认浏览器使用HTTP 1.1，所以它的作用基本忽略。

另外一个问题是到期时间是有服务端生成的，但是客户端时间可能跟服务端时间有误差，这就会导致缓存命中的误差，所以HTTP 1.1版本，使用Cache-Control替代。

### Cache-Control

Cache-Control是最重要的规则。常见的取值有private，public，max-age，no-cache，no-store，**默认为private**

- private：客户端可以缓存
- public：客户端和代理服务器都可以进行缓存
- max-age=xxx：缓存内容将在xxx秒后失效
- no-cache：需要使用对比缓存来验证缓存数据
- no-store：所有内容都不会缓存，强制缓存，对比缓存都不会触发

举个例子：

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/%E5%BC%BA%E5%88%B6%E7%BC%93%E5%AD%98%E4%BE%8B%E5%AD%90.jpg)

图中Cache-Control**仅指定max-age，所以默认为private**，缓存时间为3153600秒（365天）也就是说，在365天内再次请求这个数据，直接使用。

## 对比缓存

**对比缓存**，顾名思义，需要进行比较判断是否可以使用缓存。浏览器第一次请求数据时，服务器会将缓存标识与数据一起返回给客户端，客户端将二者备份至缓存数据库中。

再次请求数据时，客户端将备份的缓存标识发送给服务器，服务器根据缓存标识进行判断，判断成功后，返回304状态码，通知客户端比较成功，可以使用缓存数据。

第一次访问：

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/%E7%AC%AC%E4%B8%80%E6%AC%A1%E8%AE%BF%E9%97%AE.jpg)

第二次访问：

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/%E7%AC%AC%E4%BA%8C%E6%AC%A1%E8%AE%BF%E9%97%AE.jpg)

通过两图的对比，我们可以清楚的发现，在**对比缓存生效时，状态码为304，并且报文大小和数据量大大减少**。

原因是，服务端在进行缓存标识后，只返回header部分，通过状态码通知客户端使用缓存，不在需要将报文主体部分返回给客户端。

对于对比缓存来说，缓存标识的传递使我们着重需要理解的，他在请求header和响应header间传递。

一共下面两种传递：

### Last-Modified：

服务器在响应请求是，告诉浏览器资源的最后修改时间。

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/Last-Modified.jpg)

### If-Modified-Since：

再次请求服务器的时候，那么浏览器将在请求中添加参数If-Modified-Since（值为上次响应里面的Last-Modified），服务器收到请求之后发现有头If-Modified-Since则与被请求资源的最后修改时间进行比对。

若资源的最后修改时间**大于**If-Modified-Since，说明资源有被改动过，则**响应整片资源内容**，返回状态码**200**；若资源的最后修改时间**小于或者等于**If-Modified-Since，说明**资源无新修改**，则响应**HTTP 304**，告知浏览器继续使用保存的cache。

### Etag：

服务器响应请求时，告诉浏览器当前资源在服务器的唯一标识（生成规则有服务器决定）。

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/Etag.jpg)

### If-None-Match:

再次请求服务器时，通过此字段通知服务器客户端缓存数据的唯一标识。服务器收到请求后发现有头If-None-Match则与被请求资源的唯一标识进行比对，不同，说明资源又被改动过，则响应整片资源内容，返回状态码200；相同，说明资源没有新修改，则响应HTTP 304，告知浏览器继续使用所保存的cache。

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/If-None_Match.jpg)

## 总结

对于强制缓存，服务器通知浏览器一个缓存时间，在缓存时间内，下次请求，直接用缓存，不在时间内，执行比较缓存策略。

对于比较缓存，将缓存信息中的Etag和Last-Modified通过请求发送给服务器，由服务器校验，返回304状态码时，浏览器直接使用缓存。

**浏览器第一次请求：**

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/%E7%AC%AC%E4%B8%80%E6%AC%A1%E8%AF%B7%E6%B1%82.jpg)

**浏览器第二次请求：**

![](https://ykitty.oss-cn-beijing.aliyuncs.com/photo/%E7%AC%AC%E4%BA%8C%E6%AC%A1%E8%AF%B7%E6%B1%82.jpg)





