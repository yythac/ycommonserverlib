#pragma once

#include "ycommon.h"
#include <string>

/*
需要改进的内容：
1、增加线程池中线程数自动调节功能（完成）
2、增加支持SSL连接(完成）
3、增加对不带包长度的纯数据包格式支持（完成）
4、增加根据服务器硬件配置自动调节服务器参数功能

*/

#if defined(WIN32) || defined(__CYGWIN__)
#if !defined(SOCKET)
#include <winsock2.h>
#endif
typedef SOCKET y_socket_type;
#else
typedef int y_socket_type;
#endif

namespace YCOMMON {
	namespace YSERVER {

		/// File format types.
		typedef enum class tag_key_file_format
		{
			/// ASN.1 file.
			asn1_file,

			/// PEM file.
			pem_file
		}key_file_format;

		class YCOMMONSERVERLIB_API ycommon_server
		{
		public:

			ycommon_server();
			virtual ~ycommon_server();

			//初始化服务器
			//use_ssl----------true:启用ssl；false:不启用ssl
			//use_raw_data-----true:使用原始数据包格式；false:使用（2字节长度+数据内容）打包格式
			bool create(bool use_ssl = false,bool use_raw_data = false);
			//启动服务器,默认io线程数位cpu个数*2
			void start_server(int thread_num = -1);
			//停止服务器
			void stop_server();
			//判断服务器是否正常运行
			bool is_running();

			//设置服务器监听端口和ip
			bool set_server_addr(unsigned short port, const std::string& ip = "0.0.0.0");
			
			//是否使用原始数据包
			bool is_use_raw_data();
			//是否作为SSL服务器
			bool is_use_ssl();
			//设置SSL连接参数
			bool set_certificate_chain_file(const std::string& chain_file);
			bool set_private_key_file(const std::string& key_file, key_file_format format = key_file_format::pem_file);
			bool set_tmp_dh_file(const std::string& dh_file);

			//设置工作线程池参数
			//设置线程池最小线程数
			bool set_pool_min_thread_num(unsigned int  num);
			//设置线程池最大线程数
			bool set_pool_max_thread_num(unsigned int num);

			//获取线程池最小线程数
			unsigned int get_pool_min_thread_num();
			//获取线程池最大线程数
			unsigned int get_pool_max_thread_num();

			//异步发送数据，不等待，立即返回
			bool async_send_data(void* conn, const char* pdata, int len);
			//同步发送数据，等待数据发完才返回
			bool send_data(void* conn, const char* pdata, int len);

			//结束收发数据
			void shutdown(void* conn);
			//关闭连接
			void disconnect(void* conn);

			/////////////////////下面为深度定制辅助功能//////////////////////////////////////////
			//获取boost库socket指针（返回boost::asio::ip::tcp::socket* 或者<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>*）
			void *boost_handle(void* conn);
			//获取boost::asio::ssl::context*
			void *boost_ssl_context(void* conn);
			//获取平台相关的socket句柄
			y_socket_type native_handle(void* conn);

		protected:
			//收到客户端连接后回调函数,返回true表示接受连接，返回false表示断开连接
			virtual bool on_accept(void* conn) { return true; }
			//连接已经建立成功
			virtual void on_connect(void* conn) { }
			//数据处理回调函数,重载该函数用于处理数据包
			//客户端发送的包为（2字节长度+数据内容）
			//这里收到的数据为 数据内容，已经自动根据数据包长度收到完整的数据，2字节长度已去除
			virtual bool on_process_data(void* conn, const char* pdata, int len) { return true; }
			//连接关闭回调函数，重载该函数用于连接关闭后的清理工作
			virtual void on_close(void* conn) {}

			virtual std::string& get_key_file_password() const
			{
				static std::string pass("");
				return pass;
			}


		private:
			//是否使用SSL连接，true：使用SSL连接；false：不使用SSL连接
			bool use_ssl_;
			//是否使用原始数据而不用（2字节长度+数据内容）的打包格式，true：使用原始数据包格式；false：使用（2字节长度+数据内容）打包格式
			bool use_raw_data_;

			//内部服务器
			void* pinter_server_;

		};

	}
}