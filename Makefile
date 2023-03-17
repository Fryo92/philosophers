# Variables

NAME	=	philo

CC		=	cc
FLAG	=	-Wall -Wextra -Werror #-fsanitize=thread
SRC_DIR	=	src/
OBJ_DIR =	obj/
INCLUDE	=	./include


# Colors

DEF_COLOR	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m

# Sources

FILES	=	main utils utils_eat utils_check error routine init

SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

###

OBJF	=	.cache_exists

$(OBJF)	:
	@mkdir -p $(OBJ_DIR)

all		:	$(NAME)

$(NAME)	:	$(OBJS) $(INCLUDE)/philo.h ./Makefile
	@echo "$(YELLOW)COMPILING PHILO...$(DEF_COLOR)"
	$(CC) $(FLAG) $(OBJS) -I$(INCLUDE) -o $(NAME) -lpthread
	@echo "$(GREEN)Philo compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c | $(OBJF)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean	:
	@rm -rf $(OBJ_DIR)
	@rm -f $(OBJF)
	@echo "$(MAGENTA)Philo objects cleaned!$(DEF_COLOR)"

fclean	:	clean
	@rm -f $(NAME)
	@echo "$(YELLOW)Philo executable cleaned!$(DEF_COLOR)"

re		:	fclean all
	@echo "$(GREEN)Cleaned and rebuilt!$(DEF_COLOR)"

.PHONY	:	all clean fclean re