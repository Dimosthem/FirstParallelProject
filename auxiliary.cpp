#include "auxiliary.hpp"

using namespace std;

vector<vector<int>> importFromFile(string fileName){
	int dimension=0;
	bool symmetric = false;
	vector<int> arr1;
	vector<int> arr2;

	arr1.push_back(0);
	ifstream file(fileName);

	if (!file){
		cerr<<"Couldnt open the file"<<endl;
		vector<vector<int>> err;
		return err;
	}

	

	while(true){
		
		string line;
		getline(file, line);
		char s[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','p','r','s','t','y','u','w','z','%','-'};
		if (line.find_first_of(s)!=-1)
		{
			if((line.find("symmetric"))<100000 && !symmetric){
				
				symmetric = true;
				cout<<"The matrix you have loaded contains the flag [symmetric]"<<endl;
			}
			continue;    
		}else{
			istringstream stream(line);
			
			string dim;
			stream>>dim;
			cout<<dim<<endl;
			dimension = atoi(dim.c_str());
			cout<<dimension<<endl;
			
			break;
		}
	}
	
	
	vector<vector<int>> pnx(dimension);

	while(file){
		string strValue;
		string strIndex;
		file>>strIndex>>strValue;
		
		int value = atoi(strValue.c_str()) -1;
		int index = atoi(strIndex.c_str()) -1;
		//cout<<index<<" "<<value<<endl;
		if(index==-1 || value==-1){
			break;
		}
		
		pnx[index].push_back(value);

		if(symmetric){
			pnx[value].push_back(index);
		}
	}
	
	for(int i=0; i<dimension; i++){
		int size = pnx[i].size();
		
		if(size>0){
			arr1.push_back(size+arr1[i]);
			for (int j =0; j<size; j++){
				arr2.push_back(pnx[i][j]);
			}
		}else{
			arr1.push_back(arr1[i]);
		}
	}

	
	vector<vector<int>> result;
	result.push_back(arr1);
	result.push_back(arr2);


	return result;
}

vector<int> sliceArray(vector<int>& arr, int x, int y){
	vector<int> result;
	
	for (int i=x; i<y; i++){
		result.push_back(arr[i]);
	}

	return result;
}



/*int intersection(vector<int> & arr1 , vector<int>& arr2 ){
	int res = 0;
	for (int i =0; i<arr1.size(); i++){
		if (binary_search(arr2.begin(), arr2.end(), arr1[i])){
			res++;
		}
	}
	return res;
}*/
int intersection(const int &startA, const int &endA , const int &startB, const int &endB , const int& i , const int &j,const vector<int>& arr2){
	int result =0;
	int iteratorA = startA;
	int iteratorB = startB;
	while ( iteratorA <endA && iteratorB<endB){
		if(arr2[iteratorA]>arr2[iteratorB]){
			iteratorB++;
			continue;
		}else if(arr2[iteratorA]<arr2[iteratorB]){
			iteratorA++;
			continue;
		}else if(arr2[iteratorA]==arr2[iteratorB]){
			if(arr2[iteratorA]!=i && arr2[iteratorA]!=j){
				result++;
			}
			iteratorA++;
			iteratorB++;
			continue;
		}
	}
	return result;
}
/*int intersection(const int startA, const int endA , const int startB, const int endB , const vector<int>& arr2){
	int result =0;
	int iteratorA = startA;
	int iteratorB = startB;
	int step=2;
	//boolean good = true;
	int direction =0;
	while ( iteratorA <endA && iteratorB<endB){
		if(arr2[iteratorA]>arr2[iteratorB]){
			iteratorB+=step;
			
			if(direction==-1){
				iteratorA--;
			}
			else if(iteratorB>=endB){
				iteratorB--;
			}
			direction =1;
			continue;
		}else if(arr2[iteratorA]<arr2[iteratorB]){
			iteratorA+=step;
			
			if(direction==1){
				iteratorB--;
			}
			else if(iteratorA>=endA){
				iteratorB--;
			}
			direction =1;
			continue;
		}else if(arr2[iteratorA]==arr2[iteratorB]){
			result++;
			iteratorA++;
			iteratorB++;
			continue;
		}
	}
	return result;
}*/
/*int intersection(int startA, int endA , int startB, int endB , vector<int>& arr2 ){
	//cout<<"startA "<<startA<<" endA "<<endA<<" startB "<<startB<<" endB "<<endB<<endl; 
	int res = 0;
	for (int i =startA; i<endA; i++){
		int sB = startB;
		int eB = endB;
		int middle = (sB+eB)/2;
		while(true){
			if(arr2[middle]==arr2[i]){
				res++;
				break;
			}
			else if(arr2[i]<arr2[middle]){
				eB = middle;
				middle = (sB+middle)/2;
			}else{
				sB = middle;
				middle =(eB+middle)/2;
			}
			if(middle == sB){
				if(arr2[middle+1]!=arr2[i]){
					break;
				}else{
					res++;
					break;
				}
			}
		}
	}
	return res;
}*/

void printOneDimensionalArray(vector<int>& arr){

	for (int i=0; i<arr.size() ; i++){
		cout<<arr[i];
		cout<<" ";

	}
	cout<<""<<endl;

}

void exportToFile(string fileName, float densityPercentage, int dimension){
	ofstream out {fileName};
	out<<"pattern symmetric"<<endl;
	out<<dimension<<" "<<dimension<<" "<<"123456789"<<endl;
	for (int i =0; i<dimension; i++){
		for(int j =i+1; j<dimension; j++){
			float tmp = rand()%1000000;
			tmp /=1000000.f;
			if (tmp<= densityPercentage){
				out<<(j+1)<<" "<<(i+1)<<endl;
			}
		}
	}
	out.close();
}


vector<vector<int>> importFromFileToFullSize(string fileName){
	int dimension=0;
	bool symmetric = false;
	vector<int> arr1;
	vector<int> arr2;

	arr1.push_back(0);
	ifstream file(fileName);

	if (!file){
		cerr<<"Couldnt open the file"<<endl;
		vector<vector<int>> err;
		return err;
	}

	

	while(true){
		
		string line;
		getline(file, line);
		char s[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','p','r','s','t','y','u','w','z','%','-'};
		if (line.find_first_of(s)!=-1)
		{
			if((line.find("symmetric"))<100000 && !symmetric){
				
				symmetric = true;
				cout<<"The matrix you have loaded contains the flag [symmetric]"<<endl;
			}
			continue;    
		}else{
			istringstream stream(line);
			
			string dim;
			stream>>dim;
			cout<<dim<<endl;
			dimension = atoi(dim.c_str());
			cout<<dimension<<endl;
			
			break;
		}
	}
	
	
	vector<vector<int>> pnx(dimension, vector<int>(dimension,0));

	while(file){
		string strValue;
		string strIndex;
		file>>strIndex>>strValue;
		
		int value = atoi(strValue.c_str()) -1;
		int index = atoi(strIndex.c_str()) -1;
		//cout<<index<<" "<<value<<endl;
		if(index==-1 || value==-1){
			break;
		}
		
		pnx[index][value]=1;

		if(symmetric){
			pnx[value][index]=1;
		}
	}
	return pnx;
}

void printTwoDimensionalArray(vector<vector<int>>& vec){
	for (int i =0; i<vec.size() ; i++){
		for(int j=0; j<vec.size(); j++){
			cout<<vec[i][j]<<" ";
		}
		cout<<""<<endl;
	}
}