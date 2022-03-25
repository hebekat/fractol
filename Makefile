CFLAGS := -Wall -Werror -Wextra
NAME = fractol
C_SOURCES := 	main.c\
				equations.c\
				math.c\
				controls.c\
				utils.c\

all:$(NAME) 


$(NAME): $(OBJ)
	$(CC) $(C_SOURCES)  -L. -lmlx -framework OpenGL -framework AppKit  -Ofast -o $(NAME)

%.o: %.c
	$(CC)  -Imlx -c $< -o $@

bonus:
	$(MAKE) WITH_BONUS=1 all

clean:
	rm -f $(C_SOURCES:.c=.o) $(BONUS_FILES:.c=.o)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: re  
	./fractol

.PHONY := all clean fclean bonus re