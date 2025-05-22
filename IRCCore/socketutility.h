// socketutility.h

#pragma once

#include <iostream>
#include <WinSock2.h>

void cleanup(SOCKET sock);
sockaddr_in make_sockaddr_in(const int, const unsigned short, const unsigned long = 0);
