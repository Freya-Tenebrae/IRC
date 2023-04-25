# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/04 17:28:09 by mmercore          #+#    #+#              #
#    Updated: 2023/04/25 21:23:37 by cmaginot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# PLACE AT THE TOP OF YOUR MAKEFILE
#---------------------------------
# Progress bar defs
#--------------------------------
#  words = count the number of words
ifneq ($(words $(MAKECMDGOALS)),1) # if no argument was given to make...
.DEFAULT_GOAL = all # set the default goal to all
#  http://www.gnu.org/software/make/manual/make.html
#  $@ = target name
#  %: = last resort recipe
#  --no-print-directory = don't print enter/leave messages for each output grouping
#  MAKEFILE_LIST = has a list of all the parsed Makefiles that can be found *.mk, Makefile, etc
#  -n = dry run, just print the recipes
#  -r = no builtin rules, disables implicit rules
#  -R = no builtin variables, disables implicit variables
#  -f = specify the name of the Makefile
%:                   # define a last resort default rule
	@$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST)) # recursive make call,
else
ifndef ECHO
#  execute a dry run of make, defining echo beforehand, and count all the instances of "COUNTTHIS"
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
	-nrRf $(firstword $(MAKEFILE_LIST)) \
	ECHO="COUNTTHIS" | grep -c "COUNTTHIS")
#  eval = evaluate the text and read the results as makefile commands
N := x
#  Recursively expand C for each instance of ECHO to count more x's
C = $(words $N)$(eval N := x $N)
#  Multipy the count of x's by 100, and divide by the count of "COUNTTHIS"
#  Followed by a percent sign
#  And wrap it all in square brackets
ECHO = echo -ne "\r [`expr $C '*' 100 / $T`%]"
endif
#------------------
# end progress bar
#------------------

NAME			=	ft_irc

# FOLDERS

SRCSFOLDER		=	SRCS/

OBJSFOLDER		=	OBJS/

INCLUDESFOLDER 	= 	INCL/

# SOURCES

SRC				=	main.cpp 	\
					utils.cpp	\
					Server.cpp	\
					User.cpp	\
					Channel.cpp \
					Reply.cpp	\
					cmd/admin.cpp \
					cmd/away.cpp \
					cmd/cap.cpp \
					cmd/connect.cpp \
					cmd/help.cpp \
					cmd/info.cpp \
					cmd/invite.cpp \
					cmd/join.cpp \
					cmd/kick.cpp \
					cmd/kill.cpp \
					cmd/links.cpp \
					cmd/luser.cpp \
					cmd/mode.cpp \
					cmd/modt.cpp \
					cmd/names.cpp \
					cmd/nick.cpp \
					cmd/notice.cpp \
					cmd/oper.cpp \
					cmd/part.cpp \
					cmd/pass.cpp \
					cmd/ping.cpp \
					cmd/pong.cpp \
					cmd/privmsg.cpp \
					cmd/quit.cpp \
					cmd/rehash.cpp \
					cmd/restart.cpp \
					cmd/squit.cpp \
					cmd/stats.cpp \
					cmd/time.cpp \
					cmd/topic.cpp \
					cmd/user.cpp \
					cmd/userhost.cpp \
					cmd/version.cpp \
					cmd/wallops.cpp \
					cmd/who.cpp \
					cmd/whois.cpp \
					cmd/whowas.cpp\
					cmd/close.cpp

BONS			=	BONS/main.cpp

SRCS			=	$(addprefix $(SRCSFOLDER), $(SRC))

INCLUDES		=	ft_irc.hpp Server.hpp User.hpp Reply.hpp Channel.hpp

# COMPILATION AND LINKING

OBJS 			=	${SRC:%.cpp=$(OBJSFOLDER)%.o}

$(OBJSFOLDER)%.o	:	$(SRCSFOLDER)%.cpp
					$(CXX) $(CXXFLAGS) -MD -c $< -o $@ -I $(INCLUDESFOLDER)
					@$(ECHO) $@


