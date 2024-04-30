#include <iostream>
#include <Windows.h>
#include <fstream>
#include <list>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;

class Student {//Это класс Student
private:
    int score = 0;//это Переменная который делает оценки
    string name = "";//это Переменная который можно назвать студента имя
    string subject = "";//это Переменная который предметы задают

public:
    int GetScore() const {//здесь мы возрашаем оценки
        return score;
    }

    Student(string name, string subject) : name(name), subject(subject) {}//здесь мы создаём коструктор с пареметрами

    void SetScore(int Score) {//здесь мы создаём обЪект оценки
        this->score = Score;
    }

    string GetName() const {//здесь мы возрашаем имена
        return name;
    }

    string GetSub() const {//здесь мы возрашаем предметы
        return subject;
    }

    friend ostream& operator<<(ostream& os, const Student& s) {//здесь мы вводим с помошью перегрузков операторв в файл и возрашаем
        os << "Имя:" << s.name << " Предмет:" << s.subject << " Оценки:" << s.score << endl;
        return os;
    }

    bool operator<(const Student& ss) const {//здесь мы возрашаем оценки и делаем перегруза операторов 
        return score < ss.score;
    }
};

class StudentFile :Student {//это класс File который мы вводим файлы
private:
    list<Student> group;//Это Переменная который мы заимодействуем с списков студентов

public:
    StudentFile(const string& name, const string& subject) :Student(name, subject) {//здесь мы создаём коструктор с пареметрами файлов
        group.emplace_back(name, subject);
    }

    void SetPush(const Student& s) {//здесь мы добавляем списки студентов 
        group.push_back(s);
    }

    void UpdScore(const string& name, int newScore) {//здесь мы изменям оценки
        for (auto& i : group) {
            if (i.GetName() == name) {
                i.SetScore(newScore);
                break;
            }
        }
    }

    void RemoveStudent(const string& name) {//здесь мы удаляем студентов
        group.remove_if([name](const Student& student) {
            return student.GetName() == name;
            });
    }

    void SortByScore(bool ascending = true) {//здесь мы сортируем по возрастанию
        group.sort();
        if (!ascending) {
            group.reverse();
        }
    }

    void PrintStudents() const {//здесь мы выводим студентов
        for (const auto& student : group) {
            cout << student << endl;
        }
    }

    void WriteToFile(const string& filename) const {//здесь мы записываем файл
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& student : group) {
                file << student.GetName() << " " << student.GetSub() << " " << student.GetScore() << endl;
            }
            file.close();
        }
        else {
            cout << "Не удается открыть файл: " << filename << endl;
        }
    }

    void ReadFromFile(const string& filename) {//здесь мы читаем в файл
        group.clear();//с начало мы очищаем списки
        ifstream file(filename);
        if (file.is_open()) {//делаем проверку на того что откроется файл если нет, то "Не удается открыть файл"
            string name, subject;
            int score;
            while (file >> name >> subject >> score) {
                group.push_back(Student(name, subject));
                group.back().SetScore(score);
            }
            file.close();
        }
        else {
            cout << "Не удается открыть файл " << filename << endl;
        }
    }
    void SortByAverageScore(bool ascending = true) {
        group.sort([](const Student& a, const Student& b) {
            return a.GetScore() < b.GetScore();
            });
        if (!ascending) {
            group.reverse();
        }
    }
    void AddStudentWithSubjectAndScoreFromInput() {
        string name, subject;
        int score;
        cout << "Введите имя студента: ";
        cin >> name;
        cout << "Введите предмет: ";
        cin >> subject;
        cout << "Введите оценку: ";
        cin >> score;
        group.emplace_back(name, subject);
        group.back().SetScore(score);
    }

    void AddStudentFromInput() {
        string name, subject;
        int score;
        cout << "Введите имя студента: ";
        cin >> name;
        cout << "Введите предмет: ";
        cin >> subject;
        cout << "Введите оценку: ";
        cin >> score;
        group.emplace_back(name, subject);
        group.back().SetScore(score);
    }

};

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
    StudentFile manager("имя по умолчанию:", "тема по умолчанию:");
    int choice;
    do {
        cout << "Выберите действие:" << endl;
        cout << "1. Добавить студента с оценкой из клавиатуры" << endl;
        cout << "2. Добавить студента с оценкой и предметом из клавиатуры" << endl;
        cout << "3. Сортировать студентов по среднему баллу" << endl;
        cout << "4. Вывести список студентов" << endl;
        cout << "5. Записать данные в файл" << endl;
        cout << "6. Выйти" << endl;
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            manager.AddStudentFromInput();
            break;
        case 2:
            manager.AddStudentWithSubjectAndScoreFromInput();
            break;
        case 3:
            manager.SortByAverageScore();
            break;
        case 4:
            manager.PrintStudents();
            break;
        case 5:
            manager.WriteToFile("students.txt");
            break;
        case 6:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
            break;
        }
    } while (choice != 6);

    return 0;
}