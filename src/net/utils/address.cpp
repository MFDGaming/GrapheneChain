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

#include "address.h"

string address::getHostname() {
    return this->hostname;
}

void address::setHostname(string hostname) {
    this->hostname = hostname;
}

int address::getPort() {
    return this->port;
}

void address::setPort(int port) {
    this->port = port;
}