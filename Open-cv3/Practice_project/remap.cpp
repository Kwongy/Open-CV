#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


Mat g_srcImage, g_dstImage, g_mapX, g_mapY;

int update_map(int key) {
	for (int j = 0; j < g_srcImage.rows; ++j) {
		for (int i = 0; i < g_srcImage.cols; ++i) {
			switch (key)
			{
			case '1':
				if (i > g_srcImage.cols * .25 && i < g_srcImage.cols * .75
					&& j > g_srcImage.rows * .25 && j < g_srcImage.rows * .75) {
					g_mapX.at<float>(j, i) = static_cast<float>(2 * (i - g_srcImage.cols * .25) + .5);
					g_mapY.at<float>(j, i) = static_cast<float>(2 * (j - g_srcImage.rows * .25) + .5);
				}
				else {
					g_mapX.at<float>(j, i) = g_mapY.at<float>(j, i) = 0;
				}
				break;
			case '2':
				g_mapX.at<float>(j, i) = static_cast<float>(i);
				g_mapY.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
				break;
			case '3':
				g_mapX.at<float>(j, i) = static_cast<float>(g_srcImage.cols - i);
				g_mapY.at<float>(j, i) = static_cast<float>(j);
				break;
			case '4':
				g_mapX.at<float>(j, i) = static_cast<float>(g_srcImage.cols - i);
				g_mapY.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
				break;
			}
		}
	}
	return 1;
}

int main() {
	system("color 2F");
	g_srcImage = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImage.data) {
		cout << "Image reading error!" << endl;
		return false;
	}
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());
	g_mapX.create(g_srcImage.size(), CV_32FC1);
	g_mapY.create(g_srcImage.size(), CV_32FC1);
	namedWindow("Window", WINDOW_AUTOSIZE);
	imshow("Window", g_srcImage);

	while (true) {
		int key = waitKey(0);
		if (key == 27) break;
		update_map(key);
		remap(g_srcImage, g_dstImage, g_mapX, g_mapY, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
		imshow("Window", g_dstImage);
	}

	return 0;
}