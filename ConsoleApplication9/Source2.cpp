#include <iostream>
#include <Windows.h>
#include <fstream>
#include <list>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;

class Student {//��� ����� Student
private:
    int score = 0;//��� ���������� ������� ������ ������
    string name = "";//��� ���������� ������� ����� ������� �������� ���
    string subject = "";//��� ���������� ������� �������� ������

public:
    int GetScore() const {//����� �� ��������� ������
        return score;
    }

    Student(string name, string subject) : name(name), subject(subject) {}//����� �� ������ ���������� � �����������

    void SetScore(int Score) {//����� �� ������ ������ ������
        this->score = Score;
    }

    string GetName() const {//����� �� ��������� �����
        return name;
    }

    string GetSub() const {//����� �� ��������� ��������
        return subject;
    }

    friend ostream& operator<<(ostream& os, const Student& s) {//����� �� ������ � ������� ����������� ��������� � ���� � ���������
        os << "���:" << s.name << " �������:" << s.subject << " ������:" << s.score << endl;
        return os;
    }

    bool operator<(const Student& ss) const {//����� �� ��������� ������ � ������ ��������� ���������� 
        return score < ss.score;
    }
};

class StudentFile :Student {//��� ����� File ������� �� ������ �����
private:
    list<Student> group;//��� ���������� ������� �� �������������� � ������� ���������

public:
    StudentFile(const string& name, const string& subject) :Student(name, subject) {//����� �� ������ ���������� � ����������� ������
        group.emplace_back(name, subject);
    }

    void SetPush(const Student& s) {//����� �� ��������� ������ ��������� 
        group.push_back(s);
    }

    void UpdScore(const string& name, int newScore) {//����� �� ������� ������
        for (auto& i : group) {
            if (i.GetName() == name) {
                i.SetScore(newScore);
                break;
            }
        }
    }

    void RemoveStudent(const string& name) {//����� �� ������� ���������
        group.remove_if([name](const Student& student) {
            return student.GetName() == name;
            });
    }

    void SortByScore(bool ascending = true) {//����� �� ��������� �� �����������
        group.sort();
        if (!ascending) {
            group.reverse();
        }
    }

    void PrintStudents() const {//����� �� ������� ���������
        for (const auto& student : group) {
            cout << student << endl;
        }
    }

    void WriteToFile(const string& filename) const {//����� �� ���������� ����
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& student : group) {
                file << student.GetName() << " " << student.GetSub() << " " << student.GetScore() << endl;
            }
            file.close();
        }
        else {
            cout << "�� ������� ������� ����: " << filename << endl;
        }
    }

    void ReadFromFile(const string& filename) {//����� �� ������ � ����
        group.clear();//� ������ �� ������� ������
        ifstream file(filename);
        if (file.is_open()) {//������ �������� �� ���� ��� ��������� ���� ���� ���, �� "�� ������� ������� ����"
            string name, subject;
            int score;
            while (file >> name >> subject >> score) {
                group.push_back(Student(name, subject));
                group.back().SetScore(score);
            }
            file.close();
        }
        else {
            cout << "�� ������� ������� ���� " << filename << endl;
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
        cout << "������� ��� ��������: ";
        cin >> name;
        cout << "������� �������: ";
        cin >> subject;
        cout << "������� ������: ";
        cin >> score;
        group.emplace_back(name, subject);
        group.back().SetScore(score);
    }

    void AddStudentFromInput() {
        string name, subject;
        int score;
        cout << "������� ��� ��������: ";
        cin >> name;
        cout << "������� �������: ";
        cin >> subject;
        cout << "������� ������: ";
        cin >> score;
        group.emplace_back(name, subject);
        group.back().SetScore(score);
    }

};

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
    StudentFile manager("��� �� ���������:", "���� �� ���������:");
    int choice;
    do {
        cout << "�������� ��������:" << endl;
        cout << "1. �������� �������� � ������� �� ����������" << endl;
        cout << "2. �������� �������� � ������� � ��������� �� ����������" << endl;
        cout << "3. ����������� ��������� �� �������� �����" << endl;
        cout << "4. ������� ������ ���������" << endl;
        cout << "5. �������� ������ � ����" << endl;
        cout << "6. �����" << endl;
        cout << "�����: ";
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
            cout << "����� �� ���������." << endl;
            break;
        default:
            cout << "�������� �����. ���������� �����." << endl;
            break;
        }
    } while (choice != 6);

    return 0;
}