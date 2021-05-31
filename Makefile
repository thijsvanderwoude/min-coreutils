CC = gcc
CARGS = -O3

all: build

build: mkdir cat split uname

mkdir:
	rm -rf bin
	mkdir bin

cloc:
	cloc .

clean:
	rm -rf bin

cat:
	$(CC) $(CARGS) src/cat/cat.c -o bin/cat

split:
	$(CC) $(CARGS) src/split/split.c -o bin/split

uname:
	$(CC) $(CARGS) src/uname/uname.c -o bin/uname
