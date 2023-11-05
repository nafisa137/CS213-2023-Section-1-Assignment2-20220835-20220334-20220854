//file: 2-5-8-11 problems.cpp
//purpose: solving 2,5,8,11 problems
//Author: Safa Tawfik
//section: s1, s2
//ID: 20220835

#include <iostream>
#include<string>
#include<bits\stdc++.h>
using namespace std;
//problem 5
//size of list of top player 
const int TopPlayerlist = 10;
//struct to store the player information --->1:name, 2:score
struct Player_Data {
    string name;
    int score;
};

//Vector to stored the player
vector<Player_Data> player;

// Add player -->creat variable from data type layer_Data (struct) and enter the name and score the stored them in vector
void AddPlayer(vector<Player_Data>& p) { // Pass by reference
    Player_Data pp;
    cout << "Enter the Player name:\n";
    cin >> pp.name;
    cout << "Enter the Player score:\n";
    cin >> pp.score;
    p.push_back(pp);

    //stored the element of vector dependent of  score from bigger to smalle
    sort(p.begin(), p.end(), [](const Player_Data& a, const Player_Data& b) {
        return a.score > b.score;
        });

    //check if size of vector greater than 10 -->pop the last element
    if (p.size() > TopPlayerlist) {
        p.pop_back();
    }
}

//print the element list of top
void PrintTop(const vector<Player_Data>& p) {
    cout << "Top ten players:\n";
    for (int i = 0; i < p.size(); i++) {
        cout << p[i].name << "\t" << p[i].score << "\n";
    }
}

//Display_Player_High_scor

void Display_Player_High_score(const vector<Player_Data>& p, string name) {
    int score = -1;
    for (int i = 0; i < p.size(); i++) {

  
        //All alphabetic characters in 2 strings are converted to lowercase before comparsion
        string lowercaseName = p[i].name;
        transform(lowercaseName.begin(), lowercaseName.end(), lowercaseName.begin(), ::tolower);
        string lowercaseInputName = name;
        transform(lowercaseInputName.begin(), lowercaseInputName.end(), lowercaseInputName.begin(), ::tolower);
        if (lowercaseName==lowercaseInputName) {
            score = p[i].score;
            break;
        }
    }
    if (score != -1) {
        cout << name << " highest score: " << score << endl;
    }
    else {
        cout << name << " not in the top 10\n";
    }
}
//problem 8

void pattern(int n, int i) {
    //Base case Recursion stoped
    if (n == 0) {
        return;
    }
   
    //The first recursion 
    //it will be (4,0)then(2,0)then(1,0) then (0,0)the recursion stop and start implempent the recursion from(1,0) to (8,0) ,then implement the loops,after implement the loops there is a second recursion and start to implement the second recursion

   pattern(n / 2, i);
     for (int j = 0; j < i; j++) {
           cout << " ";
     }
     for (int j = 0; j < n; j++) {
           cout << "*";
     }
      cout << endl;
      //second recursion 
      //in second recursion implement the recursion and go to the start of the function check if n==0 or not and implempent the first recurion and stop when n==0 then implement the second recursion again
      
      pattern(n / 2, i + n / 2);
      //stop the recursion when the second recursion (1,8)
    
}

//problem 11
void charByChar(ifstream& file1, ifstream& file2) {
    char c1, c2;
    int line = 1, charNum = 0;
//take the information in file character by character
    while (file1.get(c1) && file2.get(c2)) {
        charNum++;
        //check if character in file 1 not equal character in file 2
        if (c1 != c2) {
            cout << "Files not the same" << endl;
            cout << "difference found at line " << line << ", character " << charNum << endl;
            cout << "first file: " << c1 << " second file: " << c2 << endl;
            return ;
        }
//if line finsh Scroll down to a new line
        if (c1 == '\n') {
            line++;
            charNum = 0;
        }
    }

    //eof( ) that returns nonzero (meaning TRUE) when there are no more data to be read from an input file stream, and zero (meaning FALSE) otherwise.
    if (file1.eof() && file2.eof()) {
        cout << "Files are similar." << endl;
        return;
    } else {
        cout << "files are not the same each of them larger than the other" << endl;
        return ;
    }
}

