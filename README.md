# opencv-image-over-udp
This program allows to send an opencv image using a C++ socket and receive the same image on a Python client.  
`UDPSocket.cpp` is the library used to send the images over the udp socket and it can be used either as a library or as a standard class. The `UDPClient_python` is the python client that receives the images.  

## Requirements
- CMake
- opencv 4.3
- python3

## Usage
This code can be used either as a library (shared object) or as a class to be compiled along with your code.

- ### **Library**
  In order to build the library use the `CMakeLists.txt`   file present inside this folder.
  ```
  mkdir bin && cd bin
  cmake .. && make
  ```
  A `libudpsocket.so` will be generated inside the `bin`   folder.

- ### **Class**
  If you want to use the class inside your project with no   library you can add both `UDPSocket.cpp` and `UDPSocket.h`   to the sources and compile them along with your code.  
  If you are using CMake you can find an example inside `./  Example/CMAkeLists.txt`.

## Example
The `Example` folder contains a simple example of an image that is being read and sent to the ip address and port. The default ip and port are `127.0.0.1` and `50000`, and the default image is `image.jpg` (The marvelous *Dream caused by the flight of a bee* by Salvador Dali :) ).  
The image is resized before sending it so as to have a relatively small data buffer to send (less than 100 MB)

Feel free to change ip, port and the image inside the code.  
In order to launch the sample do the following.

### **Server**
Build and launch the server by doing:
```
cd Example
cmake . && make
./udpSend
```

### **Client**
Open a different terminal and launche the python client:
```
cd UDPClient_python

### optional ###
virtualenv -p /usr/bin/python3 env
source env/bin/activate

pip install -r requirements.txt
python client.py 50000
```
