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

#### Run the code:
./setInterfaces

#### All:
clear && make clean && make &&  ./setInterfaces

#### Ports cleanup MacOS:

to kill:

sudo lsof -n -i UDP:44445 | grep 44445 | awk '{ print $2 }' | xargs kill

to list:

lsof -Pn -i4

sudo lsof -i UDP | grep 44445


### Report videos:

Part 1: https://youtu.be/TvIazYpTJp0

Part 2: https://youtu.be/zRfCULzkOwg

-----------------------------------

### Results:

Initial setup of ethernet interfaces with local Ip:
![RNN](https://raw.githubusercontent.com/mmehedin/DVrouting/master/Results/Screen_Shot_2019-05-10_at_8.43.03_PM.png)



Each Router Node is instantiated and contains the routing table information with infinite values:
![RNN](https://raw.githubusercontent.com/mmehedin/DVrouting/master/Results/Screen_Shot_2019-05-10_at_8.43.48_PM.png)



Threads are created for each node to support the server (infinite loop)  and the client (sending data every 15 seconds):
![RNN](https://raw.githubusercontent.com/mmehedin/DVrouting/master/Results/Screen_Shot_2019-05-10_at_8.44.38_PM.png)



Server and clients communicate and the node A routing table is printed upon complition of the update:
![RNN](https://raw.githubusercontent.com/mmehedin/DVrouting/master/Results/Screen_Shot_2019-05-10_at_8.45.19_PM.png)



Each nodes sends its table in 6 sepparate messages one for each row (node in the net) containing "destination nextHop cost SenderName):

![RNN](https://raw.githubusercontent.com/mmehedin/DVrouting/master/Results/Screen_Shot_2019-05-10_at_8.45.31_PM.png)



---------------------------------------

Reference: https://www.geeksforgeeks.org/udp-server-client-implementation-c/

-----
