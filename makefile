.PHONY : clean

CC = g++
CPPFLAGS = -fPIC -g
LDFLAGS = -shared
COMPPATH = -L./
LDPATH = -Wl,-rpath=./ 
HEADERS = $(shell echo *.h)
TARGET = Executable_file
RM = rm -rf
CFLAG = -c
OFLAF = -o

$(TARGET): libzpool.so main.o
	$(CC) $(COMPPATH)  $(LDPATH)  $(OFLAF) $(TARGET) main.o -lzpool
	
libzpool.so: zpool.o
	$(CC) $(LDFLAGS) $(OFLAF) libzpool.so zpool.o
zpool.o: zpool.cpp $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAG) zpool.cpp

main.o: main.cpp $(HEADERS)
	$(CC) $(CFLAG) main.cpp

clean:
	$(RM) *.o *.so $(TARGET)
	
