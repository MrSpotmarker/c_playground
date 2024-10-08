#ifndef CHAT_SOCKETHELPER_H
#define CHAT_SOCKETHELPER_H

struct sockaddr_in* createIPv4Address (char *ip, int port);
int getSocketFd();

#endif //CHAT_SOCKETHELPER_H
