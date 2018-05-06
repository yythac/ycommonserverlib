// TestConfig.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//#include <boost/filesystem.hpp>

int main()
{
	YLOG_INIT(true, false, YDEBUG_LEVEL);

	YCOMMON::CONFIG::ycommon_config my_config;

	if (my_config.load_configuration("testconfig.properties") == false)
	{
		YINFO_OUT("load config file:%s error!", "testconfig.properties");
		return -1;
	}
	char *root_dir = my_config.get_string("ftp.server.root_dir", "");
	char *anonymous_info = my_config.get_string("ftp.server.allow_anonymous", "1::rwd");

	YINFO_OUT("Ftp Server Root Dir:%s", root_dir);
	YINFO_OUT("Anonymous User Info:%s", anonymous_info);

	bool allow_anonymous = !(anonymous_info[0] == '0');
	YINFO_OUT("FTP Server Root Dir:%s,Is Allow Anonymous:%s", root_dir, allow_anonymous ? "true" : "false");
	char* ftp_user = my_config.get_string("ftp.server.user1", "");
	YINFO_OUT("FTP Server User Infomation:%s", ftp_user);
	YCOMMON::GLOBAL::ycommon_free(root_dir);
	YCOMMON::GLOBAL::ycommon_free(ftp_user);

	if (my_config.set_string("ftp.server.root_dir", "/") == false)
	{
		YINFO_OUT("set key:%s error!", "ftp.server.root_dir");
		return -1;
	}
	YINFO_OUT("change \"ftp.server.root_dir\" to %s", "/");

	int i = !allow_anonymous;
	anonymous_info[0] = '0' + i;
	if (my_config.set_string("ftp.server.allow_anonymous", anonymous_info) == false)
	{
		YINFO_OUT("set key:%s error!", "ftp.server.allow_anonymous");
		return -1;
	}
	if (my_config.save_configuration() == false)
	{
		YINFO_OUT("save config file:%s error!", "testconfig.properties");
		return -1;
	}
	YINFO_OUT("change \"ftp.server.allow_anonymous\" to %d", i);

	YCOMMON::GLOBAL::ycommon_free(anonymous_info);

	////////////test ini config file

	if (my_config.load_configuration("testconfig.ini") == false)
	{
		YINFO_OUT("load config file:%s error!", "testconfig.ini");
		return -1;
	}
	root_dir = my_config.get_string("ftp.server.root_dir", "","ftp server");
	anonymous_info = my_config.get_string("ftp.server.allow_anonymous", "1::rwd", "ftp server");

	YINFO_OUT("Ftp Server Root Dir:%s", root_dir);
	YINFO_OUT("Anonymous User Info:%s", anonymous_info);

	allow_anonymous = !(anonymous_info[0] == '0');
	YINFO_OUT("FTP Server Root Dir:%s,Is Allow Anonymous:%s", root_dir, allow_anonymous ? "true" : "false");
	ftp_user = my_config.get_string("ftp.server.user1", "", "ftp server");
	YINFO_OUT("FTP Server User Infomation:%s", ftp_user);
	YCOMMON::GLOBAL::ycommon_free(root_dir);
	YCOMMON::GLOBAL::ycommon_free(ftp_user);

	int port = my_config.get_int("server.port", 21, "common server");
	YINFO_OUT("Common Server Listen Port:%d", port);

	if (my_config.set_string("ftp.server.root_dir", "/", "ftp server") == false)
	{
		YINFO_OUT("set key:%s error!", "ftp.server.root_dir");
		return -1;
	}
	YINFO_OUT("change \"ftp.server.root_dir\" to %s", "/");

	i = !allow_anonymous;
	anonymous_info[0] = '0' + i;
	if (my_config.set_string("ftp.server.allow_anonymous", anonymous_info, "ftp server") == false)
	{
		YINFO_OUT("set key:%s error!", "ftp.server.allow_anonymous");
		return -1;
	}
	if (my_config.save_configuration() == false)
	{
		YINFO_OUT("save config file:%s error!", "testconfig.ini");
		return -1;
	}
	YINFO_OUT("change \"ftp.server.allow_anonymous\" to %s", anonymous_info);

	YCOMMON::GLOBAL::ycommon_free(anonymous_info);

	if (my_config.load_configuration("testconfig.xml") == false)
	{
		YINFO_OUT("load config file:%s error!", "testconfig.xml");
		return -1;
	}
	root_dir = my_config.get_string("ftp.server.root_dir", "", "ftp server");
	anonymous_info = my_config.get_string("ftp.server.allow_anonymous", "1::rwd", "ftp server");

	YINFO_OUT("ftp.server.root_dir:%s", root_dir);
	YINFO_OUT("ftp.server.allow_anonymous:%s", anonymous_info);

	YCOMMON::GLOBAL::ycommon_free(root_dir);
	YCOMMON::GLOBAL::ycommon_free(anonymous_info);

	if (my_config.set_string("ftp.server.root_dir", "/", "ftp server") == false)
	{
		YINFO_OUT("set key:%s error!", "ftp.server.root_dir");
		return -1;
	}
	YINFO_OUT("change \"ftp.server.root_dir\" to %s", "/");

	if (my_config.save_configuration() == false)
	{
		YINFO_OUT("save config file:%s error!", "testconfig.xml");
		return -1;
	}

    return 0;
}

