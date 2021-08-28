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

#include "utils/address.h"
#include "utils/binary_stream.h"
#include "utils/udpServerSocket.h"

#include <iostream>
#include <thread>

using namespace std;

class server {
    private:
        udpServerSocket *serverSocket;
        address *addr;

    public:
        address *getAddress();

        void run();

        server(string addr, int port) {
            this->addr = new address(addr, port);
            this->serverSocket = new udpServerSocket(this->addr);

            std::thread serverThread(&server::run, this);
        }
};