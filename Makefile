##
## EPITECH PROJECT, 2019
## make file
## File description:
## make file
##

RM		=	rm -f

SRC_CLASS	=	src/class_init/structure_init.c	\
				src/class_init/structure_init_functions.c	\
				src/class_init/socket_class_init.c	\
				src/class_init/init_map_class.c	\
				src/class_init/user_info.c	\

SRC_ERROR	=	src/errors/errors_server.c

SRC_SERVER	=	src/server/clients_connection/create_new_client_connection.c	\
				src/server/clients_connection/client_loop.c	\
				src/server/server_creation/create_server.c	\
				src/server/server_commands/parse_commands.c	\
				src/server/server_commands/simple_commands.c	\
				src/server/server_commands/directory_commands.c	\
				src/server/server_commands/mode_commands.c	\
				src/server/server_commands/transfert_commands.c	\
				src/server/server_commands/commands.c	\
				src/server/server_commands/transfert_file_commands.c	\

SRC_TOOLS	=	src/tools/split_array.c	\
				src/tools/writing_tools.c	\
				src/tools/copy_tools.c	\

SRC		=	$(SRC_CLASS)	\
			$(SRC_ERROR)	\
			$(SRC_SERVER)	\
			$(SRC_TOOLS)	\
			src/main.c	\

OBJ		=	$(SRC:.c=.o)

NAME	=	myftp

CC		=	gcc

CFLAGS	+=	-I ./inc/

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) -I ./inc/ -g3

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY	:	all clean fclean re
