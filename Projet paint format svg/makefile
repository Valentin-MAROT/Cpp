
CPPFLAGS= -std=c++17 -g -Wall -Wextra -Wconversion -O0 -I -D
SRCs=Shape.cpp Grawink.cpp Liste.cpp SVG.cpp shapetype.cpp main.cpp
OBJs=$(patsubst %.cpp,$(Dest)/%.o,$(SRCs))
LDLIBs=
EXE=Projet
CXX=g++
Dest=build
Header=headers
Src=srcs
SVG=resultats


$(EXE): libgraweditor.a $(Dest)/main.o
	$(CXX) $(CPPFLAGS) -o $(EXE) $(Dest)/main.o -L$(Dest) -lgraweditor $(LDLIBs)
clean:
	rm -f $(EXE) $(Dest)/libgraweditor.a $(Dest)/*.o
	rm -rf $(SVG)

libgraweditor.a: $(OBJs)
	@echo " "
	@echo "===================="
	@echo "Building $@"
	@echo "===================="
	@echo " "
	@mkdir -p $(Dest)
	@ar rcs $(Dest)/$@ $(Dest)/*.o
	@echo "===================="
	@echo "Library $@ built"
	@echo "===================="
	@echo " "

$(Dest)/Shape.o: $(Src)/Shape.cpp $(Header)/Shape.h $(Header)/Point.h $(Header)/SVG.h
	$(CXX) $(CPPFLAGS) -c -o $(Dest)/Shape.o $(Src)/Shape.cpp
$(Dest)/Grawink.o: $(Src)/Grawink.cpp $(Header)/Grawink.h $(Header)/Shape.h $(Header)/Liste.h $(Header)/Point.h $(Header)/Array.h $(Header)/SVG.h
	$(CXX) $(CPPFLAGS) -c -o $(Dest)/Grawink.o $(Src)/Grawink.cpp
$(Dest)/Liste.o: $(Src)/Liste.cpp $(Header)/Liste.h
	$(CXX) $(CPPFLAGS) -c -o $(Dest)/Liste.o $(Src)/Liste.cpp
$(Dest)/SVG.o: $(Src)/SVG.cpp $(Header)/SVG.h
	$(CXX) $(CPPFLAGS) -c -o $(Dest)/SVG.o $(Src)/SVG.cpp
$(Dest)/main.o: $(Src)/main.cpp $(Header)/Shape.h $(Header)/Grawink.h $(Header)/Liste.h $(Header)/SVG.h $(Header)/Point.h $(Header)/Array.h $(Header)/SVG.h
	$(CXX) $(CPPFLAGS) -c -o $(Dest)/main.o $(Src)/main.cpp
$(Dest)/shapetype.o: $(Src)/shapetype.cpp $(Header)/shapetype.h
	$(CXX) $(CPPFLAGS) -c -o $(Dest)/shapetype.o $(Src)/shapetype.cpp
run: $(EXE)
	@echo " "
	@echo "===================="
	@echo "Running $(EXE)"
	@echo "===================="
	@echo " "
	@mkdir -p $(SVG)
	@./$(EXE) -s
	@for file in *.svg; do \
    if [ -f "$$file" ]; then \
        mv $$file $(SVG); \
    fi \
	done
