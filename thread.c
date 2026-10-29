#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bank_account
{
	char name[50];
	double balance;
	pthread_mutex_t lock;
	/*i want to use threads*/
	void*(*withdraw)(void *);
};

struct bank_account *new_account(char *, double, void *);

/*routine*/
void *wdraw(void *arg)
{
	struct bank_account *ba = (struct bank_account *)arg;
	pthread_mutex_lock(&ba->lock);
	ba->balance -=  5.00;/*withdraw*/
	printf("%.2lf\n", ba->balance);
	pthread_mutex_unlock(&ba->lock);
	return NULL;
}

int
main(int argc, char *argv[])
{
	pthread_t t1, t2;/*new thread*/
	struct bank_account *newBank = new_account("Rhema", 10.00, &wdraw);
	/*let's say from the same account we wnat to withdraw 5.00*/
	/*we now call it between the two threads*/
	pthread_create(&t1, NULL, newBank->withdraw, (void *)newBank);
	pthread_create(&t2, NULL, newBank->withdraw, (void *)newBank);
	pthread_join(t1, NULL); pthread_join(t2, NULL);
	pthread_mutex_destroy(&newBank->lock);
	free(newBank);
	return 0;
}

#define DEFT (sizeof(struct bank_account))
struct bank_account *
new_account(char *name, double init_balance, void *func)
{
	struct bank_account *nb = (struct bank_account *)malloc(DEFT);	
	strcpy(nb->name, name);
	nb->balance = init_balance;
	nb->withdraw = func;
	pthread_mutex_init(&nb->lock, NULL);
	return nb;
}
