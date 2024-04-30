#include <iostream>
#include <Windows.h>
#include <fstream>
#include <list>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;
class Util {//��� ����� ��� 2 ������
public:
    static bool IsSymmetric(const string& word) {//��� ������ �������� �� ����� ������������
        int len = word.length();
        for (int i = 0; i < len / 2; ++i) {
            if (word[i] != word[len - i - 1]) {
                return false;
            }
        }
        return true;
    }

    static void PrintSymmetricWords(const string& filename) {// ����� ��� ������ ������������ ���� �� �����
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "�� ������� ������� ����:" << filename << endl;
            return;
        }

        vector<string> words;
        string word;
        while (file >> word) {
            words.push_back(word);
        }
        file.close();
        for (size_t i = 0; i < words.size() - 1; ++i) {
            if (IsSymmetric(words[i])) {
                cout << words[i] << endl;
            }
        }
    }

    static void RemoveDuplicates(const string& inputFilename, const string& outputFilename) {// ����� ��� �������� ���������� �� �����
        ifstream inputFile(inputFilename);
        if (!inputFile.is_open()) {
            cout << "�� ������� ������� ������� ����: " << inputFilename << endl;
            return;
        }

        unordered_set<string> uniqueWords;
        string word;
        while (inputFile >> word) {
            uniqueWords.insert(word);
        }
        inputFile.close();

        ofstream outputFile(outputFilename);
        if (!outputFile.is_open()) {
            cout << "�� ������� ������� �������� ����:" << outputFilename << endl;
            return;
        }

        for (const auto& word : uniqueWords) {
            outputFile << word << endl;
        }
        outputFile.close();

        cout << "��������� ��������� � ���������� � " << outputFilename << endl;
    }
};

int main() {//��� ����� �����
    setlocale(LC_ALL, "rus");//��� ����� ����� ������� ������� ����
    SetConsoleCP(1251);//��� ���������
    string filename;
    cout << "������� ��� �����: ";
    cin >> filename;
    Util::PrintSymmetricWords(filename);
    string inputFilename, outputFilename;
    cout << "������� ��� �������� �����: ";
    cin >> inputFilename;
    cout << "������� ��� ��������� �����: ";
    cin >> outputFilename;
    Util::RemoveDuplicates(inputFilename, outputFilename);
}