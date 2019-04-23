#all: goclient clean

# Makefile
# Make the client executable file:
setInterfaces : main.o freader.o other.h

# Produced by:
	g++ -o setInterfaces main.o freader.o
# 
#-----------------------------------------------------------------
# Make freader.
freader.o : freader.cpp other.h
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"freader.d" -MT"other.h" -o "freader.o" "freader.cpp"
# make main.o
main.o : main.cpp other.h
        g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"main.d" -MT"other.h" -o "main.o" "main.cpp"

clean:
	rm -rf *o setInterfaces
