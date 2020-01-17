# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nvan-der <nvan-der@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/17 19:33:11 by nvan-der       #+#    #+#                 #
#    Updated: 2020/01/17 22:01:20 by nvan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

buf = 100
all:
	gcc get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=$(buf) -g