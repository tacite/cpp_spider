##
## Makefile for Makefile
##
## Made by Florent Beaurain
## Login   <beauraF@epitech.net>
##
## Started on  Sat Jul 25 17:11:05 2015 Florent Beaurain
## Last update Sat Oct 31 18:37:50 2015 Florent BEAURAIN
##

include			source.mk

NAME_SERVER		=	bin_server

OBJS_SERVER		=	$(SRC_SERVER:.cpp=.o)

CXX			?=	g++

DEBUG			?=	no

CXXFLAGS		+=	-Iclient/inc -Iserver/inc -std=c++11

ifeq ($(CXX), clang++)
CXXFLAGS		+=	-Weverything -Wno-padded
else
CXXFLAGS		+=	-W -Wall -Wextra
endif

ifeq ($(DEBUG), yes)
CXXFLAGS		+=	-g
endif

all:			$(NAME_SERVER)

$(NAME_SERVER):		$(OBJS_SERVER)
			$(CXX) -o $(NAME_SERVER) $(OBJS_SERVER)

clean:
			@rm -vf $(OBJS_SERVER)

fclean:			clean
			@rm -vf $(NAME_SERVER)

re:			fclean all

.PHONY:			clean fclean re
