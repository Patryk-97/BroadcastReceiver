#pragma once

#ifndef __BROADCAST_RECEIVER_H__
#define __BROADCAST_RECEIVER_H__

#include "IpProtocol.h"

#include <Winsock2.h>
#include <string>
#include <stdint.h>
#include <memory>
#include <Ws2tcpip.h>
#include <iostream>

class BroadcastReceiver
{
public:
   BroadcastReceiver();
   ~BroadcastReceiver();
   void reset(void);
   bool init(IpProtocol ipProtocol);
   bool bind(const char* address, const uint16_t port);
   int recvFrom(char* recvBuff, int recvBuffSize);
   void close(void);
   std::string getRemoteAddressIp(void) const;
   uint16_t getRemotePort(void) const;

private:
   void fillAddrInfoCriteria(addrinfo* hints) const;
   bool fillNetworkAddressStructure(const char* address, sockaddr_in* socketAddr);
   void fillPort(uint16_t port, sockaddr_in* socketAddr);
   void fillIpProtocolFamily(sockaddr_in* socketAddr);

private:
   SOCKET socketId;
   sockaddr_in recvAddr;
   IpProtocol ipProtocol;
};

#endif // __BROADCAST_RECEIVER_H__