RM				=	rm -rf

CXX				=	clang++

CXXFLAGS		=	-Wall -Werror -Wextra -std=c++98

CXXFLAGS		+= -g3 #-pedantic-errors

LFLAGS			=

# FORMAT

# RULES


.PHONY: all
all			:	$(NAME)

				
$(NAME)		:	$(OBJSFOLDER) $(OBJS)
				@echo	"       ============================= Attempting link..."
				$(CXX) $(CXXFLAGS) $(OBJS) -o $@ -I $(INCLUDESFOLDER) $(LFLAGS)
				@$(ECHO) $@
				@echo	"       =============================`tput setaf 2` Linking Success `tput sgr0`=============================="
				@make credits

bonus		:	$(BONS)
				@echo	"       ============================= Compiling bot..."
				@$(ECHO) $@
				$(CXX) $(CXXFLAGS) $(BONS) -o "bot" -I $(INCLUDESFOLDER) $(LFLAGS)


.PHONY: fsanitize
fsanitize	:	$(SRCS)
				@echo	"       ============================= Compiling with fsanitize..."
				$(CXX) $(CXXFLAGS) -o1 -g3 -fsanitize=address $(SRCS) -o $(NAME) -I $(INCLUDESFOLDER) $(LFLAGS)
				@echo	"       =========================`tput setaf 69` Fsanitize Address ready `tput sgr0`========================="


depend		:
				makedepend -- $(CXXFLAGS) -- $(SRC)
				
.PHONY: clean
clean		:
				@echo	"       ============================= Deleting objects..."
		    	${RM} ${OBJS}
				@$(ECHO) $@
				${RM} ${OBJSFOLDER}
				@$(ECHO) $@

.PHONY: fclean
fclean		:
				make clean
				@echo	"       ============================= Deleting executable..."
				$(RM) $(NAME)
				@$(ECHO) $@

.PHONY: re
re			:
				@echo ========== RE ==========
				make fclean
				make all

.PHONY: loop
loop		:
				@echo "`tput setaf 0`Hello World 0`tput sgr0`"
				@echo "`tput setaf 1`Hello World`tput sgr0`"
				@echo "`tput setaf 2`Hello World`tput sgr0`"
				@echo "`tput setaf 3`Hello World`tput sgr0`"
				@echo "`tput setaf 4`Hello World`tput sgr0`"
				@echo "`tput setaf 5`Hello World 5`tput sgr0`"
				@echo "`tput setaf 6`Hello World`tput sgr0`"
				@echo "`tput setaf 7`Hello World`tput sgr0`"
				@echo "`tput setaf 8`Hello World`tput sgr0`"
				@echo "`tput setaf 9`Hello World`tput sgr0`"
				@echo "`tput setaf 10`Hello World 10`tput sgr0`"
				@echo "`tput setaf 11`Hello World`tput sgr0`"
				@echo "`tput setaf 12`Hello World`tput sgr0`"
				@echo "`tput setaf 13`Hello World`tput sgr0`"
				@echo "`tput setaf 14`Hello World`tput sgr0`"
				@echo "`tput setaf 15`Hello World 15`tput sgr0`"
				@echo "`tput setaf 16`Hello World`tput sgr0`"
				@echo "`tput setaf 17`Hello World`tput sgr0`"
				@echo "`tput setaf 18`Hello World`tput sgr0`"
				@echo "`tput setaf 19`Hello World`tput sgr0`"
				@echo "`tput setaf 20`Hello World 20`tput sgr0`"


				@echo "========== We are making =========="
				#sp='/-\|'
				#printf ' '
				#while true; do
			#		printf '\b%.1s' "$sp"
			#		sp=${sp#?}${sp%???}
			#	done

$(OBJSFOLDER)	:
				@echo	"       ============================= `tput setaf 3` Compiling objects...`tput sgr0`"
				mkdir -p $@/cmd

