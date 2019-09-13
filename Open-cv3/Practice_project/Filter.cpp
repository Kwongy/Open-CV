#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>

using namespace std;
using namespace cv;

Mat g_srcImg, g_dstImg1, g_dstImg2, g_dstImg3;
int g_nBoxFilterValue = 3;
int g_nMeanBlurValue = 3;
int g_nGaussianBlurValue = 3;

static void on_BoxFilter(int, void *) {
	boxFilter(g_srcImg, g_dstImg1, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1));
	imshow("Box Filter", g_dstImg1);
}

static void on_MeanBlur(int, void *) {
	blur(g_srcImg, g_dstImg2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1), Point(-1, -1));
	imshow("Mean Blur", g_dstImg2);
}

static void on_GaussianBlur(int, void *) {
	GaussianBlur(g_srcImg, g_dstImg3, Size(g_nGaussianBlurValue * 2 + 1, g_nGaussianBlurValue * 2 + 1),0 ,0);
	imshow("Gaussian Blur", g_dstImg3);
}

int main() {
	// color
	system("color5E");
	// read image
	g_srcImg = imread("C:\\Users\\kwong\\Pictures\\girl.jpg", 1);
	if (!g_srcImg.data) {
		printf("Image reading error!\n");
		return -1;
	}
	namedWindow("Artwork Master");
	imshow("Artwork Master", g_srcImg);

	// ----- Box Filter
	namedWindow("Box Filter");
	createTrackbar("Value:", "Box Filter", &g_nBoxFilterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);

	// ----- Mean Filter
	namedWindow("Mean Blur");
	createTrackbar("Value:", "Mean Blur", &g_nMeanBlurValue, 40, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);

	// ----- Gaussian Filter
	namedWindow("Gaussian Blur");
	createTrackbar("Value:", "Gaussian Blur", &g_nGaussianBlurValue, 40, on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue, 0);

	while (waitKey(1) != 27) {}

	//Mat img = imread("C:\\Users\\kwong\\Pictures\\girl.jpg");
	//namedWindow("Artwork Master");
	//imshow("Artwork Master", img);
	//Mat out;
	//boxFilter(img, out, -1, Size(5, 5));
	//namedWindow("Mean Filter");
	//imshow("Mean Filter", out);
	//blur(img, out, Size(7, 7));
	//namedWindow("Blur Filter");
	//imshow("Blur Filter", out);
	//GaussianBlur(img, out, Size(3, 3), 0, 0);
	//namedWindow("GaussianBlur Filter");
	//imshow("GaussianBlur Filter", out);
	//waitKey(0);

	return 0;
}
