#include<stdio.h>
#include <opencv2/opencv.hpp>

#include "SIFT_ALG.h"
#include "SURF_ALG.h"
#include "ORB_ALG.h"
#include "BRISK_ALG.h"
#include "FREAK_ALG.h"


#define ALGORITHM 3
using namespace std;
using namespace cv;

void pic_read()
{
	string string_left = "C:\\Users\\A17061.AUTELSZ\\Desktop\\300meters obstacleavoiding\\stereo pic\\seq00\\seq00-left";
	string string_right = "C:\\Users\\A17061.AUTELSZ\\Desktop\\300meters obstacleavoiding\\stereo pic\\seq00\\seq00-right";
	cv::Mat img_left, img_right;
	for (int i = 0; i < 10000; i++)
	{
		char filename_left[256], filename_right[256];
		if (i<10)
		{
			sprintf(filename_left, "%s\\image_0000000%d_0.png", string_left.c_str(), i);
			sprintf(filename_right, "%s\\image_0000000%d_1.png", string_right.c_str(), i);
		}
		else if (i<100)
		{
			sprintf(filename_left, "%s\\image_000000%d_0.png", string_left.c_str(), i);
			sprintf(filename_right, "%s\\image_000000%d_1.png", string_right.c_str(), i);
		}
		else if (i<1000)
		{
			sprintf(filename_left, "%s\\image_00000%d_0.png", string_left.c_str(), i);
			sprintf(filename_right, "%s\\image_00000%d_1.png", string_right.c_str(), i);
		}
		else
		{
			sprintf(filename_left, "%s\\image_0000%d_0.png", string_left.c_str(), i);
			sprintf(filename_right, "%s\\image_0000%d_1.png", string_right.c_str(), i);
		}
		img_left = imread(filename_left);
		img_right = imread(filename_right);
		
		if (!img_left.empty())
		{
			//ORB_Algorithm(img_left, img_right);
			cv::imshow("img_left", img_left);
			cv::imshow("img_right", img_right);
			waitKey(-1);
		}
		else
		{
			return;
		}
	}
}

int main(void)
{

	pic_read();
	cv::Mat imgA = imread("3.jpg");
	cv::Mat imgB = imread("3.3.jpg");
	if (ALGORITHM == 1) return SIFT_Algorithm(imgA, imgB);//296
	if (ALGORITHM == 2) return SURF_Algorithm(imgA, imgB);//130
	if (ALGORITHM == 3) return ORB_Algorithm(imgA, imgB);//36
	if (ALGORITHM == 4) return BRISK_Algorithm(imgA, imgB);//25
	if (ALGORITHM == 5) return FREAK_Algorithm(imgA, imgB);//90

	//��ȡ������ת�Ƕȣ��ڲκ��ԣ�����ȡ��������󣬱��ʾ���
	//���ʾ������������ϵ�������Ĺ�һ����ͼ������ľ���Լ��������ά�ȣ�3X3����Ϊ2�����������ⲿ��������ת�ǶȺ�ƽ��λ�ơ�
	          //����������������������λ�ã�������һ��ͼ���ϵ�һ���㣬�����ʾ�����˿ɵõ���һ��ͼ���ϵĵĶԼ��ߣ�����С��Ӧ���������Χ�������������ת��ƽ�ƾ���

	//�ڲξ��������������꣨����������أ��͹�һ����ͼ�����꣨���ʾ�����أ�֮���ϵ�ľ����ɽ���F��ͼ��������ͼ��͹��ύ���ƫ����������

	//��������ǰ��������ͼ��Ĺ���λ�ò�һ��������������ϵ���������뿼������ڲ�������������3D�ؽ�������ƥ�䣬�볡���޹أ����ɳ����еĵ���ͼ���еĶ�Ӧ��ϵ���㣬�����������Ρ�
}
