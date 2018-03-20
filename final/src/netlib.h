#ifndef _NET_LIB_H_
#define _NET_LIB_H_

#include <stdint.h> /* uintN_t */
#include <stdlib.h> /* calloc() exit macros */
#include <stdio.h> /* perror() */
#include <string.h> /* strdup */
#include <strings.h> /* bzero */

#include <fcntl.h> /* used for open() and read() */
#include <unistd.h> /* used for close() , dup2() */
#include <sys/types.h> /* defines unsigned types (sys/socket.h) */
#include <sys/stat.h> /* struct stat */
#include <sys/socket.h> /* defines socket macros & socket func */
#include <netdb.h> /* defines datatypes and structures (netinet/in.h) */
#include <netinet/in.h> /* used for address structures */ 
#include <arpa/inet.h> /* contains byte order functions */

#include <sys/select.h> /* select and other functions */

#define TRUE	1
#define FALSE	0
#define LISTENQ 5
#define KB_SIZE 1024
#define PORT_STRLEN  5 /* ports are 16 bits (65535) */
#define ADDRLEN			INET_ADDRSTRLEN + PORT_STRLEN

/* perror wrapper */
static inline void
error(int retval, char* msg) {
	if(retval == -1) {
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

#endif /* _NET_LIB_H_ */
