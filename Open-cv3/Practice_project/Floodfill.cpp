#include <iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;
int g_nFillMode = 1;
int g_nLowDifference = 20, g_nUpDifference = 20;
int g_nConnectivity = 4;
int g_bIscolor = true;
bool g_bUseMask = false;
int g_nNewMaskVal = 255;

static void onMouse(int event, int x, int y, int, void *) {
	if (event != EVENT_LBUTTONDOWN) return;
	Point seed = Point(x, y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	
	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;
	Scalar newVal = g_bIscolor ? Scalar(b, g, r) : Scalar(r * 0.299 + g * 0.587 + b * 0.114);

	Mat dst = g_bIscolor ? g_dstImage : g_grayImage;
	int area;
	if (g_bUseMask) {
		threshold(g_maskImage, g_maskImage, 1, 128, THRESH_BINARY);
		area = floodFill(dst, g_maskImage, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
		imshow("Mask", g_maskImage);
	}
	else {
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
	}
	imshow("Effect picture", dst);
	cout << area << "Effect picture" << endl;
}


int main() {
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return -1;
	}

	g_srcImage.copyTo(g_dstImage);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	g_maskImage.create(g_srcImage.rows + 2, g_srcImage.cols + 2, CV_8UC1);

	namedWindow("Effect picture");
	createTrackbar("Maximum negative difference", "Effect picture", &g_nLowDifference, 255, 0);
	createTrackbar("Maximum positive difference", "Effect picture", &g_nUpDifference, 255, 0);
	setMouseCallback("Effect picture", onMouse, 0);
	while (true) {
		imshow("Effect picture", g_bIscolor ? g_dstImage : g_grayImage);
		int c = waitKey(0);
		if ((c & 255) == 27) {
			cout << "Quit" << endl;
			break;
		}
		switch ((char)c) {
		case '1':
			if (g_bIscolor) {
				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
				g_maskImage = Scalar::all(0);
				g_bIscolor = false;
			}
			else {
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIscolor = true;
			}
			break;
		case '2':
			if (g_bUseMask) {
				destroyWindow("Mask");
				g_bUseMask = false;
			}
			else {
				namedWindow("Mask", 0);
				g_maskImage = Scalar::all(0);
				imshow("Mask", g_maskImage);
				g_bUseMask = true;
			}
			break;
		case '3':
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
			g_maskImage = Scalar::all(0);
			break;
		case '4':
			g_nFillMode = 0;
			break;
		case '5':
			g_nFillMode = 1;
			break;
		case '6':
			g_nFillMode = 2;
			break;
		case '7':
			g_nConnectivity = 4;
			break;
		case '8':
			g_nConnectivity = 8;
			break;

		}
		
	}


	return 0;
}