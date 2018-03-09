# ycommonserverlib

    Is a cross-platform network server framework built using the boost library��openssl library��
    poco library and c++ 11,but using it does not require installing these libraries.

    Its features:

    1, the use of object pool, support socket reuse
    2, using the memory pool
    3, thread pool of the number of threads can automatically adjust
    4, support SSL connection
    5, support the original data packet and (2 bytes length + data content) data packet format
    6, can quickly generate a basic full-featured network server program
    
    include---------------include files of ycommonserverlib
    lib-------------------lib files of ycommonserverlib
    YEchoServer-----------A sample of simple echo server using ycommonserverlib
    EchoClient------------A client program using to test YEchoServer
    TestConfig------------A sample program using config file of ycommonserverlib

    ��һ��ʹ��boost�⡢openssl�⡢poco�⼰c++ 11���ɵĿ�ƽ̨�����������ܣ�����ʹ����������Ҫ��װ��Щ�⡣

    �����ص㣺

    1��ʹ�ö���أ�֧��socket����
    2��ʹ���ڴ��
    3��ʹ�ÿ��Զ������߳������߳���
    4��֧��SSL����
    5��֧��ԭʼ���ݰ�����2�ֽڳ���+�������ݣ����ݰ���ʽ
    6���ܿ������ɻ���������ȫ���������������

    include---------------ycommonserverlib���ͷ�ļ�
    lib-------------------ycommonserverlib��Ŀ��ļ�
    YEchoServer-----------һ��ʹ��ycommonserverlib���ɵ�echo������
    EchoClient------------���ڲ���echo�������Ŀͻ���
    TestConfig------------һ��ʹ��ycommonserverlib�����ļ�������
