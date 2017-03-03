#ifndef NCSOCKET_H
#define NCSOCKET_H
#include "settings.h"


class Socket
{
    public:
        ncSocket();
        virtual ~ncSocket();

    protected:
        int TCP

    private:
        int sockfd;
};

#endif // NCSOCKET_H
