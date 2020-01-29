# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nvan-der <nvan-der@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/17 19:33:11 by nvan-der       #+#    #+#                 #
#    Updated: 2020/01/24 20:10:31 by nvan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

buf = 32
all:
	gcc get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=$(buf) -g