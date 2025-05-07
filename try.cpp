#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Class for FlashCard
class FlashCard {
public:
    string question;
    string answer;

    FlashCard() {}

    FlashCard(string q, string a) {
        question = q;
        answer = a;
    }

    void inputCard() {
        cout << "Enter question: ";
        getline(cin, question);
        cout << "Enter answer: ";
        getline(cin, answer);
    }

    void displayCard() {
        cout << "\nFlashcard Loaded:\n";
        cout << "Q: " << question << "\n";
        cout << "A: " << answer << "\n";
    }

    void saveToFile(string filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << question << endl;
            file << answer << endl;
            file.close();
            cout << "Flashcard saved successfully!\n";
        } else {
            cout << "Error saving file.\n";
        }
    }

    void loadFromFile(string filename) {
        ifstream file(filename);
        if (file.is_open()) {
            getline(file, question);
            getline(file, answer);
            file.close();
            cout << "Flashcard loaded successfully!\n";
        } else {
            cout << "Error loading file.\n";
        }
    }
};

int main() {
    FlashCard card;
    int choice;

    while (true) {
        cout << "\n=== Flash Card Menu ===\n";
        cout << "1. Create Flashcard\n";
        cout << "2. Load Flashcard\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear newline left in buffer

        if (choice == 1) {
            card.inputCard();
            card.saveToFile("flashcard.txt");
        } else if (choice == 2) {
            card.loadFromFile("flashcard.txt");
            card.displayCard();
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
