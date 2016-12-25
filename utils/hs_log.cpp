#include "hs_log.h"

zlog_category_t* my_cat;

bool hs_log_init(const char* conf_file, const char* category)
{
	int rc = zlog_init(conf_file);
	if (rc) {
		return false;
	}
	my_cat = zlog_get_category("my_cat");
	if (!my_cat) {
		zlog_fini();
		return false;
	}
	return true;
}

void hs_log_destroy()
{
	zlog_fini();
}
