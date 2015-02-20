CFLAGS=-std=c++11 -g
SOURCES=TaroJiroDividing.cpp
EXES=$(SOURCES:.cpp=)

all: $(SOURCES) $(EXES)

$(EXES): $(SOURCES)
	g++ $(CFLAGS) $(SOURCES) -o $@
	./$@
