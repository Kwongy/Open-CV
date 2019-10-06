#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/photo/photo.hpp>
using namespace std;
using namespace cv;
#define WINDOW_NAME1 "Artwork picture"
#define WINDOW_NAME2 "Effect picture"

Mat g_srcImage, g_maskImage;
Point previousPoint(-1, -1); 

static void on_Mouse(int event, int x, int y, int flag, void *) {
	if (x < 0 || x >= g_srcImage.cols || y < 0 || y >= g_srcImage.rows) return;
	if (event == EVENT_LBUTTONUP || !(flag & EVENT_FLAG_LBUTTON))
		previousPoint = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)
		previousPoint = Point(x, y);
	else if (event == EVENT_MOUSEMOVE && (flag & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (previousPoint.x < 0)
			previousPoint = pt;
		line(g_maskImage, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		line(g_srcImage, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		previousPoint = pt;
		imshow(WINDOW_NAME1, g_srcImage);
	}
}


int main() {
	system("color 1E");
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", -1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}
	g_maskImage = Mat::zeros(g_srcImage.size(), CV_8U);
	Mat srcImage = g_srcImage.clone();
	imshow(WINDOW_NAME1, srcImage);
	setMouseCallback(WINDOW_NAME1, on_Mouse, 0);
	while (true) {
		int c = waitKey(0);
		if (char(c) == 27) break;
		if (char(c) == '2') {
			g_maskImage = Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			//imshow("image", g_srcImage);
		}
		if (char(c) == '1' || char(c) == ' ') {
			Mat inpaintedImage;
			inpaint(g_srcImage, g_maskImage, inpaintedImage, 3, INPAINT_TELEA);
			imshow(WINDOW_NAME2, inpaintedImage);
		}
	}

	return 0;
}