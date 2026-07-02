TARGET=huffman
CXX=g++
DEBUG=-g
OPT=-O0
CXXFLAGS=$(DEBUG) $(OPT) $(WARN) -pipe
LD=g++
OBJS= main.o aplicacao.o bits.o huffman.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
	@rm -rf *.o

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp -o main.o

huffman.o: src/huffman.cpp
	$(CXX) -c $(CXXFLAGS) src/huffman.cpp -o huffman.o

aplicacao.o: src/aplicacao.cpp
	$(CXX) -c $(CXXFLAGS) src/aplicacao.cpp -o aplicacao.o

bits.o: src/bits.cpp
	$(CXX) -c $(CXXFLAGS) src/bits.cpp -o bits.o
