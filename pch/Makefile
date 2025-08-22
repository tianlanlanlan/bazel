all: main

log.h.gch: log.h
	g++ -std=c++11 -o log.h.gch -c log.h

main: main.cc log.h.gch
	g++ main.cc

.PHONY: clean
clean:
	rm -f main log.h.gch