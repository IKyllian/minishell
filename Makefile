NAME = minishell
LIB_NAME = libft.a

HEADER = ./inc/minishell.h
LIB_PATH = ./libft/
SRCS =  main.c \
		./builtins/echo.c \
		./builtins/pwd.c \
		./builtins/cd.c \

OBJS = $(SRCS:.c=.o)

CC = gcc
FLAGS = -Wextra -Werror -Wall
RM = rm -f

all : $(NAME)
 
%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(LIB_PATH)$(LIB_NAME) $(OBJS) $(HEADER)
		$(CC) $(FLAGS) -o $@ $(OBJS) $(LIB_PATH)$(LIB_NAME)

$(LIB_PATH)$(LIB_NAME) :
		@make -C $(LIB_PATH)

run : $(NAME)
	./minishell

clean :
		$(RM) $(OBJS)
		@make clean -C $(LIB_PATH)

fclean : clean
	$(RM) $(NAME)
	@make fclean -C $(LIB_PATH)

re : fclean all

.PHONY : clean fclean re all run