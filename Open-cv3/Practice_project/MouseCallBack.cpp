#include<opencv2/opencv.hpp>
using namespace cv;
#define WINDOW_NAME "Windows"

Rect g_rectangle;
bool g_isdraw = false;
RNG g_rng(12345);

//draw rectangle

void DrawRectangle(cv::Mat& img, cv::Rect box) {
	rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}

// mouse call back

void on_Mouse(int event, int x, int y, int flags, void * param) {
	Mat & image = *(cv::Mat *)param;
	switch (event) {
		//mouse move
		case EVENT_MOUSEMOVE: {
			if (g_isdraw) {
				g_rectangle.width = x - g_rectangle.x;
				g_rectangle.height = y - g_rectangle.y;

			}
		}
		break;
		//mouse down
		case EVENT_LBUTTONDOWN: {
			g_isdraw = true;
			g_rectangle = Rect(x, y, 0, 0);
		}
		break;
		//mouse up
		case EVENT_LBUTTONUP: {
			g_isdraw = false;
			if (g_rectangle.width < 0) {
				g_rectangle.x += g_rectangle.width;
				g_rectangle.width *= -1;
			}
			if (g_rectangle.height < 0) {
				g_rectangle.y += g_rectangle.height;
				g_rectangle.height *= -1;
			}
			DrawRectangle(image, g_rectangle);
		}
	}
}

int main() {
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat img(600, 800, CV_8UC3), tempImage;
	img.copyTo(tempImage);
	g_rectangle = Rect(-1, -1, 0, 0);
	img = Scalar::all(0);

	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_Mouse, (void *)&img);

	while (true) {
		img.copyTo(tempImage);
		if (g_isdraw) DrawRectangle(tempImage, g_rectangle);
		imshow(WINDOW_NAME, tempImage);
		//keyboard input is ESC, break
		if (waitKey(10) == 27) break;   
	}
	return 0;
}