/*
	Barbara Hazlett
	hazlettb@onid.oregonstate.edu
	CS311-400
	Homework6, primeMProc version 
*/

/* 
	- used code from lecture for creating shared memory
    - used code from http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html
	for bit array functions
	- modified code from http://www.programminglogic.com/the-sieve-of-eratosthenes-implemented-in-c/
	for prime algorithm
*/

#include "primeMProc.h"

int main (int argc, char **argv) {	
	int	qflag = 0;
	unsigned long int m_size = UINT_MAX;
	int object_size;
	int n_procs = 1;
	unsigned long int i = 0;
	unsigned long int j = 0;
	int n = 0;
	pid_t pids[n_procs];
	pid_t pid;
	int status;
	
	parse_com(argc, argv, &qflag, &m_size, &n_procs);
	unsigned int *bitmap;
	object_size = UINT_MAX/8 + 4;
	
	//create shared memory
	void *addr = create_mem("/hazlettb_prime", object_size);	
	bitmap = (unsigned int*)addr;	
	
	//set up bitmap for sieve 
	for (i=3;i<m_size;i+=2)
			setBit(bitmap,i);
			
	//fork the children
	for (i = 0; i < n_procs; ++i) {
		if ((pids[i] = fork()) < 0) {
			perror("fork");
			abort();
		}
		else if (pids[i] == 0) {
				
	//each child calculates and stores some of the primes
			n = 3 + 2*i;
			for (i = n; i < m_size; i+=(2*n_procs)){
				if (testBit(bitmap, i))
					for (j=i;i*j<m_size;j++)
						clearBit(bitmap,(i*j));					
			}
			exit(0);
		}
	}

	//wait for children to exit
	while (n_procs > 0) {
		pid = wait(&status);
		--n_procs;  
	}
			
	//step through array, check for twins and print if no q		
	for (i = 0; i < (m_size - 2); i++) {
		if (testBit(bitmap, i) && testBit(bitmap,(i+2))) {
			if (qflag == 0)
				printf("%lu %lu\n", i, i + 2);					
		}	
	}	
	
	//unlink memory object
	if (shm_unlink("/hazlettb_prime") == -1)
		printf("unlink failed");
	
	return 0;

}

void parse_com(int argc, char **argv, int *qflag, unsigned long int *m_size, int *n_procs){
	extern char *optarg;
	int c;
	
	while ((c = getopt(argc, argv, "qm:c:")) != -1)
		switch (c) {
		case 'q':
			*qflag = 1;
			break;
		case 'm':
			*m_size = atol(optarg);
			if (*m_size > 4294967295) {
				printf("Cannot run for above UINT_MAX");
				exit(EXIT_FAILURE);
			}	
			break;
		case 'c':
			*n_procs = atoi(optarg);
			break;
		case '?':
	    default:
            printf ("Usage: %s -q -m <value> -c <value>\n", argv[0]);
			exit(EXIT_FAILURE);
			break;

		}	
}

void *create_mem(char *path, int object_size) {
	int sh_fd;
	void *addr;
	
	sh_fd = shm_open(path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (sh_fd == -1)
		exit(EXIT_FAILURE);
	
	if (ftruncate(sh_fd, object_size) == -1)
		exit(EXIT_FAILURE);
		
	addr = mmap(NULL, object_size, PROT_READ | PROT_WRITE, MAP_SHARED, sh_fd, 0);

	return addr;
}


