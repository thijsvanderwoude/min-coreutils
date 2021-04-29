all: build

build: mkdir cat cloc

mkdir:
	rm -rf bin
	mkdir bin

cloc:
	cloc src

clean:
	rm -rf bin

cat:
	gcc src/cat/cat.c -o bin/cat
