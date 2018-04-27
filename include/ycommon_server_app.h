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
			//初始化应用程序，并调用内部main函数
			int run(int argc, char** argv);

			//初始化应用程序，并调用内部main函数
			int run(int argc, wchar_t** argv);

		protected:

			//在内部服务器初始化开始时调用，用于应用程序初始化，返回0表示继续执行，返回非0表示退出
			virtual int init(const std::vector<std::string>& args) { return 0; }
			//在内部服务器初始化结束时调用，用于应用程序初始化，返回0表示继续执行，返回非0表示退出
			virtual int main(const std::vector<std::string>& args) { return 0; }

			//获取键值为key的字符串型配置，默认值为defaultValue，section为配置文件为ini格式时的节，返回的char*指针内存在dll内分配，需要调用ycommon_free释放
			char* get_string(const std::string& key, const std::string& defaultValue, const std::string& section = "") const;

			//获取键值为key的整数型配置，默认值为defaultValue，section为配置文件为ini格式时的节
			int get_int(const std::string& key, int defaultValue, const std::string& section = "") const;

			//设置默认参数，当没有配置文件时使用默认值
			//设置服务器监听端口和ip
			bool set_default_server_addr(unsigned short port, const std::string& ip = "0.0.0.0");
			//设置是否启用SSL连接
			bool set_default_is_use_ssl(bool is_use_ssl);
			//设置是否用原始数据包格式
			bool set_default_is_use_raw_data(bool is_use_raw_data);

		private:
			//内部服务器
			void* pinter_appserver_;
		};

	}
}