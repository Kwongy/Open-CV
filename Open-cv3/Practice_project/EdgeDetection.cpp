#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage, g_grayImage;
Mat g_canny, g_sobel_x, g_sobel_y, g_scharr_x, g_scharr_y, g_scharrAbs_x, g_scharrAbs_y;
int g_cannyLowThreshold = 1, g_sobelSize = 1;

static void on_Canny(int, void*) {
	// Gaussian filter
	blur(g_grayImage, g_canny, Size(3, 3));

	Canny(g_canny, g_canny, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);

	g_dstImage = Scalar::all(0);
	g_srcImage.copyTo(g_dstImage, g_canny);
	imshow("Canny Image", g_dstImage);
}

static void on_Sobel(int, void*) {
	Sobel(g_srcImage, g_sobel_x, CV_16S, 1, 0,
		(2 * g_sobelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobel_x, g_sobel_x);

	Sobel(g_srcImage, g_sobel_y, CV_16S, 1, 0,
		(2 * g_sobelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobel_y, g_sobel_y);

	addWeighted(g_sobel_x, 0.5, g_sobel_y, 0.5, 0, g_dstImage);

	imshow("Sobel Image", g_dstImage);
}

void Scharr() {
	Scharr(g_srcImage, g_scharr_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(g_scharr_x, g_scharrAbs_x);

	Scharr(g_srcImage, g_scharr_y, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(g_scharr_y, g_scharrAbs_y);

	addWeighted(g_scharrAbs_x, 0.5, g_scharrAbs_y, 0.5, 0, g_dstImage);

	imshow("Scharr Image", g_dstImage);
}


int main() {
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}
	system("color 2F");
	namedWindow("Artwork Master");
	imshow("Artwork Master", g_srcImage);
	
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	namedWindow("Canny Image", WINDOW_AUTOSIZE);
	namedWindow("Sobel Image", WINDOW_AUTOSIZE);
	createTrackbar("Value", "Canny Image", &g_cannyLowThreshold, 120, on_Canny);
	createTrackbar("Value", "Sobel Image", &g_sobelSize, 3, on_Sobel);

	on_Canny(0, 0);
	on_Sobel(0, 0);
	Scharr();
	while (true) {
		int key = waitKey(0);
		if (key == 27)	break;
	}
	return 0;
}

