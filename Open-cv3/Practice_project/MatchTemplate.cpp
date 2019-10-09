#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "Artwork picture"
#define WINDOW_NAME2 "Effect picture"

Mat g_srcImage, g_templateImage, g_resultImage;
int g_nMatchMethod = 0, g_nMaxTrackbar = 5;

void on_Match(int, void*) {
	Mat srcImage;
	g_srcImage.copyTo(srcImage);
	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	int resultImage_cols = g_srcImage.cols - g_templateImage.cols + 1;
	g_resultImage.create(resultImage_rows, resultImage_cols, CV_32FC1);

	matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod);
	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());

	double minVal, maxVal;
	Point minLocation, maxLocation, matchLocation;
	minMaxLoc(g_resultImage, &minVal, &maxVal, &minLocation, &maxLocation, Mat());

	if (g_nMatchMethod == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED) {
		matchLocation = minLocation;
	}
	else {
		matchLocation = maxLocation;
	}

	rectangle(srcImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),
		Scalar(0, 0, 255), 2, 8, 0);
	rectangle(g_resultImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),
		Scalar(0, 0, 255), 2, 8, 0);

	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, g_resultImage);
}

int main() {
	system("color BA");
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\boy.jpg", 1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}

	g_templateImage = imread("C:\\Users\\kwong\\Pictures\\boy2.jpg", 1);
	if (!g_templateImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}

	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);

	createTrackbar("Ways", WINDOW_NAME1, &g_nMatchMethod, g_nMaxTrackbar, on_Match);
	on_Match(0, 0);
	waitKey(0);

	return 0;
}