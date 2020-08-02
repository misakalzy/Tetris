CC = gcc
CXX = g++
LINK = -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopenal32 -lfreetype -lwinmm -lgdi32 -lopengl32
DEF = -DSFML_GRAPHICS_EXPORTS -DSTBI_FAILURE_USERMSG -DSFML_STATIC
BIN = Tetris.exe
OBJ = Game.o main.o Data.o Object.o
INC = -I./include 
CXXFLAGS = -std=c++17 $(DEF) $(INC) 

all:$(BIN) clean
$(BIN):$(OBJ)
	$(CXX) $^ $(LINK) -o $@
%.d:%.cpp
	$(CXX) -MM $< > $@
sinclude $(OBJ:.o=.d)
%.o:%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
clean:
	del $(OBJ:.o=.d)
.PHONY: clean all