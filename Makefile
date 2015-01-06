CC=g++
CFLAGS= -Wall
LIBS= -lboost_filesystem -lboost_system -lpthread -lboost_thread
all: telnetDemon
telnetDemon: main.cpp configFile.cpp
	$(CC) -g -o $@  $^ $(LIBS)
clean: 
	rm -f telnetDemon

