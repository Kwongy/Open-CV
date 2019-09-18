#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage, g_tempImage;

int main() {
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}
	namedWindow("Window", WINDOW_AUTOSIZE);
	imshow("Window", g_srcImage);

	g_tempImage = g_srcImage;
	g_dstImage = g_tempImage;
	int key = 0;
	while (1) {
		key = waitKey(9);
		switch (key) {
		case 27:
			return 0;
			break;
		case 'q':
			return 0;
			break;
		case 'a':
			pyrUp(g_tempImage, g_dstImage, Size(g_tempImage.cols * 2, g_tempImage.rows * 2));
			cout << "Base on pyrUp zooming in two times" << endl;
			break;
		case 'w':
			resize(g_tempImage, g_dstImage, Size(g_tempImage.cols * 2, g_tempImage.rows * 2));
			cout << "Base on resize zooming in two times" << endl;
			break;
		case 'd':
			pyrDown(g_tempImage, g_dstImage, Size(g_tempImage.cols / 2, g_tempImage.rows / 2));
			cout << "Base on pyrDown reduce the double" << endl;
			break;
		case 's':
			resize(g_tempImage, g_dstImage, Size(g_tempImage.cols / 2, g_tempImage.rows / 2));
			cout << "Base on resize reduce the double" << endl;
			break;
		}
		imshow("Window", g_dstImage);
		g_tempImage = g_dstImage;
	}

	return 0;
}