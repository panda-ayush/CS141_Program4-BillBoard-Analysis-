/* main.cpp
  Program 4 BillBoard Analysis
   Author: Ayush Panda
   Date: 03/17/2022
   Class: CS 141, Spring 2022, UIC
   System: Windows using CLion
*/
#include <cassert> //header file
#include <cctype> //changing letters
#include <iostream> //cout
#include <fstream> // for file stream
#include <vector> // for vectors
#include <string> // for strings
#include <sstream> //for stream object
#include <algorithm> //find function
using namespace std;

struct billBoard { //struct for vectors

string date; //saves the date from CSV file
string year; //saves the year from CSV file
string rank; //saves the rank from CSV file
string song; //saves the song from CSV file
string artist; //saves the artist from CSV file
string lastWeek; //saves the last week rank from CSV file
string peakRank; //saves the peak rank from CSV file
string weeksOnBoard; //saves the weeks on board from CSV file

};
//function to output instruction for program
void gameDisplayInstructions() {
  cout << "Program 4: BillBoard Analysis " << endl;
  cout << "CS 141, Spring 2022, UIC " << endl << " " << endl;
  
  cout << "This program will analyze weekly Billboard data spanning from 1960 - 2020." << endl << endl;

  cout << "Select file option:" << endl;
  cout << "   1. To analyze charts top 50: 1960 - 1980 data file" << endl;
  cout << "   2. To analyze charts top 50: 1981 - 2000 data file" << endl;
  cout << "   3. To analyze charts top 50: 2001 - 2020 data file" << endl;
  
}

