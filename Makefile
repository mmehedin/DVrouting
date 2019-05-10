#all: goclient clean
LIBS = -std=c++11
# Makefile
# Make the client executable file:
setInterfaces : main.o freader.o Router.o other.h Router.h port.h

# Produced by:
	g++ -o setInterfaces main.o freader.o Router.o
# 
#-----------------------------------------------------------------
executable: main.o freader.o Router.o
	g++ main.o freader.o Router.o

#Make Router.o
Router.o: Router.cpp Router.h
	g++ -c Router.cpp

# Make freader.
freader.o : freader.cpp other.h
	g++ -O0 -g3 -Wall -fmessage-length=0 $(LIBS) -MMD -MP -MF -MT -c "freader.cpp"
#-----------------------------------------------------------------
# make main.o
main.o : main.cpp Router.h port.h
        g++ -O0 -g3 -Wall -fmessage-length=0 $(LIBS) -MMD -MP -MF -MT -c "main.cpp"
#------------------------------------------
clean:
	rm -rf *o setInterfaces
