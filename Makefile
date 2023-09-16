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

LIBDIR		= ./lib

SRCDIR		= ./srcs
SRC			= main.c vec3.c parsing.c
SRC			:=	$(addprefix $(SRCDIR)/, $(SRC))
OBJ			= $(SRC:.c=.o)

INC			= -Iincludes -Imlx -Ilib/libft -Ilib/gnl
NAME		= miniRT
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
LIBFLAGS	= -L$(LIBDIR)/libft -L$(LIBDIR)/gnl -L$(LIBDIR)/mlx -lft -lgnl -lmlx -framework OpenGL -framework AppKit
RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
	@$(MAKE) -C ./$(LIBDIR)/mlx
	@$(MAKE) -C ./$(LIBDIR)/gnl
	@$(MAKE) -C ./$(LIBDIR)/libft
	@echo $(GREEN)"mlx made" $(EOC)
	@$(CC) $(LIBFLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN)"miniRT made" $(EOC)

%.o: 		%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) ./$(LIBDIR)mlx/*.o
	@$(RM) ./$(LIBDIR)/libft/*.o
	@$(RM) ./$(LIBDIR)/gnl/*.o
	@echo $(GREEN)"lib cleaned" $(EOC)
	@$(RM) $(OBJ) $(BOBJ)
	@echo $(GREEN)"miniRT cleaned" $(EOC)

fclean:		clean
	@$(RM) $(NAME)
	@echo $(GREEN)"miniRT fcleaned" $(EOC)

re:			fclean all

.PHONY:		clean fclean re
