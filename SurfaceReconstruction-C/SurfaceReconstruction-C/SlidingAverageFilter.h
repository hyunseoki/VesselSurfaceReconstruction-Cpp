#pragma once

#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;

using std::vector;

namespace SlidingAverageFilter
{
	vector<vector<double>> SlidingAverageFilter(vector<vector<double>> &points);
	vector<vector<double>> RecursiveSlidingAverageFilter(vector<vector<double>> &points);
	vector<vector<double>> SlidingAverageFilterSub(vector<vector<double>> &points, double thres);
	double calDiff(vector<vector<double>> &points1, vector<vector<double>> &points2);
}