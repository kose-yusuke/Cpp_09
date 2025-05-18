NAME     = RPN
CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 
SRCS     = main.cpp RPN.cpp
OBJS     = $(SRCS:.cpp=.o)
INCLUDES	= -I .
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: $(NAME)
	@echo "== Running Tests  =="
	@echo "--- Basic Test ---"
	./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	./$(NAME) "7 7 * 7 -"
	./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
	./$(NAME) "(1 + 1)" || true
	@echo "\n--- Error Case Test ---"
	./$(NAME) "1 2 + -" || true
	./$(NAME) "42 + 1" || true
	./$(NAME) "7 % 4" || true
	./$(NAME) "4 9 + 0 /" || true
	@echo "\n--- Additional Test ---"
	./$(NAME) "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *"
	./$(NAME) "1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 /"
	./$(NAME) "2 1 + 3 *"
	./$(NAME) "4 7 5 / +"
	./$(NAME) "9 6 9 3 + 1 * / * 7 + 5 +"
	./$(NAME) "1 2 /"
	./$(NAME) "1 2 / 2 *"
	./$(NAME) "1e308 1e308 +" || true
	@echo ""
	@echo "== Tests Completed =="

.PHONY: all clean fclean re run