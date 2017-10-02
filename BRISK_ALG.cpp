#include "BRISK_ALG.h"

int BRISK_Algorithm(cv::Mat imgA, cv::Mat imgB)
{
	BRISK brisk;
	vector<KeyPoint> keyPointsA, keyPointsB;
	Mat descriptorsA, descriptorsB;


	double tstart = clock();
	brisk(imgA, Mat(), keyPointsA, descriptorsA);
	brisk(imgB, Mat(), keyPointsB, descriptorsB);
	

	BruteForceMatcher<Hamming> matcher;
	vector<DMatch> matches;
	matcher.match(descriptorsA, descriptorsB, matches);
	//--Return the minimum distances of pairs
	double  tstop = clock();
	cout << "BRISK getdescriptorstime [s]: " << tstop - tstart << endl;

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
		if (matches[i].distance < 0.6*max_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_matches;
	drawMatches(imgA, keyPointsA, imgB, keyPointsB,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	cv::imshow("BRISK_match", img_matches);
	waitKey();
	return 0;
}