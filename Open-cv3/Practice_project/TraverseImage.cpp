#include<opencv.hpp>
#include<iostream>
#include<vector>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;
#define WINDOW_NAME "Image"
#define WINDOW_EFFECT_NAME "Effect Image"
char url[] = "F:\\VscodeWorkspace\\Latex\\pic.png";
/*
	访问图片中像素的方法有三种:
	1, 指针访问
	2. 迭代器iterator
	3, 动态地址计算
*/
Mat Img = imread(url);
void colorReduce1(Mat &outImg, int div) {
	outImg = Img.clone();
	int rowNumber = outImg.rows;
	int colNumber = outImg.cols * outImg.channels();

	for (int i = 0; i < rowNumber; ++i) {
		uchar* data = outImg.ptr<uchar>(i);
		for (int j = 0; j < colNumber; j++)
		{
			data[j] = data[j] / div * div + div / 2;
		}
	}
}
void colorReduce2(Mat &outImg, int div) {
	outImg = Img.clone();
	int channelNumber = outImg.channels();
	Mat_<Vec3b>::iterator it = outImg.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = outImg.end<Vec3b>();
	for (; it != itend; it++) {
		for (int i = 0; i < channelNumber; i++)
		{
			(*it)[i] = (*it)[i] / div * div + div / 2;
		}
	}
}
void colorReduce3(Mat &outImg, int div) {
	outImg = Img.clone();
	int rowNumber = outImg.rows;
	int colNumber = outImg.cols;
	int channelNumber = outImg.channels();
	for (int i = 0; i < rowNumber; ++i) {
		for (int j = 0; j < colNumber; j++)
		{
			for (int k = 0; k < channelNumber; k++)
			{
				outImg.at<Vec3b>(i, j)[k] = outImg.at<Vec3b>(i, j)[k] / div * div + div / 2;
			}
		}
	}
}
int main() {
	imshow(WINDOW_NAME, Img);
	waitKey(0);
	for (int i = 1; i < 4; i++)
	{
		Mat dstImg;
		dstImg.create(Img.rows, Img.cols, Img.type());
		double time0 = static_cast<double>(getTickCount());
		if (i == 1){
			colorReduce1(dstImg, 32);
		}
		else if(i == 2){	
			colorReduce2(dstImg, 32);
		}
		else {
			colorReduce3(dstImg, 32);
		}
		time0 = ((double)getTickCount() - time0) / getTickFrequency();
		cout << "The "<< i << " time performance period is " << time0 << endl;
		imshow(WINDOW_EFFECT_NAME, dstImg);
		waitKey(0);
		/*
		The 1 time performance period is 0.00237862
		The 2 time performance period is 0.0902927
		The 3 time performance period is 0.0846642
		*/
	}
	return 0;
}