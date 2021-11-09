CXXFLAGS = /I include
LDDFLAGS =  kernel32.lib user32.lib Advapi32.lib lib/pdcurses.lib
OBJS = obj\Main.obj obj\RivaCross.obj obj\RTSShared.obj
LINK = link.exe
RM = del

all: RivaCross.exe

RivaCross.exe: $(OBJS)
	$(LINK) $** /OUT:$@ $(LDDFLAGS)

	
{src}.cpp{obj}.obj::
	$(CXX) $(CXXFLAGS) /c /Fo:obj\ $<

clean:
	$(RM) RivaCross.exe
	$(RM) obj\*.obj
