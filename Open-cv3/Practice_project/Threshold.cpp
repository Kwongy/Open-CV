#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;

void on_Threshold(int, void *) {
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
	imshow("Window", g_dstImage);
}

int main() {
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
	namedWindow("Window", WINDOW_AUTOSIZE);
	createTrackbar("Mode", "Window", &g_nThresholdType, 4, on_Threshold);
	createTrackbar("Value", "Window", &g_nThresholdValue, 255, on_Threshold);

	on_Threshold(0, 0);
	while (true) {
		int key = waitKey(20);
		if (char(key) == 27) break;
	}

	return 0;
}