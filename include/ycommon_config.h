#pragma once
#include "ycommon.h"
#include <memory>
#include <string>

namespace YCOMMON {
	namespace CONFIG {
		//�����ļ�����
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
			//���������ļ�
			bool load_configuration(const std::string& path);
			//���������ļ������pathΪ�գ��򱣴�Ϊ����ʱ����ļ�
			bool save_configuration(const std::string& path = "");

			//���������ļ���
			const std::string& get_config_file();
			//���������ļ�����
			config_file_type get_config_type();

			//

			//��ȡ��ֵΪkey���ַ��������ã�Ĭ��ֵΪdefaultValue��sectionΪ�����ļ�Ϊini��ʽʱ�Ľڣ����ص�char*ָ���ڴ���dll�ڷ��䣬��Ҫ����ycommon_free�ͷ�
			char* get_string(const std::string& key, const std::string& defaultValue, const std::string& section = "") const;

			//��ȡ��ֵΪkey�����������ã�Ĭ��ֵΪdefaultValue��sectionΪ�����ļ�Ϊini��ʽʱ�Ľ�
			int get_int(const std::string& key, int defaultValue, const std::string& section = "") const;

			//���ü�ֵΪkey�����ã�Ĭ��ֵΪdefaultValue��sectionΪ�����ļ�Ϊini��ʽʱ�Ľ�
			bool set_string(const std::string& key, const std::string& value, const std::string& section = "");

			//���ü�ֵΪkey�����ã�Ĭ��ֵΪdefaultValue��sectionΪ�����ļ�Ϊini��ʽʱ�Ľ�
			bool set_int(const std::string& key, int value, const std::string& section = "");


		private:

			void *common_config_{ nullptr };

			config_file_type config_file_type_{ config_file_type::unknow_file };
		};

	}
}