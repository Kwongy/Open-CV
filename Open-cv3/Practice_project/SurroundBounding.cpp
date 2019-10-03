#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "Artwork picture"
#define WINDOW_NAME2 "Effect picture"

Mat g_srcImage, g_grayImage;
RNG g_rng(12345);
int g_nThresh = 50, g_nMaxThresh = 255;

void on_ContoursChange(int, void*) {
	Mat threshold_out;
	vector<vector<Point> >contours;
	vector<Vec4i> hierarchy;
	threshold(g_grayImage, threshold_out, g_nThresh, 255, THRESH_BINARY);

	findContours(threshold_out, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f> center(contours.size());
	vector<float> radius(contours.size());

	for (unsigned int i = 0; i < contours.size(); ++i) {
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
		minEnclosingCircle(contours_poly[i], center[i], radius[i]);
	}

	Mat drawing = Mat::zeros(threshold_out.size(), CV_8UC3);
	
	for (unsigned int i = 0; i < contours.size(); ++i) {
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);

		namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
		imshow(WINDOW_NAME2, drawing);
	}

}

int main() {
	system("color 1A");
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	createTrackbar("Thresh", WINDOW_NAME1, &g_nThresh, g_nMaxThresh, on_ContoursChange);
	on_ContoursChange(0, 0);
	waitKey(0);

	return 0;
}