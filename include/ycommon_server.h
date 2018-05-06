#pragma once

#include "ycommon.h"
#include "ycommon_socket.h"
#include <string>

/*
��Ҫ�Ľ������ݣ�
1�������̳߳����߳����Զ����ڹ��ܣ���ɣ�
2������֧��SSL����(��ɣ�
3�����ӶԲ��������ȵĴ����ݰ���ʽ֧�֣���ɣ�
4�����Ӹ��ݷ�����Ӳ�������Զ����ڷ�������������

*/

namespace YCOMMON {
	namespace YSERVER {

		//SSL��Կ�ļ�����
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
			//use_ssl----------true:����ssl��false:������ssl;use_raw_data-----true:ʹ��ԭʼ���ݰ���ʽ��false:ʹ�ã�2�ֽڳ���+�������ݣ������ʽ
			bool create(bool use_ssl = false,bool use_raw_data = true);
			//����������,-1��ʾĬ��io�߳���λcpu����*2
			void start_server(int thread_num = -1);
			//ֹͣ������
			void stop_server();
			//�жϷ������Ƿ���������
			bool is_running();

			//���÷����������˿ں�ip
			bool set_server_addr(unsigned short port, const std::string& ip = "0.0.0.0");

			//����ssl�����ӳ����֣�������ʾftps���������һ��ʼ����ͨ���ӣ��ں��������и�����Ҫ�л���ssl����
			//Ҫ�����ַ�ʽ�ڵ���createʱ���봫��use_sslΪ1,�������ú�ssl���Ӳ���
			bool set_delay_ssl(bool delay);
			//�Ƿ�ʹ��ԭʼ���ݰ�
			bool is_use_raw_data();
			//�Ƿ���ΪSSL������
			bool is_use_ssl();
			//����SSL���Ӳ���
			bool set_certificate_chain_file(const std::string& chain_file);
			bool set_private_key_file(const std::string& key_file, key_file_format format = key_file_format::pem_file);
			bool set_tmp_dh_file(const std::string& dh_file);

		/*	//���ù����̳߳ز���
			//�����̳߳���С�߳���
			static bool set_pool_min_thread_num(unsigned int  num);
			//�����̳߳�����߳���
			static bool set_pool_max_thread_num(unsigned int num);

			//��ȡ�̳߳���С�߳���
			static unsigned int get_pool_min_thread_num();
			//��ȡ�̳߳�����߳���
			static unsigned int get_pool_max_thread_num();
		*/

			/////////////////////����Ϊ��ȶ��Ƹ�������//////////////////////////////////////////
			//��ȡboost::asio::ssl::context*
			void *boost_ssl_context();


		protected:
			//�յ��ͻ������Ӻ�ص�����,����true��ʾ�������ӣ�����false��ʾ�Ͽ�����
			virtual bool on_accept(i_ycommon_socket* conn) { return true; }
			//�����Ѿ������ɹ�
			virtual void on_connect(i_ycommon_socket* conn) { }
			//���ݴ���ص�����,���ظú������ڴ������ݰ�
			//�ͻ��˷��͵İ�Ϊ��2�ֽڳ���+�������ݣ�
			//�����յ�������Ϊ �������ݣ��Ѿ��Զ��������ݰ������յ����������ݣ�2�ֽڳ�����ȥ��������ֵĿǰû����
			virtual bool on_process_data(i_ycommon_socket* conn, const char* pdata, int len) { return true; }
			//���ӹرջص����������ظú����������ӹرպ��������
			virtual void on_close(i_ycommon_socket* conn) {}

			//��ȡSSL��Կ�ļ���������Ļص�����
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