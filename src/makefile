#SRC=main.cpp Carte.cpp
SRCBASE=$(wildcard *.cpp)  

SRC= $(SRCBASE) main.cxx
SRCTEST = $(SRCBASE) main_test_agent_memoire.cxx tests_catch.cxx

EXE=prog
EXETEST=test

DOSSIER=build

SFMLINCLUDE=-I /home/mathvdt/sma/src/include
# CXXFLAGS+=-Wall -Wextra -MMD -g -O2 -fdiagnostics-color=auto $(SFMLINCLUDE)
CXXFLAGS+= -MMD -g -fdiagnostics-color=auto $(SFMLINCLUDE)

SFMLLIB=-L /home/mathvdt/sma/src/lib
LDSFML=$(SFMLLIB) -lsfml-graphics  $(SFMLLIB) -lsfml-window $(SFMLLIB) -lsfml-system
LDFLAGS=   $(LDSFML)
#-lSDL 


TMP = $(SRC:.cpp=.o)
TMP2 = $(TMP:.cxx=.o) 

OBJ=$(addprefix $(DOSSIER)/, $(TMP2) ) 
DEP=$(addprefix $(DOSSIER)/, $(TMP2:.o=.d))

TMP3 = $(SRCTEST:.cpp=.o)
TMP4 = $(TMP3:.cxx=.o)

OBJTEST=$(addprefix build/,$(TMP4:.cpp=.o))
DEPTEST=$(addprefix build/,$(TMP4:.o=.d))

# export LD_LIBRARY_PATH=/home/mathvdt/sma/src/lib	

all: $(OBJ)
	$(CXX) $^ -o $(EXE) $(LDFLAGS) 

test : $(OBJTEST)
	$(CXX) -o $(EXETEST) $^ $(LDFLAGS)
	./$(EXETEST)

$(DOSSIER)/%.o: %.cpp
	@mkdir -p $(DOSSIER)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(DOSSIER)/%.o: %.cxx
	@mkdir -p $(DOSSIER)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf build core *.gch
	rm */$(EXE)

-include $(DEPCXX)
-include $(DEPCPP)
