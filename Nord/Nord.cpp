// Nord.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <stack>
#include <string>

struct BracketInfo {
    char type;
    int line;
    int column;
};

void reportErrors(std::stack<BracketInfo> incorrectBracketStack, std::string filePath) {
    while (!incorrectBracketStack.empty()) {
        std::cout << "Invalid bracket " << incorrectBracketStack.top().type << " at " << filePath << ":" << incorrectBracketStack.top().line << ":" << incorrectBracketStack.top().column << std::endl;
        incorrectBracketStack.pop();
    }
}

void checkBrackets(const std::string filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return;
    }

    std::stack<BracketInfo> bracketStack;
    std::stack<BracketInfo> incorrectBracketStack;
    char currentChar;
    int line = 1, column = 0;

    while (file.get(currentChar)) {
        column++;
        if (currentChar == '\n') {
            line++;
            column = 0;
        }

        if (currentChar == '[' || currentChar == '{' || currentChar == '(') {
            bracketStack.push({ currentChar, line, column });
        }
        else if (currentChar == ']' || currentChar == '}' || currentChar == ')') {
            if (bracketStack.empty() ||
                (currentChar == ']' && bracketStack.top().type != '[') ||
                (currentChar == '}' && bracketStack.top().type != '{') ||
                (currentChar == ')' && bracketStack.top().type != '(')) {
                incorrectBracketStack.push({ currentChar, line, column });
            }
            else {
                bracketStack.pop();
            }
        }
    }

    while (!bracketStack.empty()) {
        incorrectBracketStack.push(bracketStack.top());
        bracketStack.pop();
    }

    file.close();
    reportErrors(incorrectBracketStack, filepath);
}



int main() {
    std::cout << "Please write the name of the file and the extension (.txt, .cpp, .ts):";
    std::string filePath;
    std::cin >> filePath;
    checkBrackets(filePath);
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
