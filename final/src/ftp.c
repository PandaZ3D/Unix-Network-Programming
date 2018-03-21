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
packet_t* cmdpkt(int socketfd, char* cmd, char* args, uint8_t arglen, uint8_t status)
{
	/* note that commands sent are not NULL teminated */
	packet_t* P = malloc(sizeof(packet_t));
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
		
		printf("%s %d %d\n", inet_ntoa(my_addr.sin_addr), ntohs(my_addr.sin_port), len);
		
		uint16_t port = ntohs(my_addr.sin_port);
		uint32_t ip = ntohl(my_addr.sin_addr.s_addr);
		
		uint8_t n[6];
		n[0] = (ip >> 24) & 0xFF;
		n[1] = (ip >> 16) & 0xFF;
		n[2] = (ip >> 8) & 0xFF;
		n[3] = ip & 0xFF;
		n[4] = (port / 256) & 0xFF;
		n[5] = (port % 256) & 0xFF;
		
		/* wierd bug only works with this loop calling printf */
		int i;
		for(i = 0; i<6; i++) {
			printf("");
		}
		printf("");
		
		/* tried to flush stdout */
		/*status = fflush(stdout);
		if(status != 0)
		{
			fprintf(stderr, "error on fflush()\n");
			exit(EXIT_FAILURE);
		}
		usleep(1000);
		*/
		
		char buf[ADDRLEN + 1];
		uint8_t bytes = sprintf(buf, "%d,%d,%d,%d,%d,%d",
							n[0], n[1], n[2], n[3], n[4], n[5]);
							
		memcpy(P->cmd, cmd, CMDLEN);
		memcpy(&P->arglen, &bytes, 1);
		memcpy(P->arg, buf, bytes);
		/* NULL terminate if possible */
		int left = MAXARG - bytes;
		memset(P->arg + left, 0, left);
	}
	
	/* genericc packet assignments */
	memcpy(&P->status, &status, 1);
	if(args != NULL)
	{
		memcpy(&P->arglen, &arglen, 1);
		memcpy(P->arg, args, arglen);
		/* NULL terminate if possible */
		int left = MAXARG - arglen;
		memset(P->arg + left, 0, left);
	}
	return P;
}

/* sends cmd defined in packet */
void sendcmd(int socketfd, packet_t* cmd)
{
	int expected = sizeof(packet_t);
	int bytes = 0, sent = 0;
	do {
		bytes = write(socketfd, cmd, sizeof(packet_t));
			error(bytes, "sendcmd(): write()");
		sent += bytes;
	} while(sent < expected && bytes > 0);
}

/* returns packet buffered in socket */
packet_t* recvcmd(int socketfd)
{
	packet_t* P = malloc(sizeof(packet_t));
	int expected = sizeof(packet_t);
	int recv = 0, bytes = 0;
	do {
		bytes = read(socketfd, P, sizeof(packet_t));
			error(bytes, "sendcmd(): write()");
		recv += bytes;
	} while(recv < expected && bytes > 0);
	
	return P;
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


/* function to do port calculation, returns struct with info */
socklen_t parseport(packet_t* P, struct sockaddr_in* ret_addr)
{
	struct sockaddr_in new_addr;
	bzero((char*) &new_addr, sizeof new_addr);
	char* info = strndup(P->arg, strnlen(P->arg, MAXARG));
	char *tok;
	uint8_t n[6] , i = 0;
	
	tok = strtok(info, ",");
	do{
		n[i] = atoi(tok);
	} while (((tok = strtok(NULL, ",")) != NULL) && i++ < 6);
	
	for(i = 0; i<6; i++)
	{
		printf("", n[i]);
	}
	printf("");
	
	/* ip conversion works */
	uint16_t port = 0;
	uint32_t ip = 0;
	
	/* numbers are sent and recvd in Network Byte Order */
	ip |= (n[0] << 24);
	ip |= (n[1] << 16);
	ip |= (n[2] << 16);
	ip |= n[3];
	port += (256 * n[4]) + n[5];
	
	/* make the client address */
	new_addr.sin_family = AF_INET;
	new_addr.sin_port=  htons(port);
	new_addr.sin_addr.s_addr = htonl(ip);
	
	socklen_t len = sizeof new_addr;
	memcpy(ret_addr, &new_addr, len);
	
	printf("%s %d %d\n", inet_ntoa(new_addr.sin_addr), ntohs(new_addr.sin_port), len);
	return len;
}

/* frees allocated packet struct */
void freepkt(packet_t* P)
{
	if(P != NULL)
	{
		free(P);
		P = NULL;
	}
}

/* generic printf funciton for packets */
void printpkt(packet_t* P)
{
	char buf[CMDLEN + 1];
	buf[CMDLEN] = 0;
	memcpy(buf, P->cmd, CMDLEN);
	printf("%s: ", buf);
	if(P->status)
		printf("%d ", P->status);
	if(P->arglen)
	{
		char* arg = strndup(P->arg, P->arglen);
		printf("%s", arg);
		free(arg);
	}
	printf("\n");
}
