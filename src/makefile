#SRC=main.cpp Carte.cpp
SRCBASE=$(wildcard *.cpp)  

SRC= $(SRCBASE) main.cxx
SRCTEST = $(SRCBASE) main_test_agent_memoire.cxx tests_catch.cxx

EXE=prog
EXETEST=test

CXXFLAGS+=-Wall -Wextra -MMD -g -O2 -fdiagnostics-color=auto
LDFLAGS= #-lSDL

TMP = $(SRC:.cpp=.o)
TMP2 = $(TMP:.cxx=.o) 

OBJ=$(addprefix build/, $(TMP2) ) 
DEP=$(addprefix build/, $(TMP2:.o=.d))

TMP3 = $(SRCTEST:.cpp=.o)
TMP4 = $(TMP3:.cxx=.o)

OBJTEST=$(addprefix build/,$(TMP4:.cpp=.o))
DEPTEST=$(addprefix build/,$(TMP4:.o=.d))


all: $(OBJ)

	$(CXX) -o $(EXE) $^ $(LDFLAGS)

test : $(OBJTEST)
	$(CXX) -o $(EXETEST) $^ $(LDFLAGS)
	./$(EXETEST)



build/%.o: %.cpp
	echo $(OBJ)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ -c $<

build/%.o: %.cxx
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf build core *.gch
	rm */$(EXE)

-include $(DEPCXX)
-include $(DEPCPP)
