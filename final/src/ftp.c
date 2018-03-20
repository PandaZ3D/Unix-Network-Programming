#include "ftp.h"

/* returns a generic TCP socket with custum options for debugging */
int setsocket(void) 
{
		int socketfd = socket(AF_INET, SOCK_STREAM, 0);
			error(socketfd, "setsocket(): socket()");
			
		/* Eliminates "ERROR on binding: Address already in use" error. */
		int socketoption = 1;
			setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, 
				(const void *)&socketoption , sizeof(int));
				
		return socketfd;
}

/* creates a listening socket to be used for incomming connections */
int listensocket(int portno)
{
	/* create socket */
	int listenfd = setsocket();
	
	/* get server IP information */
	struct sockaddr_in my_addr;
	bzero((char*) &my_addr, sizeof my_addr);
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(portno);
	my_addr.sin_family = inet_addr(INADDR_ANY);
	socklen_t addrlen = sizeof my_addr;
	
	/*  set listeneing options */
	int status = listen(listenfd, LISTENQ);
		error(status, "listensocekt(): listen()");
		
	/* bind adrress to get connections */
	status = bind(listenfd, (struct sockaddr*) &my_addr, addrlen);
		error(status, "listensocket():  bind()");
		
	return listenfd;
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