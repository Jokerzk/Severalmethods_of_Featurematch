#include "SURF_ALG.h"

int SURF_Algorithm(cv::Mat imgA, cv::Mat imgB)
{
	SURF surf;
	vector<KeyPoint> keyPointsA, keyPointsB;
	Mat descriptorsA, descriptorsB;
	//surf.hessianThreshold = 1000.0f;


	double tstart = clock();
	surf(imgA, Mat(), keyPointsA, descriptorsA);
	surf(imgB, Mat(), keyPointsB, descriptorsB);

	cout << surf.hessianThreshold << endl;
	//--Get discriptors of imgs
	
	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptorsA, descriptorsB, matches);
	//--Return the minimum distances of pairs
	double  tstop = clock();
	cout << "SURF getdescriptorstime [s]: " << tstop - tstart << endl;

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
	vector<DMatch> good_matches;
	for (int i = 0; i<descriptorsA.rows; i++)
	{
		if (matches[i].distance < 0.2*max_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_matches;
	drawMatches(imgA, keyPointsA, imgB, keyPointsB,
		matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	cv::imshow("SURF_match", img_matches);
	waitKey();
	return 0;
	
}