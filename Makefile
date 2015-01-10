UNAME := $(shell uname)
CC=clang++
CFLAGS= -Wall
LIBS= -lboost_filesystem -lboost_system -lpthread -lboost_thread
SOURCE =  src/main.cpp src/configFile.cpp src/telnetServer.cpp src/localServer.cpp src/execShell.cpp
INCLUDE = 
ifeq ($(UNAME), FreeBSD)
	LIBS += -L /usr/local/lib
	INCLUDE += -I /usr/local/include
endif
telnetDemon: $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $^  $(LIBS) $(INCLUDE) 
clean: 
	rm -f telnetDemon

