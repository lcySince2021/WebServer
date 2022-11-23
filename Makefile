CXX ?= gcc
CXXFLAGS= -g -std=c++11 

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CXXFLAGS += -g
else
	CXXFLAGS += -02
endif

server: main.cpp ./source/*.cpp
	$(CXX) -o server $^ $() -L ./source/ `mysql_config --cflags --libs`;

clean:
	rm -r server
