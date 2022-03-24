//Baris Akalin

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "strutils.h"

using namespace std;

struct tvseries{
		string name; //This variable stores the name of this tv series.

		string actorname; //This variable stores the name of an actor or actress 
						 //who acts in this tv series.
		double rating;
		int countforavg; //This variable stores how many times this tv series 
						//rated and is used to calculate rating average of the tv series.
		double ratingavg;
	};

//this function adds new elements to a vector of tvseries struct.
void insertactorandtvseriesname(vector<tvseries> & all, string tempactortovector, string temptvseriestovector){

	tvseries tv;
	tv.actorname = tempactortovector;
	tv.name = temptvseriestovector;
	tv.rating = 0;
	tv.countforavg = 0;
	all.push_back(tv);
}

//This function swaps positions of two elements in a vector of tvseries struct.
void Swap (tvseries & s1, tvseries & s2){
	tvseries temp;
	temp = s1;
	s1 = s2;
	s2 = temp;
}

//This function sorts elements of a vector of tvseries struct according to their
//rating average.
void SelectSort(vector<tvseries> & a, int size){
    int j,k,min;
    for(j=0 ; j< size-1; j++){	
		min = j;
        for(k=j+1; k<size; k++){
			if (a[k].ratingavg > a[min].ratingavg) {
                min = k;
			}
			else if ( a[k].ratingavg == a[min].ratingavg && a[k].name < a[min].name){
				min = k;
			}
        }
        Swap(a[min],a[j]);
    }    
}

//This function prints all elements of a vector of tvseries struct.
void print(vector<tvseries> & a){

	cout << "RANK,NAME,ACTOR,POINTS" << endl;
	for(unsigned int i=0; i < a.size(); i++){
	
		cout << i+1 << "," << a[i].name << "," << a[i].actorname << "," << a[i].ratingavg << endl;
	}
}

