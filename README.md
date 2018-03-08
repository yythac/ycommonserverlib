# ycommonserverlib

    Is a cross-platform network server framework built using the boost library、openssl library、
poco library and c++ 11,but using it does not require installing these libraries.

    Its features:

    1, the use of object pool, support socket reuse
    2, using the memory pool
    3, thread pool of the number of threads can automatically adjust
    4, support SSL connection
    5, support the original data packet and (2 bytes length + data content) data packet format
    6, can quickly generate a basic full-featured network server program

    是一个使用boost库、openssl库、poco库及c++ 11生成的跨平台网络服务器框架，但是使用它并不需要安装这些库。

    它的特点：

    1、使用对象池，支持socket复用
    2、使用内存池
    3、使用可自动调节线程数的线程数
    4、支持SSL连接
    5、支持原始数据包及（2字节长度+数据内容）数据包格式
    6、能快速生成基本功能齐全的网络服务器程序