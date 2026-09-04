CC      = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++98

# ─── Edit these two variables for each exercise ───────────────────────────────
NAME    = program          # Final binary name
SRCS    = main.cpp         # Add more .cpp files here as needed
# ─────────────────────────────────────────────────────────────────────────────

OBJS    = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
