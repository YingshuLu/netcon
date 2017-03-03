#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdarg.h>
#include <string>

#include "logging.h"
#include "configEngine.h"
#include "netSocket.h"

#include "http_parser.h"
const std::string  WORKPATH    =  "/usr/netcon";
const std::string  CONFIGPATH  =  WORKPATH + "/etc";
const std::string  LOGPATH     =  WORKPATH + "/log";
const std::string  CONFIG_FILE =  CONFIGPATH + "/netcon.ini";
const std::string  LOG_NAME    =  "netcon";

extern int errno;

#endif // SETTINGS_H_INCLUDED
