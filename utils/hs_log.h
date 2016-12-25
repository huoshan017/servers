#ifndef __HS_LOG_H__
#define __HS_LOG_H__

#if defined(__cplusplus)
extern "C" {
#endif
#include "zlog.h"
#if defined(__cplusplus)
}
#endif

extern zlog_category_t* my_cat;

bool hs_log_init(const char* conf_file, const char* categroy);
void hs_log_destroy();

#define HsLogDebug(...) \
	zlog(my_cat, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
			ZLOG_LEVEL_DEBUG, __VA_ARGS__)

#define HsLogInfo(...) \
	zlog(my_cat, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
			ZLOG_LEVEL_INFO, __VA_ARGS__)

#define HsLogNotice(...) \
	zlog(my_cat, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
			ZLOG_LEVEL_NOTICE, __VA_ARGS__)

#define HsLogWarn(...) \
	zlog(my_cat, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
			ZLOG_LEVEL_WARN, __VA_ARGS__)

#define HsLogError(...) \
	zlog(my_cat, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
			ZLOG_LEVEL_ERROR, __VA_ARGS__)

#define HsLogFatal(...) \
	zlog(my_cat, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
			ZLOG_LEVEL_FATAL, __VA_ARGS__)

#endif
