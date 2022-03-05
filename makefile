# tool macros
CC = gcc
CCFLAGS := --coverage
DBGFLAGS := -g
CCOBJFLAGS := $(CCFLAGS) -c

# path macros
BIN_PATH := Bin
OBJ_PATH := Temp
DBG_PATH := Debug

SRC=Sources/src/main.c \
    Sources/src/algo.c

OBJS := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

DIRS := $(dir $(SRC))
#set directories for make to search

vpath %.c $(DIRS)

all:$(BIN_PATH)/target.exe
 

$(BIN_PATH)/target.exe: createFolders $(OBJS)
	$(CC) $(OBJS) -o $(BIN_PATH)/target.exe

$(OBJ_PATH)/%.o:%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean createFolders
clean:
	rm -f $(OBJ_PATH)/*
	rm -f $(BIN_PATH)/*

createFolders:
	@echo Creating folder $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)
	@echo Creating folder $(BIN_PATH)
	@mkdir -p $(BIN_PATH)   