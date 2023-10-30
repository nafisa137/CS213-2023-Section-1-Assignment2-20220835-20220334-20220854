#include <iostream>
#include <vector>
#include <string>

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




int main() {
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
    return 0;
}
