#include "fat.h"

/* packet structure definition */
struct packet_t 
{
		char cmd[CMDLEN]; 		/* 4 bytes		: cmd */
		uint8_t status;				/* 1 byte 		: [reply status code] */
		uint8_t arglen;				/* 1 byte 		: [length of args] */
		char arg[MAXARG];		/* 255 bytes : [cmd message] */
} __attribute__ ((packed));
