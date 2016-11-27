CFLAGS= -Wall -g
LFLAGS= -Wall -g
CXX=g++

PROGRAMS=main 

all: $(PROGRAMS)
	@echo "DONE"

obj=planetinfo.o utilities.o main.o
main: $(obj)
	$(CXX) $(LFLAGS) $(obj) -o main

utilities.o: utilities.cc utilities.h
	$(CXX) $(CFLAGS) -c utilities.cc    

planetinfo.o: planetinfo.cc planetinfo.h
	$(CXX) $(CFLAGS) -c planetinfo.cc	

#evolution.o: evolution.cc evolution.h planetinfo.h utilities.h
#	$(CXX) $(CFLAGS) -c evolution.cc 

main.o: main.cc utilities.h planetinfo.h #evolution.h 
	$(CXX) $(CFLAGS) -c main.cc

#%.o: %.cc %.h
#	$(CXX) $(CFLAGS) -c $<

clean:
	rm -f *.o *.mod $(PROGRAMS)

realclean: clean
	rm -f *~
