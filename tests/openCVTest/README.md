Fails on trying to obtain information from the webcam 

Based on Guide from 2022 Spring: https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2022-student-howtos/DetectMotionUsingUSBWebcamAndOpenCV.pdf
Deprecated information such as still using avconv 
No version mentioned as the method to compile in the guide does not work for OpenCV4 which is currently the latest version as of writing 

Current working compile code:
g++ -DOPENCV_GENERATE_PKGCONFIG=ON -O2 pkg-config --cflags --libs opencv4 -lrt camera.cpp -o camera -lopencv_videoio -lopencv_imgcodecs -lopencv_core -lopencv_imgproc -lv4l2 -lpthread