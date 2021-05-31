CC = gcc
CARGS = -Os

all: build

build: mkdir cat pwd uname

mkdir:
	rm -rf bin
	mkdir bin

cloc:
	cloc .

clean:
	rm -rf bin

cat:
	$(CC) $(CARGS) src/cat/cat.c -o bin/cat

pwd:
	$(CC) $(CARGS) src/pwd/pwd.c -o bin/pwd

uname:
	$(CC) $(CARGS) src/uname/uname.c -o bin/uname
