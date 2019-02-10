#include <iostream>
#include "opencv2\highgui.hpp"
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

Mat srcImg, rotMat, dstImg;

//初始化參數
int rotationAngle = 30;
int scale = 1;

void rotationDemo(int, void*);
Point2f center;

String WindowName = "Image Rotate";
String trackbarRotateAngle = "Rotation Angle";
String trackbarScale = "Image Scale";

int main(void) {

	srcImg = imread("../../data/images/sample.jpg", IMREAD_COLOR);
	imshow("Source Image", srcImg);

	//影像中心位置
	center = Point2f(srcImg.cols / 2, srcImg.rows / 2);
	cout << "image size" << srcImg.cols << "," << srcImg.rows << endl;
	cout << "image center:" << center << endl;

	namedWindow(WindowName);
	//創建滑動軸
	createTrackbar(trackbarRotateAngle, WindowName, &rotationAngle, 360, rotationDemo);
	createTrackbar(trackbarScale, WindowName, &scale, 5, rotationDemo);

	rotationDemo(0, 0);

	waitKey(0);
}

void rotationDemo(int, void *)
{
	/*
	仿射變換(warpAffine):
	OpenCV提供getAffineTransform()和getRotationMatrix2D()函式，
	getAffineTransform()透過變換前後三個點來得到目標矩陣，
	getRotationMatrix2D()透過旋轉中心、旋轉角度和放大倍率來得到目標矩陣。
	*/
	//取得旋轉矩陣
	rotMat = getRotationMatrix2D(center, rotationAngle, scale);

	//仿射變換(warpAffine)
	warpAffine(srcImg, dstImg, rotMat, Size(srcImg.cols, srcImg.rows));
	//顯示旋轉角度
	putText(dstImg, "Angle:" + to_string((int)rotationAngle),
		center, 1, 3, Scalar(255, 255, 0), 1, CV_AA);

	imshow(WindowName, dstImg);
}
