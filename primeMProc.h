/*
	Barbara Hazlett
	hazlettb@onid.oregonstate.edu
	CS311-400
	Homework6, primeMProc version 
*/

#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <pthread.h>
#include <getopt.h>
#include <math.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#ifndef _PRIMEMPROC_H
#define _PRIMEMPROC_H

#define UINT_MAX 4294967295

#define setBit(A,k)     ( A[(k/32)] |= (1 << (k%32)) )
#define clearBit(A,k)   ( A[(k/32)] &= ~(1 << (k%32)) )            
#define testBit(A,k)    ( A[(k/32)] & (1 << (k%32)) )

extern void *create_mem(char *path, int object_size);
extern void parse_com(int argc, char **argv, int *qflag, unsigned long int *m_size, int *n_procs);

#endif 