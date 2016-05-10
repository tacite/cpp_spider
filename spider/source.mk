##
## source.mk for source.mk
##
## Made by Florent Beaurain
## Login   <beauraF@epitech.net>
##
## Started on  Sat Jul 25 17:11:32 2015 Florent Beaurain
## Last update Wed Oct 28 17:34:12 2015 Florent BEAURAIN
##

DIR_SERVER		=	server/src/
DIR_CLIENT		=	client/src/

SRC_SERVER		+=	$(DIR_SERVER)main.cpp
SRC_SERVER		+=	$(DIR_SERVER)Client.cpp
SRC_SERVER		+=	$(DIR_SERVER)Server.cpp
SRC_SERVER		+=	$(DIR_SERVER)USocket.cpp
SRC_SERVER		+=	$(DIR_SERVER)Protocole.cpp
SRC_SERVER		+=	$(DIR_SERVER)Input.cpp
SRC_SERVER		+=	$(DIR_SERVER)FileLog.cpp
