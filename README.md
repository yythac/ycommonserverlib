# ycommonserverlib

    Is a cross-platform network server framework built using c++11 and the boost library、openssl library、
    poco library,but using it does not require installing these libraries.

    Its features:

    1, The use of object pool, support socket reuse
    2, Using the memory pool
    3, Thread pool of the number of threads can automatically adjust
    4, Support SSL connection
    5, Support the original data packet and (2 bytes length + data content) data packet format
    6, Support log function
    7, Can quickly generate a basic full-featured network server program
    8, No need to install third-party libraries
    9, Supports configuration files in properties, xml, ini, json format. The default configuration file is
    in the directory of program, The configuration file name is (program name.extension) and the extension
    is been based on the configuration file format.
    
    Directory content:

    include---------------include files of ycommonserverlib
    lib-------------------lib files of ycommonserverlib
    YEchoServer-----------A sample of simple echo server using ycommonserverlib
    yftpServer------------A sample of simple ftp server using ycommonserverlib
    EchoClient------------A client program using to test YEchoServer
    TestConfig------------A sample program using config file of ycommonserverlib

    How to use ycommonserverlib please refer to YEchoServer and yftpserver
    
    =================================================================================================

    是一个使用c++11 和 boost库、openssl库、poco库生成的跨平台网络服务器框架，但是使用它并不需要安装这些库。

    它的特点：

    1、使用对象池，支持socket复用
    2、使用内存池
    3、使用可自动调节线程数的线程池
    4、支持SSL连接
    5、支持原始数据包及（2字节长度+数据内容）数据包格式
    6、支持日志功能
    7、能快速生成基本功能齐全的网络服务器程序
    8、不需要安装第三方库
    9、支持properties，xml，ini，json格式的配置文件，默认配置文件为程序所在目录下文件名为（程序名.扩展名）的文件
    ，扩展名可以为根据配置文件的而定

    目录内容：

    include---------------ycommonserverlib库的头文件
    lib-------------------ycommonserverlib库的库文件
    YEchoServer-----------一个使用ycommonserverlib生成的echo服务器
    yftpserver------------一个使用ycommonserverlib生成的FTP服务器
    EchoClient------------用于测试echo服务器的客户端
    TestConfig------------一个使用ycommonserverlib配置文件的例子

    具体使用方法请参考YEchoServer和yftpserver

