#include <iostream>
#include <Windows.h>
#include <fstream>
#include <list>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;
class Util {//Это класс для 2 прокта
public:
    static bool IsSymmetric(const string& word) {//это создаёт является ли слова симметричным
        int len = word.length();
        for (int i = 0; i < len / 2; ++i) {
            if (word[i] != word[len - i - 1]) {
                return false;
            }
        }
        return true;
    }

    static void PrintSymmetricWords(const string& filename) {// Метод для вывода симметричных слов из файла
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Не удается открыть файл:" << filename << endl;
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

    static void RemoveDuplicates(const string& inputFilename, const string& outputFilename) {// Метод для удаления дубликатов из файла
        ifstream inputFile(inputFilename);
        if (!inputFile.is_open()) {
            cout << "Не удается открыть входной файл: " << inputFilename << endl;
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
            cout << "Не удается открыть выходной файл:" << outputFilename << endl;
            return;
        }

        for (const auto& word : uniqueWords) {
            outputFile << word << endl;
        }
        outputFile.close();

        cout << "Удаленные дубликаты и записанные в " << outputFilename << endl;
    }
};

int main() {//это точка входа
    setlocale(LC_ALL, "rus");//это точка чтобы вывести русский язык
    SetConsoleCP(1251);//это кодировка
    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;
    Util::PrintSymmetricWords(filename);
    string inputFilename, outputFilename;
    cout << "Введите имя входного файла: ";
    cin >> inputFilename;
    cout << "Введите имя выходного файла: ";
    cin >> outputFilename;
    Util::RemoveDuplicates(inputFilename, outputFilename);
}