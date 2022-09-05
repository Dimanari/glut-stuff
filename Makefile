#reverted to manual Makefile due to bugs

#don't kill my Object files you murderer!
.SECONDARY: $(OBJS)

#using the proper command to compile everything
CC = g++ -std=c++11 -pedantic-errors -Wall -Wextra
CFLAGS = -iquote ./include -I /usr/include/GL
vlg = valgrind --leak-check=yes --track-origins=yes
RELEASE = -DNDEBUG -O3
DEBUG = -g
#all object files to clean

libs = $(wildcard libs/*.o)
libs += -lglut -lGLU -lGL

objs = $(patsubst src/%.cpp,bin/%.o,$(wildcard src/*.cpp))
objects = game

all : release debug

debug : $(objects:=_d)
	$(vlg) ./$<

release : $(objects)

% : test/%_test.cpp $(objs)
	$(CC) $(CFLAGS) $(RELEASE) -o $@ $^ $(libs)

bin/%.o : src/%.cpp include/%.hpp
	$(CC) $(CFLAGS) $(RELEASE) -c -o $@ $<

%_d : test/%_test.cpp $(objs:.o=_d.o)
	$(CC) $(CFLAGS) $(DEBUG) -o $@ $^ $(libs)

bin/%_d.o : src/%.cpp include/%.hpp
	$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<

.PHONY : clean
clean : 
	rm -f *.o bin/*.o $(objects) *_d all
