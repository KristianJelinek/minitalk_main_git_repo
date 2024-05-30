# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kjelinek < kjelinek@student.42prague.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 19:01:31 by kjelinek          #+#    #+#              #
#    Updated: 2024/05/30 13:20:08 by kjelinek         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: client server

client: client.o
	$(CC) $(CFLAGS) -o client client.o

server: server.o
	$(CC) $(CFLAGS) -o server server.o

client.o: client.c
	$(CC) $(CFLAGS) -c client.c

server.o: server.c
	$(CC) $(CFLAGS) -c server.c

clean:
	rm -f *.o

fclean: clean
	rm -f client server

re: fclean all