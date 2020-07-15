import socket
import sys
import time
import struct
import numpy as np
import cv2
import sys

def main(port):

    print("Start python client at port ", str(port))

    # Create a UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ('', 50000)
    sock.bind(server_address)

    image_buffer = b''
    reading = False

    while True:
        try:
            data = sock.recvfrom(4096)

            # Check if data contains buffer_start
            if b'buffer_start' in data:
                print("Obtaining image...")
                reading = True
                continue
            
            # Check if data contains buffer_end
            elif b'buffer_end' in data:
                print("Image acquired!")

                # Check if the buffer is not empty and if it has the correct dimension.
                if image_buffer != b'':
                    image_buffer = np.fromstring(image_buffer, dtype='uint8')
                    image_buffer = cv2.imdecode(image_buffer, 1)
                    image_buffer = cv2.resize(image_buffer, (1280, 720), interpolation = cv2.INTER_AREA) 
                    cv2.imshow("image", image_buffer)
                    cv2.waitKey(1)
                    reading = False
                    image_buffer = b''
                    continue
                else:
                    print("Image buffer is empty")

            if reading == True:
                image_buffer += data[0]

            # Check buffer size
            if len(image_buffer) > 500000:
                reading = False
                image_buffer = b''

        except KeyboardInterrupt:
            print(" Exit...")
            break
        except:
            print(" Client error catch...")
            break

    print('Closing socket...')
    sock.close()

def printHelp():
    print('Usage:')
    print('python3 client.py 50000')


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print('Error: insert the port to be used by the udp socket.')
        printHelp()
    main(sys.argv[1])

    
        