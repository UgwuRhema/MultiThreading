#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

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
	pthread_join(thread_main, 0);
	pid_t pid = fork();
	if (pid == 0)
	{
		_exit(0);
	} else if (pid < 0){
		perror("Fork Failed!");
		exit(1);
	} else {
		int status;
		/* this waitpid is the culprit */
		waitpid(pid, &status, 0);
		sleep(2);
		printf("Parent process, ran child %d and has completed\n", (int)pid);
	}
	return 0;
}
