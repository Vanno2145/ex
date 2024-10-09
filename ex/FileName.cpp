#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

int main() {
    setlocale(0, "ru");
    string filename;
    cout << "������� ���� � HTML-�����: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "������ �������� �����: " << filename << endl;
        return 1;
    }

    stack<string> tags;
    string line;

    while (getline(file, line)) {
        
        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

        
        if (line.length() > 1 && line[0] == '<' && line[line.length() - 1] == '>') {
            bool isClosingTag = line[1] == '/';
            string tagName = line.substr(isClosingTag + 1, line.length() - 2 - isClosingTag);

            if (isClosingTag) {
                if (tags.empty() || tags.top() != tagName) {
                    cout << "������ �������� ����: " << tagName << endl;
                    return 1;
                }
                tags.pop();
            }
            else {
                tags.push(tagName);
            }
        }
    }

    if (tags.empty()) {
        cout << "HTML-���� �������." << endl;
    }
    else {
        cout << "HTML-���� �� �������. �� ��� ���� �������." << endl;
    }

    return 0;
}