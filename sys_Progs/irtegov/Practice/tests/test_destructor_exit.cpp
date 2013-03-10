#include <pthread.h>
#include <unistd.h>
#include <iostream>

class TestClass {
public:
	int value;
	TestClass(int parameter) {
		std::cout << "Constructed " << parameter << "\n";
		value=parameter;
	}
	~TestClass() {
		std::cout << "destructed " << value << "\n";
	}
};

extern "C" {
void *body_forexit(void * param) {
	TestClass a(1);

	sleep(1);
	pthread_exit((void *)a.value);
	return (void *)a.value;
}

void *body_forreturn(void * param) {
	TestClass b(2);
	
	sleep(2);
	return (void *)b.value;
}
} // extern "C"

int main() {

	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, body_forexit, NULL);
	pthread_detach(thread1);
	pthread_create(&thread2, NULL, body_forreturn, NULL);
	pthread_detach(thread2);
	// pthread_exit(NULL);
	_exit(0);
	return 0;
}
