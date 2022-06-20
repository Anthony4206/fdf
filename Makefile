# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 13:11:44 by alevasse          #+#    #+#              #
#    Updated: 2022/06/20 09:30:28 by alevasse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= fdf
NAME_B 			= fdf

SRC 			= src/main.c

SRC_B 			= 

OBJ 			= ${SRC:.c=.o}
OBJ_B 			= ${SRC_B:.c=.o}

INCLUDE 		= -I./include/ -Imlx

MLX				= -lmlx -framework OpenGL -framework AppKit

HEAD			= 
					
LIBS 			= ./libft/
				
CC 				= gcc -g
CFLAGS 			= -Wall -Wextra -Werror

AR 				= ar rcs
RM 				= rm -f

GREEN			:= "\033[0;32m"
CYAN			:= "\033[0;36m"
RESET			:= "\033[0m"

%.o:			%.c
				@${CC} ${CFLAGS} ${INCLUDE} -o $@ -c $<

all: 			${NAME}

bonus:			${OBJ_B} ${HEAD}
				@make all -C ${LIBS}
				@echo ${GREEN}"Successfully updated 'libft'" ${RESET}
				@${CC} ${CFLAGS} ${INCLUDE} ${MLX} -o ${NAME_B} ${OBJ_B} ${LIBS}libft.a
				@echo ${GREEN}"Compiled '${NAME_B}' with success" ${RESET}
				@touch bonus

${NAME}:		${OBJ} ${HEAD}
				@make all -C ${LIBS}
				@echo ${GREEN}"Successfully updated 'libft'" ${RESET}
				@${CC} ${CFLAGS} ${INCLUDE} ${MLX} -o ${NAME} ${OBJ} ${LIBS}libft.a
				@echo ${GREEN}"Compiled '${NAME}' with success" ${RESET}

clean:
				@make clean -C ${LIBS}
				@${RM} ${OBJ} ${OBJ_B}
				@echo ${CYAN}"Cleaned '${NAME}' objects with success"${RESET}
				
fclean:			clean
				@make fclean -C ${LIBS}
				@${RM} ${NAME} ${NAME_B}
				@echo ${CYAN}"Removed '${NAME}' with success"${RESET}

re:				fclean all

.PHONY: 		all clean fclean re