#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *
function(void *args)
{
	(void)args;
	printf("Hello World\n");
	return NULL;
}

/* for now i'm just gonna just print text using threads */
int
main(void)
{
	pthread_t thread_main;
	pthread_create(&thread_main, function, NULL);
	pthread_join(thread_main, NULL);
	return 0;
}
