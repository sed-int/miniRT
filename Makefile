#-------------------------------------------

BLACK       =   "\033[0;30m"
GRAY        =   "\033[1;30m"
RED         =   "\033[1;31m"
GREEN       =   "\033[0;32m"
YELLOW      =   "\033[1;33m"
PURPLE      =   "\033[0;35m"
CYAN        =   "\033[1;36m"
WHITE       =   "\033[1;37m"
EOC         =   "\033[0;0m"
LINE_CLEAR  =   "\x1b[1A\x1b[M"

#-------------------------------------------

SRCDIR		=	./srcs
SRC			= main.c vec3.c ray.c
SRC			:=	$(addprefix $(SRCDIR)/, $(SRC))
OBJ			= $(SRC:.c=.o)


INC			= -Iincludes
NAME		= miniRT
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
MFLAGS		= -Lmlx -lmlx -framework OpenGL -framework AppKit
RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
	@$(MAKE) -C ./mlx
	@echo $(GREEN)"mlx made" $(EOC)
	@$(CC) $(MFLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN)"miniRT made" $(EOC)

%.o: 		%.c
	@$(CC) $(CFLAGS) -Imlx $(INC) -c $< -o $@

clean:
	@$(RM) mlx/*.o
	@echo $(GREEN)"mlx cleaned" $(EOC)
	@$(RM) $(OBJ) $(BOBJ)
	@echo $(GREEN)"miniRT cleaned" $(EOC)

fclean:		clean
	@$(RM) $(NAME) $(BNAME)
	@echo $(GREEN)"miniRT fcleaned" $(EOC)

re:			fclean all

.PHONY:		clean fclean re
