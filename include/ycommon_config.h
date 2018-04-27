#pragma once
#include "ycommon.h"
#include <memory>
#include <string>

namespace YCOMMON {
	namespace CONFIG {
		//配置文件类型
		typedef enum class tag_config_file_type
		{
			unknow_file,
			property_file,
			ini_file,
			json_file,
			xml_file
		}config_file_type;

		class YCOMMONSERVERLIB_API ycommon_config
		{
		public:
			ycommon_config();
			virtual ~ycommon_config();
			//加载配置文件
			bool load_configuration(const std::string& path);
			//保存配置文件，如果path为空，则保存为加载时候的文件
			bool save_configuration(const std::string& path = "");

			//返回配置文件名
			const std::string& get_config_file();
			//返回配置文件类型
			config_file_type get_config_type();

			//

			//获取键值为key的字符串型配置，默认值为defaultValue，section为配置文件为ini格式时的节，返回的char*指针内存在dll内分配，需要调用ycommon_free释放
			char* get_string(const std::string& key, const std::string& defaultValue, const std::string& section = "") const;

			//获取键值为key的整数型配置，默认值为defaultValue，section为配置文件为ini格式时的节
			int get_int(const std::string& key, int defaultValue, const std::string& section = "") const;

			//设置键值为key的配置，默认值为defaultValue，section为配置文件为ini格式时的节
			bool set_string(const std::string& key, const std::string& value, const std::string& section = "");

			//设置键值为key的配置，默认值为defaultValue，section为配置文件为ini格式时的节
			bool set_int(const std::string& key, int value, const std::string& section = "");


		private:

			void *common_config_{ nullptr };

			config_file_type config_file_type_{ config_file_type::unknow_file };
		};

	}
}