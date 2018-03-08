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

			int run(int argc, char** argv);
			/// Runs the application by performing additional initializations
			/// and calling the main() method.

			int run(int argc, wchar_t** argv);
			/// Runs the application by performing additional initializations
			/// and calling the main() method.
			///
			/// This Windows-specific version of init is used for passing
			/// Unicode command line arguments from wmain().
		protected:
			virtual int main(const std::vector<std::string>& args) { return 0; }

			///返回的char*指针内存在dll内分配，需要调用ycommon_free释放
			char* get_string(const std::string& key, const std::string& defaultValue) const;
			/// If a property with the given key exists, returns the property's string value,
			/// otherwise returns the given default value.
			/// If the value contains references to other properties (${<property>}), these
			/// are expanded.
			int get_int(const std::string& key, int defaultValue) const;
			/// If a property with the given key exists, returns the property's int value,
			/// otherwise returns the given default value.
			/// Throws a SyntaxException if the property can not be converted
			/// to an int.
			/// Numbers starting with 0x are treated as hexadecimal.
			/// If the value contains references to other properties (${<property>}), these
			/// are expanded.
			
		private:
			//内部服务器
			void* pinter_appserver_;
		};

	}
}