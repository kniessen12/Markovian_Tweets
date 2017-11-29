#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <istream>

#include <stdlib.h> 
using namespace std;


typedef map< vector<string>, vector<string> > MAP;

void inputFile(MAP &word, string speech){
	string word1 = "";
	string word2 = "";
	string word3 = "";
	vector<string> KEY;
	
	for (int i = 0; i < speech.length(); i++){
	    if (speech[i] == ' '){
	    	if(word1 != ""){
	    		KEY.push_back(word1);
	    		KEY.push_back(word2);
	    		word[KEY].push_back(word3);
	    	    KEY.clear();
	    	}
	    	
			word1 = word2;
			word2 = word3;
			word3 = "";
	    }
	    
	    else{
	        word3 += speech[i];
	    }
	}
	
	KEY.clear();
	KEY.push_back(word1);
	KEY.push_back(word2);
	word[KEY].push_back(word3);
	
} //inputFile

string generateTweet(MAP &word){
	vector< vector<string> > start;
	string Tweet = "";
	MAP::iterator iter;
	
	for (iter = word.begin(); iter != word.end(); ++iter) {
		char i = iter -> first[0][iter -> first[0].size() - 1];
        if(isupper(iter -> first[0][0]) and i != '.' and i != '?' and i != '!'){
        
        	start.push_back(iter -> first);
        }
       	
	}
	
	srand(time(NULL));
	int vec1 = rand() % start.size();
	vector<string> curKEY = start[vec1];
	string word1 = curKEY[0];
	string word2 = curKEY[1];
	string word3 = "";

	Tweet += word1 + " " + word2;
	char last = Tweet[Tweet.size() - 1];

	while(last != '.' and last != '?' and last != '!' and word.count(curKEY) > 0){
		int vec2 = rand() % word.at(curKEY).size();
		word3 = word.at(curKEY)[vec2];
		Tweet += " " + word3;
		last = Tweet[Tweet.size()-1];
		word1 = word2;
		word2 = word3;
		curKEY.clear();
		curKEY.push_back(word1);
		curKEY.push_back(word2);
	
	}
	return Tweet;
	
} //generateTweet

int main(int argc, char** argv){
   
    MAP word;
	
	string str2;
	string str3 = "";
	ifstream Speech(argv[1]);
	
	if(Speech.is_open()){
		while(getTweet(Speech, str2)){
			str3 += str2 + " ";
		}
	}
	
	inputFile(word, str3);	
	
	string tweet;
	
	do{
		tweet = generateTweet(word);
	}
	
	while(tweet.size() > 145 or tweet.size() < 80);
	
	cout << tweet << endl;
	
	return 0;

}//main
