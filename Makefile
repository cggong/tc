CFLAGS=-std=c++11 -g
SOURCES=TopView.cpp
EXES=$(SOURCES:.cpp=)

all: $(SOURCES) $(EXES)

$(EXES): $(SOURCES)
	g++ $(CFLAGS) $(SOURCES) -o $@
