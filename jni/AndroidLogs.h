#ifndef ANDROIDLOGS_H_
#define ANDROIDLOGS_H_

/*
 * AndroidLogs.h
 *
 *  Created on: 08.06.2012
 *      Author: trex
 */

#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "XOproject"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "test_native", __VA_ARGS__))

#endif /* ANDROIDLOGS_H_ */
