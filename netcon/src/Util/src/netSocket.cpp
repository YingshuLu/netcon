#include "netSocket.h"
#include "settings.h"

bool netSocket::validateIPv4(const std::string& addr)
{

    return true;
}

bool netSocket::validatePort(const int port)
{
    if(port >= 0 && port <= 65535)
    {
        return true;
    }
    return false;
}

bool netSocket::validateFamily(const int family)
{
    return true;
}

int netSocket::getSocketAddr(sockaddr_in* pa, const std::string& addr, const int port, const int family)
{
    if(!validateIPv4(addr.c_str()) || !validatePort(port) || !validateFamily(family))
        return -1;

    sockaddr_in* psAddr = pa;

    bzero(psAddr, sizeof(sockaddr_in));
    psAddr-> sin_family = family;
//    psAddr-> sin_addr.s_addr = inet_addr(addr.c_str());
    psAddr-> sin_addr.s_addr = htonl(INADDR_ANY);
    psAddr-> sin_port = htons(port);

    return 0;
}

int netSocket::TCPServer(const sockaddr_in* paddr)
{

    if(paddr == NULL)
    {
        DBG_LOG("Paramter false: socketaddr_in is NULL");
        return -1;
    }

    int conn_sock = -1;
    // tcp socket fd
	INFO_LOG("TCP socket init...");
    conn_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(conn_sock == -1)
    {
        DBG_LOG("Socket create error: conn_socket = %d",conn_sock);
        return -1;
    }
	
	socklen_t addr_len = sizeof(sockaddr);

	INFO_LOG("Bind TCP socket...");
	if (bind(conn_sock, (sockaddr*) paddr, addr_len) != 0 )
	{
		DBG_LOG("Bind sock: %d failed!", conn_sock);
		DBG_LOG("%s",strerror(errno));
		return -1;
	}

/*
    int sockfd = connect(conn_sock, (sockaddr*) paddr, sizeof(sockaddr));
    if(sockfd == -1)
    {
        DBG_LOG("TCP Connect failed");
        return -1;
    }
*/
	INFO_LOG("Listening socket: %d", conn_sock);
	if(listen(conn_sock, 20) != 0)
	{
		DBG_LOG("Listen sock:%d", conn_sock);
		return -1;
	}

	daemon(0,0);
	char buf[20480] = {0};
	
	while(1)
	{ 
		sockaddr_in caddr;
		
		INFO_LOG("Accepting socket: %d", conn_sock);
		int sockfd = accept(conn_sock, (sockaddr*) &caddr, &addr_len);
		if(sockfd == -1)
		{
			DBG_LOG("Accept socket:%d failed", sockfd);
		}
		memset(buf, 0, sizeof(buf));
		char* ptr = buf;
	
		int cnt = 0;
		INFO_LOG("get a connect: ohh");
		while((cnt = read(sockfd, ptr, 1024)) > 0)
		{
			DBG_LOG("message: %s", ptr);
			ptr += cnt;
			
		}
		*ptr = '\0';

		DBG_LOG("Get message: %s", buf);
		close(sockfd);

	}
    return 0;
}
int netSocket::TCPConnectTo(const sockaddr_in* paddr)
{

    if(paddr == NULL)
    {
        DBG_LOG("Paramter false: socketaddr_in is NULL");
        return -1;
    }

    int conn_sock = -1;
    // tcp socket fd
	INFO_LOG("TCP socket init...");
    conn_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(conn_sock == -1)
    {
        DBG_LOG("Socket create error: conn_socket = %d",conn_sock);
        return -1;
    }
	
	socklen_t addr_len = sizeof(sockaddr);

	INFO_LOG("Bind TCP socket...");
	if (bind(conn_sock, (sockaddr*) paddr, addr_len) != 0 )
	{
		DBG_LOG("Bind sock: %d failed!", conn_sock);
		return -1;
	}
/*
    int sockfd = connect(conn_sock, (sockaddr*) paddr, sizeof(sockaddr));
    if(sockfd == -1)
    {
        DBG_LOG("TCP Connect failed");
        return -1;
    }
*/
	if(listen(conn_sock, 20) != 0)
	{
		DBG_LOG("Listen sock:%d", conn_sock);
		return -1;
	}

	char buf[20480] = {0};
	
	while(1)
	{ 
		sockaddr_in caddr;
		
		INFO_LOG("accepting...");
		int sockfd = accept(conn_sock, (sockaddr*) &caddr, &addr_len);
		if(sockfd == -1)
		{
			DBG_LOG("Accept socket:%d failed", sockfd);
		}
		memset(buf, 0, sizeof(buf));
		char* ptr = buf;
	
		int cnt = 0;
		while((cnt = read(sockfd, ptr, 1024)) > 0)
		{
			ptr += cnt;
		}
		*ptr = '\0';

		close(sockfd);
		DBG_LOG("Get message: %s", ptr);

	}
    return 0;
}
