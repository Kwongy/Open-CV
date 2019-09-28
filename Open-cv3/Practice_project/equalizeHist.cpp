#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage;

int main() {
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}
	cvtColor(g_srcImage, g_srcImage, COLOR_BGR2GRAY);
	imshow("Artwork Picture", g_srcImage);

	equalizeHist(g_srcImage, g_dstImage);
	imshow("After equlizeHist", g_dstImage);

	waitKey(0);

	return 0;
}