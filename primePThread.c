/*
	Barbara Hazlett
	hazlettb@onid.oregonstate.edu
	CS311-400
	Homework6, primePThread version 
*/
/* 
	- used code from http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html
	for bit array functions
	- modified code from http://www.programminglogic.com/the-sieve-of-eratosthenes-implemented-in-c/
	for prime algorithm
	- used code from http://stackoverflow.com/questions/22006507/thread-safe-bit-array to debug my
	program and to try out mutex
*/

#include "primePThread.h"

struct thread_data
{
	int thread_id;
	unsigned long int m_size;
	long int * bit_array;
	int n_threads;
};

pthread_mutex_t mutex_mark;

int main (int argc, char **argv) {
	
	int	qflag = 0;
	unsigned long int m_size = UINT_MAX;
	int n_threads = 1;
	pthread_t threads[n_threads];
	int rc;
    long int t;
	long int *bit_array;
	long int i;

	parse_com(argc, argv, &qflag, &m_size, &n_threads);
		
	//declare struct
	struct thread_data thread_data_array[n_threads];	
	
	//allocate memory for the bit array
	bit_array = calloc((m_size/32)+1, sizeof(long int));
	
	//set up bitmap for sieve 
	for (i=3;i<m_size;i+=2) 
			setBit(bit_array,i);
				
	//create threads	
    for(t = 0; t < n_threads; t++){
        //printf("In main: creating thread %ld\n", t);		
		thread_data_array[t].thread_id = t;
		thread_data_array[t].m_size = m_size;
		thread_data_array[t].n_threads = n_threads;
		thread_data_array[t].bit_array = bit_array;			
        rc = pthread_create(&threads[t], NULL, calcPrimes, (void *)&thread_data_array[t]);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }
 
	
	//step through array, check for twins and print if no q
	for (i = 0; i < (m_size - 2); i++) {
		if (testBit(bit_array, i) && testBit(bit_array,(i+2))) {
			if (qflag == 0)
				printf("%lu %lu\n", i, i + 2);					
		}	
	}	
	
	pthread_exit(NULL);
	//free memory	
	free(bit_array);
	//free(thread_data_array);
	
	return 0;

}

void parse_com(int argc, char **argv, int *qflag, unsigned long int *m_size, int *n_threads){
	extern char *optarg;
	int c;
	
	while ((c = getopt(argc, argv, "qm:c:")) != -1)
		switch (c) {
		case 'q':
			*qflag = 1;
			break;
		case 'm':
			*m_size = atol(optarg);
			if (*m_size > UINT_MAX) {
				printf("Cannot run for above UINT_MAX");
				exit(EXIT_FAILURE);
			}	
			break;
		case 'c':
			*n_threads = atoi(optarg);
			break;
		case '?':
	    default:
            printf ("Usage: %s -q -m <value> -c <value>\n", argv[0]);
			break;

		}	
}

void *calcPrimes(void *threadarg){
	int n;
	long int i, j;
	int taskid;
	long int m_size;
	int n_threads;
	long int *bit_array;
	struct thread_data *my_data;
		
	my_data = (struct thread_data *) threadarg;
	taskid = my_data->thread_id;
	m_size = my_data->m_size;
	bit_array = my_data->bit_array;
	n_threads = my_data->n_threads;
	n = 3 + 2*taskid;
	for (i = n; i < m_size; i+=(2*n_threads)){
		if (testBit(bit_array, i)){
			for (j=i;i*j<m_size;j++){
				//pthread_mutex_lock(&mutex_mark);
				clearBit(bit_array,(i*j));	
				//pthread_mutex_unlock(&mutex_mark);
			}
		}		
	}
	
	return 0;
}


	
