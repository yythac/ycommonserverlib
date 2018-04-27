#pragma once
#include "ycommon_server.h"
#include <vector>
#include <string>

//
// Macro to implement main()
//
#if defined(_WIN32) && defined(_UNICODE)
#define YCOMMON_SERVER_MAIN(App) \
	int wmain(int argc, wchar_t** argv)	\
	{									\
		try 							\
		{								\
			App app;					\
			return app.run(argc, argv);	\
		}								\
		catch (std::exception& e)		\
		{								\
			std::cout << (e.what() == nullptr ? "NULL" : e.what()); \
			return -1;\
		} \
	}
#elif defined(POCO_VXWORKS)
#define YCOMMON_SERVER_MAIN(App) \
	int pocoSrvMain(const char* appName, ...) 				\
	{ 														\
		std::vector<std::string> args; 						\
		args.push_back(std::string(appName)); 				\
		va_list vargs; 										\
		va_start(vargs, appName); 							\
		const char* arg = va_arg(vargs, const char*); 		\
		while (arg) 										\
		{ 													\
			args.push_back(std::string(arg));				\
			arg = va_arg(vargs, const char*); 				\
		} 													\
		va_end(vargs); 										\
		try													\
		{ 													\
			App app;										\
			return app.run(args); 							\
		} 													\
		catch (std::exception& e)		\
		{								\
			std::cout << (e.what() == nullptr ? "NULL" : e.what()); \
			return -1;\
		} \
	}
#else
#define YCOMMON_SERVER_MAIN(App) \
	int main(int argc, char** argv)		\
	{									\
		try 							\
		{								\
			App app;					\
			return app.run(argc, argv);	\
		}								\
		catch (std::exception& e)		\
		{								\
			std::cout << (e.what() == nullptr ? "NULL" : e.what()); \
			return -1;\
		} \
	}
#endif


namespace YCOMMON {
	namespace YSERVER {

		class YCOMMONSERVERLIB_API ycommon_server_app :
			public ycommon_server
		{
		public:
			ycommon_server_app();
			virtual ~ycommon_server_app();
			//��ʼ��Ӧ�ó��򣬲������ڲ�main����
			int run(int argc, char** argv);

			//��ʼ��Ӧ�ó��򣬲������ڲ�main����
			int run(int argc, wchar_t** argv);

		protected:

			//���ڲ���������ʼ����ʼʱ���ã�����Ӧ�ó����ʼ��������0��ʾ����ִ�У����ط�0��ʾ�˳�
			virtual int init(const std::vector<std::string>& args) { return 0; }
			//���ڲ���������ʼ������ʱ���ã�����Ӧ�ó����ʼ��������0��ʾ����ִ�У����ط�0��ʾ�˳�
			virtual int main(const std::vector<std::string>& args) { return 0; }

			//��ȡ��ֵΪkey���ַ��������ã�Ĭ��ֵΪdefaultValue��sectionΪ�����ļ�Ϊini��ʽʱ�Ľڣ����ص�char*ָ���ڴ���dll�ڷ��䣬��Ҫ����ycommon_free�ͷ�
			char* get_string(const std::string& key, const std::string& defaultValue, const std::string& section = "") const;

			//��ȡ��ֵΪkey�����������ã�Ĭ��ֵΪdefaultValue��sectionΪ�����ļ�Ϊini��ʽʱ�Ľ�
			int get_int(const std::string& key, int defaultValue, const std::string& section = "") const;

			//����Ĭ�ϲ�������û�������ļ�ʱʹ��Ĭ��ֵ
			//���÷����������˿ں�ip
			bool set_default_server_addr(unsigned short port, const std::string& ip = "0.0.0.0");
			//�����Ƿ�����SSL����
			bool set_default_is_use_ssl(bool is_use_ssl);
			//�����Ƿ���ԭʼ���ݰ���ʽ
			bool set_default_is_use_raw_data(bool is_use_raw_data);

		private:
			//�ڲ�������
			void* pinter_appserver_;
		};

	}
}