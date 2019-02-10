#include <iostream>
#include "opencv2\highgui.hpp"
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

Mat srcImg, rotMat, dstImg;

//��l�ưѼ�
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

	//�v�����ߦ�m
	center = Point2f(srcImg.cols / 2, srcImg.rows / 2);
	cout << "image size" << srcImg.cols << "," << srcImg.rows << endl;
	cout << "image center:" << center << endl;

	namedWindow(WindowName);
	//�Ыطưʶb
	createTrackbar(trackbarRotateAngle, WindowName, &rotationAngle, 360, rotationDemo);
	createTrackbar(trackbarScale, WindowName, &scale, 5, rotationDemo);

	rotationDemo(0, 0);

	waitKey(0);
}

void rotationDemo(int, void *)
{
	/*
	��g�ܴ�(warpAffine):
	OpenCV����getAffineTransform()�MgetRotationMatrix2D()�禡�A
	getAffineTransform()�z�L�ܴ��e��T���I�ӱo��ؼЯx�}�A
	getRotationMatrix2D()�z�L���त�ߡB���ਤ�שM��j���v�ӱo��ؼЯx�}�C
	*/
	//���o����x�}
	rotMat = getRotationMatrix2D(center, rotationAngle, scale);

	//��g�ܴ�(warpAffine)
	warpAffine(srcImg, dstImg, rotMat, Size(srcImg.cols, srcImg.rows));
	//��ܱ��ਤ��
	putText(dstImg, "Angle:" + to_string((int)rotationAngle),
		center, 1, 3, Scalar(255, 255, 0), 1, CV_AA);

	imshow(WindowName, dstImg);
}
