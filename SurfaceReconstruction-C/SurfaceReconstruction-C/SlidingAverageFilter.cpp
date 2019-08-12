#include "pch.h"
#include "SlidingAverageFilter.h"

vector<vector<double>> SlidingAverageFilter::SlidingAverageFilter(vector<vector<double>>& points)
{
	size_t length = points.size();
	vector<vector<double>> result;
	vector<double> point(3, 0.0);

	size_t i = 0;
	result.push_back(points[i]);

	for (i = 1; i < length-1; i++)
	{
		point[0] = (result[i - 1][0] + points[i][0] * 2 + points[i+1][0]) / 4;
		point[1] = (result[i - 1][1] + points[i][1] * 2 + points[i+1][1]) / 4;
		point[2] = (result[i - 1][2] + points[i][2] * 2 + points[i+1][2]) / 4;
		result.push_back(point);
	}

	result.push_back(points[i]);

	return result;
}

vector<vector<double>> SlidingAverageFilter::RecursiveSlidingAverageFilter(vector<vector<double>>& points)
{
	vector<vector<double>> result = SlidingAverageFilter(points);

	double diff = calDiff(points, result);

	result = SlidingAverageFilterSub(result, diff);

	return result;
}

vector<vector<double>> SlidingAverageFilter::SlidingAverageFilterSub(vector<vector<double>>& points, double diff)
{
	vector<vector<double>> result = SlidingAverageFilter(points);
	
	double newDiff = calDiff(points, result);

	if ((diff - newDiff) / diff > 0.04)
	{
		result = SlidingAverageFilterSub(result, newDiff);
	}

	return result;
}

double SlidingAverageFilter::calDiff(vector<vector<double>>& points1, vector<vector<double>>& points2)
{
	size_t length = points1.size();
	vector<double> xDiff(length, 0.0);
	vector<double> yDiff(length, 0.0);
	vector<double> zDiff(length, 0.0);

	for (size_t i = 0; i < length; i++)
	{
		xDiff[i] = abs(points1[i][0] - points2[i][0]);
		yDiff[i] = abs(points1[i][1] - points2[i][1]);
		zDiff[i] = abs(points1[i][2] - points2[i][2]);
	}

	double xMax = * ( std::max_element(xDiff.begin(), xDiff.end()) );
	double yMax = * ( std::max_element(yDiff.begin(), yDiff.end()) );
	double zMax = * ( std::max_element(zDiff.begin(), zDiff.end()) );

	return std::max({ xMax, yMax, zMax });
}
