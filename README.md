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

    ��һ��ʹ��boost�⡢openssl�⡢poco�⼰c++ 11���ɵĿ�ƽ̨�����������ܣ�����ʹ����������Ҫ��װ��Щ�⡣

    �����ص㣺

    1��ʹ�ö���أ�֧��socket����
    2��ʹ���ڴ��
    3��ʹ�ÿ��Զ������߳������߳���
    4��֧��SSL����
    5��֧��ԭʼ���ݰ�����2�ֽڳ���+�������ݣ����ݰ���ʽ
    6���ܿ������ɻ���������ȫ���������������