TARGET_NAME	=	minishell

CC			=	gcc
# CC_FLAGS	=	-Wall -Werror -Wextra -fPIC -g
CC_FLAGS	=	-Wall -Werror -Wextra -g
DEL_DIR		=	rm -rf
DEL			=	rm -f
MAKE_LIBFT	=	make -C $(LIBFT_PATH)

INC_PATH	=	./includes/ $(LIBFT_PATH)includes/ ./obj/ $(LIBFT_PATH)obj/
OBJ_PATH	=	./obj/
SRC_PATH	=	./srcs/
LEXER_PATH	=	$(SRC_PATH)lexer/
PROC_PATH	=	$(SRC_PATH)processor/
CMD_PATH	=	$(SRC_PATH)command/
UTILS_PATH	=	$(SRC_PATH)utils/
TERM_PATH	=	$(SRC_PATH)term/
LIBFT_PATH	=	./libft/

OBJ			=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))
GCH			=	$(addprefix $(OBJ_PATH),$(GCH_NAME))

INC			=	$(addprefix -I,$(INC_PATH))

GCH_NAME	=	$(HEADERS:.h=.h.gch)

OBJ_NAME	=	$(SRC_NAME:.c=.o)
OBJ_NAME	+=	$(LEXER_NAME:.c=.o)
OBJ_NAME	+=	$(PROC_NAME:.c=.o)
OBJ_NAME	+=	$(CMD_NAME:.c=.o)
OBJ_NAME	+=	$(UTILS_NAME:.c=.o)
OBJ_NAME	+=	$(TERM_NAME:.c=.o)

SRC_NAME	=	main.c

UTILS_NAME	=	create_prompt.c		\
				display_prompt.c	\
				init.c				\
				exec.c				\
				del.c				\
				signal.c			\
				exec_bin_path.c		\
				command_history.c

CMD_NAME	=	create_command.c	\
				delete_command.c

LEXER_NAME	=	lexer.c

PROC_NAME	=	clear_processor.c		\
				pwd_processor.c			\
				cd_processor.c			\
				echo_processor.c		\
				env_processor.c			\
				exit_processor.c		\
				setenv_processor.c		\
				unsetenv_processor.c	\
				arbitrary_processor.c

TERM_NAME	=	term_settings.c	\
				term_init.c	\
				term_goto.c

HEADERS		=	minishell.h

LIBFT		=	$(LIBFT_PATH)libft.a

TERMCAP		=	-ltermcap

all: $(TARGET_NAME)

create_lib:
	$(MAKE_LIBFT)

$(TARGET_NAME): create_lib $(GCH) $(OBJ)
	@$(CC) -o $(TARGET_NAME) $(OBJ) $(LIBFT) $(TERMCAP)
	@echo "Linking" [ $(TARGET_NAME) ]

$(OBJ_PATH)%.h.gch: ./includes/%.h
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC)
	@echo "Compiling" [ $< ]

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC)
	@echo "Compiling" [ $< ]

$(OBJ_PATH)%.o: $(TERM_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC)
	@echo "Compiling" [ $< ]

$(OBJ_PATH)%.o: $(LEXER_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC)
	@echo "Compiling" [ $< ]

$(OBJ_PATH)%.o: $(PROC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC)
	@echo "Compiling" [ $< ]

$(OBJ_PATH)%.o: $(CMD_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC)
	@echo "Compiling" [ $< ]

$(OBJ_PATH)%.o: $(UTILS_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC)
	@echo "Compiling" [ $< ]

clean:
	@$(MAKE_LIBFT) clean
	@$(DEL_DIR) $(OBJ_PATH)
	@echo "Cleaning obj [ $(TARGET_NAME) ]..."

fclean:	clean
	@$(MAKE_LIBFT) fclean
	@$(DEL) $(TARGET_NAME)
	@echo "Remove..." [ $(TARGET_NAME) ]

re: fclean all

.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re
