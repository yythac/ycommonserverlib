#pragma once

/*
* user_manager.h :: ftp user manager class header file
*
* Mail :: yyt_hac@163.com
*
*Copyright (c) 2015 yyt_hac
*/

#include <memory>
#include <string>
#include <list>
#include <mutex>

using namespace std;

#include "user_node.h"

namespace ftp {
	namespace server {

		class user_manager
		{
		public:
			user_manager();
			~user_manager();

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
				
			//ɾ���û�
			//������
			//name����Ҫɾ�����û���
			//���أ�
			//true:ɾ���ɹ�
			//false:û���ҵ��û����������
			bool delete_user(const wstring& name);

			//�����û�Ȩ��
			//������
			//name:��Ҫ����Ȩ�޵��û������ձ�ʾ�����û�
			//priv:��Ҫ���õ��û�Ȩ��
			//true:����Ȩ�޳ɹ�
			//false:û���ҵ��û������������
			bool set_user_privilege(const std::wstring& name, unsigned char priv);

			//����һ���û���ͬʱ��¼�����������
			//����:
			//name:��Ҫ���ò������û���
			//����:
			//true:���óɹ�
			//fasle:����ʧ��
			bool set_user_max_client(const std::wstring& name, int max_client);

			//��ȡһ���û���ͬʱ��¼�����������
			//����:
			//name:��Ҫ��ȡ�������û���
			//����:
			//>= 0:�û���ͬʱ��¼�����������
			//< 0:��ȡʧ��
			int get_user_max_client(const std::wstring& name);

			//��ȡ�û�Ȩ��
			//����:
			//name:
			//����:
			//>0: ���û���Ȩ��
			//0: ��ȡȨ��ʧ��
			unsigned char get_user_privilege(const std::wstring& name);
			//��ȡ�û���¼����
			bool get_user_password(const std::wstring& name, std::wstring& password);
			//��ȡ�û�ftpĿ¼
			bool get_user_home_directory(const std::wstring& name, std::wstring& home_dir);

			//�����û�����
			//������
			//name:��Ҫ����������û������ձ�ʾ�����û�
			//priv:��Ҫ���õ��û�����
			//true:��������ɹ�
			//false:û���ҵ��û������������
			bool set_user_password(const std::wstring& name, const std::wstring& password);
			//�����û���ʼĿ¼
			//������
			//name:��Ҫ������ʼĿ¼���û���
			//priv:��Ҫ���õ���ʼĿ¼
			//true:������ʼĿ¼�ɹ�
			//false:û���ҵ��û������������
			bool set_user_home_directory(const std::wstring& name, const std::wstring& home_dir);

			bool proccess_home_directory(std::wstring& home_dir);

			sp_client_node find_client(boost::asio::ip::tcp::socket& ctrl_socket);

			//�����û�
			//������
			//name����Ҫ���ҵ��û���
			//���أ�
			//sp_user_node:�ҵ����û���Ϣ
			//nullptr:û���ҵ��û�
			sp_user_node find_user(const wstring& name)
			{
				for (auto user: ftp_user_list_)
				{
					if (user->get_user_name() == name)
					{
						return user;
					}
				}
				return nullptr;
			}

			//����û�
			//������
			//user����Ҫ��ӵ��û���Ϣ�ṹ
			//���أ�	
			//��
			void add_user(const sp_user_node& user)
			{
				ftp_user_list_.push_back(user);
			}
			//ɾ�������û�
			void delete_all_user(void)
			{
				std::lock_guard<std::mutex> lock(user_lock_);
				auto pos = ftp_user_list_.begin();

				while (pos != ftp_user_list_.end())
				{
					(*pos)->get_client_manager().delete_all_client();
					pos = ftp_user_list_.erase(pos);
				}
			}
			//��ȡ������
			int get_last_error()
			{
				return last_error_.get_error_code();
			}

#ifdef CFTPSERVER_USE_EXTRACMD

			/* Enum the Extra Commands a User can got. */
			enum class ftp_extra_cmd {

				ExtraCmd_EXEC = 0x1,

			};

			/* Set the supported Extra-Commands of a User.
			Arguments:
			-user name.
			-the user's Extra-Commands concatenated with the bitwise inclusive
			binary operator "|".
			Returns:
			-on success: true.
			-on error: false.
			*/
			bool set_user_extra_cmd(const std::wstring& name, unsigned char extra_cmd)
			{
				std::lock_guard<std::mutex> lock(user_lock_);
				auto user = find_user(name);
				if (user != nullptr)
				{
					user->set_extra_cmd(extra_cmd);
					return true;
				}
				last_error_.set_error_code(YFTP_ERROR_USER_NOT_FOUND);
				return false;
			}

			/* Get the supported Extra-Commands of a User.
			Arguments:
			-user name.
			Returns:
			-on succes: the user's Extra-Commands concatenated with the bitwise
			inclusive binary operator "|".
			-on error: 0.
			*/
			unsigned char get_user_extra_cmd(const std::wstring& name)
			{
				std::lock_guard<std::mutex> lock(user_lock_);
				auto user = find_user(name);
				if (user != nullptr)
				{
					return user->getextra_cmd();
				}
				last_error_.set_error_code(YFTP_ERROR_USER_NOT_FOUND);
				return 0;

			}

#endif

		private:
			//ftp�û��б�
			user_list	ftp_user_list_;

			//������
			error_manager last_error_;

			mutex user_lock_;

		};

	}
}