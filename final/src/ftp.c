#include "fat.h"

/* packet structure definition */
struct packet_t 
{
		char cmd[CMDLEN]; 		/* 4 bytes		: cmd */
		uint8_t status;				/* 1 byte 		: [reply status code] */
		uint8_t arglen;				/* 1 byte 		: [length of args] */
		char arg[MAXARG];		/* 255 bytes : [cmd message] */
} __attribute__ ((packed));

/* creates a listening socket to be used for incomming connections */
int listensocket(int socketfd)
{
	return 0;
}

/* sends cmd defined in packet */
void sendcmd(int socketfd, pkt cmd)
{
	
}
/* returns packet buffered in socket */
pkt recvcmd(int)
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