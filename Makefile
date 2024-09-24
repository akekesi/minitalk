BIN = bin
INC = include
OBJ = obj
SRC = src

TARGET_SERVER = $(BIN)/server
TARGET_CLIENT = $(BIN)/client
TARGET_SERVER_BONUS = $(BIN)/server_bonus
TARGET_CLIENT_BONUS = $(BIN)/client_bonus

CC = cc
CCFLAG = -Wall -Wextra -Werror -I$(INC)

RM = rm -rf

DEPS = $(INC)/minitalk.h

SRCS_COMMON = $(SRC)/ft_atoi.c \
	$(SRC)/ft_is.c \
	$(SRC)/ft_itoa.c \
	$(SRC)/ft_putstr.c \

SRCS_S = $(SRC)/server.c $(SRCS_COMMON)
SRCS_C = $(SRC)/client.c $(SRCS_COMMON)

OBJS_S = $(SRCS_S:$(SRC)/%.c=$(OBJ)/%.o)
OBJS_C = $(SRCS_C:$(SRC)/%.c=$(OBJ)/%.o)

$(OBJ)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) $(CCFLAG) -c $< -o $@

all: $(TARGET_SERVER) $(TARGET_CLIENT)

$(TARGET_SERVER): $(OBJS_S)
	$(CC) -o $@ $^

$(TARGET_CLIENT): $(OBJS_C)
	$(CC) -o $@ $^

bonus: $(TARGET_SERVER_BONUS) $(TARGET_CLIENT_BONUS)

$(TARGET_SERVER_BONUS): $(OBJS_S)
	$(CC) -o $@ $^

$(TARGET_CLIENT_BONUS): $(OBJS_C)
	$(CC) -o $@ $^

clean:
	$(RM) $(OBJS_S)
	$(RM) $(OBJS_C)

fclean: clean
	$(RM) $(TARGET_SERVER)
	$(RM) $(TARGET_CLIENT)
	$(RM) $(TARGET_SERVER_BONUS)
	$(RM) $(TARGET_CLIENT_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