//function to output menu options
void menuOption() {
  cout << "Select a menu option: " << endl;
  cout << "   1. Display overall information about the data" << endl;
  cout << "   2. Display the Billboard info of the song with the most #1 occurrences for a given decade or year" << endl;
  cout << "   3. Display the Billboard info for the most long-lasting song on the charts for a given decade or year" << endl;
  cout << "   4. Display the Billboard info for the song with the greatest weekly climb on the charts given a decade or year" << endl;
  cout << "   5. Artist Search - Return the Billboard info for records that matches user input for artist search" << endl;
  cout << "   6. Exit" << endl;
}

 
//function to parse through csv file and save objects into vector
void createVector(char fileName[], vector <billBoard> & chartsTop) {

  
  chartsTop.clear();

  string inputLine, tempDate, tempRank, tempSong, tempArtist, tempLastWeek, tempPeakRank, tempWeeksOnBoard;

  ifstream inStream;

  inStream.open(fileName);
  
  assert(inStream.fail() == false);

  billBoard abillBoard;

  getline(inStream, inputLine);

  while ( getline (inStream, inputLine)) {
    
    abillBoard.date =inputLine.substr(0,inputLine.find(','));

    tempRank = inputLine.substr(inputLine.find(',') + 1);
    
    abillBoard.year = abillBoard.date.substr( (abillBoard.date).size()-4, (abillBoard.date).size()-1);

    abillBoard.rank = tempRank.substr(0, tempRank.find(','));

    tempSong = tempRank.substr(tempRank.find(",") + 1);

    abillBoard.song = tempSong.substr(0, tempSong.find(","));

    tempArtist = tempSong.substr(tempSong.find(",") + 1);

    abillBoard.artist = tempArtist.substr(0, tempArtist.find(","));

    tempLastWeek = tempArtist.substr(tempArtist.find(",") + 1);

    abillBoard.lastWeek = tempLastWeek.substr(0, tempLastWeek.find(","));

    if (abillBoard.lastWeek.empty() == true) {
      abillBoard.lastWeek = "0";
    }

    tempPeakRank = tempLastWeek.substr(tempLastWeek.find(",") + 1);

    abillBoard.peakRank = tempPeakRank.substr(0, tempPeakRank.find(","));

    tempWeeksOnBoard = tempPeakRank.substr(tempPeakRank.find(",") + 1);

    abillBoard.weeksOnBoard = tempWeeksOnBoard.substr(0, tempWeeksOnBoard.find(","));

  chartsTop.push_back(abillBoard);
  }

    inStream.close();
}
//funciton for menu option 2
void menuOptionFunction2(vector <billBoard> & chartsTop) {
      int time; //variable for user to select time period
      int occurenceNum = 0; //saves the number of occurences
      int maxOccurence = 0; //saves the max number of occurences
      char userChoice; //inputs user choice for menu option 
      bool condition = false; //boolean statement for outputting data
      bool condition2 = false;

      vector <billBoard> occurences; //vector to save the information from main vector
      vector <int> numberOccurence; //vector to save number of occurences
      vector <string> checkSong;//vector to check song
      vector <string> checkArtist;//vector to check artist
      vector <int> checkNum;//vector for occurence num
      vector <string> songName;
      vector <string> artistName;
      vector <int> counter;
    


      //clears vectors
      occurences.clear(); 
      numberOccurence.clear();
      checkSong.clear();
      checkArtist.clear();
      checkNum.clear();

      //prompts user for choice
      cout << "Enter D to select a decade or Y to select a year." << endl;
      cin >> userChoice;
      

        userChoice = toupper(userChoice); //changes user choice to upper case character


        if (userChoice == 'D') { //checks to see if user wanted to find data within the decade
          cout << "Your choice --> Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
          cin >> time; //inputs time period
          time =  time - (time % 10);
        for (int i = 0; i < chartsTop.size(); i++) { //checks if decade is equal to the input decade
          if ((stoi(((chartsTop.at(i)).year)) >= time) && (stoi(((chartsTop.at(i)).year)) < (time + 10))) { 

        if (stoi(chartsTop.at(i).rank) == 1) { //checks if correct decade and if rank is equal to 1
            occurences.push_back(chartsTop.at(i)); 

          }
        }
      }
        for (int k = 0; k < occurences.size(); k++)  {//calculates number of occurrences
            condition2 = false;
          for (int j = 0; j < songName.size(); j++) {
            if (occurences.at(k).song == songName.at(j)) {
              if (occurences.at(k).artist == artistName.at(j)) {
                counter.at(j)++;
                condition2 = true;
                break; 
              } 
              }
            }
            if(condition2 == false) {
              songName.push_back(occurences.at(k).song);
              artistName.push_back(occurences.at(k).artist);
              counter.push_back(1); 
            }
            
            }
          if (counter.size() != 0) {
            maxOccurence = counter.at(0);
          }
          for (int i = 0; i < counter.size(); i++) {
            if (counter.at(i) > maxOccurence) {
              maxOccurence = counter.at(i);
            }
          }
          condition = true; 
          
          }
          
        if (userChoice == 'Y') { //checks if user wants to see the data of a year
          cout << "Your choice --> Enter the year you would like to choose (e.g. 2001)." << endl;
          cin >> time;
        for (int i = 0; i < chartsTop.size(); i++) { //checks if correct year of data and if the rank of the data is 1
          if ((stoi((chartsTop.at(i)).year) == time) && stoi(chartsTop.at(i).rank) == 1) {
             occurences.push_back(chartsTop.at(i)); 
          }
        }
        for (int k = 0; k < occurences.size(); k++)  {//calculates number of occurrences
            condition2 = false; //
          for (int j = 0; j < songName.size(); j++) {
            if (occurences.at(k).song == songName.at(j)) {//saves songs of that index
              if (occurences.at(k).artist == artistName.at(j)) {//saves the song of the given index
                counter.at(j)++;
                condition2 = true;
                break; 
              } 
              }
            } //finds the unique songs and saves it to vector
            if(condition2 == false) {
              songName.push_back(occurences.at(k).song);
              artistName.push_back(occurences.at(k).artist);
              counter.push_back(1); 
            }
          
          if (numberOccurence.size() != 0) {
            maxOccurence = numberOccurence.at(0); //finds max occurrence
          }
          for (int i = 0; i < counter.size(); i++) {
            if (counter.at(i) > maxOccurence) { //counter for number of repeats
              maxOccurence = counter.at(i);
            }
          }
          condition = true; //prompts program to output data
          }
    }
        else if ((userChoice != 'Y') && (userChoice != 'D')) { //checks if user input is valid
          cout << "Your choice --> Invalid entry. Try again." << endl;
          menuOptionFunction2(chartsTop);
          return;
        }
      if (occurences.size() == 0) { //checks if the time frame selected was correct
        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
        condition = false;
        }
      
        if (condition){ //outputs data
          cout << "The song(s) with the most #1 occurrences for selected time period is:" << endl;
          for (int i = 0; i < songName.size(); i++ ) {
            if (counter.at(i) == maxOccurence) {

                cout << "\tSong Title: " << songName.at(i) << endl;
                cout << "\tArtist: " << artistName.at(i) << endl;
                cout << "\t# of occurrences: " << counter.at(i) << endl;

             
              }
            }
          }
          cout << endl;
  }
      

