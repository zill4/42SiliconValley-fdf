# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/14 12:24:10 by jcrisp            #+#    #+#              #
#    Updated: 2019/01/14 12:38:45 by jcrisp           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

#	src / obj files
SRC	= main.c err.c hookers.c parse.c rendo.c
OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

LIBFT	= ./libft/libft.a
LIBINC	= -I./libft
LIBLINK	= -L./libft -lft

MLX		= ./minilibx/libmlx.a
MLXINC	= -I./minilibx
MLXLINK	= -L./minilibx -lmlx -framework OpenGL -framework AppKit

LIBGFX		= ./libgfx/libgfx.a
LIBGFXINC	= -I./libgfx
LIBGFXLINK	= -L./libgfx -lgfx

SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: obj libft mlx libgfx $(NAME)

gfx:
	rm -rf $(NAME)
	rm -rf $(OBJDIR)
	make -C ./libgfx fclean
	make

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(LIBINC) $(MLXINC) $(LIBGFXINC) -I $(INCDIR) -o $@ -c $<

libft: $(LIBFT)

mlx: $(MLX)

libgfx: $(LIBGFX)

$(LIBFT):
	make -C ./libft

$(MLX):
	make -C ./minilibx

$(LIBGFX):
	make -C ./libgfx

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(MLXLINK) $(LIBGFXLINK) $(LIBLINK)

clean:
	rm -rf $(OBJDIR)
	make -C ./libft clean
	make -C ./minilibx clean
	make -C ./libgfx clean

fclean: clean
	rm -rf $(NAME)
	make -C ./libft fclean
	make -C ./libgfx fclean

re: fclean all

