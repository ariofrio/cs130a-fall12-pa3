CXXFLAGS=-std=gnu++0x
LDFLAGS=

SRC=\
     main.o \
		 graph.o

.PHONY: all test clean

all: hops

hops: $(SRC)
	$(CXX) $(LDFLAGS) $(SRC) -o $@

test: hops
	test/run_all.sh ./hops

clean:
	rm -f *.o
	rm -f hops

