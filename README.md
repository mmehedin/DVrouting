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

<!--- [![Gihub work viz](https://raw.githubusercontent.com/mmehedin/one_shot_summarization/master/temp/output.png)](https://youtu.be/FkW8_dybynM "One shot") --->
![Gihub work viz](https://raw.githubusercontent.com/mmehedin/one_shot_summarization/master/temp/output.gif)


-----------------------------------

### Results:

DV Routing part 1:
![RNN](https://raw.githubusercontent.com/mmehedin/HTTP_Server_Client/master/Results/client_get_8.27.21.png)


---------------------------------------

Reference: https://www.geeksforgeeks.org/udp-server-client-implementation-c/

-----
