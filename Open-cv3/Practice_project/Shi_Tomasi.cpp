#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "Window1"

Mat g_srcImage, g_grayImage;
int g_maxCornerNumber = 33;
int g_maxTrackbarNumber = 500;
RNG g_rng(12345);

void on_GoodFeatureToTrack(int, void*) {
	if (g_maxCornerNumber <= 1) g_maxCornerNumber = 1;
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	double k = 0.04;
	Mat copy = g_srcImage.clone();
	goodFeaturesToTrack(g_grayImage, corners, g_maxCornerNumber, qualityLevel, minDistance, Mat(), blockSize, false, k);
	cout << "Number of the corners is :"<<corners.size() << endl;
	int r = 4;
	for (unsigned int i = 0; i < corners.size(); ++i) {
		circle(copy, corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)), -1, 8, 0);
	}
	imshow(WINDOW_NAME1, copy);
}

int main() {
	system("color CE");
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", -1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	createTrackbar("Max of Corners is", WINDOW_NAME1, &g_maxCornerNumber, g_maxTrackbarNumber, on_GoodFeatureToTrack);
	on_GoodFeatureToTrack(0, 0);
	waitKey(0);

	return 0;
}