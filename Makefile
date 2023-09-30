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
SRC			= main.c vec3.c \
			collison_cy.c collison_pl.c collison_sp.c \
			ray.c parser.c parser_utils.c \
			setter.c setter_utils.c setter_object.c \
			camera.c
SRC			:=	$(addprefix $(SRCDIR)/, $(SRC))
OBJ			= $(SRC:.c=.o)

INC			= -Iincludes -Ilib/mlx -Ilib/libft -Ilib/get_next_line
NAME		= miniRT
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
LIBFLAGS	= -L$(LIBDIR)/libft -L$(LIBDIR)/get_next_line -L$(LIBDIR)/mlx -lft -lgnl -lmlx -framework OpenGL -framework AppKit
RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
	@$(MAKE) -C ./$(LIBDIR)/mlx
	@$(MAKE) -C ./$(LIBDIR)/get_next_line
	@$(MAKE) -C ./$(LIBDIR)/libft
	@echo $(GREEN)"mlx made" $(EOC)
	@$(CC) $(LIBFLAGS) $(OBJ) -o $(NAME) -fsanitize=address -g3
	@echo $(GREEN)"miniRT made" $(EOC)

%.o: 		%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) ./$(LIBDIR)mlx/*.o
	@$(RM) ./$(LIBDIR)/libft/*.o
	@$(RM) ./$(LIBDIR)/get_next_line/*.o
	@echo $(GREEN)"lib cleaned" $(EOC)
	@$(RM) $(OBJ) $(BOBJ)
	@echo $(GREEN)"miniRT cleaned" $(EOC)

fclean:		clean
	@$(RM) $(NAME)
	@echo $(GREEN)"miniRT fcleaned" $(EOC)

re:			fclean all

.PHONY:		clean fclean re
