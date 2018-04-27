/*
* ftp_server.h
*
* Mail :: yyt_hac@163.com
*
*Copyright (c) 2015 yyt_hac
*/

#pragma once

#define BOOST_ALL_NO_LIB

#include <ctime>
#include <cctype>
#include <cstdio>
//#include <fstream>
#include <fcntl.h>
#include <cstdlib>
#include <cstring>
#include <stdarg.h>
#include <mutex>
//#include <thread>
//#include <atomic>


//#include <sys/stat.h>
#include <boost/asio.hpp>
#ifdef SERVER_APP
#include <boost/asio/ssl.hpp>
#endif
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
//#include <boost/atomic.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <boost/filesystem.hpp>

using namespace boost::filesystem;


#include "request_parser.h"
#include "user_manager.h"

#define LOG_TAG "yftpserver"
#ifndef WIN32

//#include <../../common/c/JniLog.h>

#else

#include "../common/c/JniLog.h"

#endif


namespace ftp {
	namespace server {

		/***************************************
		 * THE CLASS: ftp_server
		 ***************************************/
		class ftp_server
		{

		public:

			/* Constructor */
			ftp_server(void);
			/* Destructor */
			~ftp_server(void);
#ifdef SERVER_APP
			static void server_app(YCOMMON::YSERVER::ycommon_server_app *app)
			{
				server_app_ = app;
			}
			static YCOMMON::YSERVER::ycommon_server_app* server_app()
			{
				return server_app_;
			}
	
			static boost::asio::ssl::context& ssl_context()
			{
				if (server_app_->boost_ssl_context() == nullptr)
					return context_;
				else
					return *(boost::asio::ssl::context*)server_app_->boost_ssl_context();
			}

			static bool set_certificate_chain_file(const std::string& chain_file)
			{
				boost::system::error_code ec;

				context_.use_certificate_chain_file(chain_file, ec);
				if (!ec)
				{
					return true;
				}
				else
				{
					YERROR_OUT("ftp_server::set_certificate_chain_file::use_certificate_chain_file:chain_file(%s),error(%s)", chain_file.c_str(), ec.message().c_str());
				}

				return false;
			}
			
			static bool set_private_key_file(const std::string& key_file, YCOMMON::YSERVER::key_file_format format, boost::function<std::string&()> get_pass)
			{

				boost::system::error_code ec;

				context_.set_password_callback(get_key_file_password,ec);
				if (!ec)
				{
					context_.use_private_key_file(key_file, format == YCOMMON::YSERVER::key_file_format::pem_file ? boost::asio::ssl::context::pem : boost::asio::ssl::context::asn1, ec);
					if (!ec)
					{
						return true;
					}
					else
					{
						YERROR_OUT("ftp_server::set_private_key_file::use_private_key_file:key_file(%s),error(%s)", key_file.c_str(), ec.message().c_str());
					}
				}
				else
				{
					YERROR_OUT("ftp_server::set_private_key_file::set_password_callback:key_file(%s),error(%s)", key_file.c_str(), ec.message().c_str());
				}


				return false;
			}
			static bool set_tmp_dh_file(const std::string& dh_file)
			{

				boost::system::error_code ec;

				context_.set_options(
					boost::asio::ssl::context::default_workarounds
					| boost::asio::ssl::context::no_sslv2
					| boost::asio::ssl::context::single_dh_use);
				if (!ec)
				{

					context_.use_tmp_dh_file(dh_file, ec);
					if (!ec)
					{
						return true;
					}
					else
					{
						YERROR_OUT("ftp_server::set_tmp_dh_file::use_tmp_dh_file:dh_file(%s),error(%s)", dh_file.c_str(), ec.message().c_str());
					}
				}
				else
				{
					YERROR_OUT("ftp_server::set_tmp_dh_file:set_options:dh_file(%s),error(%s)", dh_file.c_str(), ec.message().c_str());
				}

				return false;
			}
#endif
			//����pasvģʽ���ݶ˿ڷ�Χ
			static bool set_data_port_range(unsigned short int data_port_start, unsigned int number)
			{
				if (data_port_start <= 1024 || number == 0)
				{
					return false;
				}
				data_port_range_.start = data_port_start;
				data_port_range_.num = number;

				return true;
			}
			//��ȡpasvģʽ���ݶ˿ڷ�Χ
			static bool get_data_port_range(unsigned short int *data_port_start, int *number)
			{

				if (data_port_start && number)
				{

					*data_port_start = data_port_range_.start;
					*number = data_port_range_.num;
					return true;

				}
				return false;

			}

			//��ȡ������
			int get_last_error()
			{
				return last_error_.get_error_code();
			}
			//��ȡ�����ַ���
			wstring get_last_error_string()
			{
				return last_error_.to_string();
			}

			//����û�
			//������
			//name����Ҫ��ӵ��û���
			//password:�û�����
			//home_dir:�û���ʼĿ¼
			//priv:�û�Ȩ��
			//���أ�	
			//true:����û��ɹ�
			//false:����û�ʧ��
			bool add_user(const wstring& name, const wstring& password
				, const wstring& home_dir, unsigned char priv);
			bool delete_user(const wstring& name);
			//�����û�Ȩ��
			bool set_user_privilege(const std::wstring& name, unsigned char priv)
			{
				return user_manager_.set_user_privilege(name, priv);
			}
			//�����û�����
			bool set_user_password(const std::wstring& name, const std::wstring& password)
			{
				return user_manager_.set_user_password(name, password);
			}
			//�����û�Ŀ¼
			bool set_user_home_directory(const std::wstring& name, const std::wstring& home_dir)
			{
				return user_manager_.set_user_home_directory(name, home_dir);
			}
			//��ʼ�������û�
			bool allow_anonymous(bool do_allow, const std::wstring& home_dir, unsigned char priv=FTP_USER_PRIV_READ);
			//�ж��Ƿ�����������¼
			bool is_anonymous_allowed(void) 
			{

				return this->is_allow_anonymous_;

			}
			//���ӿ�ʼ
			bool start_work(reply& ftpreply);

			//����ftp����
			bool process_command(YCOMMON::YSERVER::i_ycommon_socket& ctrl_socket, char *pdata, int datalen, reply& ftpreply);
			//���ӽ���
			bool end_work(YCOMMON::YSERVER::i_ycommon_socket& ctrl_socket);

			/***************************************
			 * PRIVATE
			 ***************************************/
		private:

			static data_port_range data_port_range_;
#ifdef SERVER_APP
			static boost::asio::ssl::context context_;

			static YCOMMON::YSERVER::ycommon_server_app *server_app_;
			//���ط�����˽Կ����
			static std::string& get_key_file_password(std::size_t max_length,  // The maximum size for a password.
				boost::asio::ssl::context::password_purpose purpose) // Whether password is for reading or writing.) 
			{
				static std::string pass; //��������ʱ�����������þ�̬�������Ա����
				pass = "test";
				return pass;
			}
#endif

			user_manager user_manager_;

			//������
			error_manager last_error_;
			/*****************************************
			 * CONFIG
			 *****************************************/

			bool is_allow_anonymous_;



		};
	}
}

