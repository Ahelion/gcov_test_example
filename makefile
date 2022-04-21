# path macros
BIN_PATH := Bin
OBJ_PATH := Temp
DBG_PATH := Debug

#target name
TARGET=target.exe

# tool macros
#tests we run under linux or cigwin, for github action
ifdef TEST
CC = gcc
GCOV =gcov
else
CC = D:/tools/gcc-8.2.0/bin/gcc.exe
GCOV =D:/tools/gcc-8.2.0/bin/gcov.exe
endif

CCFLAGS := -o1 -g
TESTFLAGS := -g --coverage

#check if we run tests
ifdef TEST
CCFLAGS := $(CCFLAGS) \
           $(TESTFLAGS)
endif

CCOBJFLAGS := $(CCFLAGS)

#main interest
SRC_ALGO=Sources/src/algo.c

#check if we run tests
ifdef TEST
MAIN=tests
TEST_TARGETS= runTests getCoverage
else
MAIN=src
endif

SRC=Sources/$(MAIN)/main.c

#create list of all sources
SRC := $(SRC) $(SRC_ALGO) 

#create objects name
OBJS := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

#all directories
DIRS := $(dir $(SRC))

#build includes
INCS := $(addprefix -I./, $(DIRS))

#set directories for make to search
vpath %.c $(DIRS)

all:$(BIN_PATH)/$(TARGET) $(TEST_TARGETS)

.PHONY: clean createFolders $(TEST_TARGETS)
 

$(BIN_PATH)/$(TARGET): createFolders $(OBJS)
	@echo ++Linking $@
	@$(CC) $(CCOBJFLAGS) $(OBJS) -o $(BIN_PATH)/$(TARGET)

$(OBJ_PATH)/%.o:%.c
	@echo ++Compiling $< to $@
	@$(CC) $(INCS) $(CCOBJFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_PATH)/*
	rm -f $(BIN_PATH)/*
	rm -f *.gcov

createFolders:
	@echo ++Creating folder $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)
	@echo ++Creating folder $(BIN_PATH)
	@mkdir -p $(BIN_PATH)
    
runTests:
	@echo ++Running tests: $(BIN_PATH)/$(TARGET)
	@$(BIN_PATH)/$(TARGET)

getCoverage:
	@echo ++Ghatering coverage for: $(BIN_PATH)/$(TARGET)
	@$(GCOV) -b --object-directory $(OBJ_PATH) $(SRC_ALGO)