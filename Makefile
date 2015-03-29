CFLAGS=-std=c++11 -g
SOURCES=dnasort.cpp
EXES=$(SOURCES:.cpp=)

all: $(SOURCES) $(EXES)

$(EXES): $(SOURCES)
	g++ $(CFLAGS) -O0 $(SOURCES) -o $@
	./$@
