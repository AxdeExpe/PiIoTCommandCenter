Installation:

sudo apt-get update && sudo apt-get upgrade -y

<jsoncpp/json/json.h>
-->
sudo apt-get install libjsoncpp-dev

<sqlite3.h>
-->
sudo apt-get install sqlite3 libsqlite3-dev

<wiringPi.h>
sudo apt-get install wiringPi

compiling:
g++ -o main main.cpp -ljsoncpp
g++ -o main main.cpp -ljsoncpp -lwiringPi