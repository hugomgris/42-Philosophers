# -=-=-=-=-    COLOURS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

DEF_COLOR   = \033[0;39m
YELLOW      = \033[0;93m
CYAN        = \033[0;96m
GREEN       = \033[0;92m
BLUE        = \033[0;94m
RED         = \033[0;91m

# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME        := philo

# -=-=-=-=-    FLAG -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC          = cc
FLAGS       = -Werror -Wall -Wextra -g #-fsanitize=address
DFLAGS      = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

RM          = rm -fr

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC         := main.c			\
				utils.c			\
				parser.c		\
				initializer.c	\
				exiter.c		\
				threader.c		\
				timer.c			\
				printer.c		\
				simulator.c		\
				observer.c

SRCDIR      = src
SRCS        = $(addprefix $(SRCDIR)/, $(SRC))

OBJDIR      = .obj
OBJS        = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

DEPDIR      = .dep
DEPS        = $(addprefix $(DEPDIR)/, $(SRC:.c=.d))

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: dirs $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile includes/philo.h
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	$(CC) $(FLAGS) $(DFLAGS) -c $< -o $@
	@echo "$(CYAN)Object file created: $@ $(DEF_COLOR)"

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)!$(DEF_COLOR)"
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"
	@echo "$(RED)Death is not defeat.$(DEF_COLOR)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "$(BLUE)Created directory: $(OBJDIR) $(DEF_COLOR)"

$(DEPDIR):
	@mkdir -p $(DEPDIR)
	@echo "$(BLUE)Created directory: $(DEPDIR) $(DEF_COLOR)"

dirs: $(OBJDIR) $(DEPDIR)

clean:
	@$(RM) $(OBJDIR) $(DEPDIR)
	@echo "$(RED)Cleaned object files and dependencies$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Cleaned all binaries$(DEF_COLOR)"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re