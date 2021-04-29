CC = gcc
CARGS = -Os

all: build

build: mkdir cat uname cloc

mkdir:
	rm -rf bin
	mkdir bin

cloc:
	cloc .

clean:
	rm -rf bin

cat:
	$(CC) $(CARGS) src/cat/cat.c -o bin/cat

uname:
	$(CC) $(CARGS) src/uname/uname.c -o bin/uname
