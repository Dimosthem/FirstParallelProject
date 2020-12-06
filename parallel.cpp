#include "parallel.hpp"
#include "auxiliary.hpp"

using namespace std;
pthread_mutex_t row_mutex;
pthread_mutex_t c3_mutex;
queue<int> rows;
vector<int> pc3;
void findNumberOfTrianglesV4openMP(vector<int>& arr1, vector<int>& arr2){
	const int n = arr1.size();
	
	vector<int> c3(n-1, 0);
	
	#pragma omp parallel for
	for (int i =0; i<(n-1); i++){
		
		if(i>0){
			c3[i-1] = c3[i-1]/2;
		}
		const int dif = arr1[i+1]-arr1[i];
		if(dif >0){
			
			
			for (int j=0; j<dif; j++){
				int column = arr2[arr1[i]+j];
				if(column<=i){
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


void findNumberOfTrianglesV4Cilk(vector<int>& arr1, vector<int>& arr2){
	const int n = arr1.size();
	
	vector<int> c3(n-1, 0);
	
	
	cilk_for (int i =0; i<(n-1); i++){
		
		if(i>0){
			c3[i-1] = c3[i-1]/2;
		}
		const int dif = arr1[i+1]-arr1[i];
		if(dif >0){
			
			
			for (int j=0; j<dif; j++){
				int column = arr2[arr1[i]+j];
				if(column<=i){
					continue;
				}
				const int dif2 = arr1[column+1] - arr1[column];
				if(dif2>0){
					
					
					const int  val = intersection(arr1[i], arr1[i+1], arr1[column], arr1[column+1], i,column,arr2);
					
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

/*void findNumberOfTrianglesV4pThreads(vector<int>& arr1, vector<int>& arr2){
	int n = arr1.size();
	
	vector<vector<int>> values(n-1);
	
	vector<int> c3(n-1, 0);
	for (int i =0; i<(n-1); i++){
		rows.push(i);
	}
	Args1 args1;
	args1.ar1 = &arr1;
	args1.ar2 = &arr2;
	args1.val = &values;
	
	pthread_t threads[NUM_OF_THREADS];
	
	for(int i=0; i<NUM_OF_THREADS; i++){
		pthread_create(&threads[i], NULL, v4pThreadFunction1, &args1);
		
	}
	for(int i=0; i<NUM_OF_THREADS; i++){
		pthread_join(threads[i], NULL);
	}
	for (int i =0; i<(n-1); i++){
		rows.push(i);
	}

	Args2 args2;
	args2.c3 = &c3;
	args2.val = &values;
	for(int i=0; i<NUM_OF_THREADS; i++){
		pthread_create(&threads[i], NULL, v4pThreadFunction2, &args2);
		pthread_join(threads[i], NULL);
	}
	for(int i=0; i<NUM_OF_THREADS; i++){
		pthread_join(threads[i], NULL);
	}
	printOneDimensionalArray(c3);
}*/
void findNumberOfTrianglesV4pThreads(vector<int>& arr1, vector<int>& arr2){
	const int n = arr1.size();
	
	vector<int> c3(n-1, 0);
	pc3 =c3;
	Args3 args;
	args.ar1 = &arr1;
	args.ar2 = &arr2;
	
	pthread_t threads[NUM_OF_THREADS];
	for (int i =0; i<(n-1); i++){
		rows.push(i);
	}
	for (int i =0; i<NUM_OF_THREADS; i++){
		pthread_create(&threads[i], NULL, v4pThreadFunction1, &args);

	}
	for(int i=0; i<NUM_OF_THREADS; i++){
		pthread_join(threads[i], NULL);
	}
	for (int i =0; i<(n-1); i++){
		rows.push(i);
	}
	
	for (int i =0; i<NUM_OF_THREADS; i++){
		pthread_create(&threads[i], NULL, v4pThreadFunction2, &args);

	}
	for(int i=0; i<NUM_OF_THREADS; i++){
		pthread_join(threads[i], NULL);
	}
	printOneDimensionalArray(pc3);
}



void* v4pThreadFunction1(void* args){
	Args3 & arguments = *(static_cast<Args3*>(args));
	vector<int> &arr1 = *(arguments.ar1);

	vector<int> &arr2 =  *(arguments.ar2);
	
	
	
	while(true){
		int i=-1;
		pthread_mutex_lock (&row_mutex);

		if(rows.empty()){
			pthread_mutex_unlock (&row_mutex);
			return (void*)0;
		}
		i = rows.front();
		rows.pop();
		pthread_mutex_unlock (&row_mutex);
		if(i==-1){
			cout<<"we did an oopsie"<<endl;
			break;
		}
		
		/*if(i>0){
			pthread_mutex_lock (&c3_mutex);
			pc3[i-1] = pc3[i-1]/2;
			pthread_mutex_unlock (&c3_mutex);
		}*/
		const int dif = arr1[i+1]-arr1[i];
		if(dif >0){
			
			
			for (int j=0; j<dif; j++){
				int column = arr2[arr1[i]+j];
				if(column<=i){
					continue;
				}
				const int dif2 = arr1[column+1] - arr1[column];
				if(dif2>0){
					
					
					const int  val = intersection(arr1[i], arr1[i+1], arr1[column], arr1[column+1],i,column, arr2);
					
					if(val>0){
						pthread_mutex_lock (&c3_mutex);
						pc3[i]+=val;
						pc3[column]+=val;
						pthread_mutex_unlock (&c3_mutex);
						
						
					}
				}
			}
		}
		
	}
}


void* v4pThreadFunction2(void* args){

	
	while(true){
		int i=-1;
		pthread_mutex_lock (&row_mutex);

		if(rows.empty()){
			pthread_mutex_unlock (&row_mutex);
			return (void*)0;
		}
		i = rows.front();
		rows.pop();
		pthread_mutex_unlock (&row_mutex);
		if(i==-1){
			cout<<"we did an oopsie"<<endl;
			break;
		}
		pc3[i] = pc3[i]/2;
	}

	return (void*) 0;

}


void findNumberOfTrianglesV3openMP(vector<int>& arr1, vector<int>& arr2){
	int n = arr1.size();
	vector<int> c3(n-1,0);
	omp_set_dynamic(0);
	omp_set_num_threads(NUM_OF_THREADS);
	
	#pragma omp parallel for
	for(int i =0; i<(n-1) ; i++){
		int dif1 =  arr1[i+1] -arr1[i];
		
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

void findNumberOfTrianglesV3Cilk(vector<int>& arr1, vector<int>& arr2){
	int n = arr1.size();
	vector<int> c3(n-1,0);

	
	cilk_for (int i =0; i<(n-1) ; i++){
		
		int dif1 =  arr1[i+1] -arr1[i];
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

void findNumberOfTrianglesV3pThreads(vector<int>& arr1, vector<int>& arr2){
	int n = arr1.size();
	vector<int> c3(n-1,0);

	for (int i =0; i<(n-1); i++){
		rows.push(i);
	}
	Args3 args1;
	args1.ar1 = &arr1;
	args1.ar2 = &arr2;
	args1.c3 = &c3;
	
	pthread_t threads[NUM_OF_THREADS];
	for(int i=0; i<NUM_OF_THREADS; i++){
		pthread_create(&threads[i], NULL, v3pThreadFunction1, &args1);
		
	}
	for(int i=0; i<NUM_OF_THREADS; i++){
		pthread_join(threads[i], NULL);
	}
	for (int i =0; i<(n-1); i++){
		rows.push(i);
	}

	
	
	printOneDimensionalArray(c3);


}

void* v3pThreadFunction1(void* args){
	Args3 & arguments = *(static_cast<Args3*>(args));
	vector<int> &arr1 = *(arguments.ar1);

	vector<int> &arr2 =  *(arguments.ar2);
	vector<int> &c3 = *(arguments.c3);
	int n = arr1.size();
	while(1){
		int i=-1;
		pthread_mutex_lock (&row_mutex);

		if(rows.empty()){
			pthread_mutex_unlock (&row_mutex);
			return (void*)0;
		}
		i = rows.front();
		rows.pop();
		pthread_mutex_unlock (&row_mutex);
		if(i==-1){
			cout<<"we did an oopsie"<<endl;
			break;
		}
		
		
	
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
}


