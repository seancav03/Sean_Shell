SRCDIR = src
OBJSDIR = build
INCLUDESDIR = include
TESTDIR = tests

SOURCES = process.cpp main.cpp parser.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = shelllab

CXX = g++
CXXFLAGS = -Wall -g -I$(INCLUDESDIR)

all: directories shelllab

directories:
	mkdir -p $(OBJSDIR)

# Create the program binary
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o shelllab \
			$(OBJSDIR)/*.o

# Compile rules for each dependecy
main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c -o $(OBJSDIR)/main.o $(SRCDIR)/main.cpp

process.o: $(SRCDIR)/process.cpp $(SRCDIR)/process.cpp
	$(CXX) $(CXXFLAGS) -c -o $(OBJSDIR)/process.o $(SRCDIR)/process.cpp

parser.o: $(SRCDIR)/parser.cpp $(SRCDIR)/parser.cpp
	$(CXX) $(CXXFLAGS) -c -o $(OBJSDIR)/parser.o $(SRCDIR)/parser.cpp

# Make the test_runner
test: $(TESTDIR)/test_process.cpp
	$(CXX) $(CXXFLAGS) -Isrc/ -o unittests $(TESTDIR)/test_*.cpp

# Rule to clean up intermediate file and executable
clean:
	rm -rf $(OBJSDIR)
	rm -f shelllab unittests *.o