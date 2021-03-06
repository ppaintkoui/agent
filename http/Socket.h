/*
 * Socket.h
 *
 *  Created on: 12/07/2017
 *  Copyright 2017 Stefano Ceccherini (stefano.ceccherini@gmail.com)
 */

#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>

class Socket {
public:
	Socket();
	Socket(int domain, int type, int protocol);
	virtual ~Socket();

	virtual int Open(int domain, int type, int protocol);
	virtual void Close();
	
	int FD() const;
	bool IsOpened() const;

	virtual int Connect(const struct sockaddr *address, socklen_t len);
	int Connect(const struct hostent* hostEnt, const int port);
	int Connect(const char *hostName, const int port);

	void SetOption(int level, int name, const void *value, socklen_t len);

	virtual int Read(void* data, const size_t& length);
	virtual int Write(const void* data, const size_t& length);

private:
	int fFD;
};

#endif // SOCKET_H
