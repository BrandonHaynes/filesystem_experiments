CC = gcc
CFLAGS = -Wall -std=gnu99

all: readFile readBytes readSizeAndBytes readSizeAndBytes_amalgamations readBytes_amalgamations measureThroughput

readFile:
	$(CC) $(CFLAGS) -o readFile readFile.c clearCache.c

readBytes:
	$(CC) $(CFLAGS) -o readBytes readBytes.c clearCache.c

readSizeAndBytes: 
	$(CC) $(CFLAGS) -o readSizeAndBytes readSizeAndBytes.c clearCache.c

readSizeAndBytes_amalgamations: 
	$(CC) $(CFLAGS) -o readSizeAndBytes_amalgamations readSizeAndBytes_amalgamations.c clearCache.c

readBytes_amalgamations: 
	$(CC) $(CFLAGS) -o readBytes_amalgamations readBytes_amalgamations.c clearCache.c

measureThroughput:
	$(CC) $(CFLAGS) -o measureThroughput measureThroughput.c clearCache.c
