#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <cstddef>        // std::size_t
#include <stdlib.h>
//#include <sys/resource.h>
//#include <bits/stdc++.h>
#include "parallel.hpp"
#include "auxiliary.hpp"
using namespace std;
void printOneDimensionalArray(vector<int>& arr);


  	
template<int N>
void findNumberOfTrianglesV1(int pinax[][N]){
	vector<int> c3(N,0);
	int totalTrinagles =0;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			for(int k=0; k<N; k++){
				if ((pinax[i][j]==1)&&(pinax[j][k]==1)&&(pinax[k][i]==1)&&(i!=k)&&(i!=j)&&(j!=k)){
					c3[i] ++;
					c3[j] ++;
					c3[k] ++;
				}
			}
		}

	}
	for (int i=0; i<N; i++){
		c3[i] /=6;
		totalTrinagles += c3[i];
	}
	printOneDimensionalArray(c3);
}

void findNumberOfTrianglesV2(vector<vector<int>>& pinax){
	int N = pinax.size();
	vector<int> c3(N,0);
	int totalTrinagles =0;
	for(int i=0; i<N; i++){
		//cout<<"I is : "<<i<<endl;
		for(int j=i; j<N; j++){
			for(int k=j; k<N; k++){
				
				if (((pinax[i][j]==1)&&(pinax[j][k]==1)&&(pinax[k][i]==1))&&(pinax[k][i]==1)&&(i!=k)&&(i!=j)&&(j!=k)){
					c3[i] ++;
					c3[j] ++;
					c3[k] ++;
				}
			}
		}

	}
	for (int i=0; i<N; i++){
		
		totalTrinagles += c3[i];
	}
	printOneDimensionalArray(c3);
}

/*void findNumberOfTrianglesV3(vector<int>& arr1, vector<int>& arr2){
	int n = arr1.size();
	vector<int> c3(n-1,0);
	for (int i=0; i<n-1; i++){
		int dif1 = arr1[i+1] - arr1[i];
		if(dif1>0){
			vector<int> col1(sliceArray(arr2, arr1[i], arr1[i+1]));
			for(int j =0; j < dif1; j++){
				int dif2 = arr1[col1[j]+1]-arr1[col1[j]];
				if(dif2>0){
					vector<int> col2(sliceArray(arr2, arr1[col1[j]], arr1[col1[j]+1]));
					for(int k=0; k<dif2; k++){
						int dif3 = arr1[col2[k]+1]-arr1[col2[k]];
						if(dif3>0){
							vector<int> col3(sliceArray(arr2, arr1[col2[k]], arr1[col2[k]+1]));
							for(int l=0; l<dif3; l++){
								if(col3[l]==i){
									c3[i]++;
								}
							}
						}
					}
				}
			}
		}
	}
	for (int i  =0; i<n-1; i++){
		c3[i] /=2;
	}
	printOneDimensionalArray(c3);
}*/

void findNumberOfTrianglesV3(const vector<int> & arr1, const vector<int> & arr2){
	int n = arr1.size();
	vector<int> c3(n-1,0);
	for(int i =0; i<(n-1) ; i++){
		int dif1 =  arr1[i+1] -arr1[i];
		//if(i%5000==0)
		//	cout<<i<<endl;
		if(dif1){
			for(int j =0;  j<dif1; j++){
				int column1 = arr2[j+arr1[i]];
				if(column1<=i){
					continue;
				}
				int dif2 = arr1[column1 + 1]  - arr1[column1];
				if(dif2>0){
					for(int k =0; k<dif2; k++){
						int column2 = arr2[arr1[column1] + k];
						if(column2<=column1){
							continue;
						}
						int dif3  = arr1[column2+1] - arr1[column2];
						if(dif3>0){
							for (int l =0; l<dif3; l++){
								int column3 = arr2[arr1[column2]+l];
								if(column3>i)
									break;
								if(column3==i&&column1!=i&&column2!=i&& column1!=column2){
									
									c3[i]++;
									c3[column2]++;
									c3[column1]++;
									break;
								}
							}
						}
					}
				} 
			}
		}
	}
	printOneDimensionalArray(c3);
}


