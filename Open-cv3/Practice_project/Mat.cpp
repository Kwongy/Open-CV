#include<opencv2/core/core.hpp>
#include<opencv.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc_c.h>
using namespace std;
using namespace cv;
#define WINDOW_WIDTH 600
#define WINDOW_NAME1 "Image 1"
#define WINDOW_NAME2 "Image 2"

void DrawEllipse(Mat img, double angle) {
	int thickness = 2;
	int lineType = 8;

	ellipse(
		img, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
		Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
		angle, 0, 360, Scalar(255, 129, 0),
		thickness,
		lineType
	);
}

void DrawFilledCircle(Mat img, Point center) {
	int thickness = -1;
	int lineType = 8;
	circle(
		img, center,
		WINDOW_WIDTH / 32,
		Scalar(0, 0, 255),
		thickness,
		lineType
	);
}

void DrawPolygon(Mat img) {
	int lineType = 8;
	Point rookPoints[1][20];
	
}

void DrawLine(Mat img, Point start, Point end) {
	int thickness = 2;
	int lineType = 8;
	line(img, start, end,
		Scalar(0, 0, 0),
		thickness,
		lineType);
}

int main() {
	/*Mat E = Mat::eye(4, 4, CV_64F);
	E = Mat::ones(2, 2, CV_32F);
	E = Mat::zeros(3, 3, CV_8UC1);
	Mat L(2, 2, CV_8UC3, Scalar(0, 0, 255));
	L.create(4, 4, CV_8UC2);
	L = (Mat_<double>(3, 3) << 0, 1, 0, 1, 5, 1, 0, 1, 0);
	*/
	//cout << L << endl;
	//cout << E << endl;
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);
	DrawFilledCircle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));
	imshow(WINDOW_NAME1, atomImage);
	moveWindow(WINDOW_NAME1, 0, 200);
	waitKey(0);
	return 0;
}