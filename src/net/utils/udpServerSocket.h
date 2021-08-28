/*
 *  Created by StealthHydra179, TechyGuy17 and Alexander Argentakis (MFDGaming)
 *
 * If you found this code useful please donate here:
 *https://www.patreon.com/GrapheneDev
 *
 * This code is distributed under the GPL 3 license, to read it refer to https://github.com/Graphene-Dev/GrapheneChain/blob/master/LICENSE . if you find an error put it in
 * the errors page on GitHub
 *
 * Thank you
 */

#ifndef GRAPHENECHAIN_UDPSERVERSOCKET_H
#define GRAPHENECHAIN_UDPSERVERSOCKET_H

#include "address.h"
#include "binary_stream.h"

#include <iostream>
#include <cstring.h>

#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

#else

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>

#endif

using namespace std;

class udpServerSocket {
    private:
        int sockfd;
        address *addr;
    
        int setNonBlocking(bool nonblocking);

    public:
        udpServerSocket(address *addr, bool isNonBlocking = true) {
            #ifdef _WIN32

            WSADATA wsa;
            if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
                std::cout << "Winsock failed. Error Code : " << WSAGetLastError() << "\n";
                exit(EXIT_FAILURE);
            }

            #endif

            this->sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

            this->setNonBlocking(true);

            struct sockaddr_in s_address;
            memset(&s_address, 0, sizeof(s_address));

            s_address.sin_family = AF_INET;
            s_address.sin_addr.s_addr = inet_addr(addr->getHostname().c_str());
            s_address.sin_port = htons(addr->getPort());

            if (bind(this->sockfd, (struct sockaddr *) &s_address, sizeof(s_address)) < 0) {
                std::cout << "Failed to bind port " << addr->getPort() << "\n";
                exit(EXIT_FAILURE);
            }
        }

        void receiveData(binary_stream_t *stream, address *addr);

        void sendData(binary_stream_t *stream, address *addr);
};

#endif
