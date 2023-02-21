# philo executable
NAME = philo

#make directories
INC_DIR = include
SRC_DIR = sources
OBJ_DIR = object

SRCS = main.c utilities.c init.c start.c even_philo.c eat_sleep.c threads.c
#will add all object files into a directory one above
# %o: %c same as .c=.o
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC	= gcc
RM	= rm -rf
#-fsanitize=address can be added to cflags for debugging with -g3
CFLAGS = -g -Wall -Werror -Wextra -pthread
# -fsanitize=thread
#to create all of the .o files from files in SRC_DIR in OBJ_DIR
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

all:	$(NAME)

#"-c $< -o $@" is equivalent to "$(OBJ_SRC) -o philo"
# -C changes the path
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\x1b[31mphilo ready\\x1b[0m\n";

# -o turns object files into executable (coming after it)
#adding an @ before a command stops it from being printed

clean:
	$(RM) $(OBJ_DIR)
	@echo "object files removed"
fclean: clean
	$(RM) $(NAME)
	@echo "object files and binary removed"

re:	fclean all
	@echo "object files and binary removed and binary remade"

# to remove all recipes that aren't files to avoid relinking
.PHONY:		all clean fclean re