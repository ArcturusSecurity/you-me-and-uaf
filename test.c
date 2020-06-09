#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exploit() { puts("The horrors, of spider island!"); }
void goodfun() { puts("I'm Bob Boxbody"); }

typedef struct {
	uint8_t methodName[20];
	uintptr_t (*func)();
} Object;

int main(int argc, char **argv) {
	uintptr_t obj1, obj2;
	puts("[>] Use-After-Free, by example\n");
	printf("[+] Address of 'goodfun' function: %p\n", goodfun);
	printf("[+] Address of 'exploit' function: %p\n\n", exploit);

	puts("[+] Allocating object obj1");
	Object *oThing = (void *)malloc(sizeof(Object));
	if ( oThing == NULL ) { puts("[!] Couldn't allocate!"); return 1; }

	oThing->func = (void *)goodfun;
	obj1 = (uintptr_t)oThing;

	printf("[+] Address of obj1 in memory    : %p\n", obj1);
	printf("[+] Address of obj1->func pointer: %p\n\n", oThing->func);

	puts("[+] Calling obj1->func()");
	(*oThing->func)();

	puts("\n[+] Freeing object obj1");
	free(oThing);
	puts("[+] Allocating new object obj2");
	Object *oNewObject = (void *)malloc(sizeof(Object));
	obj2 = (uintptr_t)oNewObject;
	if ( oNewObject == NULL ) {
		puts("[!] Couldn't allocate!"); return 1;
	}
	if ( obj1 != obj2 ) {
		puts("[+] obj2 allocated to a new address. Exploit failed");
		return 1;
	} else {
		puts("[+] obj2 allocated to the same address as free'd obj1!");
	}
	oNewObject->func = (void *)exploit;
	printf("[+] Address of obj2 in memory    : %p\n\n", oNewObject);
	printf("[+] Address of obj2->func pointer: %p\n\n", oNewObject->func);

	puts("[+] Calling obj1->func()");
	(*oThing->func)();

	free(oNewObject);
	return 0;
}
