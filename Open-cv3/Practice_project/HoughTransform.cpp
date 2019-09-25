#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat g_srcImage, g_midImage, g_dstImage;
vector<Vec4i> g_lines;
int g_nthreshold = 100;

static void on_HoughLines(int, void*) {
	Mat dstImage = g_dstImage.clone();
	Mat midImage = g_midImage.clone();

	vector<Vec4i> mylines;

	HoughLinesP(midImage, mylines, 1, CV_PI / 180, g_nthreshold + 1, 50, 10);

	for (size_t i = 0; i < mylines.size(); i++) {
		Vec4i l = mylines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 180, 55), 1, LINE_AA);
		
		imshow("Effect Picture", dstImage);
	}
}

int main() {
	system("color 3F");
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}

	imshow("Artwork Master", g_srcImage);
	namedWindow("Effect Picture", 1);
	createTrackbar("Value", "Effect Picture", &g_nthreshold, 200, on_HoughLines);

	Canny(g_srcImage, g_midImage, 50, 200, 3);
	cvtColor(g_midImage, g_dstImage, COLOR_GRAY2BGR);
	
	on_HoughLines(g_nthreshold, 0);
	HoughLinesP(g_midImage, g_lines, 1, CV_PI / 180, 80, 50, 10);
	imshow("Effect Picture", g_dstImage);

	waitKey(0);
	return 0;
}