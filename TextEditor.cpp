#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <windows.h> // For Sleep()

using namespace std;

// Node structure for linked list
struct node {
    string data;
    node *next;
};

class linked_list {
private:
    node *head, *tail;
    int numOfLines;

public:
    linked_list() : head(NULL), tail(NULL), numOfLines(0) {}

    // Insert text at a specified line (1-based)
    void insertAt(string data, int position) {
        node *temp = new node{data, NULL};

        if(position < 1 || position > numOfLines + 1){
            cout << "Invalid position!" << endl;
            delete temp;
            return;
        }

        if(position == 1){
            temp->next = head;
            head = temp;
            if(tail == NULL) tail = head;
        } else {
            node *prev = head;
            for(int i=1; i<position-1; i++) prev = prev->next;
            temp->next = prev->next;
            prev->next = temp;
            if(temp->next == NULL) tail = temp;
        }

        numOfLines++;
        cout << "Inserted successfully at line " << position << "!\n";
    }

    // Delete the specified line (1-based)
    void deleteLine(int lineGiven) {
        if(lineGiven < 1 || lineGiven > numOfLines || head==NULL) {
            cout<<"Invalid line number!\n";
            return;
        }
        node *temp = head, *prev = NULL;
        for(int i=1; i<lineGiven; i++) {
            prev = temp;
            temp = temp->next;
        }
        if(prev == NULL){
            head = head->next;
        } else {
            prev->next = temp->next;
        }
        if(temp == tail) tail = prev;
        delete temp;
        numOfLines--;
        cout << "Line " << lineGiven << " deleted successfully.\n";
    }

    // Print all lines
    void printall() {
        node *temp = head;
        int lineNo = 1;
        if(temp == NULL){
            cout<<"Document is empty!\n";
        } else{
            cout << "\n--- Document Start ---\n";
            while(temp){
                cout<<lineNo++<<") "<<temp->data<<endl;
                temp=temp->next;
            }
            cout << "--- Document End ---\n";
        }
        Sleep(800);
    }

    // Save to file
    void saveAll() {
        string fileName;
        cout<<"Enter file name (without extension): ";
        cin >> fileName;
        fileName += ".txt";
        ofstream file(fileName.c_str());
        node *temp = head;
        while(temp){
            file<<temp->data<<endl;
            temp = temp->next;
        }
        file.close();
        cout<<"Saved successfully to " << fileName << "!\n";
        Sleep(800);
    }

    // Input logic for insertion
    void insertMenu() {
        int line;
        string data;

        cout << "Enter line number to insert at (1 for top, " << (numOfLines+1) << " for end): ";
        cin >> line;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a numeric value.\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        cout << "Enter text: ";
        getline(cin, data);

        insertAt(data, line);
    }

    // Input logic for deletion
    void deleteMenu() {
        int line;
        cout << "Enter line number to delete: ";
        cin >> line;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a numeric value.\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        deleteLine(line);
    }

    // Main menu
    void menu() {
        int choice = -1;
        while(choice != 0) {
            cout<<"\n====TEXT EDITOR====\n";
            cout<<"1. Insert text\n2. Delete line\n3. Print all\n4. Save file\n0. Exit\n";
            cout<<"Enter choice: ";
            cin >> choice;

            if(cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Invalid choice! Please enter a numeric value.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(choice){
                case 1:
                    insertMenu(); break;
                case 2:
                    deleteMenu(); break;
                case 3:
                    printall(); break;
                case 4:
                    saveAll(); break;
                case 0:
                    cout<<"Exiting...\n"; break;
                default:
                    cout<<"Invalid choice!\n";
            }
        }
    }
};

int main(){
    linked_list editor;
    editor.menu();
    return 0;
}
