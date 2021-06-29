#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <array>
#include <vector>
#include <unistd.h>
#include <exception>
using std::cout;
using std::cin;
using std::endl;
using std::ios;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::getline;
using namespace std;
class FileOperation{

public:
	fstream file;
	string fileName;
	char delimiter = '|';
	void createFile(){
		ifstream ifile(fileName);
		if(ifile){
			cout<<"File Exists \n";
			ifile.close();
		}
		else{
			file.open(fileName, ios::out);
			if(!file){
				cout << "Error: File "<<fileName <<" Creation failure \n";
			}
			else{
				cout << "Info: File Created \n";
			}
			file.close();
		}
	}
	void createRecords(string data[]){
		ofstream fileOut;
		ifstream fileIn;
		fileIn.open(fileName);
		fileOut.open(fileName, ios::app);
		if(fileIn.is_open()){
			fileOut<<data[0]<<"|"<<data[1]<<"|"<<data[2]<<"|"<<data[3]<<"|"<<data[4]<<endl;
		}
		cout << "data updated successully \n";
		fileIn.close();
		fileOut.close();
	}
	void updateFile(vector<string> data){
		this->wipeFile();
		ofstream fileOut;
		ifstream fileIn;
		fileIn.open(fileName);
		fileOut.open(fileName, ios::app);
		if(fileIn.is_open()){
			for(int i=0; i < data.size(); i++){
				if(data[i]!="")
				fileOut << data[i]<<endl;
			}
		}
		cout << "data updated successully \n";
		fileIn.close();
		fileOut.close();

	}
	vector<string> currentFileContent(){
		vector<string> temp;
		string line;
		fstream fileIn;
		fileIn.open(fileName, ios::in);
		if(fileIn.is_open()){
			while (getline(fileIn, line)){
				temp.push_back(line);
			}
		}
		fileIn.close();
		return temp;
	}
	void createUserRecords(){

		string data[5];
		int universityCount;
		cout<< "Enter the total number of universities Records to be created \n";
		cin >> universityCount;
		for(int i = 0; i < universityCount; i++){
			cout << "Enter the following details for University "<<i+1<<endl;
			cout << "Enter serial Number:";
			getline(cin, data[0]);
			if(data[0].empty()){
				getline (cin, data[0]);
			}
			cout << "Enter University name:";
			getline(cin, data[1]);
			if(data[1].empty()){
			  getline (cin, data[1]);
			}
			cout << "Enter University city:";
			getline(cin, data[2]);
			if(data[2].empty()){
			  getline (cin, data[2]);
			}
			cout << "Enter University branch:";
			getline(cin, data[3]);
			if(data[3].empty()){
			  getline (cin, data[3]);
			}
			cout << "Enter University rank:";
			getline(cin, data[4]);
			if(data[4].empty()){
			  getline (cin, data[4]);
			}
		}
		this->createRecords(data);
	}
	string getUserRecords(){
		string record;
		string data[5];
		int universityCount;
		cout << "Enter the following details for University "<<endl;
		cout << "Enter serial Number:";
		getline(cin, data[0]);
		if(data[0].empty()){
			getline (cin, data[0]);
		}
		cout << "Enter University name:";
		getline(cin, data[1]);
		if(data[1].empty()){
		  getline (cin, data[1]);
		}
		cout << "Enter University city:";
		getline(cin, data[2]);
		if(data[2].empty()){
		  getline (cin, data[2]);
		}
		cout << "Enter University branch:";
		getline(cin, data[3]);
		if(data[3].empty()){
		  getline (cin, data[3]);
		}
		cout << "Enter University rank:";
		getline(cin, data[4]);
		if(data[4].empty()){
		  getline (cin, data[4]);
		}

		record = data[0]+"|"+data[1]+"|"+data[2]+"|"+data[3]+"|"+data[4];
		return record;
	}

