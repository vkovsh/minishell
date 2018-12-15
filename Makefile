TARGET_NAME	=	minishell

CC			=	gcc
CC_FLAGS	=	-Wall -Werror -Wextra -fPIC
DEL_DIR		=	rm -rf
DEL			=	rm -f
MAKE_LIBFT	=	make -C $(LIBFT_PATH)

INC_PATH	=	./includes/ $(LIBFT_PATH)includes/
OBJ_PATH	=	./obj/
SRC_PATH	=	./srcs/
LIBFT_PATH	=	./libft/

OBJ			=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC			=	$(addprefix -I, $(INC_PATH))

OBJ_NAME	=	$(SRC_NAME:.c=.o)

SRC_NAME	=	main.c

all: $(TARGET_NAME)

$(TARGET_NAME): $(OBJ)
	@$(MAKE_LIBFT) so
	@$(CC) -o $(TARGET_NAME) $(OBJ) $(LIBFT_PATH)libft.so
	@echo "Compiling" [ $(TARGET_NAME) ]

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC)
	@echo "Linking" [ $< ]

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
