#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage;
int g_nElementShape = MORPH_RECT;

int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackHatNum = 0;

static void on_OpenClose(int, void *) {
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;
	int absolute = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(g_nElementShape ,Size(absolute * 2 + 1, absolute * 2 + 1), Point(absolute, absolute));
	if (offset < 0) {
		morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, element);
	}
	else {
		morphologyEx(g_srcImage, g_dstImage, MORPH_CLOSE,element);
	}
	imshow("Opening-and-closing operation", g_dstImage);
}

static void on_ErodeDilate(int, void *) {
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;
	int absolute = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(g_nElementShape, Size(absolute * 2 + 1, absolute * 2 + 1), Point(absolute, absolute));
	if (offset < 0) {
		erode(g_srcImage, g_dstImage, element);
	}
	else {
		dilate(g_srcImage, g_dstImage, element);
	}
	imshow("Erode and Dilate", g_dstImage);
}

static void on_TopBlackHat(int, void *) {
	int offset = g_nTopBlackHatNum - g_nMaxIterationNum;
	int absolute = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(g_nElementShape, Size(absolute * 2 + 1, absolute * 2 + 1), Point(absolute, absolute));
	if (offset < 0) {
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, element);
	}
	else {
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
	}
	imshow("Top-and-Black hat", g_dstImage);
}

int main() {
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImage.data) {
		printf("Image reading error!\n");
		return -1;
	}
	namedWindow("Artwork Master");
	imshow("Artwork Master", g_srcImage);

	g_nOpenCloseNum = 9;
	g_nErodeDilateNum = 9;
	g_nTopBlackHatNum = 2;

	namedWindow("Opening-and-closing operation", 1);
	createTrackbar("Value", "Opening-and-closing operation", &g_nOpenCloseNum, g_nMaxIterationNum * 2 + 1, on_OpenClose);

	namedWindow("Erode and Dilate", 1);
	createTrackbar("Value", "Erode and Dilate", &g_nErodeDilateNum, g_nMaxIterationNum * 2 + 1, on_ErodeDilate);
	
	namedWindow("Top-and-Black hat", 1);
	createTrackbar("Value", "Top-and-Black hat", &g_nTopBlackHatNum, g_nMaxIterationNum * 2 + 1, on_TopBlackHat);

	while (1) {
		int c;
		on_OpenClose(g_nOpenCloseNum, 0);
		on_ErodeDilate(g_nErodeDilateNum, 0);
		on_TopBlackHat(g_nTopBlackHatNum, 0);
		c = waitKey(0);

		if (char(c) == 'q' || char(c) == 27) {
			break;
		}
		if (char(c) == 49) {
			g_nElementShape = MORPH_ELLIPSE;
		}
		else if (char(c) == 50) {
			g_nElementShape = MORPH_RECT;
		}
		else if (char(c) == 51) {
			g_nElementShape = MORPH_CROSS;
		}
		else if (char(c) == ' ') {
			g_nElementShape = (g_nElementShape + 1) % 3;
		}
	}
	return 0;
}