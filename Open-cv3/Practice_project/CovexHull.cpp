#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "Window one"
#define WINDOW_NAME2 "Window two"

Mat g_srcImage, g_grayImage;
int g_nThresh = 50, g_maxThresh = 255;
Mat srcImage = g_srcImage.clone();
Mat g_thresholdImage_out;
RNG g_rng(12345);
vector<vector<Point> >g_vContours;
vector<Vec4i> g_vHierarchy;

void on_ThreshChange(int, void*) {
	threshold(g_grayImage, g_thresholdImage_out, g_nThresh, 255, THRESH_BINARY);
	findContours(g_thresholdImage_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<vector<Point> >hull(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); ++i) {
		convexHull(Mat(g_vContours[i]), hull[i], false);
	}
	Mat drawing = Mat::zeros(g_thresholdImage_out.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_vContours.size(); ++i) {
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}
	imshow(WINDOW_NAME2, drawing);
}

int main() {
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	createTrackbar("Thresh", WINDOW_NAME1, &g_nThresh, g_maxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);
	waitKey(0);
	return 0;
}