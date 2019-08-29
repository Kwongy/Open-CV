#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
using namespace cv;
#define WINDOW_NAME "Linear mixed"

const int AlphaValueMax = 100;
int AlphaValueSlider;
double AlphaValue, BetaValue;

Mat srcImage1, srcImage2, mixImage;

void on_Trackbar(int, void*) {
	AlphaValue = (double)AlphaValueSlider / AlphaValueMax;
	BetaValue = 1.0 - AlphaValue;
	addWeighted(srcImage1, AlphaValue, srcImage2, BetaValue, 0.0, mixImage);
	imshow(WINDOW_NAME, mixImage);
}

int main() {
	char img_path1[100] = "F:\\TheGrandSegmentation-master\\experiment\\test_img0.tif";
	char img_path2[100] = "F:\\TheGrandSegmentation-master\\experiment\\test_0.tif";
	srcImage1 = imread(img_path1);
	if (!srcImage1.data) {
		printf("load image one error, please try again\n");
		return -1;
	}
	srcImage2 = imread(img_path2);
	if (!srcImage2.data) {
		printf("load image two error, please try again\n");
		return -1;
	}

	AlphaValueSlider = 70;
	namedWindow(WINDOW_NAME, 1);
	char TrackbarName[] = "";
	createTrackbar(TrackbarName, WINDOW_NAME, &AlphaValueSlider, AlphaValueMax, on_Trackbar);

	on_Trackbar(AlphaValueSlider, 0);
	waitKey(0);

	return 0;
}