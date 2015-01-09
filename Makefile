CC=clang++
CFLAGS= -Wall
LIBS= -lboost_filesystem -lboost_system -lpthread -lboost_thread
all: telnetDemon
telnetDemon: src/main.cpp src/configFile.cpp src/telnetServer.cpp src/localServer.cpp src/execShell.cpp
	$(CC) $(CFLAGS) -o $@  $^ $(LIBS)
clean: 
	rm -f telnetDemon

