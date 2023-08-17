CXX ?= gcc
# CXXFLAGS= -g -std=c++11 

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CXXFLAGS += -g
else
	CXXFLAGS += -02
endif

server: main.cpp ./source/*.cpp
	$(CXX) -o server $^ $() -L ./source/ -L ./thirdparty/libhv/lib/ -L ./thirdparty/workflow/lib/ -I ./thirdparty/ -lworkflow -lhv `mysql_config --cflags --libs` -g -std=c++14;

clean:
	rm -r server
