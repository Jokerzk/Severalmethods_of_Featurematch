#ifndef _FREAK_ALG_H_
#define _FREAK_ALG_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>
#include <vector>
#include <time.h>

using namespace cv;
using namespace std;

int FREAK_Algorithm(cv::Mat imgA, cv::Mat imgB);

#endif
