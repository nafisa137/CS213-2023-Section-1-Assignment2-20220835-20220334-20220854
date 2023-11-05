//file: 3-6-9-12 problems.cpp
//purpose: solving 3,6,9,12 problems
//Author: nafisa abdulrahman
//section: s1, s2
//ID: 20220854

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <regex>
#include <fstream>
using namespace std;

vector<string> split(const string& target, const string& delimiter) {
    vector<string> result;
    string::size_type start = 0;
    string::size_type end = target.find(delimiter);

    while (end != string::npos) {
        result.push_back(target.substr(start, end - start));
        start = end + delimiter.size();
        end = target.find(delimiter, start);
    }

    result.push_back(target.substr(start)); // Get the last part after the last delimiter

    return result;
}

void binaryNum(int n) {
    if (n > 0) {
        binaryNum(n / 2);
        cout << n % 2;
    } else if (n == 0) {
        cout << 0;
    }
}


void numbers(const string& prefix, int k) {
    if (k == 0) {
        cout << prefix << std::endl;
    } else {
        numbers(prefix + "0", k - 1);
        numbers(prefix + "1", k - 1);
    }
}



bool bears(int n) {
    // Base cases
    if (n == 42) {
        return true;
    } else if (n < 42) {
        return false;
    }

    // Rule 1: If n is even, call the function recursively with n/2.
    if (n % 2 == 0 && bears(n / 2)) {
        return true;
    }

    // Rule 2: If n is divisible by 3 or 4, calculate the next number and call the function recursively.
    int lastDigit = n % 10;
    int secondLastDigit = (n % 100) / 10;
    int nextNumber = lastDigit * secondLastDigit;
    if ((n % 3 == 0 || n % 4 == 0) && bears(n - nextNumber)) {
        return true;
    }

    // Rule 3: If n is divisible by 5, call the function recursively with n - 42.
    if (n % 5 == 0 && bears(n - 42)) {
        return true;
    }

    // If none of the rules lead to a win, return false.
    return false;
}

map<string, int> keywords{
        {"Bank", 2},
        {"Credit card", 3},
        {"Social security number", 3},
        {"Password", 2},
        {"Login", 2},
        {"Account", 2},
        {"Verification", 3},
        {"Verify", 2},
        {"Update", 1},
        {"Security", 3},
        {"Information", 2},
        {"Verify your account", 2},
        {"Click the link", 3},
        {"Email account", 2},
        {"Suspend", 1},
        {"Your account will be locked", 3},
        {"Confirm", 3},
        {"Fraud", 1},
        {"Urgent", 2},
        {"Unauthorized access", 3},
        {"Phishing", 2},
        {"Suspicious activity", 2},
        {"Re-confirm", 3},
        {"Financial institution", 1},
        {"Deactivate", 2},
        {"Fraudulent", 2},
        {"Social network", 1},
        {"Reset password", 3},
        {"PayPal", 3},
        {"eBay", 3}
};

void scan(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open this file" << endl;
    } else {
        string lines;
        string words;
        while (getline(file, lines)) {
            words += lines;
        }
        file.close();

        int totalPoints = 0;
        vector<tuple<string, int, int>> phishing;

        for (const auto& entry : keywords) {
            const string& keyword = entry.first;
            int points = entry.second;

            regex regex("\\b" + keyword + "\\b", regex_constants::icase);

            int occurrences = distance(sregex_iterator(words.begin(), words.end(), regex), sregex_iterator());

            if (occurrences > 0) {
                totalPoints += points * occurrences;
                phishing.emplace_back(keyword, occurrences, points * occurrences);
            }
        }

        for (const auto& result : phishing) {
            cout << get<0>(result) << " - Occurrences: " << get<1>(result) << ", Total Points: " << get<2>(result) << endl;
        }

        cout << "Total Points for the message: " << totalPoints << endl;
    }
}






int main(){
    int x;
    cout << "case number:\n";
    cin >> x;
    cin.ignore();  // Consume the newline character left in the input stream

    if (x == 1) {
        string input;
        cout << "Enter the input string:\n";
        getline(cin, input);  // Read a full line of input, including spaces
        string delimiter;

        cout << "The delimiter:\n";
        getline(cin, delimiter);  // Read the delimiter

        vector<string> result = split(input, delimiter);

        for (const string& part : result) {
            cout << part << " ";
        }
        cout << endl;
    } else if (x == 2) {
        cout << " The number is : \n";
        int m;
        cin >> m;
        binaryNum(m);
    }
    else if(x == 3){
        string prefix;
        cout << "Enter prefix\n";
        getline(cin, prefix);
        int m;
        cout << "Enter K\n";
        cin >>  m ;
        numbers(prefix , m);
    }
    else if (x == 4){
        int i;
        cout << "Enter the number of bears: ";
        cin >> i;

        if (bears(i)) {
            cout << "You have reached the goal!" << endl;
        }
        else {
            cout << "You lost the game " << endl;
        }
    }
    else if(x == 5){
        string filename = "sample_email.txt"; // Replace with the name of your text file
        scan(filename);
    }
    else {
        cout <<"choose a case \n";
    }
    return 0;
}
