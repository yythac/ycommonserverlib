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
			//��ʼssl����
			virtual bool i_handshake() = 0;
			//�첽�������ݣ����ȴ�����������
			virtual bool i_async_send_data(const char* pdata, int len) = 0;
			//ͬ���������ݣ��ȴ����ݷ���ŷ���
			virtual bool i_send_data(const char* pdata, int len) = 0;

			//�����շ�����
			virtual void i_shutdown() = 0;
			//�ر�����
			virtual void i_disconnect() = 0;

			virtual bool i_is_use_ssl() = 0;

			/////////////////////����Ϊ��ȶ��Ƹ�������//////////////////////////////////////////
			//��ȡboost��socketָ�루����boost::asio::ip::tcp::socket* ����<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>*��
			virtual void *i_next_layer() = 0;
			//����boost::asio::basic_socket*
			virtual void *i_lowest_layer() = 0;
			//��ȡƽ̨��ص�socket���
			virtual y_socket_type i_native_handle() = 0;
		};
	}
}