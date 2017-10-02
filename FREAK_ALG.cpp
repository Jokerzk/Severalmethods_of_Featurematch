#include "FREAK_ALG.h"

int FREAK_Algorithm(cv::Mat imgA, cv::Mat imgB)
{
	vector<KeyPoint> keypointsA, keypointsB;
	Mat descriptorsA, descriptorsB;
	vector<DMatch> matches;

	//SiftFeatureDetector detector(2000, 4);
	//FastFeatureDetector detectorf;
	//detectorf.detect(imgA, keypointsA);
	BRISK briskdetector;
	FREAK freak;
	BruteForceMatcher<Hamming> matcher;

	int tstart = clock();
	briskdetector.detect(imgA, keypointsA);
	briskdetector.detect(imgB, keypointsB);
	
	freak.compute(imgA, keypointsA, descriptorsA);
	freak.compute(imgB, keypointsB, descriptorsB);
	

	// match
	// 	t = (double)getTickCount();
	matcher.match(descriptorsA, descriptorsB, matches);
	int tstop = clock();
	cout << "FREAK getdescriptorstime time [s]: " << tstop - tstart << endl;
	// 	t = ((double)getTickCount() - t)/getTickFrequency();
	// 	std::cout << "matching time [s]: " << t << std::endl;

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
	
	vector<DMatch> good_matches;
	for (int i = 0; i<descriptorsA.rows; i++)
	{
		if (matches[i].distance < 0.6*max_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}

	// Draw matches
	Mat imgMatch_Freak;
	drawMatches(imgA, keypointsA, imgB, keypointsB, matches, imgMatch_Freak,
		Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	cv::imshow("FREAK_match", imgMatch_Freak);
	waitKey();
	return 0;
}