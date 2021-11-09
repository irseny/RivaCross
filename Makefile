CXXFLAGS = -Iinclude -Wno-multichar
LDDFLAGS = lib/pdcurses.a
OBJS = obj/Main.o obj/RivaCross.o obj/RTSShared.o
RM = rm

all: RivaCross.exe

RivaCross.exe: $(OBJS)
	$(CXX) -o $@ $^ $(LDDFLAGS)
	
obj/%.o: src/%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	$(RM) RivaCross.exe
	$(RM) obj\*.obj
