# ycommonserverlib

    Is a cross-platform network server framework built using c++11 and the boost library��openssl library��
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

    ��һ��ʹ��c++11 �� boost�⡢openssl�⡢poco�����ɵĿ�ƽ̨�����������ܣ�����ʹ����������Ҫ��װ��Щ�⡣

    �����ص㣺

    1��ʹ�ö���أ�֧��socket����
    2��ʹ���ڴ��
    3��ʹ�ÿ��Զ������߳������̳߳�
    4��֧��SSL����
    5��֧��ԭʼ���ݰ�����2�ֽڳ���+�������ݣ����ݰ���ʽ
    6��֧����־����
    7���ܿ������ɻ���������ȫ���������������
    8������Ҫ��װ��������
    9��֧��properties��xml��ini��json��ʽ�������ļ���Ĭ�������ļ�Ϊ��������Ŀ¼���ļ���Ϊ��������.��չ�������ļ�
    ����չ������Ϊ���������ļ��Ķ���

    Ŀ¼���ݣ�

    include---------------ycommonserverlib���ͷ�ļ�
    lib-------------------ycommonserverlib��Ŀ��ļ�
    YEchoServer-----------һ��ʹ��ycommonserverlib���ɵ�echo������
    yftpserver------------һ��ʹ��ycommonserverlib���ɵ�FTP������
    EchoClient------------���ڲ���echo�������Ŀͻ���
    TestConfig------------һ��ʹ��ycommonserverlib�����ļ�������

    ����ʹ�÷�����ο�YEchoServer��yftpserver

