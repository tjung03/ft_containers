NAME =		ft_containers
TESTER =	rchallie_tester
FT =		my_ft_test
STD =		my_std_test

CPP = 		c++
CPPFLAGS =	-g3 -fsanitize=address -pedantic -std=c++98 -W -Wall -Wextra -Werror

SRCS_T =	main.cpp tester.cpp tester_map.cpp tester_stack.cpp tester_vector.cpp
SRCS_F =	main_ft.cpp
SRCS_S =	main_std.cpp

OBJS_T =	$(SRCS_T:.cpp=.o)
OBJS_F =	$(SRCS_F:.cpp=.o)
OBJS_S =	$(SRCS_S:.cpp=.o)

.PHONY:		all clean fclean re

%.o : %.cpp
			$(CPP) $(CPPFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(TESTER) $(FT) $(STD)

$(TESTER):	$(OBJS_T)
			@echo "\n\033[0;33mCompiling..."
			$(CPP) $(CPPFLAGS) -o $(TESTER) $(OBJS_T)
			@echo "\033[0m"

$(FT):		$(OBJS_F)
			@echo "\n\033[0;33mCompiling..."
			$(CPP) $(CPPFLAGS) -o $(FT) $(OBJS_F)
			@echo "\033[0m"

$(STD):		$(OBJS_S)
			@echo "\n\033[0;33mCompiling..."
			$(CPP) $(CPPFLAGS) -o $(STD) $(OBJS_S)
			@echo "\033[0m"

clean:
			@echo "\n\033[0;31mCleaning..."
			rm -rf $(OBJS_T) $(OBJS_F) $(OBJS_S)
			@echo "\033[0m"

fclean:		clean
			@echo "\033[0;31mRemoving executable..."
			rm -f $(TESTER) $(FT) $(STD)
			@echo "\033[0m"

re: 		fclean all
