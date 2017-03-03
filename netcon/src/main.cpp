#include <iostream>
#include <string>
#include "settings.h"

using namespace std;

extern configEngine* pini = configEngine::getInstance();

int init()
{
    configEngine* pconfig = configEngine::getInstance();
    pconfig->setConfigPath(CONFIG_FILE);
    string logPath = pconfig->getValueByKey("log", "path");
    string verbose = pconfig->getValueByKey("log", "verbose");
    cout << "logPath: " << logPath << "\nverbose: " + verbose <<endl;
    if(logPath == "")
    {
        logPath = LOGPATH;
    }

	logging* plog = logging::getInstance();
	plog->setLogPath(logPath);
	plog->setLevel(verbose);
	return true;
}

int TCPPortScan(const string& dst, const int port)
{
    sockaddr_in addr;
    if(netSocket::getSocketAddr(&addr, dst, port, AF_INET) == -1)
    {
        DBG_LOG("get socketaddr failed");
        return -1;
    }

    if(netSocket::TCPConnectTo(&addr) == -1)
    {
        DBG_LOG("IP: %s, Port: %d not opened", dst.c_str(), port);
        return -1;
    }
    INFO_LOG("IP: %s, Port: %d available", dst.c_str(), port);
    return 0;
}

int runTCPserver()
{
	sockaddr_in addr; 
	string dst = "127.0.0.1";
	string sport = pini->getValueByKey("http-proxy", "port");
	if(sport == "" || sport == string())
	{
		DBG_LOG("Read netcon.ini failed");
		exit(-1);
	}

	int port = atoi(sport.c_str());
    INFO_LOG("Scan IP: %s, Port: %d", dst.c_str(), port);
	if(netSocket::getSocketAddr(&addr, dst, port, AF_INET) == -1)
	{
		DBG_LOG("get socketaddr failed");
		return -1;
	}

	return netSocket::TCPServer(&addr);
}

int main(int argc, char* argv[])
{

    init();
    runTCPserver();
    return 0;
}