	void updateRecord(string operation){

		vector<string> temp;
		string line;
		fstream fileIn;
		fileIn.open(fileName, ios::in);
		if(fileIn.is_open()){
			while (getline(fileIn, line)){
				temp.push_back(line);

			}
		}

		if(stringMatch(operation, "name")){
			vector<int> indexCollector;
			string collegeName = "";
			cout<<"Enter the college name to update"<<endl;
			getline(cin, collegeName);
			if(collegeName==""){
				getline(cin, collegeName);
			}
			for(int i = 0; i < temp.size(); i++){
				if(stringMatch(temp[i], collegeName)){
					indexCollector.push_back(i);
				}
			}

			cout<<"Total Records found: "<<indexCollector.size()<<endl;
			if(indexCollector.size()==1){
				int val = indexCollector[0];
				modifyRecord(temp, val);
			}
			else{
				string collegeBranch;
				cout<<"Enter university branch to update record "<<endl;
				getline(cin, collegeBranch);
				if(collegeBranch==""){
					getline(cin, collegeBranch);
				}
				for(int i = 0; i < indexCollector.size(); i++){
					if(stringMatch(temp[indexCollector[i]], collegeBranch)){
						modifyRecord(temp, i);
						break;
					}
				}
			}
		}

		else if(stringMatch(operation, "rank")){
			vector<int> indexCollector;
			string collegeRank;
			int rank;
			cout<<"Enter the college rank to update"<<endl;
			getline(cin, collegeRank);
			if(collegeRank == ""){
				getline(cin, collegeRank);
			}
			rank = stoi(collegeRank);
			for(int i = 0; i < temp.size(); i++){
				if(this->getRank(temp[i]) == rank){
					indexCollector.push_back(i);
				}
			}
			cout<<"Total Records found: "<<indexCollector.size()<<endl;
			if(indexCollector.size()==1){
				int val = indexCollector[0];
				modifyRecord(temp, val);
			}
			else{
				string collegeName = "";
				int index[indexCollector.size()];
				cout<<"Enter the college name to update"<<endl;
				getline(cin, collegeName);
				if(collegeName==""){
					getline(cin, collegeName);
				}
				for(int i = 0; i < indexCollector.size(); i++){
					if(stringMatch(temp[indexCollector[i]], collegeName)){
						index[i] = indexCollector[i];
					}
				}
				cout<<"Total Records found: "<<(sizeof(index)/sizeof(index[0]))<<endl;
				if((  sizeof(index)/sizeof(index[0])  ) ==1){
					int val = index[0];
					modifyRecord(temp, val);
				}
				else {
					string collegeBranch;
					cout<<"Enter university branch to update record "<<endl;
					getline(cin, collegeBranch);
					if(collegeBranch==""){
						getline(cin, collegeBranch);
					}
					for(int i = 0; i < (  sizeof(index)/sizeof(index[0])  ); i++){
						if(index[i]!=0){
							if(stringMatch(temp[index[i]], collegeBranch)){
								modifyRecord(temp, index[i]);
								break;
							}
						}
					}
				}
			}
		}
	}
	void modifyRecord(vector<string> &temp, int ind){
		temp.erase(temp.begin()+ind);
		string rec = this->getUserRecords();
		temp.push_back(rec);
		this->updateFile(temp);

	}
private:

	int getRank(string mainString){
		return stoi(mainString.substr(this->getLastOccurance(mainString)+1, mainString.size()));
	}
	int getLastOccurance(string mainString){
		int lastIndex = -1;
		for(int i =0; i < mainString.length(); i++){
			if(mainString[i] == delimiter){
				lastIndex = i;
			}
		}
		return lastIndex;
	}
	string convert(string str){
	    for(int i=0; i < str.length(); i++){
	        str[i] = tolower(str[i]);
	    }
	    return str;
	}
	bool stringMatch(string var1, string var2){
		bool var = (convert(var1)).find(convert(var2)) != std::string::npos;
		if(var)
			return true;
		else
			return false;
	}

	void wipeFile(){
		ofstream fileOut;
		ifstream fileIn;
		fileIn.open(fileName);
		fileOut.open(fileName, ios::out | ios::trunc);
		if(fileIn.is_open()){
			fileOut;
		}
		cout << "data cleared successully \n";
		fileIn.close();
		fileOut.close();
	}

	string* convertArray(vector<string> array){
		string* strArray = new string[array.size()];
		for(int i = 0; i < array.size(); i++){
			strArray[i] = array[i];
		}
		return strArray;
	}

};

class sortingOperation{
public:

	fstream file;
	string fileName;
	char delimiter = '|';
	FileOperation fileOps;

	void sortRank(string operation){
		if(stringMatch(operation, "name")){
			vector <string> data = this->currentFileContent();
			int lastInd = data.size();
			this->quickSort(data, 0, lastInd);


		}
		else if(stringMatch(operation, "rank")){
			vector <string> data = this->currentFileContent();
			int lastInd = data.size();
			this->quickSort(data, 0, lastInd-1);
			this->displayRecords(data);
		}
	}

