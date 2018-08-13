PROJECT = phash
SOURCEDIR = ./src
CC = g++
CFLAGS = -std=c++11 -c -O2 -fpic -Wall -Wextra -I $(SOURCEDIR)
LINKS = -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect -lopencv_imgcodecs

SOURCES = $(shell find "$(SOURCEDIR)" -name "*.cpp" -o -name "*.c" -o -name "*.s")
OBJECTS = $(patsubst %.s, %.o, $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(SOURCES))))

all: $(PROJECT).so

$(PROJECT).so : $(OBJECTS)
	$(CC) -o $(PROJECT).so $(OBJECTS) -shared -lphpcpp $(LINKS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	find src -name "*.o"  | xargs rm -f
	rm -f $(PROJECT).so
	
#Makefile By Aodzip