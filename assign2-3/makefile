CFLAGS= -Wall -g
LFLAGS= -Wall -g
CXX=g++

PROGRAMS=main 

all: $(PROGRAMS)
	@echo "DONE"

obj=planetinfo.o main-using-class.o
main: $(obj)
	$(CXX) $(LFLAGS) $(obj) -o main

planetinfo.o: planetinfo.cc planetinfo.h
	$(CXX) $(CFLAGS) -c planetinfo.cc	

main-using-class.o: main-using-class.cc planetinfo.h
	$(CXX) $(CFLAGS) -c main-using-class.cc

#%.o: %.cc %.h
#	$(CXX) $(CFLAGS) -c $<

clean:
	rm -f *.o *.mod $(PROGRAMS)

realclean: clean
	rm -f *~
