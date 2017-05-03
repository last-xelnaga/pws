PREFIX =

-include Makefile.prefix

OBJDIR = obj
TARGET = pws

CC = $(PREFIX)g++

CFLAGS = -Wall -Wextra -O2 -fno-omit-frame-pointer
#CFLAGS	= -Wall -Wextra -O0 -g -ggdb

INC = -I. -IwiringPi/wiringPi
LIB = -lpthread -LwiringPi/wiringPi -lwiringPi

SRC	= \
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

$(OBJDIR)/main.o: Makefile

# valgrind --leak-check=full --show-leak-kinds=all ./shp_client
