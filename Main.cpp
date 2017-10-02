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

	//求取矩阵旋转角度，内参忽略，无深度。基础矩阵，本质矩阵
	//本质矩阵：在相机坐标系下描述的归一化的图像坐标的矩阵约束，矩阵维度：3X3，秩为2，仅依赖于外部参数即旋转角度和平移位移。
	          //可用来估计两个相机的相对位置，当给定一侧图像上的一个点，被本质矩阵相乘可得到另一侧图像上的的对极线，可缩小对应点的搜索范围，可用于求解旋转和平移矩阵。

	//内参矩阵：描述像素坐标（基本矩阵相关）和归一化的图像坐标（本质矩阵相关）之间关系的矩阵，由焦距F和图像中心与图像和光轴交点的偏差量决定。

	//基本矩阵：前提是左右图像的光心位置不一样，在像素坐标系下描述，须考虑相机内部参数。可用于3D重建和特征匹配，与场景无关，可由场景中的点在图像中的对应关系计算，进而可求出外参。
}
