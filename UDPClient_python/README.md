# UDP Client
`client.py` starts a program that takes as input a specific port and wait fro incoming data at that port. 
The program starts collecting packages as part of an image whenever it receives `buffer_start` and it shows the received image when it receives `buffer_end`.

## Usage
Install the required packages with
```
pip install -r requirements.txt
```
and launch the program
```
python3 client.py <port>
```