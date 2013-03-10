#include <stdio.h>
void main(void)
{
	char greeting[] = "Ahoy";
	char* c = greeting + 1;
	unsigned long badnews = *(unsigned long*)c;
	printf("c: %c", *c);
	return;
}
