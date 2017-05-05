PREFIX =

-include Makefile.prefix

OBJDIR = obj
TARGET = pws

CC = $(PREFIX)g++

CFLAGS = -Wall -Wextra -O2 -fno-omit-frame-pointer
#CFLAGS	= -Wall -Wextra -O0 -g -ggdb

INC = -I. -IwiringPi/wiringPi
LIB = -LwiringPi/wiringPi -lwiringPi -lrt -lpthread

SRC	= \
    board_setup.cpp \
    main.cpp

OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY: all clean

all: $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJDIR) $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIB)

clean:
	rm -rf $(OBJDIR) $(TARGET)

$(OBJDIR)/board_setup.o: board_setup.hpp Makefile
$(OBJDIR)/main.o: Makefile

# valgrind --leak-check=full --show-leak-kinds=all ./pws
