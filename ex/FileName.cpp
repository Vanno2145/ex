#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

int main() {
    setlocale(0, "ru");
    string filename;
    cout << "Введите путь к HTML-файлу: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
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
                    cout << "Ошибка закрытия тега: " << tagName << endl;
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
        cout << "HTML-файл валиден." << endl;
    }
    else {
        cout << "HTML-файл не валиден. Не все теги закрыты." << endl;
    }

    return 0;
}