.PHONY:	log
log			:
				@echo	"       ==============================`tput setaf 69` Captain's log `tput sgr0`=============================="
				@cat NOTE/logbook | tr '\n' '\r' | rev | cut -d '@' -f 1 | rev | tr '\r' '\n' | sed "s/mmercore/`tput setaf 69`Mmercore, le beau, le bienheureux`tput sgr0`/" | sed "s/cmaginot/`tput setaf 5`Cmaginot`tput sgr0`/" | sed "s/plam/`tput setaf 9`Plam`tput sgr0`/"

note		:
				@echo "\n\n" >> NOTE/logbook
				@whoami >> NOTE/logbook; echo -n "\t" >> NOTE/logbook; date >> NOTE/logbook
				@cat >> NOTE/logbook

.PHONY:	credits
credits		: 	#$(NAME)
				@echo	"       `tput setaf 69`===========================================================================`tput sgr0`"
				@echo	"  `tput setaf 63` ███████╗████████╗     ██╗██████╗  ██████╗`tput sgr0`             `tput setaf 99`,MMM`tput sgr0``tput setaf 147`8`tput sgr0``tput setaf 135`&&&`tput sgr0``tput setaf 93`.`tput sgr0`"
				@echo	"   `tput setaf 62`██╔════╝╚══██╔══╝     ██║██╔══██╗██╔════╝`tput sgr0`        `tput setaf 5`_...`tput sgr0``tput setaf 99`MMMMM`tput sgr0``tput setaf 147`88`tput sgr0``tput setaf 135`&&&`tput sgr0``tput setaf 92`&`tput sgr0``tput setaf 5`..._`tput sgr0`"
				@echo	"   `tput setaf 61`█████╗     ██║        ██║██████╔╝██║     `tput sgr0`     `tput setaf 13`.::'''`tput sgr0``tput setaf 98`MMMMM`tput sgr0``tput setaf 146`88`tput sgr0``tput setaf 134`&&&&&`tput sgr0``tput setaf 92`&`tput sgr0``tput setaf 5`'''::.`tput sgr0`"
				@echo	"   `tput setaf 60`██╔══╝     ██║        ██║██╔══██╗██║     `tput sgr0`    `tput setaf 13`::`tput sgr0`     `tput setaf 98`MMMMM`tput sgr0``tput setaf 146`88`tput sgr0``tput setaf 133`&&&&&`tput sgr0``tput setaf 91`&`tput sgr0`     `tput setaf 5`::`tput sgr0`"
				@echo	"   `tput setaf 59`██║        ██║███████╗██║██║  ██║╚██████╗`tput sgr0`    `tput setaf 13`'::....`tput sgr0``tput setaf 96`MMMMM`tput sgr0``tput setaf 145`88`tput sgr0``tput setaf 132`&&&&&`tput sgr0``tput setaf 90`&`tput sgr0``tput setaf 5`....::'`tput sgr0`"
				@echo	"   `tput setaf 58`╚═╝        ╚═╝╚══════╝╚═╝╚═╝  ╚═╝ ╚═════╝`tput sgr0`      `tput setaf 13`\`''''`tput sgr0``tput setaf 95`MMMMM`tput sgr0``tput setaf 144`88`tput sgr0``tput setaf 131`&&&`tput sgr0``tput setaf 89`&`tput sgr0``tput setaf 13`''''\``tput sgr0`"
				@echo	"       `tput setaf 58`=================================================`tput sgr0``tput setaf 94`'MMM`tput sgr0``tput setaf 144`8`tput sgr0``tput setaf 130`&&`tput sgr0``tput setaf 88`&'`tput sgr0``tput setaf 58`==`tput sgr0``tput setaf 59`==`tput sgr0``tput setaf 60`==`tput sgr0``tput setaf 61`===`tput sgr0``tput setaf 62`====`tput sgr0``tput setaf 63`====`tput sgr0`"
				@echo	" 					`tput setaf 226`– CMAGINOT, MMERCORE, PLAM.`tput sgr0`"

-include $(OBJS:.o=.d)

endif
