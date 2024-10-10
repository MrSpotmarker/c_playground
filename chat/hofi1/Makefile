all: server client

sockethelper.o:
	gcc -c socketHelper.c -o sockethelper.o

server: sockethelper.o
	gcc sockethelper.o server.c -o server

client: sockethelper.o
	gcc sockethelper.o client.c -o client


clean:
	rm -rf sockethelper.o client server
