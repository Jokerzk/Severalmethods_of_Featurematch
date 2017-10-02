#include "ORB_ALG.h"

int ORB_Algorithm(cv::Mat imgA, cv::Mat imgB)
{
	ORB orb;
	vector<KeyPoint> keyPointsA, keyPointsB;
	Mat descriptorsA, descriptorsB;
	double tstart = clock();
	orb(imgA, Mat(), keyPointsA, descriptorsA);
	orb(imgB, Mat(), keyPointsB, descriptorsB);
	drawKeypoints(imgA, keyPointsA, imgA, Scalar::all(-1));
	drawKeypoints(imgB, keyPointsB, imgB, Scalar::all(-1));
	cv::imshow("keypointsA", imgA);
	cv::imshow("keypointsB", imgB);
	waitKey();
	//--Get discriptors of imgs
	BruteForceMatcher<Hamming> matcher;
	vector<DMatch> matches;
	
	matcher.match(descriptorsA, descriptorsB, matches);
	//--Return the minimum distances of pairs
	double  tstop = clock();
	cout << "ORB getdescriptorstime [s]: " << tstop - tstart << endl;

	double max_dist = 0;
	double min_dist = 100;
	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i<descriptorsA.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	printf("-- Max dist : %f \n", max_dist);
	printf("-- Min dist : %f \n", min_dist);
	//-- Draw only "good" matches (i.e. whose distance is less than 0.6*max_dist )

	vector<int> queryIdxs(matches.size()), trainIdxs(matches.size());
	for (size_t i = 0; i < matches.size(); i++)
	{
		queryIdxs[i] = matches[i].queryIdx;
		trainIdxs[i] = matches[i].trainIdx;
	}

	Mat H12,H13;   //单应矩阵  
	vector<Point2f> points1; KeyPoint::convert(keyPointsA, points1, queryIdxs);
	vector<Point2f> points2; KeyPoint::convert(keyPointsB, points2, trainIdxs);
	int ransacReprojThreshold = 10;  //拒绝阈值  
	H12 = findHomography(Mat(points1), Mat(points2), CV_RANSAC, ransacReprojThreshold);//根据匹配点获得单应矩阵
	H13 = findFundamentalMat(Mat(points1), Mat(points2), FM_RANSAC);
	cout << H13 << endl;
	vector<DMatch> matchesMask;
	Mat points1t;
	perspectiveTransform(Mat(points1), points1t, H12);//利用单应矩阵透视变换得到图1中各点的MASK
	for (size_t i = 0; i < points1.size(); i++)  //保存‘内点’  
	{
		if (norm(points2[i] - points1t.at<Point2f>((int)i, 0)) <= ransacReprojThreshold) //当图2中之前找的匹配点与MASK的灰度值小于给定阈值时，标记为内点
		{
			matchesMask.push_back(matches[i]);
		}
	}
	Mat img_matches_ransac;
	drawMatches(imgA, keyPointsA, imgB, keyPointsB,
		matchesMask, img_matches_ransac, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	cv::imshow("ORB_match_ransac", img_matches_ransac);

	vector<DMatch> good_matches;
	for (int i = 0; i<descriptorsA.rows; i++)
	{
		if (matches[i].distance < 0.6*max_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_matches;
	drawMatches(imgA, keyPointsA, imgB, keyPointsB,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	cv::imshow("ORB_match", img_matches);
	cv::waitKey();
	return 0;
}