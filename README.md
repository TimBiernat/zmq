# fitlet2 / centos
sudo yum group install "Development Tools"
sudo yum install https://dl.fedoraproject.org/pub/epel/epel-release-latest-8.noarch.rpm
sudo yum install czmq-devel

# raspberry pi 
compilation tools
  sudo apt-get install libtool pkg-config build-essential autoconf automake
czmq lib install
  sudo apt-get install libczmq-dev

compile
  gcc -Wall -lczmq ping.c -o ping

local tcp (~400 uS roundtrip in pi4-64)
  ./echo
  ./ping tcp://localhost:5555 1

server tcp (pi4-64)
  ./echo
client (~700us roundtrip from pi3-64)
  ./ping tcp://<server>:5555 1

inproc://example
ipc://example.ipc

pull tcp://*:5555
push tcp://pi3-64:5555

areas of investigation:
  pubsub
    sensor data broadcast to subscribers, on receipt subscriber sends response
  discovery protocols
