//file:main.cpp
//purpose: solutions of problems 1,4,7,10
//Author: mariam Matar Ahmed Ali
//section: s1,s2
//ID: 20220334

#include "bits/stdc++.h"
using namespace std;

struct dominoT{
    int left;
    int right;
};
map <int , bool> check;
deque<dominoT> domino_out;

bool FormChainDomino(vector<dominoT> &dominoes){
    if(domino_out.size() == dominoes.size()){ // base case that will stop the implementation and return true
        cout<<endl;
        cout<<"There is a solution: "<<endl;
        for (int i = 0; i < domino_out.size() ; ++i) {
            cout << "["<< domino_out[i].left << " | " << domino_out[i].right <<"]"<<" ";
        }
        return true;
    }

    for (int i = 1; i < dominoes.size() ; ++i) {
        if(check[i]){
            continue;//here we will check if the current domino was used before or not,
                     // if it was used before then we will skip it
        }
        else {
            if(dominoes[i].right == domino_out.front().left){ // if the right side of user domino was equal to
                                                            // the left side of chain , we will push it in the
                                                            // front of chain and make sure to convert its value
                                                            // into true so we do not compare use again
                domino_out.push_front(dominoes[i]);
                check[i] = true;
                if (FormChainDomino(dominoes )){ // here we used backtracking to make it complete
                                                // its recursive process by itself so it gets the right
                                                // solution from the beginning
                    return true;
                }
                else{
                    domino_out.pop_front(); // after the recursive process, if it found that it will not reach
                                          // the right solution we will pop this domino from chain and make
                                          // its value false again so we can use it later in a better order
                    check[i] = false;
                }
            }

            if(dominoes[i].left == domino_out.back().right){
                domino_out.push_back(dominoes[i]);
                check[i] = true;
                if(FormChainDomino(dominoes)){
                    return true;
                }
                else{
                    domino_out.pop_back();
                    check[i] = false;
                }
            }
        }
    }
    return false;
}


int main(){
    int n;
    cout<<"for solution of Q.1, choose 1: "<<endl;
    cout<<"for solution of Q.4, choose 2: "<<endl;
    cout<<"for solution of Q.7, choose 3: "<<endl;
    cout<<"for solution of Q.10, choose 4: "<<endl;
    cin>>n;
    if (n==1){
        char sentence[100];
        cout<<"Enter your full sentence: "<<endl;
        cin.getline(sentence,100);
        int length = strlen(sentence);
        int first_element = sentence[0];
        if (islower(first_element)){
            sentence[0] = toupper(sentence[0]);
        }
        for (int i=1;i<length;i++){
            int sec = sentence[i];
            if (isupper(sec) and sentence[i]!= ' '){
                sentence[i] = tolower(sentence[i]);
            }

        }
        cout<<"your sentence after correcting it: "<<endl;
        for (int i=0;i<length;i++){
            if (sentence[i] == ' '){
                if (sentence[i-1]==' ') {
                    continue;
                }
            }
            cout<<sentence[i];
        }
    }
    else if (n==2){
        vector <int> v_solution;
        vector <int> v1;//vector of normal elements from 2 to N
        vector <int> v2;//vector of elements after eliminating multiplies of 2
        vector <int> v3;//vector of elements after eliminating multiplies of 3
        vector <int> v5;//vector of elements after eliminating multiplies of 5
        int N;
        cout<<"Enter the number that you want all prime numbers between it and 2:"<<endl;
        cin>>N;
        if (N>=5){
            for (int i=2;i<N+1;i++){
                v1.push_back(i);
            }
            for (int i=0;i<v1.size();i++){  //for the circle of 2
                if (v1[i] %2 != 0){
                    v2.push_back(v1[i]);
                }
            }
            v2.push_back(2);

            for (int i=0;i<v2.size();i++){ // for the circle of 3
                if (v2[i] %3 != 0){
                    v3.push_back(v2[i]);
                }
            }
            v3.push_back(3);

            for (int i=0;i<v3.size();i++){// for the circle of 5
                if (v3[i] %5 != 0){
                    v5.push_back(v3[i]);
                }
            }
            v5.push_back(5);
            sort(v5.begin(),v5.end());
            cout<<"the prime numbers are: "<<endl;
            for (int i=0;i<v5.size();i++){
                cout<<v5[i]<<" ";
            }
            cout<<endl;
        }
        else {
            if (N==2) cout<<"the prime numbers are: "<<2<<endl;
            else if (N==3 || N ==4) cout<<"the prime numbers are: "<<2<<" "<<3<<endl;
        }
    }
    else if (n==3){
        int domino_size;
        cout<<"enter the size of your dominos: "<<endl;
        cin >> domino_size;
        vector<dominoT> dominoes(domino_size);
        for (int i = 0; i < domino_size; ++i) {
            cout<<"enter left and right dots of the domino: ";
            cin >> dominoes[i].left>>dominoes[i].right;
        }

        domino_out.push_front(dominoes[0]);//here we chose the first domino from the left to compare with
                                            // during ordering process
        check[0] = true;
        if(FormChainDomino(dominoes)){ // it will print solution if the function returned true
        }
        else{
            cout << "There is no solution" << endl;
        }
    }
    else if (n==4){
        map <string,string> replace;
        ifstream f_alter;
        f_alter.open("alternative words.txt");//file with each word and alternative of it
        string line1;
        while (getline(f_alter,line1)){   // to set replace each word with the alternative of it
            int pos = line1.find(' ');       //to iterate until it find the position of a single word
            if (pos != string::npos){           //if there was a space already in the line, it found a word
                string key_word = line1.substr(0,pos);
                string value_word = line1.substr(pos+1);//to start the next word from after the space directly
                replace[key_word] = value_word;
            }
        }

        ofstream f_write;
        f_write.open("output.txt");  //file of the file after alternating any words in it
        ifstream f_read;
        f_read.open("input.txt");    //file that will read the inputs of user
        string line,word;
        istringstream s; //here we will read each word from the input file to alter each
                        // word if found with the new value of it
        while (!f_read.eof()){//while we did not yet reach the end of the file
            getline(f_read,line);
            s.clear();
            s.str(line);
            while(s.good()){
                s>>word;
                auto it = replace.find(word);
                if (it != replace.end()){
                    f_write<<it->second<<" ";
                }
                else{
                    f_write<<word<<" ";
                }

            }
            f_write<<endl;
        }

        f_read.close();
        f_write.close();
        f_alter.close();
    }
}
