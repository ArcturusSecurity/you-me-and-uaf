#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void exploit() { puts("The horrors, of spider island!"); }
void goodfun() { puts("I'm Bob Boxbody"); }

typedef struct {
	uint8_t methodName[20];
	uintptr_t (*func)();
} Object;

void doProcess(Object* obj) {
	printf("[+] Calling %s\n", obj->methodName);
	(*obj->func)();
}

int main(int argc, char **argv) {
	Object *oThing = (void *)malloc(sizeof(Object));
	oThing->func = (void *)goodfun;
	strcpy(oThing->methodName, "goodfun_method");


	doProcess(oThing);
//	puts("addrs:");
//	printf("  exploit: %p\n", (void*)exploit);
//	printf("   oThing: %p\n", (void*)oThing);
	free(oThing); // done with this object now

	uint8_t *userInput = (void *)malloc(32);
//	printf("userInput: %p\n", (void*)oThing);
	read(STDIN_FILENO, userInput, 32); // read 32 bytes

	doProcess(oThing); // whoops, we shouldn't have processed this again

	return 0;
}