//menu option 3 function
void menuOption3 (vector <billBoard> & chartsTop) {
      int time;
      int highest = 0;
      char userChoice;
      int index = 0;
      bool condition = false;
  
      cout << "Enter D to select a decade or Y to select a year." << endl; //prompts user to input decade or year
      cin >> userChoice;
      

        userChoice = toupper(userChoice); //changes user input to uppercase
        
        if (userChoice == 'D') { //checks if user input is for decade function
          cout << "Your choice --> Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
          cin >> time;
          time =  time - (time % 10);
        for (int i = 0; i < chartsTop.size(); i++) {
          if ((stoi(((chartsTop.at(i)).year)) >= time) && (stoi(((chartsTop.at(i)).year)) < (time + 10))) { 
            if (stoi((chartsTop.at(i)).weeksOnBoard) > highest) //checks for highest week on board
            {
              highest = stoi((chartsTop.at(i)).weeksOnBoard); //finds highest number of weeks on board
              index = i; //saves index value
              condition = true; //prompt program to output data
            }
           }
        }
        if (highest == 0) { // checks if there time frame is outside of given input 
        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
          }
     }
          
        else if (userChoice == 'Y') { //checks if user input is for year
          cout << "Your choice --> Enter the year you would like to choose (e.g. 2001)." << endl;
          cin >> time;
        for (int i = 0; i < chartsTop.size(); i++) {
          if (stoi((chartsTop.at(i)).year) == time) {
            if (stoi((chartsTop.at(i)).weeksOnBoard) > highest)//checks for highest week on board
              {  
              highest = stoi((chartsTop.at(i)).weeksOnBoard);//finds highest number of weeks on board
              index = i; // saves index value
              condition = true; //prompts program to output data
            }
          }
        }
      if (highest == 0) { // checks if there time frame is outside of given input 
        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
        }
      }
          
        else if ((userChoice != 'Y') || (userChoice != 'D')) { //if user input is not for year or decade recalls function
           cout << "Your choice --> Invalid entry. Try again." << endl;
          menuOption3(chartsTop);
        }
        while (condition){ //outputs data
          cout << "The song with the highest number of weeks on the charts is:" << endl;
          cout << "\t" << (chartsTop.at(index)).song << " by " << (chartsTop.at(index)).artist << " with " << (chartsTop.at(index)).weeksOnBoard << " weeks on the chart.";
          cout << endl;
          break;
        }
      }