int main(){

	string actor; //This variable stores the name of the series-actor file.
	cout << "Welcome to Netflix TV Series Ratings Calculator!" << endl;
	cout << "Please enter a filename for Series-Actor file: ";
	cin >> actor;
	
	ifstream input;
	
	input.open(actor.c_str());

	while(input.fail()){
	
		cout << "Can not find the specified file." << endl;
		
		cout << "Please enter a filename for Series-Actor file: ";
		cin >> actor;
	
		input.open(actor.c_str());
	}

	string ratings; //This variable stores the name of the series-actor file.
	
	cout << "Please enter a filename for Rating file: ";
	cin >> ratings;
	
	ifstream input2;
	
	input2.open(ratings.c_str());

	while(input2.fail()){
	
		cout << "Can not find the specified file." << endl;
		
		cout << "Please enter a filename for Rating file: ";
		cin >> ratings ;
	
		input2.open(ratings.c_str());
	}
	
	//This variables are these variables are used to import actor and 
	//tv series names from actors_series.txt file into a vector of tvseries struct. 
	string line,acttovector = "",temp,temp2,tvseriestovector,tempactortovector,temptvseriestovector;
	
	vector<tvseries> all;
	int location;
	

	while(getline(input,line)){
		
		location = line.find(';');

		istringstream sstream(line.substr(0,location));
		while(sstream >> temp){
		
			acttovector += temp + " ";
		}
		ToUpper(acttovector);
		tempactortovector = acttovector.substr(0,acttovector.length()-1); 
		acttovector = "";

		istringstream sstream2(line.substr(location+1,line.length()-1));
		while(sstream2 >> temp2){
		
			tvseriestovector += temp2 + " ";
		}
		ToUpper(tvseriestovector);
		temptvseriestovector = tvseriestovector.substr(0,tvseriestovector.length()-1);
		insertactorandtvseriesname(all, tempactortovector, temptvseriestovector);
		tvseriestovector = "";
	} 
	
	//This variables are these variables are used to import tv series names and 
	//given ratings to them (there can be more than
	//one rating for a tv series) from ratings.txt file into a vector of tvseries struct. 
	string line2,temp3,temptvsname,realtemptvsname, wordsstream2;
	double temprating;
	while(getline(input2,line2)){

		istringstream sstream2(line2);
		sstream2 >> temprating;
		while(sstream2 >> wordsstream2){
		
			temptvsname += wordsstream2 + " ";
		}
		realtemptvsname = temptvsname.substr(0,temptvsname.length()-1);
		ToUpper(realtemptvsname);
		
		for(int i=0; i < all.size(); i++){
		
			if(realtemptvsname == all[i].name){
			
				all[i].rating += temprating;
				all[i].countforavg ++;
			}
		}

		realtemptvsname = "";
		temptvsname = "";
	}
	for(int i=0; i < all.size(); i++){
	
		all[i].ratingavg = all[i].rating/all[i].countforavg;
	}

	
	
	SelectSort(all, all.size());
	
	
	//In the option 2, the tv series whose average rating is higher than
	//this variable are printed.
	double minimumrating;  
	//numformenu is used to get user choice in the user interface.
	//option3word and error are used to get the tv series names 
	//that user want to add his/her favorite list of tv series.
	string numformenu, option3word,error;
	//favlist contains the favorite list of tv series of user.
	vector<string> favlist;
	
	while(!(numformenu == "5")){
	
		cout << "---" << endl;
		cout << "MENU" << endl;
		cout << "1. Print the series" << endl;
		cout << "2. Search the series according to the rating" << endl;
		cout << "3. Add the series to the favorite list" << endl;
		cout <<  "4. Print the favorite list" << endl;
		cout << "5. Exit" << endl;
		cout << "---" << endl;
		cout << "Enter your choice: ";
		cin >> numformenu;
		cout << "---" << endl;
		
		if(numformenu == "1"){
		
			print(all);
		}
		else if(numformenu == "2"){
		
			cout << "Please enter the minimum rating: ";
			cin >> minimumrating;

			if(0 <= minimumrating && minimumrating <= 10){
			
				cout << "RANK,NAME,ACTOR,POINTS" << endl;
				for(int i=0; i < all.size(); i++){
				
					if(all[i].ratingavg >= minimumrating){
					
						cout << i+1 << "," << all[i].name << "," << all[i].actorname << "," << all[i].ratingavg << endl;
					}
					
				}
			}
			else{
			
				cout <<	"This is not a valid rating!" << endl;
			}
		}
		else if(numformenu == "3"){
		
			cout << "Please enter the name of series: ";
			cin.clear();
			getline(cin,error);
			getline(cin,option3word);
			ToUpper(option3word);
			
			for(int i=0; i < all.size(); i++){
			
				if(all[i].name == option3word){
				
					favlist.push_back(all[i].name);
					break;
				}
				if(i == all.size()-1){
				
					cout << "There is no such TV series!" << endl;
				}
			}
			
			int countforfavlist=0;
			for(int i=0; i < favlist.size(); i++){
			
				if(favlist[favlist.size()-1] == favlist[i]){
				
					countforfavlist++;
				}
			}
			if(countforfavlist > 1){
			
				favlist.pop_back();
				cout << "Your favorite list already have " << option3word << endl;
			}
		}
		else if(numformenu == "4"){
			int x=1;
			if(favlist.size() == 0){
			
				cout << "Your favorite list is currently empty!" << endl;
			}
			else{
				cout << "RANK,NAME,ACTOR,POINTS" << endl;
				for(int i=0; i<all.size(); i++){
			
					for(int j=0; j <favlist.size(); j++){
				
						if(all[i].name == favlist[j]){
						
							cout << x << "," << all[i].name << "," << all[i].actorname << "," << all[i].ratingavg << endl;
							x++;
						}
					}
				}
			}
		}
		else if(numformenu == "5"){}

		else{
		
			cout << "This is not a valid option!" << endl;
		}
	}
	return 0;
}
