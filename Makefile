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
	gcc src/cat/cat.c -o bin/cat

uname:
	gcc src/uname/uname.c -o bin/uname
