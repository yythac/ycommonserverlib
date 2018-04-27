#pragma once

#include "ycommon.h"

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

		class i_ycommon_socket
		{
		public:
			//开始ssl握手
			virtual bool i_handshake() = 0;
			//异步发送数据，不等待，立即返回
			virtual bool i_async_send_data(const char* pdata, int len) = 0;
			//同步发送数据，等待数据发完才返回
			virtual bool i_send_data(const char* pdata, int len) = 0;

			//结束收发数据
			virtual void i_shutdown() = 0;
			//关闭连接
			virtual void i_disconnect() = 0;

			virtual bool i_is_use_ssl() = 0;

			/////////////////////下面为深度定制辅助功能//////////////////////////////////////////
			//获取boost库socket指针（返回boost::asio::ip::tcp::socket* 或者<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>*）
			virtual void *i_next_layer() = 0;
			//返回boost::asio::basic_socket*
			virtual void *i_lowest_layer() = 0;
			//获取平台相关的socket句柄
			virtual y_socket_type i_native_handle() = 0;
		};
	}
}