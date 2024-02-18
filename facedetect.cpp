#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    VideoCapture video(0); // Change to 0 for the default camera

    if (!video.isOpened()) {
        cout << "Error: Failed to open the camera" << endl;
        return -1;
    }

    CascadeClassifier facedetect;
    if (!facedetect.load("haarcascade_frontalface_default.xml")) {
        cout << "Error: Failed to load face cascade classifier" << endl;
        return -1;
    }

    Mat img;

    while (true) {
        if (!video.read(img)) {
            cout << "Error: Failed to read frame from the camera" << endl;
            break;
        }

        if (img.empty()) {
            cout << "Error: Empty frame" << endl;
            continue;
        }

        vector<Rect> faces;
        facedetect.detectMultiScale(img, faces, 1.3, 5);

        cout << faces.size() << " face(s) found" << endl;

        for (const Rect& face : faces) {
            rectangle(img, face, Scalar(50, 50, 255), 3);
        }

        rectangle(img, Point(0, 0), Point(250, 70), Scalar(50, 50, 255), FILLED);
        putText(img, to_string(faces.size()) + " Face Found", Point(10, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 1);

        imshow("Frame", img);
        if (waitKey(1) == 27) // Exit if ESC is pressed
            break;
    }

    return 0;
}
