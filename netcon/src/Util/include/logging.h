/*+ Logging.h
 *- Create for logging, this class is designed with single instance mode.
 *- To use looging, logging level and log file should be given first.
 *- Kam Lu 11.22.2016 @trendmicro
*/
#ifndef __LOGGING_H_H_H__
#define __LOGGING_H_H_H__

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "settings.h"

#define SPLIT '/'

#ifdef WINDOWS
#define SPLIT '\\'
#endif

#define DBG_LOG(fmt,...) logging::getInstance()->dbgLog(fmt" <%s>@<%s:%d>", ##__VA_ARGS__, __func__, basename(__FILE__), __LINE__)
#define INFO_LOG(fmt,...) logging::getInstance()->infoLog(fmt" <%s>@<%s:%d>", ##__VA_ARGS__, __func__, basename(__FILE__), __LINE__)

enum LOGLEVEL{
	NOLOG = 0,
	DEBUG,
	INFO,
	ALLLOG
};

class logging
{

public:

	static logging* getInstance();
	int setLogPath(const std::string& path);
	int setLogFile(const std::string& file);
	std::string getLogFile() const;

	int dbgLog(const char* fmt, ...);
	int infoLog(const char* fmt, ...);
	int setLevel(const std::string& le);

private:
	static logging* pInstance;
	logging():endFmt("<__FUNC__>@__FILE__"), level(NOLOG){}
	int genLogging(int choice, const char* fmt, ...);
	std::string getTime();

	const std::string endFmt;
	std::string logPath;
	std::string logFile;
	int level;
};

#endif
