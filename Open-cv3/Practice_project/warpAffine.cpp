#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage, g_warp_rotateImage;
#define WINDOW_NAME1 "0rigin Window"
#define WINDOW_NAME2 "After Warping"
#define WINDOW_NAME3 "After Warping and rotating"

int main() {
	system("color 1A");
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];

	Mat rotMat(2, 3, CV_32FC1);
	Mat warpMat(2, 3, CV_32FC1);

	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}

	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(static_cast<float>(g_srcImage.cols - 1), 0);
	srcTriangle[2] = Point2f(0, static_cast<float>(g_srcImage.rows - 1));

	dstTriangle[0] = Point2f(static_cast<float>(g_srcImage.cols * 0.0),static_cast<float>(g_srcImage.rows * .33));
	dstTriangle[1] = Point2f(static_cast<float>(g_srcImage.cols * .65), static_cast<float>(g_srcImage.rows * .35));
	dstTriangle[2] = Point2f(static_cast<float>(g_srcImage.cols * .15), static_cast<float>(g_srcImage.rows * .6));

	warpMat = getAffineTransform(srcTriangle, dstTriangle);
	warpAffine(g_srcImage, g_dstImage, warpMat, g_dstImage.size());

	Point center = Point(g_dstImage.cols / 2, g_dstImage.rows / 2);
	double angle = -30.0;
	double scale = 0.8;
	rotMat = getRotationMatrix2D(center, angle, scale);
	warpAffine(g_dstImage, g_warp_rotateImage, rotMat, g_dstImage.size());

	imshow(WINDOW_NAME1, g_srcImage);
	imshow(WINDOW_NAME2, g_dstImage);
	imshow(WINDOW_NAME3, g_warp_rotateImage);

	waitKey(0);
	return 0;
}