void wordByWord(ifstream& file1, ifstream& file2) {
    string w1, w2;
    int line = 1;
    //take the information in file word by word
    while (file1 >> w1 && file2 >> w2) {

        w1.erase(remove_if(w1.begin(), w1.end(), ::isspace), w1.end());
        w2.erase(remove_if(w2.begin(), w2.end(), ::isspace), w2.end());

        if (w1 != w2) {
            cout << "Files not the same" << endl;
            cout << "Difference found at line " << line << ": ";
            cout << "first file: " << w1 << " second file: " << w2 << endl;
            return ;
        }
        line++;
    }

    if (file1.eof() && file2.eof()) {
        cout << "Files are similar." << endl;
        return ;
    } else {
        cout << "files are not the same each of them larger than the other" << endl;
        return ;
    }
}





int main()
{
  int choice;
cout<<"2.  Aprogram that converts male speech to inclusive speech that includes both male and female.\n";
cout<<"5. A program that manages a list of up to 10 players and their high scores in the computer’s memory.\n";
cout<<"8. A Fractal Pattern.\n";
cout<<"11.File comparison.\n";
  cin>>choice;
\\Clear the newline character
  cin.ignore();
  
if(choice==2){
  
string s;
cout<<"Enter the string:"<<endl;
getline(cin,s);
//making string stream
stringstream word(s);
//Read and print each word
while(word>>s){
        int wordLenth=s.size();
        char lastchar=s[wordLenth-1];

    if(s=="He")
    cout<<"He or she ";
    else if(s=="he")
    cout<<"he or she ";
    else if(s=="he.")
    cout<<"he or she.";
     else if(s=="he?")
    cout<<"he or she?";
    else if(s=="him")
    cout<<"him or her ";
     else if(s=="him.")
    cout<<"him or her. ";
     else if(s=="him?")
    cout<<"him or her? ";
    else if(s=="Him")
    cout<<"Him or her ";
    else if(s=="his")
    cout<<"his or her ";
    else if(s=="His")
    cout<<"His or her ";
    else if(s=="himself")
    cout<<"himself or herself ";

    else
        cout<<s<<" ";
}
 }
  else if(choice==5){
bool flag = true;
    while (flag) {
        int choice;
        cout << "1. Add a new player and score\n";
        cout << "2. Print the top 10 players\n";
        cout << "3. Find a player's highest score\n";
        cout << "4. Exit\n";
        cin >> choice;
        switch (choice) {
        case 1:
            AddPlayer(player);
            break;
        case 2:
            PrintTop(player);
            break;
        case 3: {
            string name;
            cout << "Enter player name to find the highest score:\n";
            cin >> name;
            Display_Player_High_score(player, name);
            break;
        }
        case 4:
            flag = false;
            break;
        default:
            cout << "Invalid choice\n";
            break;
        }
    }




    
  }


  else if(choice==8){
  pattern(8, 0);
  }


  else if(choice==11){


string firstfile, secondfile;
    ifstream file1, file2;
    int op;

    cout << "enter name of first file with .txt : ";
    cin >> firstfile;
    file1.open(firstfile.c_str());

    if (!file1.is_open()) {
        cout  << "file 1 isn't exist " << endl;
    }

    cout << "enter name of second file with .txt : ";
    cin >> secondfile;
    //c_str() convert string to array of character
    file2.open(secondfile.c_str());

    if (!file2.is_open()) {
        cout << "file 2 isn't exist " << endl;
    }

    cout << "Choose comparison "<<endl;
    cout << "1 - character by character " <<endl ;
    cout << "2 - word by word " <<endl;
    cin >> op;


    if (op == 1) {
        charByChar(file1, file2);
    } else if (op == 2) {
        wordByWord(file1, file2);
    } else {
        cout << "Invalid input choose 1 or 2" << endl;
    }

    file1.close();
    file2.close();
    
  }


return 0;


}
