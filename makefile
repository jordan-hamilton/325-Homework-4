# Source: http://web.engr.oregonstate.edu/~rookert/cs162/03.mp4

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

EXECS = activity
SRCS = activity.cpp

all: $(EXECS)

activity: activity.cpp
	$(CXX) $(CXXFLAGS) activity.cpp -o activity

clean:
	rm activity
