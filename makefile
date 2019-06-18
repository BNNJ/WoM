CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

NAME		=	wom

SRC_DIR		=	./src

SRC			=	$(addprefix $(SRC_DIR)/,$(SRCS))

SRCS		=	wom.c		\
				tools.c

OBJ_DIR		=	./obj

OBJ			=	$(addprefix $(OBJ_DIR)/,$(OBJS))
OBJS		=	$(SRCS:.c=.o)

INC_DIR		=	./include
INC			=	$(INC_DIR)/wom.h

INC_FLAGS	=	-I$(INC_DIR)
LINK_FLAGS	=	-lncurses

all:			$(NAME)

$(NAME):		$(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LINK_FLAGS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)

clean:
	@rm -rf $(OBJ_DIR)

fclean:
	@$(MAKE) clean
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
