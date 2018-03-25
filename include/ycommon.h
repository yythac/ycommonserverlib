#pragma once

#ifndef _WIN32_WINNT
#define  _WIN32_WINNT 0x0601
#endif
#define _CRT_SECURE_NO_WARNINGS

/*LIB Config Begin*/

//
// Ensure that YCOMMON_DLL is default unless YCOMMON_STATIC is defined
//
#if defined(_WIN32) 
#if !defined(YCOMMON_DLL) && !defined(YCOMMON_STATIC)
#define YCOMMON_DLL
#endif
#endif


//
// The following block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the YCOMMONSERVERLIB_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// YCOMMONSERVERLIB_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if (defined(_WIN32) || defined(_WIN32_WCE)) && defined(YCOMMON_DLL)
#if defined(YCOMMONSERVERLIB_EXPORTS)
#define YCOMMONSERVERLIB_API __declspec(dllexport)
#else
#define YCOMMONSERVERLIB_API __declspec(dllimport)	
#endif
#endif


#if !defined(YCOMMONSERVERLIB_API)
#if !defined(YCOMMON_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
#define YCOMMONSERVERLIB_API __attribute__ ((visibility ("default")))
#else
#define YCOMMONSERVERLIB_API
#endif
#endif


//
// Automatically link YCOMMONSERVERLIB library.
//
#if defined(_MSC_VER)
#if defined(YCOMMON_DLL)
#if defined(_DEBUG)
#define YCOMMON_LIB_SUFFIX "d.lib"
#else
#define YCOMMON_LIB_SUFFIX ".lib"
#endif
#elif defined(_DLL)
#if defined(_DEBUG)
#define YCOMMON_LIB_SUFFIX "mdd.lib"
#else
#define YCOMMON_LIB_SUFFIX "md.lib"
#endif
#else
#if defined(_DEBUG)
#define YCOMMON_LIB_SUFFIX "mtd.lib"
#else
#define YCOMMON_LIB_SUFFIX "mt.lib"
#endif
#endif

#if !defined(YCOMMON_NO_AUTOMATIC_LIBS) && !defined(YCOMMONSERVERLIB_EXPORTS)
#if defined(YCOMMON_DLL) && defined(_DLL)
#error("YCommonServerLib is linked with '/MTd|MT',Please link with '/MTd|MT' for you projects!")
#endif
#pragma comment(lib, "YCOMMONServerLib" YCOMMON_LIB_SUFFIX)
#endif
#endif

/*LIB Config End*/

//dll的当前版本
#define YCOMMON_SERVER_LIB_VER	1.10

namespace YCOMMON {
	namespace GLOBAL {
		//本dll中分配的内存必须调用该函数释放
		YCOMMONSERVERLIB_API void ycommon_free(char *p);
	}
	namespace LOG {

		/*LOG Config Begin*/
		//是否启用日志记录功能，定义WRITE_LOG就启用日志，否则不记录日志
#define WRITE_LOG			

//日志格式
#define LOG_FORMAT_STR 	expr::format("[%1%]%2%<%3%>(%4%): %5%")\
						% expr::attr< boost::posix_time::ptime >("TimeStamp")\
						% expr::attr< std::string >("Tag")\
						% expr::attr< severity_level >("Severity")\
						% expr::attr< attrs::current_thread_id::value_type >("ThreadID")\
						% expr::message

//日志等级
// Here we define our application severity levels.
		typedef enum class tag_severity_level
		{
			ydebug,
			yinfo,
			ywarning,
			yerror,
			ycritical
		}severity_level;

		//初始化日志功能
		/*
		to_console-----------true:输出到控制台，false:不输出到控制台
		to_file--------------true:输出到文件，false:不输出到文件
		level----------------日志记录等级，只记录等级>=level的日志
		*/
		YCOMMONSERVERLIB_API bool ylog_init(bool to_console, bool to_file, severity_level level);
		//强制保存日志缓存到文件
		YCOMMONSERVERLIB_API void ylog_flush();

		YCOMMONSERVERLIB_API void  log_level(severity_level level, const char * fmt0, ...);
		YCOMMONSERVERLIB_API void  log_level(severity_level level, const wchar_t * fmt0, ...);

#define YDEBUG_LEVEL	YCOMMON::LOG::severity_level::ydebug
#define YINFO_LEVEL		YCOMMON::LOG::severity_level::yinfo
#define YWARNING_LEVEL	YCOMMON::LOG::severity_level::ywarning
#define YERROR_LEVEL	YCOMMON::LOG::severity_level::yerror
#define YCRITICAL_LEVEL	YCOMMON::LOG::severity_level::ycritical

#ifndef WRITE_LOG
#define YLOG_INIT(x,y,z)	;
#define YWRITE_LOG(level,...) ;
#define YLOG_FLUSH()  ;

#define YFATAL_OUT(...)		;
#define YERROR_OUT(...)		;
#define YWARNING_OUT(...)	;
#define YINFO_OUT(...)		;
#define YDEBUG_OUT(...)		;
#endif

#ifndef YWRITE_LOG

		//日志记录宏
#define YLOG_INIT(x,y,level)		YCOMMON::LOG::ylog_init(x,y,level)	
#define YWRITE_LOG(level,...)		YCOMMON::LOG::log_level(level,__VA_ARGS__)
#define YLOG_FLUSH()				YCOMMON::LOG::ylog_flush()


#define YFATAL_OUT(...)		YWRITE_LOG(YCRITICAL_LEVEL,__VA_ARGS__) 
#define YERROR_OUT(...)		YWRITE_LOG(YERROR_LEVEL,__VA_ARGS__) 
#define YWARNING_OUT(...)	YWRITE_LOG(YWARNING_LEVEL,__VA_ARGS__) 
#define YINFO_OUT(...)		YWRITE_LOG(YINFO_LEVEL,__VA_ARGS__) 
#define YDEBUG_OUT(...)		YWRITE_LOG(YDEBUG_LEVEL,__VA_ARGS__) 

#endif


/*LOG Config End*/
	}

}


/*Server Config Start*/

/*Server Config End*/