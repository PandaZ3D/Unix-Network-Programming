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
			error(socketoption, "setsocket(): setsockopt()");
			
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
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	socklen_t addrlen = sizeof my_addr;
		
	/* bind adrress to get connections */
	int status = bind(listenfd, (struct sockaddr*) &my_addr, addrlen);
		error(status, "listensocket():  bind()");
	
	/*  set listeneing options */
	status = listen(listenfd, LISTENQ);
		error(status, "listensocekt(): listen()");
		
	return listenfd;
}


/* creates packet based on arguments */
packet_t* cmdpkt(int socketfd, char* cmd, char* args, uint8_t status, uint8_t arglen)
{
	/* note that commands sent are not NULL teminated */
	packet_t* cmd = malloc(sizeof(packet_t));
	if(cmd == NULL)
	{
		fprintf(stderr, "cmdpkt(): malloc failed\n");
		exit(EXIT_FAILURE);
	}
	
	/* create PORT cmd to send */
	if(socketfd != 0)
	{
		/* get IP & Port Info */
		struct sockaddr_in my_addr;
		socklen_t len = 0;
		int status  = getsockname(socketfd, (struct sockaddr*) &my_addr, &len);
			error(status, "cmdpkt: getsockname()");
			
		uint8_t n[6];
		n[0] = (my_addr.sin_addr.s_addr >> 24) & 0xFF;
		n[1] = (my_addr.sin_addr.s_addr >> 16) & 0xFF;
		n[2] = (my_addr.sin_addr.s_addr >> 8) & 0xFF;
		n[3] = my_addr.sin_addr.s_addr & 0xFF;
		n[4] = (my_addr.sin_port / 256) & 0xFF;
		n[5] = (my_addr.sin_port % 256) & 0xFF;
		
		printf("port = %d\n", ntohs(my_addr.sin_port));
		for(int i = 0; i<6; i++) {
			printf("%d ", n[1]);
		}
		printf("\n");
		
		memcpy(cmd->cmd, cmd, CMDLEN);
	}
	
	/* genericc packet assignments */
	memcpy(&cmd->status, &status, 1);
	memcpy(&cmd->arglen, &arglen, 1);
	memcpy(cmd->args, args, arglen);
	/* NULL terminate if possible */
	int left = MAXARG - arglen;
	memset(cmd->args + left, 0, left);
	
	return cmd;
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

/* generic printf funciton for packets */
void printpkt(packet_t* P)
{
	char buf[CMDLEN + 1];
	buf[CMDLEN] = 0;
	memcpy(buf, P->cmd, CMDLEN);
	printf("%s: ", buf);
	printf("%d ", P->status);
	if(P->arglen)
	{
		char* arg = strndup(P->arg, P->arglen);
		printf("%s", arg);
		free(arg);
	}
	printf("\n");
}
