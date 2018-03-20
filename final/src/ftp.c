#include "ftp.h"

/* creates a listening socket to be used for incomming connections */
int listensocket(int socketfd)
{
	return 0;
}

/* sends cmd defined in packet */
void sendcmd(int socketfd, packet_t* cmd)
{
	
}
/* returns packet buffered in socket */
packet_t* recvcmd(int socketfd)
{
	return NULL;
}

/* sends a chunk of data, returns amount of bytes sent */
int sendchunk(int socketfd, char* chunk)
{
	return 0;
}

/* recieves a chunk of data, returns pointer to chunk */
char* recvchunk(int socketfd)
{
	return NULL;
}

/* sends a whole file, returns bytes sent */
int sendfile(int socketfd, int putfd)
{
		return 0;
}

/* recieves a whole file, returns bytes recvd */
int recvfile(int socketfd)
{
		return 0;
}