#ifndef NETSOCKET_H_INCLUDED
#define NETSOCKET_H_INCLUDED

#include "settings.h"


class netSocket
{
public:
    static bool validateIPv4(const std::string&);
    static bool validatePort(const int port);
    static bool validateFamily(const int family);
    static int  getSocketAddr(sockaddr_in* pa, const std::string& addr, const int port, const int family);
    static int  TCPConnectTo(const sockaddr_in*);
    static int  UDPConnectTo(const sockaddr_in*);
    static int  TCPAccept(const sockaddr_in*);
	static int TCPServer(const sockaddr_in*);
private:
    netSocket();
    ~netSocket();

};


#endif // NETSOCKET_H_INCLUDED
