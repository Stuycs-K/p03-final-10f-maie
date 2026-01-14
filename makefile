.PHONY: clean run compile

client.o: client.c networking.h
	@gcc -Wall -c client.c

server.o: server.c networking.h
	@gcc -Wall -c server.c

networking.o: networking.c networking.h
	@gcc -Wall -c networking.c

compile client server: client.o server.o networking.o
	@gcc -o client client.o networking.o
	@gcc -o server server.o networking.o

clean:
	rm -f *.o client server log.txt
