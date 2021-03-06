NAME = ft_ls
CC := gcc

all: $(NAME)

MODULES := src includes
LIBDIRS := libft

LIBS := -Llibft -lft
#LIBS += -L/nfs/2018/c/calamber/42/github/ft_malloc/ -lftmalloc

CFLAGS += -Ilibft/includes -Iincludes -Wall -Werror -Wextra
#CFLAGS += -I/nfs/2018/c/calamber/42/github/ft_malloc/includes/
#CFLAGS += -g -fsanitize=address
MODNAME := module.mk
SRC :=

include $(patsubst %,%/$(MODNAME),$(MODULES))

OBJ :=  $(patsubst %.c,%.o,$(filter %.c,$(SRC)))
DEP :=	$(patsubst %.c,%.d,$(filter %.c,$(SRC)))

-include $(DEP)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@

%.d : %.c
	@./depend.sh $*.o $(CFLAGS) $< > $@
	@printf '\t%s' "$(CC) $(CFLAGS) -c -o $*.o $<" >> $@
	@echo $@ >> all.log

clean:
	make clean -C libft
	rm -f $(OBJ)
	rm -f $(shell cat all.log)
	@rm -f all.log

clean_nolib:
	rm -f $(OBJ)
	rm -f $(shell cat all.log)
	@rm -f all.log

fclean: clean_nolib
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
