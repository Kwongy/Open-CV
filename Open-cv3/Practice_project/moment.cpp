#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "Artwork picture"
#define	WINDOW_NAME2 "Effect picture"

Mat g_srcImage, g_grayImage;
int g_nThresh = 100, g_nMaxThresh = 255;
RNG g_rng(12345);
Mat g_canny;
vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;

void on_ThreshChange(int, void*) {
	Canny(g_grayImage, g_canny ,g_nThresh ,g_nThresh * 2, 3);
	findContours(g_canny, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<Moments> mu(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); ++i) {
		mu[i] = moments(g_vContours[i], false);
	}
	vector<Point2f> mc(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++) {
		mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
	}
	Mat drawing = Mat::zeros(g_canny.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_vContours.size(); ++i) {
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME2, drawing);

	cout << "Calculate contour area and length" << endl;
	for (unsigned int i = 0; i < g_vContours.size(); i++) {
		cout << "Contour area, " << mu[i].m00 << " opencv :" << contourArea(g_vContours[i]) 
			<< "\t Length:\t" << arcLength(g_vContours[i], true) << endl;

		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}
}

int main() {
	system("color 1E");
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	createTrackbar("Thresh", WINDOW_NAME1, &g_nThresh, g_nMaxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);
	waitKey(0);

	return 0;
}
