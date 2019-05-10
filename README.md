# DVrouting

-----

### Summary:


Goal:  simulate the DV routing; via sys/socket.h

-------------

### How to use this:
Clone the repo/download the code
build the executables:

make clean
make

On the terminal window run to create the interfaces:
bash setupInterfaces.sh

Run the code:
./setInterfaces

#####All:
clear && make clean && make &&  ./setInterfaces

#####Ports cleanup MacOS:

kill:
sudo lsof -n -i UDP:44445 | grep 44445 | awk '{ print $2 }' | xargs kill

list:
lsof -Pn -i4
sudo lsof -i UDP | grep 44445
