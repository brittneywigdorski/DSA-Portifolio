#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Define Course structure
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Define BST Node
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) {
        course = c;
        left = right = nullptr;
    }
};

// Define BST class
class BinarySearchTree {
private:
    Node* root;

    void insert(Node*& node, Course course) {
        if (node == nullptr) {
            node = new Node(course);
        } else if (course.courseNumber < node->course.courseNumber) {
            insert(node->left, course);
        } else {
            insert(node->right, course);
        }
    }

    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->course.courseNumber << ": " << node->course.courseTitle << endl;
            inOrder(node->right);
        }
    }

    void printCourse(Node* node, string courseNumber) {
        if (node == nullptr) return;
        if (node->course.courseNumber == courseNumber) {
            cout << node->course.courseNumber << ": " << node->course.courseTitle << endl;
            if (!node->course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (string prereq : node->course.prerequisites) {
                    cout << prereq << " ";
                }
                cout << endl;
            }
        } else if (courseNumber < node->course.courseNumber) {
            printCourse(node->left, courseNumber);
        } else {
            printCourse(node->right, courseNumber);
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void Insert(Course course) {
        insert(root, course);
    }

    void PrintInOrder() {
        inOrder(root);
    }

    void PrintCourse(string courseNumber) {
        printCourse(root, courseNumber);
    }
};
void LoadCourses(string filePath, BinarySearchTree& bst) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Error: Cannot open file" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cout << "Error: Invalid format (must have course number and title)" << endl;
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            course.prerequisites.push_back(tokens[i]);
        }

        bst.Insert(course);
    }

    file.close();
    cout << "Courses loaded successfully!" << endl;
}

void DisplayMenu(BinarySearchTree& bst) {
    int choice;
    string fileName;
    string courseNumber;

    do {
        cout << "\nMenu:\n";
        cout << "1. Load Data\n";
        cout << "2. Print All Courses\n";
        cout << "3. Print Course Details\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter file name: ";
                cin >> fileName;
                LoadCourses(fileName, bst);
                break;
            case 2:
                bst.PrintInOrder();
                break;
            case 3:
                cout << "Enter course number: ";
                cin >> courseNumber;
                bst.PrintCourse(courseNumber);
                break;
            case 9:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);
}

int main() {
    BinarySearchTree bst;
    DisplayMenu(bst);
    return 0;
}
