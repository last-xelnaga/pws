PREFIX =

-include Makefile.prefix

OBJDIR = obj
TARGET = pws

CC = $(PREFIX)g++

CFLAGS = -Wall -Wextra -O2 -std=c++11 -fno-omit-frame-pointer
#CFLAGS	= -Wall -Wextra -O0 -g -ggdb -std=c++11

#INC = -I. -IwiringPi/wiringPi
#LIB = -LwiringPi/wiringPi -lwiringPi -lrt -lpthread

SRC	= \
    main.cpp \

    #board_setup.cpp \
    sensor_dht.cpp \
    settings.cpp

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

$(OBJDIR)/board_setup.o: Makefile board_setup.hpp settings.hpp
$(OBJDIR)/main.o: Makefile board_setup.hpp settings.hpp sensor_dht.hpp
$(OBJDIR)/sensor_dht.o: Makefile sensor_dht.hpp
$(OBJDIR)/settings.o: Makefile settings.hpp

# valgrind --leak-check=full --show-leak-kinds=all ./pws
