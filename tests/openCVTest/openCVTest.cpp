#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/tracking.hpp>
#include <opencv4/opencv2/core/ocl.hpp>
#include <opencv4/opencv2/imgproc.hpp> 
#include <unistd.h>
#include <iostream> 
#include <time.h>

using namespace cv;
using namespace std;

#define THRESHOLD 500
 
int main(int argc, char **argv) {
    // Section 1
    Mat frame, gray, frameDelta, thresh, firstFrame;
    vector<vector<Point> > cnts;
    VideoCapture camera(CAP_V4L2); //open camera
    
    //set the video size to 512x288 to process faster
    camera.set(3, 512);
    camera.set(4, 288);

    sleep(3);

    // Section 2
    camera.read(frame);

    //convert to grayscale and set the first frame
    cvtColor(frame, firstFrame, COLOR_BGR2GRAY);
    GaussianBlur(firstFrame, firstFrame, Size(21, 21), 0);
   
    // Section 3
    while(camera.read(frame)) {

        //convert to grayscale
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, gray, Size(21, 21), 0);

        //compute difference between first frame and current frame
        absdiff(firstFrame, gray, frameDelta);
        threshold(frameDelta, thresh, 25, 255, THRESH_BINARY);
        
        dilate(thresh, thresh, Mat(), Point(-1,-1), 2);
        findContours(thresh, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        // Section 4
        for(int i = 0; i< cnts.size(); i++) {
            if(contourArea(cnts[i]) > THRESHOLD) {
                 putText(frame, "Motion Detected", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
            }
        }

      // Section 5
       std::vector<uchar> buff;
   //encode to jpg
   cv::imencode(".jpg", frame, buff); //write jpg to stdout so it can be piped
   fwrite(buff.data(),buff.size(),1,stdout); 
   fflush(stdout);
    }
    return 0;
}
