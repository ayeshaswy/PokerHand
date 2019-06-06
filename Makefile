CC=g++
CPPFLAGS=-c -Wall

SRC=main.cpp \
	InputHandler.cpp \
	Hand.cpp \
	HandEvaluator.cpp \
	Judge.cpp
OBJS=main.o \
	InputHandler.o \
	Hand.o \
	HandEvaluator.o \
	Judge.o

all: $(OBJS)
	$(CC) $(OBJS) -o poker

%.o : %.cpp
	$(CC) $(CPPFLAGS) $(SRC)
	
clean:
	rm *.o poker