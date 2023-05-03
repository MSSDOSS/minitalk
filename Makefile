SOURCES = server.c client.c men_tools.c
OBJECTS = server.o client.o men_tools.o
SOURCESBOO = server_bonus.c client_bonus.c
OBJECTSBOO = server_bonus.o client_bonus.o

CC = gcc
FLAGS = -Wall -Werror -Wextra -fsanitize=address

all: server client minitalk.h

bonus: server_bonus client_bonus

client: client.o men_tools.o
	$(CC) -o $@ client.o men_tools.o -fsanitize=address

client_bonus: client_bonus.o
	$(CC) -o $@ client_bonus.o men_tools.o -fsanitize=address

server: server.o men_tools.o
	$(CC) -o $@ $< men_tools.o -fsanitize=address

server_bonus: server_bonus.o men_tools.o
	$(CC) -o $@ $< men_tools.o -fsanitize=address

%.o: %.c minitalk.h
	$(CC) -c $(FLAGS) $<

clean:
	rm -f $(OBJECTS) $(OBJECTSBOO)

fclean: clean
	rm -f client server client_bonus server_bonus

re: fclean all

.PHONY: all bonus clean fclean re
