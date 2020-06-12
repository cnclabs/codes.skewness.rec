CC = g++
CPPFLAGS = -std=c++11 -fPIC -fopenmp -lm -Ofast
OBJECTS=
OBJECTS = util.o random.o proNet.o ./model/SkewOPT.o
all: $(OBJECTS)
	mkdir -p ../bin
	ar rcs ../bin/libproNet.a $(OBJECTS)

%.o:%.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJECTS)
	rm ../bin/libproNet.a
