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

#include "server.h"

address *server::getAddress() {
    return this->addr;
}

void server::run() {
    while (true) {
        binary_stream_t stream;
        address *addr;
        this->serverSocket->receiveData(&stream, addr);
        cout << addr->getHostname() << ":" << addr->getPort() << "\n";
    }
}

