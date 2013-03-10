#include <pthread.h>
#include <unistd.h>
#include <iostream>

class TestClass
{
	public:
	int value;
	TestClass(int param)
	{
		std::cout << "Constructed " << param << "\n";
	}

	~TestClass()
	{
		std::cout << "destructed " << value << "\n";
	}
};

extern "C"
{
	void* body_forexit(void* param)
	{
		TestClass a(0xffffffff80000000);
		sleep(1);
		pthread_exit( (void*)a.value );
		return (void*)a.value;
	}

	void* body_forreturn(void* param)
	{
		TestClass b(2);
		sleep(2);
		return (void*)b.value;
	}
}

int main(void)
{
	pthread_t thread1, thread2;

	if(pthread_create(&thread1, NULL, body_forexit, NULL))
		std::cout<<"Something went wrong!";
	pthread_detach(thread1);
	if(pthread_create(&thread2, NULL, body_forreturn, NULL))
		std::cout<<"Something went wrong!";
	pthread_detach(thread2);
	pthread_exit(NULL);
	return 0;

}