void menuOption4(vector <billBoard> & chartsTop) { //function call for menu option 4
  int time;
      int highest = 0; //saves highest difference of last week rank and rank
      int maxHighest = 0; //int for highest differenceof last week rank and rank
      char userChoice; //user choice variable
      int index = 0; //index value
      bool condition = false;

      vector <billBoard> maxHighestVect; //vector for highest value functions
      vector <int> indexVect; //saves index values

      maxHighestVect.clear(); //clears vectors
      indexVect.clear();
  
      cout << "Enter D to select a decade or Y to select a year." << endl;
      cin >> userChoice; //checks for users input
      

        userChoice = toupper(userChoice);//changes user input to capital
        
        if (userChoice == 'D') { //checks if user wants to use data of a given decade
          cout << "Your choice --> Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
          cin >> time;
          time =  time - (time % 10);
        for (int i = 0; i < chartsTop.size(); i++) {
          if ((stoi(((chartsTop.at(i)).year)) >= time) && (stoi(((chartsTop.at(i)).year)) < (time + 10))) {//finds given decade
                         if (stoi(chartsTop[i].lastWeek) >= stoi(chartsTop[i].rank)) //finds if last week rank is higher than current rank
              {
              if (maxHighest <= ((stoi((chartsTop.at(i).lastWeek)))-stoi((chartsTop.at(i).rank)))) { //if rank difference is less than the max difference
                highest = (stoi((chartsTop.at(i).lastWeek)))-stoi((chartsTop.at(i).rank)); //saves rank difference
                maxHighest = highest; //saves the highest difference
                maxHighestVect.push_back(chartsTop.at(i));//saves data information into vector
              }
            }
          }
        }
          for (int i = 0; i < maxHighestVect.size(); i++) {//loops through vector and saves index value 
            if(((stoi((maxHighestVect.at(i)).lastWeek)) - (stoi((maxHighestVect.at(i)).rank))) == maxHighest) {
              indexVect.push_back(i);
            }
            }
          condition = true;//prompts program to output data
           }
          
        else if (userChoice == 'Y') {//checks if user is checking for years
          cout << "Your choice --> Enter the year you would like to choose (e.g. 2001)." << endl;
          cin >> time;
        for (int i = 0; i < chartsTop.size(); i++) {
          if (stoi((chartsTop.at(i)).year) == time) { //checks if user year input matches csv file year
             if (stoi(chartsTop[i].lastWeek) >= stoi(chartsTop[i].rank)) //checks if last week rank greater than current rank
              {
              if (maxHighest <= ((stoi((chartsTop.at(i).lastWeek)))-stoi((chartsTop.at(i).rank)))) { //checks for highest rank
                highest = (stoi((chartsTop.at(i).lastWeek)))-stoi((chartsTop.at(i).rank));//saves rank difference
                maxHighest = highest;
                maxHighestVect.push_back(chartsTop.at(i)); 
              }
            }
          }
        }
          for (int i = 0; i < maxHighestVect.size(); i++) {
            if(((stoi((maxHighestVect.at(i)).lastWeek)) - (stoi((maxHighestVect.at(i)).rank))) == maxHighest) {//saves index value of highest rank difference
              indexVect.push_back(i);
            }
            }
          condition = true; //prompts program to output data
          }
        else if ((userChoice != 'Y') && (userChoice != 'D')) { //checks if user input is valid
           cout << "Your choice --> Invalid entry. Try again." << endl;
          menuOption4(chartsTop);//recalls function
          return;
        }
      if (maxHighestVect.size() == 0) { //checks if time frame is valid
        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
        condition = false; //prompts cout statement
        }
      
        while (condition){ //prompts program to output data from program
          cout << "The song(s) with the greatest climb from previous week to current week position: " << endl;
          for (int i = 0; i < indexVect.size(); i++ ) {
            cout << "\tSong Title: " << maxHighestVect.at(indexVect.at(i)).song << endl;
            cout << "\tArtist: " << maxHighestVect.at(indexVect.at(i)).artist << endl;
            cout << "\tWeek of: " << maxHighestVect.at(indexVect.at(i)).date << endl;
            cout << "\tPrevious Week Position: " << maxHighestVect.at(indexVect.at(i)).lastWeek << endl;
            cout << "\tCurrent Week Position: " << maxHighestVect.at(indexVect.at(i)).rank << endl;
            cout << "Difference of " << (stoi((maxHighestVect.at(indexVect.at(i)).lastWeek)))-stoi((maxHighestVect.at(indexVect.at(i)).rank)) << " between previous week and current week position" << endl;
          }
          cout << endl;
          break;
        }
      }

