CC=g++
CFLAGS= -Wall -g
LIBS= -lboost_filesystem -lboost_system -lpthread -lboost_thread
all: telnetDemon
telnetDemon: main.cpp configFile.cpp telnetServer.cpp execShell.cpp
	$(CC) $(CFLAGS) -o $@  $^ $(LIBS)
clean: 
	rm -f telnetDemon

