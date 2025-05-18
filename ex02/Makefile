NAME     = PmergeMe
CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 
SRCS     = main.cpp PmergeMe.cpp
OBJS     = $(SRCS:.cpp=.o)
INCLUDES	= -I .
OS       := $(shell uname -s)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: 
ifeq ($(OS), Linux)
	@echo "\n--- Linux Unique 3000 Test ---"
	./$(NAME) `shuf -i 1-3000`
else ifeq ($(OS), Darwin)
	@echo "\n--- macOS Unique 3000 Test ---"
	./$(NAME) `seq 1 3000 | gshuf | tr '\n' ' '`
endif

test:
	./$(NAME) 43 12 87 5 30 71 18 60 25 8 36 99 2 14 54 22 65 39 77 10 33

test2:
	./$(NAME) 43 12 87 5 30 71 18 60 25 8 36 99 2 14 54 22 65 39 77 10 33 1 3

.PHONY: all clean fclean re run test