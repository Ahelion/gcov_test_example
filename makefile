# path macros
BIN_PATH := Bin
OBJ_PATH := Temp
DBG_PATH := Debug

# tool macros
CC = gcc
GCOV = gcov
CCFLAGS := 
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
SRC=Sources/tests/main.c
else
SRC=Sources/src/main.c
endif

SRC := $(SRC) $(SRC_ALGO) 

OBJS := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

DIRS := $(dir $(SRC))

#build includes
INCS := $(addprefix -I./, $(DIRS))

#set directories for make to search
vpath %.c $(DIRS)

#check if we run tests
ifdef TEST
.PHONY: clean createFolders runTests getCoverage
all:$(BIN_PATH)/target.exe runTests getCoverage
else
.PHONY: clean createFolders
all:$(BIN_PATH)/target.exe
endif


 

$(BIN_PATH)/target.exe: createFolders $(OBJS)
	@echo ++Linking $@
	@$(CC) $(CCOBJFLAGS) $(OBJS) -o $(BIN_PATH)/target.exe

$(OBJ_PATH)/%.o:%.c
	@echo ++Compiling $< to $@
	@$(CC) -c $(INCS) $(CCOBJFLAGS) $< -o $@

clean:
	rm -f $(OBJ_PATH)/*
	rm -f $(BIN_PATH)/*

createFolders:
	@echo Creating folder $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)
	@echo Creating folder $(BIN_PATH)
	@mkdir -p $(BIN_PATH)
    
runTests:
	@echo Running tests: $(BIN_PATH)/target.exe
	@$(BIN_PATH)/target.exe

getCoverage:
	@echo Ghatering coverage for: $(BIN_PATH)/target.exe
	@$(GCOV) -b -j --object-directory $(OBJ_PATH) $(SRC_ALGO)