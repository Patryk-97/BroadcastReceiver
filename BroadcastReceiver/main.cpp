#include "BroadcastReceiver.h"
#include "WinsockManager.h"

#include <iostream>
#include <memory>

#define RECV_BUFF_SIZE 4096
#define DLL_WINSOCK_VERSION MAKEWORD(2, 2)

int main()
{
   std::unique_ptr<WinsockManager> winsockManager = std::make_unique<WinsockManager>();
   std::unique_ptr<BroadcastReceiver> broadcastReceiver = nullptr;
   uint16_t port;
   char recvBuff[RECV_BUFF_SIZE];

   if (false == winsockManager->startup(DLL_WINSOCK_VERSION))
   {
      printf("Winsock initialization error\n");
      return -1;
   }

   std::cout << "Enter port: ";
   std::cin >> port;

   broadcastReceiver = std::make_unique<BroadcastReceiver>();

   if (true == broadcastReceiver->init(IpProtocol::IPV4))
   {
      std::cout << "Socket initialized\n";
   }
   else
   {
      std::cout << "Cannot initialiaze a socket\n";
      std::cout << "Error: " << WinsockManager::getErrorMessage() << "\n";
      winsockManager->cleanup();
      return -1;
   }

   if (broadcastReceiver->bind(nullptr, port) == false)
   {
      std::cout << "Binding error\n";
      std::cout << "Error: " << WinsockManager::getErrorMessage() << "\n";
      broadcastReceiver->close();
      winsockManager->cleanup();
      return -1;
   }

   if (broadcastReceiver->recvFrom(recvBuff, RECV_BUFF_SIZE) <= 0)
   {
      std::cout << "Data have not been received\n";
      std::cout << "Error: " << WinsockManager::getErrorMessage() << "\n";
   }
   else
   {
      std::cout << "Received: " << recvBuff << "\n";
   }

   broadcastReceiver->close();
   std::cout << "Socket closed" << "\n";
   winsockManager->cleanup();
   std::cin.get();
   return 0;
}