CXX := g++
SRCS := $(shell find . -name "*.cpp" )
OBJS := $(patsubst %.cpp, objs/%.o, $(SRCS) )
CXXFLAGS = "-o2 -ggdb -fPIC"

INC_DIR := -I"./parser/include" -I"./include"
OUT_DIR = ./out/lib
OUTPUT_EXE := ./out/parser.exe

all: builddir $(OUTPUT_EXE)

builddir:
	@$(shell dirs=""; for i in $(OBJS); 	\
	do dir=$$(dirname $$i); 	\
	dirs="$$dirs:$$dir";			\
	done; echo "$$dirs"|xargs -I{} -d':' mkdir -p '{}')
	mkdir -p ./out

	
objs/%.o : %.cpp
	$(CXX) $(CXXFLAGS)  -c $< -o $@ $(INC_DIR)


$(OUTPUT_EXE): $(OBJS)
	$(CXX)  -L"/usr/lib/" $(OBJS) -o $(OUTPUT_EXE) -lclang -largp
	
clean:
	rm ./objs -r
	rm ./out -r