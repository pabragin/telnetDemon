CC=g++
CFLAGS= -Wall
LIBS= -lboost_filesystem -lboost_system -lpthread -lboost_thread
all: telnetDemon
telnetDemon: main.cpp configFile.cpp telnetServer.cpp execShell.cpp
	$(CC) -g -o $@  $^ $(LIBS) $(CFLAGS)
clean: 
	rm -f telnetDemon

