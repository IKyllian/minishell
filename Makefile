NAME = minishell
LIB_NAME = libft.a

HEADER = ./inc/minishell.h
LIB_PATH = ./libft/
LST_SRCS =  main.c						\
			error.c						\
			env/env_utils.c				\
			env/env_tools.c				\
			builtins/echo.c				\
			builtins/pwd.c				\
			builtins/cd.c				\
			builtins/builtins_utils.c	\
			builtins/export.c			\
			builtins/export_utils.c		\
			builtins/unset.c			\
			builtins/env.c				\
			builtins/exit.c				\
			builtins/exit_pipe.c		\
			parsing/escaper.c			\
			parsing/tokenizer.c			\
			parsing/quoting.c			\
			parsing/history.c			\
			parsing/subber.c			\
			parsing/retokenize.c		\
			parsing/redirecter.c		\
			parsing/validator.c			\
			sig/signals.c				\
			sig/signals_utils.c			\
			utils/array_utils.c			\
			utils/list_pars_manage.c	\
			utils/list_pars_utils.c		\
			utils/mem_utils.c			\
			utils/operators_utils.c		\
			utils/parsing_utils.c		\
			utils/tokenizer_utils.c		\
			utils/subber_utils.c		\
			utils/subber_tools.c		\
			utils/redirecter_utils.c	\
			utils/prompt_utils.c		\
			utils/strct_init.c			\
			utils/list_utils.c			\
			exec/exec.c					\
			exec/exec_utils.c			\
			exec/exec_error.c			\
			exec/exec_current_path.c	\
			redirect/heredoc.c			\
			redirect/redirect.c			\
			redirect/init_heredoc.c		\
			pipe/pipe.c					\
			pipe/pipe_utils.c			\
			prompt.c
		
LST_OBJS = $(LST_SRCS:.c=.o)

CC = gcc
FLAGS = -Wextra -Werror -Wall -g -fPIC
RLFLAGS = -lreadline -L /Users/$$USER/.brew/opt/readline/lib -I/Users/$$USER/.brew/opt/readline/include
RM = rm -rf

DIR_FILES = srcs
DIR_OBJS = .objs
LST	=	builtins	\
		env			\
		exec		\
		parsing		\
		pipe		\
		redirect	\
		sig			\
		utils

SRCS = $(addprefix $(DIR_FILES)/,$(LST_SRCS))
OBJS = $(addprefix $(DIR_OBJS)/,$(LST_OBJS))

all : libft $(NAME)

$(DIR_OBJS)/%.o : $(DIR_FILES)/%.c $(HEADER) $(LIB_PATH)$(LIB_NAME)
	@mkdir -p $(DIR_OBJS) $(addprefix $(DIR_OBJS)/,$(LST))
	$(CC) $(FLAGS) -I inc -I $(LIB_PATH) -c $< -o $@

$(NAME) : $(LIB_PATH)$(LIB_NAME) $(OBJS) $(HEADER)
		$(CC) $(FLAGS) $(RLFLAGS) -L $(LIB_PATH) -lft -o $@ $(OBJS)

libft :
		make -C $(LIB_PATH)

$(LIB_PATH)$(LIB_NAME) : libft

run : $(NAME)
	./minishell

clean :
		$(RM) $(DIR_OBJS)
		make clean -C $(LIB_PATH)

fclean : clean
	$(RM) $(NAME)
	make fclean -C $(LIB_PATH)

re : fclean all

.PHONY : clean fclean re all run libft