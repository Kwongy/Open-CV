#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "Artwork Picture"
#define WINDOW_NAME2 "Contours Picture"

Mat g_srcImage, g_dstImage, g_cannyImage;
int g_nThresh = 80, g_Max = 255;
RNG g_rng(12345);
vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;

void on_ThreshChange(int, void *) {
	Canny(g_dstImage, g_cannyImage, g_nThresh, g_nThresh * 2, 3);
	findContours(g_cannyImage, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	Mat drawing = Mat::zeros(g_cannyImage.size(), CV_8UC3);

	for (int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}
	imshow(WINDOW_NAME2, drawing);
}

int main() {
	system("color 1F");
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}
	cvtColor(g_srcImage, g_dstImage, COLOR_BGR2GRAY);
	blur(g_dstImage, g_dstImage, Size(3, 3));

	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_dstImage);

	createTrackbar("Canny threshold value", WINDOW_NAME1, &g_nThresh, g_Max, on_ThreshChange);
	on_ThreshChange(0, 0);
	waitKey(0);

	return 0;
}