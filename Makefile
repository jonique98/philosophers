NAME		= philo

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
AR			= ar rcs
RM			= rm -f

INCS_DIR	= ./
SRCS_DIR	= ./

SRC			= test.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SRC))
OBJS		=	$(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -I $(INCS_DIR)

all : $(NAME)

.c.o :
	$(CC) $(CFLAGS) -I $(INCS_DIR) -o $@ -c $?

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : clean all

PHONY	: all clean fclean re bonus