#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <mutex>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "../UDPSocket.h"

static const std::string imageName = "./image.jpg";
static const float imageScaleFactor = 0.4;
static const char ip[] = "127.0.0.1"; // Add here your alternative ip (e.g "192.168.1.6")
static const int port = 50000;

bool gRun = true;
void sig_handler(int signo) {
    printf("\nClosing ...\n");
    gRun = false;
}

int main(int argc, char *argv[]) {
    signal(SIGINT, sig_handler);
    cv::Mat frame;

    // Init socket
    UDPSocket *s = new UDPSocket(ip, port, TRUE, TRUE);

    while(gRun) {
        /* Read the frame */
        frame = cv::imread(imageName);

        /* Scale the image using the imageScaleFactor for less data loss */
        cv::resize(frame, frame, cv::Size(frame.cols * imageScaleFactor, frame.rows * imageScaleFactor));

        /* Initialize buffer and encode image */
        int pixel_number = frame.rows * frame.cols / 2;
        std::vector<uchar> buf(pixel_number);
        cv::imencode(".jpg", frame, buf);
        int length = buf.size();

        /* Start image transmission */
        std::string str = "buffer_start";
        s->send(reinterpret_cast<const unsigned char*>(str.c_str()), str.length());

        /* Transmit chunks of 1024 bytes */
        int chunkSize = 1024;
        for (size_t i = 0; i < buf.size(); i += chunkSize) {
            std::vector<uchar> tempVec = std::vector<uchar>(buf.begin() + i, buf.begin() + i + chunkSize);
            s->send(tempVec.data(), chunkSize);
        }

        /* End image transmission */
        str = "buffer_end";
        s->send(reinterpret_cast<const unsigned char*>(str.c_str()), str.length());

        printf("Sending image %s to %s:%d with length %d bytes \n", imageName.c_str(), ip, port, length);
    }

    /* Close the socket */
    s->~UDPSocket();
}