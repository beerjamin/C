/*
* p2-pthread-oops.c --
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
static int N = 5;
static const char *progname = "pthread";

static void* run(void *arg)
{
	int *i = (int *) arg;
	char buf[123];
	snprintf(buf, sizeof(buf), "thread %d", *i);
	return (NULL);
}

int main(int argc, char *argv[])
{
	int i, err;
	unsigned int n = 5;
	pthread_t *pt;
	pt = (pthread_t*)calloc(n, sizeof(pthread_t));
	if(!pt){
		fprintf(stderr, "%s: %s: %s\n", progname, __func__, strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	for (i = 0; i < N; i++) {
		err = pthread_create(&pt[i], NULL, run, &i);
		printf("%p ==> Thread created successfully\n", &pt[i]);
		if (err){
			fprintf(stderr, "unable to create the threads\n");
		}
	}
	//joining the threads
	for (i = 0; i < N; i++){
		if(pt[i]){
			err = pthread_join(pt[i], NULL);
			if (err){
				fprintf(stderr, "Unable to joint the threads\n");
			}
		}
	}
	
	return EXIT_SUCCESS;
}
