
CXX			= g++
INC_DIR		= ../include
LIB_DIR		= ../lib

INCFLAGS	= -I $(INC_DIR)
LDFLAGS		= -L $(LIB_DIR)
LDFLAGS    += -lcjson -lcjson_utils

CPPFLAGS    = -g

APP_NAME    = test

all:
	$(CXX) $(CPPFLAGS)  *.cpp -o $(APP_NAME)  $(INCFLAGS) $(LDFLAGS)

clean: rm -rf $(APP_NAME)

