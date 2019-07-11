CC=g++
CPPFLAGS=-c -Wall

SRC=main.cpp \
	InputHandle.cpp \
	HandEvaluator.cpp \
	Judge.cpp
OBJS=main.o \
	InputHandle.o \
	HandEvaluator.o \
	Judge.o

all: $(OBJS)
	$(CC) $(OBJS) -o poker

%.o : %.cpp
	$(CC) $(CPPFLAGS) $(SRC)
	
clean:
	rm *.o poker