# Don't really need flags

CXX=g++

PROGRAMS=main 

all: $(PROGRAMS)
	@echo "DONE"

main=planetinfo.o main.o
main: $(main)
	$(CXX) -o $(main) 

%.o: %.cc %.h
	$(CXX) -c $<

clean:
	rm -f *.o *.mod $(PROGRAMS)

realclean: clean
	rm -f *~
