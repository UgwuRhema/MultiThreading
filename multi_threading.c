#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

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
	pthread_create(&thread_main, NULL, &function, NULL);
	pid_t pid = fork();
	if (pid == 0)
	{
		pthread_join(thread_main, NULL);
	} else if (pid < 0){
		perror("Fork Failed!");
		exit(1);
	} else {
		printf("Parent process, waiting for child...");
	}
	return 0;
}
