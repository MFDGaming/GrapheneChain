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

#ifndef GRAPHENECHAIN_ADDRESS_H
#define GRAPHENECHAIN_ADDRESS_H

#include <iostream>

using namespace std;

class address {
    private:
        string hostname;
        int port;
    
    public:
        address(string hostname, int port) {
            this->hostname = hostname;
            this->port = port;
        }

        string getHostname();

        void setHostname(string hostname);

        int getPort();

        void setPort(int port);
};

#endif