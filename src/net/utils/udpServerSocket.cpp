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

#include "udpServerSocket.h"

int udpServerSocket::setNonBlocking(bool nonblocking) {
    if (this->sockfd < 0) {
        return 0;
    }

    #ifdef _WIN32

    unsigned long mode = nonblocking == true ? 1 : 0;
    return (ioctlsocket(this->sockfd, FIONBIO, &mode) == 0);

    #else

    int flags = fcntl(this->sockfd, F_GETFL, 0);

    if (flags == -1) {
        return 0;
    }

    flags = nonblocking == false ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);

    return (fcntl(this->sockfd, F_SETFL, flags) == 0);

    #endif
}

void udpServerSocket::receiveData(binary_stream_t *stream, address *addr) {
    struct sockaddr_in s_address;
    memset(&s_address, 0, sizeof(s_address));

    char buffer[65535];

    socklen_t s_address_length = sizeof(s_address);

    int length = recvfrom(
        this->sockfd, (char *) buffer,
        65535, 0, (struct sockaddr *) &s_address,
        &s_address_length
    );
    stream->buffer = (char *) buffer;
    stream->size = length;

    addr->setHostname(inet_ntoa(s_address.sin_addr));
    addr->setPort(htons(s_address.sin_port));
}

void udpServerSocket::sendData(binary_stream_t *stream, address *addr) {
    struct sockaddr_in s_address;
    memset(&s_address, 0, sizeof(s_address));

    s_address.sin_family = AF_INET;
    s_address.sin_addr.s_addr = inet_addr(addr->getHostname().c_str());
    s_address.sin_port = htons(addr->getPort());

    sendto(
        this->sockfd, (char *) stream->buffer,
        stream->size, 0,
        (struct sockaddr *) &s_address, sizeof(s_address)
    );
}