//function for menuOption 5
void menuOption5 (vector <billBoard> & chartsTop) {
  string artistInput; //input variable
  bool condition = false; //condition for cout statement
  cout << "Enter search text to retrieve first 10 records of #1 songs that match by artist name: " << endl;//input from user about artist name and ignores spaces
  getline(cin, artistInput);
  getline(cin, artistInput);
  vector <billBoard> artistSearch;

  artistSearch.clear();
  for (int k = 0; k < artistInput.length(); k++){ //puts artist input to lower case
    artistInput[k] = tolower(artistInput[k]); 
  }
      for (int i = 0; i <chartsTop.size(); i++) {//changes 
        string newArtist = chartsTop.at(i).artist;
        for (int j = 0; j < newArtist.length(); j++ ) {//changes charts artist to lower case
          newArtist[j] = tolower(newArtist[j]);
        }
        if ((newArtist.find(artistInput) != -1) && (stoi(chartsTop.at(i).rank) == 1)) {//checks for artist rank and to make sure artist is found
          artistSearch.push_back(chartsTop.at(i));
          if (artistSearch.size() > 9) {//checks to make sure output is less than 10
            break;
          }
        }
         condition = true; //prompts cout statement
        }
  if (artistSearch.size() == 0) { //checks for matching artist
    condition = false;
    cout << "No matching artists were found." << endl;
    return;
  }
  if (condition) { //outputs program data
    cout << "Retrieval of first 10 #1 records found based upon search by artist name: " << endl;
    for (int i = 0; i < artistSearch.size(); i++) {
    cout << i+1 << ") Song: " << artistSearch.at(i).song << endl;
    cout << "\tArtist: " << artistSearch.at(i).artist << endl;
    cout << "\tWeek of: " << artistSearch.at(i).date << endl;
    cout << "\tWeek Position: " << artistSearch.at(i).rank << endl;
  }
  }
  
 }


int main() {
  int menuOption1 = 0; //csv file option
  int menuOption2 = 0; //menu option within game
  bool condition = false;

  vector <billBoard> chartsTop; //struct vector for csv data

  
  while(true) {
    gameDisplayInstructions(); //outputs game display instructions
    cout << "Your choice --> " << endl; //prompts for menu option from user
    cin >> menuOption1;

    if (menuOption1 == 1){ //sets csv file to be passed through based on user input
      cout << endl;
      createVector("charts_top50_1960_1980.csv", chartsTop);
      condition = true;
      break;
    }
    else if (menuOption1 == 2) {
      cout << endl;
      createVector("charts_top50_1981_2000.csv", chartsTop);
      condition = true;
      break;
    }
    else if (menuOption1 == 3) { 
      cout << endl;
      createVector("charts_top50_2001_2020.csv", chartsTop);
      condition = true;
      break;
    }
    else {
      cout << "Invalid value. Exiting Program."; //if user input invalid exits program
      break;
    }

    }

    while(condition) { //checks if first menu option was chosen
    menuOption();//outputs menu options
    cout << "Your choice --> ";
    cin >> menuOption2;//input user menu option
      
    if (menuOption2 == 1){ //if user input option one
      vector <string> uniqueSongs;//vector for unique string
      vector <string> uniqueSongName;//vector for song name
      for (int i = 0; i < chartsTop.size(); i++) {//finds unique songs within data value
        if(find(uniqueSongName.begin(),uniqueSongName.end(), chartsTop.at(i).song) == uniqueSongName.end()) {
          uniqueSongName.push_back(chartsTop.at(i).song);//push back unique song values
          uniqueSongs.push_back(chartsTop.at(i).song);
        }
      }
      cout << "Total number of rows: " << chartsTop.size() << endl;//outputs total number of rows
      cout << "Number of unique songs represented in the dataset: " <<  uniqueSongs.size() << endl;//outputs size of unique songs
      cout << endl;
      }
      
    else if (menuOption2 == 2){//if menu option 2 was chosen
     menuOptionFunction2(chartsTop); //calls menu option 2 function
      cout << endl;
      
    }
    else if (menuOption2 == 3){ //if menu option 3 was chosen
      menuOption3(chartsTop); //calls menu option 3 function
      cout << endl;
    }
    else if (menuOption2 == 4){ //if menu option 4 was chosen
      menuOption4(chartsTop); // calls menu option 4 function
      cout << endl;
      
    }
    else if (menuOption2 == 5){ //if menu option 5 was chosen
      menuOption5(chartsTop); //calls menu option 5 function
      cout << endl;
      
    }
    else if (menuOption2 == 6){//exits program if menu option 6 called
      break;
    }
    else {
      
      cout << endl << "Invalid value.  Please re-enter a value from the menu options below." << endl << endl;//checks if invalid value from first option user input
    }
    
    }
  
   return 0;
}
