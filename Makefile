NAME =		ft_containers
FT =		ft_test
STD =		std_test
TESTER =	rchallie_tester

CPP = 		c++
#CPPFLAGS =	-fsanitize=address -pedantic -std=c++98 -W -Wall -Wextra -Werror
CPPFLAGS =	-fsanitize=address -Wall -Wextra -Werror

SRCS_F =	main_ft.cpp
SRCS_S =	main_std.cpp
SRCS_T =	main_tester.cpp tester.cpp tester_map.cpp tester_stack.cpp tester_vector.cpp

OBJS_F =	$(SRCS_F:.cpp=.o)
OBJS_S =	$(SRCS_S:.cpp=.o)
OBJS_T =	$(SRCS_T:.cpp=.o)

.PHONY:		all clean fclean re tester ft std

%.o : %.cpp
			$(CPP) $(CPPFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(FT) $(STD)

$(FT):		$(OBJS_F)
			@echo "\n\033[0;33mCompiling..."
			$(CPP) $(CPPFLAGS) -o $(FT) $(OBJS_F)
			@echo "\033[0m"

$(STD):		$(OBJS_S)
			@echo "\n\033[0;33mCompiling..."
			$(CPP) $(CPPFLAGS) -o $(STD) $(OBJS_S)
			@echo "\033[0m"

$(TESTER):	$(OBJS_T)
			@echo "\n\033[0;33mCompiling..."
			$(CPP) $(CPPFLAGS) -o $(TESTER) $(OBJS_T)
			@echo "\033[0m"

clean:
			@echo "\n\033[0;31mCleaning..."
			rm -rf $(OBJS_F) $(OBJS_S) $(OBJS_T)
			@echo "\033[0m"

fclean:		clean
			@echo "\033[0;31mRemoving executable..."
			rm -f $(FT) $(STD) $(TESTER)
			@echo "\033[0m"

re: 		fclean all

tester:		$(TESTER)
ft:			$(FT)
std:		$(STD)
