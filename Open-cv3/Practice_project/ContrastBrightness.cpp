#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;
#define WINDOW_NAME "Image"
int g_constrastValue;
int g_brightnessValue;
Mat Img, dstImg;
int width, heigh, channel;
char url[] = "F:\\VscodeWorkspace\\Latex\\pic.png";

static void on_ContrastAndBright(int, void *) {
	for (int i = 0; i < heigh; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < channel; k++) {
				dstImg.at<Vec3b>(i, j)[k] = saturate_cast<uchar>((g_constrastValue * 0.01) * Img.at<Vec3b>(i, j)[k] + g_brightnessValue);
			}
		}
	}
	imshow(WINDOW_NAME, dstImg);
}

int main() {
	Img = imread(url);
	if (!Img.data) {
		printf("Read error!");
		return -1;
	}
	dstImg = Mat::zeros(Img.size(), Img.type());
	width = dstImg.cols;
	heigh = dstImg.rows;
	channel = dstImg.channels();
	g_constrastValue = 80;
	g_brightnessValue = 80;
	namedWindow(WINDOW_NAME, 1);
	createTrackbar("Constrast: ", WINDOW_NAME, &g_constrastValue, 300, on_ContrastAndBright);
	createTrackbar("Bright: ", WINDOW_NAME, &g_brightnessValue, 200, on_ContrastAndBright);
	
	on_ContrastAndBright(g_constrastValue, 0);
	on_ContrastAndBright(g_brightnessValue, 0);

	while (true) {
		// keyboard input is ESC, then break
		if (waitKey(10) == 27) break;
	}
	return 0;
}