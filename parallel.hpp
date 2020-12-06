#ifndef PARALLEL
#define PARALLEL
#define NUM_OF_THREADS 2
#include <vector>
#include "cilk.h"
#include <pthread.h>
#include <queue>
#include <omp.h>
using namespace std;



struct Args2{
	vector<int> *c3;
	vector<vector<int>> *val;
};

struct Args3{
	vector<int> *ar1;
	vector<int> *ar2;
	vector<int> *c3;
};
void findNumberOfTrianglesV4openMP(vector<int>& arr1, vector<int>& arr2);
void findNumberOfTrianglesV4Cilk(vector<int>& arr1, vector<int>& arr2);
void* v4pThreadFunction1(void* args);
void findNumberOfTrianglesV4pThreads(vector<int>& arr1, vector<int>& arr2);
void* v4pThreadFunction2(void* args);
void findNumberOfTrianglesV3openMP(vector<int>& arr1, vector<int>& arr2);
void findNumberOfTrianglesV3Cilk(vector<int>& arr1, vector<int>& arr2);
void* v3pThreadFunction2(void* args);
void* v3pThreadFunction1(void* args);
void findNumberOfTrianglesV3pThreads(vector<int>& arr1, vector<int>& arr2);
#endif
