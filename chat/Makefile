OBJ:=client_socket server_socket

.PHONY:all clean
all:client_socket server_socket


client_socket:client_socket.c
	gcc -o client_socket client_socket.c

server_socket:server_socket.c
	gcc -o server_socket server_socket.c

clean:
	rm -rf $(OBJ)
