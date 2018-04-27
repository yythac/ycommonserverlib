// YEchoServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#ifdef SERVER_APP

#include "ycommon_server_app.h"
class EchoServerApp : public YCOMMON::YSERVER::ycommon_server_app
#else

#include "ycommon_server.h"
class EchoServer : public YCOMMON::YSERVER::ycommon_server
#endif
{

protected:

#ifdef SERVER_APP
	virtual int main(const std::vector<std::string>& args)
	{
		YINFO_OUT("Entering main......");
		return 0;
	}
#endif
	//返回服务器私钥密码
	virtual std::string& get_key_file_password() const override
	{
		static std::string pass; //不能用临时变量，必须用静态，或类成员变量
		pass = "test";
		return pass;
	}
	
	virtual bool on_accept(YCOMMON::YSERVER::i_ycommon_socket* conn) override
	{
		YINFO_OUT(L"Connection:%X arrived", conn);
		return true;
	}
	virtual void on_connect(YCOMMON::YSERVER::i_ycommon_socket* conn) override
	{
		YINFO_OUT(L"Connection:%X connected", conn);
		return;
	}
	//数据处理回调函数,重载该函数用于处理数据包
	//客户端发送的包为（2字节长度+数据内容）
	//这里收到的数据为 数据内容，已经自动根据数据包长度收到完整的数据，2字节长度已去除
	virtual bool on_process_data(YCOMMON::YSERVER::i_ycommon_socket* conn, const char* pdata, int len) override
	{
		//		YWRITE_LOG(yinfo, "Connection:%X recv data,len:%d", conn,len);
		conn->i_send_data(pdata, len);
		return true;

	}
	//连接关闭回调函数，重载该函数用于连接关闭后的清理工作
	virtual void on_close(YCOMMON::YSERVER::i_ycommon_socket* conn) override
	{
		YINFO_OUT("Connection:%X disconnect", conn);
	}

};
#ifdef SERVER_APP

YCOMMON_SERVER_MAIN(EchoServerApp)

#else

int main(int argc, const char* argv[])
{
	if (argc >= 2 && (0 == strcmp(argv[1], "--help") 
		|| 0 == strcmp(argv[1], "-h") || 0 == strcmp(argv[1], "-?")
		|| 0 == strcmp(argv[1], "/h") || 0 == strcmp(argv[1], "/?")))
	{
		printf("Usage:%s [port] [service thread num] [usessl] [userawdata] [certificate_chain_file] [private_key_file] [tmp_dh_file]\r\n",argv[0]);
		printf("port-------------------------server listen port,default is 8888\r\n");
		printf("service thread num-----------server io thread num,default is (CPU number * 2)\r\n");
		printf("userawdata-------------------1:server uses raw data packet;0:server uses (2bytes length + body) packet,default is 0\r\n");
		printf("usessl-----------------------1:server uses ssl;0:server don't use ssl,default is 0\r\n");
		return 1;
	}
	//初始化日志
	YLOG_INIT(true, true, YDEBUG_LEVEL);

	unsigned short port = 8888;
	if (argc >= 2)
		port = atoi(argv[1]);
	if (port <= 0)
		port = 8888;

	int thread_num = -1;
	if (argc >= 3)
	{
		thread_num = atoi(argv[2]);
	}
	bool usessl = false;
	if (argc >= 4)
	{
		usessl = (atoi(argv[3]) != 0);
	}
	bool userawdata = false;
	if (argc >= 5)
	{
		userawdata = (atoi(argv[4]) != 0);
	}
	std::string certificate_chain_file, private_key_file, tmp_dh_file;
	certificate_chain_file = "server.pem";
	private_key_file = "server.pem";
	tmp_dh_file = "dh2048.pem";

	if (argc >= 6)
	{
		certificate_chain_file = argv[4];
	}
	if (argc >= 7)
	{
		private_key_file = argv[5];
	}
	if (argc >= 8)
	{
		tmp_dh_file = argv[6];
	}
	YINFO_OUT("Echo Server port=%d,thread_num=%d", port,thread_num);
	YDEBUG_OUT("test debug msg");

	EchoServer echo_server_; //echo server

	if (echo_server_.create(usessl, userawdata) == false)
	{
		YERROR_OUT("Echo Server init failed!");
		return 0;
	}
	if (usessl)
	{
		if (echo_server_.set_certificate_chain_file(certificate_chain_file) == false)
		{
			return 0;
		}
		if (echo_server_.set_private_key_file(private_key_file) == false)
		{
			return 0;
		}
		if (echo_server_.set_tmp_dh_file(tmp_dh_file) == false)
		{
			return 0;
		}
	}
	YINFO_OUT("Thread Pool Min Thread Num:%d,Max Thread Num:%d", echo_server_.get_pool_min_thread_num(), echo_server_.get_pool_max_thread_num());
	echo_server_.set_pool_min_thread_num(4);
	echo_server_.set_pool_max_thread_num(32);
	YINFO_OUT("Thread Pool Min Thread Num:%d,Max Thread Num:%d", echo_server_.get_pool_min_thread_num(), echo_server_.get_pool_max_thread_num());

	echo_server_.set_server_addr(port);
	
	if (thread_num > 0)
		echo_server_.start_server(thread_num);
	else
		echo_server_.start_server();

	if (echo_server_.is_running())
	{
		YINFO_OUT("Echo Server is running,Please press any key to exit....");
		//强制保存日志
		YLOG_FLUSH();
		YINFO_OUT("Press 'q'+ Enter to exit......");
		while (true)
		{
			if (getchar() == 'q')
				break;
		}
	}
	else
	{
		YERROR_OUT("Echo Server start failed!");
	}
	
	echo_server_.stop_server();

    return 0;
}

#endif