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



class StudentFile:Student {//��� ����� File ������� �� ������ �����
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
};
int main() {//��� ����� �����
    setlocale(LC_ALL, "rus");//��� ����� ����� ������� ������� ����
    SetConsoleCP(1251);//��� ���������
    StudentFile manager("��� �� ���������:", "���� �� ���������:");
    manager.ReadFromFile("students.txt");
    // ���������� ������ ��������
    manager.UpdScore("�����", 57);
    // �������� ��������
    manager.RemoveStudent("�������:");
    // ���������� ��������� �� ������
    manager.SortByScore();
    // ����� ������ ���������
    manager.PrintStudents();
    // ������ ������ � ����
    manager.WriteToFile("sorted_students.txt");
}