NAME				=	server
SRCS				=	mandatory/server.c
OBJS				=	$(SRCS:.c=.o)

CLIENT_NAME 		=	client
CLIENT_SRCS			=	mandatory/client.c
CLIENT_OBJS			=	$(CLIENT_SRCS:.c=.o)

NAME_BONUS			=	server_bonus
SRCS_BONUS			=	bonus/server_bonus.c
OBJS_BONUS			=	$(SRCS_BONUS:.c=.o)

CLIENT_NAME_BONUS 	=	client_bonus
CLIENT_SRCS_BONUS 	=	bonus/client_bonus.c
CLIENT_OBJS_BONUS 	=	$(CLIENT_SRCS_BONUS:.c=.o)

HEADR				=	mandatory/minitalk.h
HD_BONUS			=	bonus/minitalk_bonus.h

MYLB				=	MYLIB
MYHD				=	MYLIB/mylib.h

FLGS				=	cc -Wall -Wextra -Werror
RM					=	rm -f

all: $(MYLB) $(NAME) $(CLIENT_NAME)

bonus: $(MYLB) $(NAME_BONUS) $(CLIENT_NAME_BONUS)

$(MYLB):
	@make -C MYLIB --no-print-directory

$(NAME): $(OBJS)
	@$(FLGS) $^ -L $(MYLB) -l ar -o $(NAME)

$(CLIENT_NAME): $(CLIENT_OBJS)
	@$(FLGS) $^ -L $(MYLB) -l ar -o $(CLIENT_NAME) 

$(OBJS): %.o: %.c $(MYHD) $(HEADR)
	@$(FLGS) -c $< -I $(MYLB) -o $@

$(CLIENT_OBJS): %.o: %.c $(MYHD) $(HEADR)
	@$(FLGS) -c $< -I $(MYLB) -o $@

$(NAME_BONUS): $(OBJS_BONUS)
	@$(FLGS) $^ -L $(MYLB) -l ar -o $(NAME_BONUS)

$(CLIENT_NAME_BONUS): $(CLIENT_OBJS_BONUS)
	@$(FLGS) $^ -L $(MYLB) -l ar -o $(CLIENT_NAME_BONUS) 

$(OBJS_BONUS): %.o: %.c $(MYHD) $(HD_BONUS)
	@$(FLGS) -c $< -I $(MYLB) -o $@

$(CLIENT_OBJS_BONUS): %.o: %.c $(MYHD) $(HD_BONUS)
	@$(FLGS) -c $< -I $(MYLB) -o $@

clean:
	$(RM) $(OBJS) $(CLIENT_OBJS) $(OBJS_BONUS) $(CLIENT_OBJS_BONUS)
	@make clean -C MYLIB --no-print-directory

fclean: clean
	$(RM) $(NAME) $(CLIENT_NAME) $(NAME_BONUS) $(CLIENT_NAME_BONUS)
	@make fclean -C MYLIB --no-print-directory

re: fclean all

.PHONY: $(MYLB)
