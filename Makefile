CXX=c++
SOURCES=cpu_burn.cpp
CXXFLAGS=-O3 -pthread
EXECUTABLE=cpu_burn
PREFIX=/usr/local/bin

CXX_MINGW=x86_64-w64-mingw32-g++
MINGW_FLAGS=-static-libgcc -static-libstdc++ -static

build:
	$(CXX) $(SOURCES) $(CXXFLAGS) -o $(EXECUTABLE)
	
install: build
	cp $(EXECUTABLE) $(PREFIX)/

uninstall:
	rm -f $(PREFIX)/$(EXECUTABLE)

clean: $(EXECUTABLE)
	rm -f $(EXECUTABLE) examples/*.out *.exe

mingw:
	$(CXX_MINGW) $(SOURCES) $(MINGW_FLAGS) $(CXXFLAGS) -o $(EXECUTABLE)