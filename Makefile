CFLAGS=-O0 -g

.test:
.demo2:

default: demo2

input:
	nm -P demo2 2>&1 | grep exploit | awk '{print $$3}'

clean:
	rm -f ./demo2 ./test

PHONY: input clean
