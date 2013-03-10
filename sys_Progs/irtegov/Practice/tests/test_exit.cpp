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


int main() {
	TestClass a(1);

	exit(0);
	
}
