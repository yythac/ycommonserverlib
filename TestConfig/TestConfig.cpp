// TestConfig.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{
	YLOG_INIT(true, false, YDEBUG_LEVEL);

	YCOMMON::CONFIG::ycommon_config my_config;

	if (my_config.load_configuration("yftpserver.properties") == false)
	{
		YINFO_OUT("load config file:%s error!", "yftpserver.properties");
		return -1;
	}
	char *root_dir = my_config.get_string("ftp.server.root_dir", "");
	bool allow_anonymous = !(my_config.get_int("ftp.server.allow_anonymous", 1) == 0);
	YINFO_OUT("FTP Server Root Dir:%s,Is Allow Anonymous:%s", root_dir, allow_anonymous ? "true" : "false");
	char* ftp_user = my_config.get_string("ftp.server.user1", "");
	YINFO_OUT("FTP Server User Infomation:%s", ftp_user);
	YCOMMON::GLOBAL::ycommon_free(root_dir);
	YCOMMON::GLOBAL::ycommon_free(ftp_user);

	int i = !allow_anonymous;
	if (my_config.set_int("ftp.server.allow_anonymous", i) == false)
	{
		YINFO_OUT("set key:%s error!", "ftp.server.allow_anonymous");
		return -1;
	}
	if (my_config.save_configuration() == false)
	{
		YINFO_OUT("save config file:%s error!", "yftpserver.properties");
		return -1;
	}
	YINFO_OUT("change \"ftp.server.allow_anonymous\" to %d", i);

    return 0;
}