	void displayRecords(vector<string> &data){
		cout<<"Records after operation"<<endl;
		cout<<"-----------------------"<<endl;
		for(int i = 0; i <data.size(); i++){
			cout<<data[i]<<endl;
		}
		cout<<"------------------------"<<endl;

	}

private:
	vector<string> currentFileContent(){
		vector<string> temp;
		string line;
		fstream fileIn;
		fileIn.open(fileName, ios::in);
		if(fileIn.is_open()){
			while (getline(fileIn, line)){
				temp.push_back(line);
			}
		}
		fileIn.close();
		return temp;
	}

	int getRank(string mainString){
		return stoi(mainString.substr(this->getLastOccurance(mainString)+1, mainString.size()));
	}

	int getLastOccurance(string mainString){
		int lastIndex = -1;
		for(int i =0; i < mainString.length(); i++){
			if(mainString[i] == delimiter){
				lastIndex = i;
			}
		}
		return lastIndex;
	}
	void quickSort(vector<string> &data, int low, int high){
		if(low < high){
			int pivotVar = this->partion(data, low, high);
			this->quickSort(data, low, pivotVar-1);
			this->quickSort(data, pivotVar+1, high);
		}
	}

	int partion(vector<string> &data, int low, int high){
		int pivot = this->getRank(data[high]);
		int i = low-1;
		for(int j=low; j<=(high-1); j++){
			if((this->getRank(data[j])) <= pivot){
				i++;
				swap(data[i], data[j]);
			}
		}
		swap(data[i+1], data[high]);
		return (i+1);
	}

	string convert(string str){
	    for(int i=0; i < str.length(); i++){
	        str[i] = tolower(str[i]);
	    }
	    return str;
	}

	bool stringMatch(string var1, string var2){
		bool var = (convert(var1)).find(convert(var2)) != std::string::npos;
		if(var)
			return true;
		else
			return false;
	}

};


string convert(string str){
    for(int i=0; i < str.length(); i++){
        str[i] = tolower(str[i]);
    }
    return str;
}
bool stringMatch(string var1, string var2){
	bool var = (convert(var1)).find(convert(var2)) != std::string::npos;
	if(var)
		return true;
	else
		return false;
}

int main(){
	FileOperation fileOps;
	fileOps.fileName= "University.txt";

	sortingOperation sortOps;
	sortOps.fileName= "University.txt";

    string login;
    const string adminPassword = "Admin";
    string userPassword;
    string operation = "";
    cout << "Welcome to VTU management system"<< endl;
    cout<< "Enter \"Admin\" or \"Student\" to apply respective previlages" << endl;
    cin >> login;
    if(convert(login) == "admin"){
        cout << "Enter the Admin password" <<endl;
        cin >> userPassword;
        if(adminPassword == userPassword){
            cout << "Logged as Admin successfully" << endl;
            cout<<"Operations permited for admin are as below: "<<endl<<endl;
            cout<<"view Records"<<endl<<"sort Records"<<endl<<"Create Records"<<endl<<"Update Records"<<endl<<"Delete Records"<<endl<<endl;
            cout<< "Enter operation to be performed from displayed list: "<<endl;
            getline(cin, operation);
            if(operation==""){
            	getline(cin, operation);
            }
            if(stringMatch(operation, "view")){
            	cout<<"Records can be displayed by sorted and viewed by below order"<<endl<<endl;
            	cout<<"Alphabetical order"<<endl<<"Rank order"<<endl;
			}
            else if(stringMatch(operation, "create")){
            	fileOps.createUserRecords();
            }
            else if(stringMatch(operation, "sort")){
            	cout<<"Records can be sorted and viewed by below order"<<endl<<endl;
            	cout<<"university name order"<<endl<<"Rank order"<<endl;
            	cout<<"Enter operation from above to sort"<<endl;
            	string sortOperation;
            	getline(cin, sortOperation);
				if(sortOperation==""){
					getline(cin, sortOperation);
				}
            	sortOps.sortRank(sortOperation);
            }
            else if(stringMatch(operation, "update")){
            	cout<<"Records can be updated by below operations: "<<endl<<endl;
            	cout<< "Name"<<endl<<"Rank"<<endl<<endl;
            	cout<<"Enter operation from above to update"<<endl;
            	string updateOperation;
            	getline(cin, updateOperation);
				if(updateOperation==""){
					getline(cin, updateOperation);
				}
            	fileOps.updateRecord(updateOperation);
            }
            else if(stringMatch(operation, "delete")){

            }
            else{
            	cout<<"Invalid Operation exiting application";
            }
        }
        else{
            cout << "Invalid password exiting application"<< endl;
        }
    }
    else if(convert(login) == "student"){
        cout << "Logged as Student successfully" << endl;
    }
    else{
        cout << "Invalid selection exiting application" << endl;
    }
    return 0;
}
