SRCS =  src/main.c \
		src/actions/actions.c \
		src/init/init.c \
		src/routine/routine.c \
		src/routine/routine2.c


OBJS = $(SRCS:.c=.o)

NAME = philo
LIBFT		= libft.a
LIBFT_DIR := ./libft
LIBFT_LIB := $(LIBFT_DIR)/libft.a
INCLUDE = -Iinc -pthread
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_LIB) $(INCLUDE) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

debug: $(OBJS) $(LIBFT_LIB)
	$(CC) $(FLAGS) -g $(SRCS) $(LIBFT_LIB) $(INCLUDE) -o $(NAME)

sanitize: $(OBJS) $(LIBFT_LIB)
	$(CC) $(FLAGS) -g -fsanitize=thread  $(SRCS) $(LIBFT_LIB) $(INCLUDE) -o $(NAME)


$(LIBFT_LIB):
	cd $(LIBFT_DIR) && $(MAKE)

clean:
	cd $(LIBFT_DIR) && $(MAKE) clean
	$(RM) $(OBJS)

fclean: clean
	cd $(LIBFT_DIR) && $(MAKE) fclean
	$(RM) $(NAME)

re: fclean all
