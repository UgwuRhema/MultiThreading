#include <iostream>
#include <thread>

void thread_function(void)
{
	std::cout << "Hello World\n";
}

int main(void)
{
	/* i believe this is how threads are made... */
	std::thread thread_main(thread_function);
	thread_main.join(); //so simple...
	return 0;
}
