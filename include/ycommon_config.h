#pragma once
#include "ycommon.h"
#include <memory>
#include <string>

namespace YCOMMON {
	namespace CONFIG {
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
			/// If a property with the given key exists, returns the property's string value,
			/// otherwise returns the given default value.
			/// If the value contains references to other properties (${<property>}), these
			/// are expanded.
			///返回的char*指针内存在dll内分配，需要调用ycommon_free释放
			char* get_string(const std::string& key, const std::string& defaultValue) const;
			/// If a property with the given key exists, returns the property's int value,
			/// otherwise returns the given default value.
			/// Throws a SyntaxException if the property can not be converted
			/// to an int.
			/// Numbers starting with 0x are treated as hexadecimal.
			/// If the value contains references to other properties (${<property>}), these
			/// are expanded.
			int get_int(const std::string& key, int defaultValue) const;

			/// Sets the property with the given key to the given value.
			/// An already existing value for the key is overwritten.
			bool set_string(const std::string& key, const std::string& value);

			/// Sets the property with the given key to the given value.
			/// An already existing value for the key is overwritten.
			bool set_int(const std::string& key, int value);


		private:

			void *common_config_{ nullptr };

			std::string config_file_{ "" };
			config_file_type config_file_type_{ config_file_type::unknow_file };
		};

	}
}