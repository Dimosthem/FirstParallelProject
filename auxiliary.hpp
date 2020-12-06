#ifndef AUXILARY
#define AUXILARY
#include <array>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <cstddef>        // std::size_t
#include <stdlib.h>
#include<iostream>
//#include <sys/resource.h>
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> importFromFile(string fileName);
vector<int> sliceArray(vector<int>& arr, int x, int y);
//int intersection(vector<int> & a , vector<int>& b );
int intersection(const int &startA, const int &endA , const int &startB, const int &endB , const int& i , const int &j,const vector<int>& arr2);
void printOneDimensionalArray(vector<int>& arr);
void exportToFile(string fileName, float densityPercentage, int dimension);
vector<vector<int>> importFromFileToFullSize(string fileName);
void printTwoDimensionalArray(vector<vector<int>>& vec);


#endif 