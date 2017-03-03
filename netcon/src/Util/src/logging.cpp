#include <iostream>
#include <string>
#include <stdarg.h>
#include <time.h>
#include <sys/io.h>
#include <unistd.h>
#include "logging.h"


logging* logging::pInstance = NULL;

logging* logging::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new logging();
	}
	return pInstance;
}

int logging::setLogFile(const std::string& file)
{
	std::string filepath = file;
	size_t pos = file.rfind(SPLIT);
	bool isPath = false;

	if (pos != std::string::npos){
		filepath = file.substr(0, pos);
		isPath = true;
	}

	if (access(filepath.c_str(), 0) < 0 || access(filepath.c_str(), 2) < 0)
	{
		if (isPath)
		{
			std::cout << "[Fatal]: File dir #" << filepath << "# not existed or has no write right!" << std::endl;
			return -1;
		}
		else if (access(filepath.c_str(), 0) > 0)
		{
			std::cout << "[Fatal]: File  #" << filepath << "#  has no write right!" << std::endl;
			return -1;
		}
	}

	logFile = file;
	return 0;
}

int logging::setLogPath(const std::string& path)
{
	logPath = path;
	return 0;
}

int logging::setLevel(const std::string& le)
{
    level = NOLOG;
    if(le == "enable")
    {
        level = ALLLOG;
    }
	return 0;
}

std::string logging::getLogFile() const
{
	const size_t BUFSIZE = 256;
	time_t tm = time(0);
	char tmpBuf[BUFSIZE];
	strftime(tmpBuf, BUFSIZE, ".%Y%m%d", localtime(&tm));

	std::string fmtPrefix = logPath + "/" + LOG_NAME;
	std::string secPrefix = fmtPrefix + tmpBuf;
    return secPrefix + ".log";
}

int logging::dbgLog(const char* fmt, ...)
{
    logFile = getLogFile();
	if (level != DEBUG && level != ALLLOG || logFile == "")
	{
		return -1;
	}

	std::string sign = "[DEBUG] ";
	std::string headStr = sign + '>' + getTime() + "< ";

	FILE* FF = fopen(logFile.c_str(), "ab");
	if (FF == NULL)
	{
		std::cerr << "Open " << logFile << " failed" << std::endl;
		return -1;
	}

	const std::string fmtTemplate = headStr + fmt + '\n';

	va_list args;
	va_start(args, fmt);
	vfprintf(FF, fmtTemplate.c_str(), args);
	va_end(args);

	fclose(FF);
	return 0;
}

int logging::infoLog(const char* fmt, ...)
{
    logFile = getLogFile();
	if (level != INFO && level != ALLLOG || logFile == "")
	{
		return -1;
	}

	std::string sign = "[INFO ] ";
	std::string headStr = sign + '>' + getTime() + "< ";

	FILE* FF = fopen(logFile.c_str(), "ab");
	if (FF == NULL)
	{
		std::cerr << "Open " << logFile << " failed" << std::endl;
		return -1;
	}

	const std::string fmtTemplate = headStr + fmt + '\n';

	va_list args;
	va_start(args, fmt);
	vfprintf(FF, fmtTemplate.c_str(), args);
	va_end(args);

	//fprintf(FF, " Line: %d <%s>@%s\n", __LINE__, __func__, __FILE__);
	fclose(FF);
	return 0;
}

std::string logging::getTime()
{
	const size_t BUFSIZE = 256;
	time_t tm = time(0);
	char tmpBuf[BUFSIZE];
	strftime(tmpBuf, BUFSIZE, "%H:%M:%S", localtime(&tm));

	return tmpBuf;
}
