# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 11:53:56 by mgiovana          #+#    #+#              #
#    Updated: 2023/03/02 12:02:17 by mgiovana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS                    =       get_next_line.c get_next_line_utils.c

OBJS                    = $(SRCS:.c=.o)

BONUS                   =       get_next_line_bonus.c get_next_line_utils_bonus.c

BONUS_OBJS		= $(BONUS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS                  = -Wall -Wextra -Werror

NAME                    = GNL.a

all:                    $(NAME)

$(NAME):                $(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
			$(RM) $(NAME)

re:			fclean all

bonus:			$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
				
.SILENT:
