
CPP			= g++
INC_DIR		= ../include
LIB_DIR		= ../lib

INCFLAGS	= -I $(INC_DIR)

LDFLAGS    += -L$(LIB_DIR)
LDFLAGS    +=  -llog4c -lrt

CPPFLAGS    = -g -pipe

APP_NAME    = test

all:
	$(CPP) $(CPPFLAGS)  *.cpp -o $(APP_NAME)  $(INCFLAGS) $(LDFLAGS)

clean:
	rm -f  $(APP_NAME)
