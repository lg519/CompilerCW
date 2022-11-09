  
CPPFLAGS += -std=c++17 -g 
#CPPFLAGS += -W -Wall -Wno-unused-parameter
CPPFLAGS += -I inc



bin/c_compiler : bin/compiler src/wrapper.sh
	cp src/wrapper.sh bin/c_compiler
	chmod u+x bin/c_compiler



bin/compiler : src/compiler.cpp ast_cpp/*.cpp ast_hpp/*.hpp src/c_lexer.yy.cpp src/c_parser.tab.cpp src/c_parser.tab.hpp
	mkdir -p bin
	g++ $(CPPFLAGS)  src/compiler.cpp ast_cpp/*.cpp src/c_lexer.yy.cpp src/c_parser.tab.cpp -o bin/compiler 



src/c_parser.tab.cpp src/c_parser.tab.hpp : src/c_parser.y
	bison -v -d src/c_parser.y -o src/c_parser.tab.cpp

src/c_lexer.yy.cpp : src/c_lexer.flex src/c_parser.tab.hpp
	flex -o src/c_lexer.yy.cpp  src/c_lexer.flex



clean :
	rm -f src/*.o
	rm -f ast_cpp/*.o
	rm -f bin/*
	rm src/*.tab.cpp
	rm src/*.yy.cpp

	rm src/*.tab.hpp
	rm src/*.output
