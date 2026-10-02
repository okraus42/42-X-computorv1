# Program name
NAME        :=	computor

# Directories
SRC_DIR     :=	src
OBJ_DIR     :=	obj
INCLUDE_DIR :=	include

# Compiler and flags
CC          :=	cc
CFLAGS      :=	-Wall -Wextra -Werror
RM          :=	rm -rf
INCLUDE     :=	-I$(INCLUDE_DIR)

# Sources and objects
SRCS        :=	main.c \
				computor.c \
				parser_get_sign.c parser_get_number.c parser_get_power.c \
				parser.c \
				reducer.c \
				solver_utils.c \
				solver.c \
				utils.c
OBJS        :=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS        :=	$(OBJS:.o=.d)

# Build rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -MMD -MP -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tests: $(NAME)
	./tests/tests.sh

-include $(DEPS)

.PHONY: all clean fclean re tests