/*void findNumberOfTrianglesV4(vector<int>& arr1, vector<int>& arr2){
	int n = arr1.size();
	vector<int> arr1R;
	vector<int> values;
	int rowCounter =0;
	vector<int> c3(n-1, 0);
	arr1R.push_back(0);

	for (int i =0; i<(n-1); i++){
		cout<<i<<endl;
		int dif = arr1[i+1]-arr1[i];
		if(dif >0){
			
			vector <int> col1(sliceArray(arr2, arr1[i], arr1[i+1]));
			//cout<<"this is the col1"<<endl;
			//printOneDimensionalArray(col1);
			int notZeros1 = col1.size();
			for (int j=0; j<notZeros1; j++){
				int dif2 = arr1[col1[j]+1] - arr1[col1[j]];
				if(dif2>0){
					
					vector<int> col2(sliceArray(arr2, arr1[col1[j]], arr1[col1[j]+1]));
					//cout<<"this is the col2"<<endl;
					//printOneDimensionalArray(col2);
					
					int val = intersection(col1, col2);
					//cout<<"and this is the val "<<val<<endl;
					
					if(val>0){
						values.push_back(val);
						rowCounter++;
					}
				}
			}
		}
	arr1R.push_back(rowCounter);
	}
	//cout<<"This is the val "<<endl;
	//printOneDimensionalArray(values);
	//cout<<"and this is the arr1R "<<endl;
	//printOneDimensionalArray(arr1R);
	for (int i=0; i<(n-1); i++){
		int dif = arr1R[i+1] -arr1R[i];
		int tmpSum =0;
		for (int j =0; j<dif; j++){
			tmpSum += values[j + arr1R[i]];
		}
		c3[i] = tmpSum/2;
	}
	printOneDimensionalArray(c3);
}*/
void findNumberOfTrianglesV4(const vector<int>& arr1, const vector<int>& arr2){
	const int n = arr1.size();
	
	vector<int> c3(n-1, 0);
	

	for (int i =0; i<(n-1); i++){
		
		if(i>0){
			c3[i-1] = c3[i-1]/2;
		}
		const int dif = arr1[i+1]-arr1[i];
		if(dif >0){
			
			
			for (int j=0; j<dif; j++){
				int column = arr2[arr1[i]+j];
				if(column<=i ){
					continue;
				}
				const int dif2 = arr1[column+1] - arr1[column];
				if(dif2>0){
					
					
					const int  val = intersection(arr1[i], arr1[i+1], arr1[column], arr1[column+1],i,column, arr2);
					
					if(val>0){
						c3[i]+=val;
						c3[column]+=val;
						
						
					}
				}
			}
		}
		
	
	}
	c3[n-2] /=2;
	
	printOneDimensionalArray(c3);
	
}
int main(){
	/*const rlim_t kStackSize = 32 * 1024 * 1024;   //32 ΜΒ
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);

    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }*/
	int arr[10][10]  = {{0, 1 ,0 ,1 ,0 ,0, 1, 1, 0, 1},
 						{1 ,0 ,1 ,0 ,1 ,1 ,0 ,1 ,1 ,1},
 						{0 ,1 ,1 ,1 ,0 ,1 ,1 ,0 ,0 ,0},
 						{1 ,0 ,1 ,0 ,1 ,1 ,0 ,0 ,1 ,0},
 						{0 ,1 ,0 ,1 ,1 ,1 ,1 ,0 ,1 ,1},
 						{0 ,1 ,1 ,1 ,1 ,0 ,0 ,1 ,1 ,0},
 						{1 ,0 ,1 ,0 ,1 ,0 ,0 ,1 ,1 ,0},
 						{1 ,1 ,0 ,0 ,0 ,1 ,1 ,0 ,1, 1},
 						{0 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,0, 1},
 						{1 ,1 ,0 ,0 ,1 ,0 ,0 ,1 ,1, 0}};
 int arr2[3][3] = {{0,1,1},{1,0,1},{1,1,1}};
 vector<int>  howManyNonZeroElementsPerLine  =  {0 , 5, 12, 16, 21, 27, 33, 38, 44, 51, 56};
 vector<int> columnIndices = {1, 3, 6, 7, 9, 0, 2, 4, 5, 7, 8, 9, 1, 3, 5, 6, 0, 2, 4, 5, 8, 1, 3, 5, 6, 8, 9, 1, 2, 3, 4, 7, 8, 0, 2, 4, 7, 8, 0, 1, 5, 6, 8, 9, 1, 3, 4, 5, 6, 7, 9, 0, 1, 4, 7, 8};


	//std::cout<<howManyNonZeroElementsPerLine[12]<<std::endl;
	
int smallArr[3][3] = {{0,1,1},
				{1,0,1},
				{1,1,0}};
int g12Arr[12][12] = {{0,1,0,1,0,1,1,0,0,0,0,0},
					  {0,0,1,0,1,1,0,1,0,0,1,1},
					  {0,0,0,1,0,0,0,0,0,0,1,1},
					  {0,0,0,0,0,0,1,0,0,0,0,0},
					  {0,0,0,0,0,1,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,1,1,0,0},
					  {0,0,0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0,0,1},
					  {0,0,0,0,0,0,0,0,0,0,0,0}};


//findNumberOfTrianglesV1<10>(arr);
//findNumberOfTrianglesV2<10>(arr);
//findNumberOfTrianglesV3(howManyNonZeroElementsPerLine, columnIndices);
vector<int> v = {1,5,3,6,9}, v1 = {2,8,9,6,7};
//findNumberOfTrianglesV4(howManyNonZeroElementsPerLine, columnIndices);
vector<vector<int>> vv(importFromFile("pinakes/biggerG.mtx"));
//vector<vector<int>> va(importFromFileToFullSize("pinakes/G12.mtx"));
//printTwoDimensionalArray(va);
//cout<<""<<endl;
//findNumberOfTrianglesV2(va);
//cout<<"The size of the difference is "<<vv[0].size()<<endl;
//cout<<"The size of arr2 "<<vv[1].size()<<endl;
//printOneDimensionalArray(vv[0]);
//printOneDimensionalArray(vv[1]);
cout<<" Now the stuff"<<endl;
auto start = std::chrono::high_resolution_clock::now();
findNumberOfTrianglesV3pThreads(vv[0],vv[1]);
//exportToFile("pinakes/myGiannisG.mtx", 0.15, 10000);
auto stop = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
cout<<" Duration is "<< duration.count()/1000000.f<<" sec"<<endl;
cout<<" "<<endl;


	return 0;
}

