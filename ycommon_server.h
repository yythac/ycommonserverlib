#pragma once

#include "ycommon.h"
#include <string>

/*
��Ҫ�Ľ������ݣ�
1�������̳߳����߳����Զ����ڹ��ܣ���ɣ�
2������֧��SSL����(��ɣ�
3�����ӶԲ��������ȵĴ����ݰ���ʽ֧�֣���ɣ�
4�����Ӹ��ݷ�����Ӳ�������Զ����ڷ�������������

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

			//��ʼ��������
			//use_ssl----------true:����ssl��false:������ssl
			//use_raw_data-----true:ʹ��ԭʼ���ݰ���ʽ��false:ʹ�ã�2�ֽڳ���+�������ݣ������ʽ
			bool create(bool use_ssl = false,bool use_raw_data = false);
			//����������,Ĭ��io�߳���λcpu����*2
			void start_server(int thread_num = -1);
			//ֹͣ������
			void stop_server();
			//�жϷ������Ƿ���������
			bool is_running();

			//���÷����������˿ں�ip
			bool set_server_addr(unsigned short port, const std::string& ip = "0.0.0.0");
			
			//�Ƿ�ʹ��ԭʼ���ݰ�
			bool is_use_raw_data();
			//�Ƿ���ΪSSL������
			bool is_use_ssl();
			//����SSL���Ӳ���
			bool set_certificate_chain_file(const std::string& chain_file);
			bool set_private_key_file(const std::string& key_file, key_file_format format = key_file_format::pem_file);
			bool set_tmp_dh_file(const std::string& dh_file);

			//���ù����̳߳ز���
			//�����̳߳���С�߳���
			bool set_pool_min_thread_num(unsigned int  num);
			//�����̳߳�����߳���
			bool set_pool_max_thread_num(unsigned int num);

			//��ȡ�̳߳���С�߳���
			unsigned int get_pool_min_thread_num();
			//��ȡ�̳߳�����߳���
			unsigned int get_pool_max_thread_num();

			//�첽�������ݣ����ȴ�����������
			bool async_send_data(void* conn, const char* pdata, int len);
			//ͬ���������ݣ��ȴ����ݷ���ŷ���
			bool send_data(void* conn, const char* pdata, int len);

			//�����շ�����
			void shutdown(void* conn);
			//�ر�����
			void disconnect(void* conn);

			/////////////////////����Ϊ��ȶ��Ƹ�������//////////////////////////////////////////
			//��ȡboost��socketָ�루����boost::asio::ip::tcp::socket* ����<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>*��
			void *boost_handle(void* conn);
			//��ȡboost::asio::ssl::context*
			void *boost_ssl_context(void* conn);
			//��ȡƽ̨��ص�socket���
			y_socket_type native_handle(void* conn);

		protected:
			//�յ��ͻ������Ӻ�ص�����,����true��ʾ�������ӣ�����false��ʾ�Ͽ�����
			virtual bool on_accept(void* conn) { return true; }
			//�����Ѿ������ɹ�
			virtual void on_connect(void* conn) { }
			//���ݴ���ص�����,���ظú������ڴ������ݰ�
			//�ͻ��˷��͵İ�Ϊ��2�ֽڳ���+�������ݣ�
			//�����յ�������Ϊ �������ݣ��Ѿ��Զ��������ݰ������յ����������ݣ�2�ֽڳ�����ȥ��
			virtual bool on_process_data(void* conn, const char* pdata, int len) { return true; }
			//���ӹرջص����������ظú����������ӹرպ��������
			virtual void on_close(void* conn) {}

			virtual std::string& get_key_file_password() const
			{
				static std::string pass("");
				return pass;
			}


		private:
			//�Ƿ�ʹ��SSL���ӣ�true��ʹ��SSL���ӣ�false����ʹ��SSL����
			bool use_ssl_;
			//�Ƿ�ʹ��ԭʼ���ݶ����ã�2�ֽڳ���+�������ݣ��Ĵ����ʽ��true��ʹ��ԭʼ���ݰ���ʽ��false��ʹ�ã�2�ֽڳ���+�������ݣ������ʽ
			bool use_raw_data_;

			//�ڲ�������
			void* pinter_server_;

		};

	}
}