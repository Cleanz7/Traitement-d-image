#Tools
CC = gcc
RM = rm
DOXYGEN = doxygen
#Macros for directories
SRC_DIR = ./src
BIN_DIR = ./bin
INC_DIR = ./include
DOC_DIR = ./doc
LIB_DIR = ./lib
#Compilation flags
CFLAGS = -Wall -Wextra -O2 -g
CPPFLAGS = -I$(INC_DIR)
LDFLAGS = -L $(LIB_DIR) -limage64

.PHONY: testimage clean distclean doc docclean

include $(SRC_DIR)/Makefile

clean:
	-@$(RM) $(SRC_DIR)/*.o

distclean: clean docclean
	-@$(RM) $(BIN_DIR)

doc:
	$(DOXYGEN) Doxyfile

doclean:
	$(RM) -r $(DOC_DIR)/testimage
