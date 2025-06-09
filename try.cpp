#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

// Class for FlashCard
class FlashCard {
    private:
        string question;
        string answer;
        int attempt;
        int correct;

    public:
        FlashCard() {}
        FlashCard(string q, string a) {
            question = q;
            answer = a;
            attempt = 0;
            correct = 0;
        }

        string getQuestion()const{return question;}
        string getAnswer()const{return answer;}
        int getAttempt()const{return attempt;}
        int getCorrect()const{return correct;}

        void setQuestion(string q){
            question = q;
        }

        void setAnswer(string a){
            answer = a;
        }
    
        void AttemptStat(bool wasCorrect){
            attempt++;
            if(wasCorrect){
                correct++;
            }
        }

        int getSuccessRate()const{
            if(attempt == 0)
                return 0;
            else
                return (correct*100)/attempt;
        }
   
};

class File{
    private:
        string filename;

    public:
        File(){}
        File(string f){
            filename = f;
        }

        void saveToFile(vector<FlashCard> & cards) {
            ofstream file(filename);

            if(!file){
                cout << "Error: Could not open file for writing."<<endl;
            }

              file <<cards.size()<<endl; //no. of cards

              for(auto & card: cards){
                file << card.getQuestion() <<endl;
                file << card.getAnswer() << endl;
                file << card.getAttempt() << endl;
                file << card.getCorrect() << endl;
              }

              file.close();
              cout << "Flashcard saved to "<< filename << endl;
        }

        vector<FlashCard> loadFromFile() {
            vector<FlashCard> cards;
            ifstream file(filename);

            if(!file){
                cout << "No existing flashcard file found. Starting with empty file." << endl;
                return cards;
            }

            int numcards;
            file >> numcards;
            file.ignore();

            for(int i=0; i<numcards; i++){
                string question, answer;
                int correct, total;

                getline(file, question);    //output is string, so use getline
                getline(file, answer);

                file >> correct;        //output is int
                file >> total;
                file.ignore();

                FlashCard card(question, answer);

                for(int j=0; j<total; j++){
                    card.AttemptStat(j<correct);
                }

                cards.push_back(card);
            }
            file.close();
            cout << "Loaded "<< numcards << " flashcards."<<endl;

            return cards;
        }
};

class FlashCardManager{     //combine card+file, by add card and save stats from file.
    private:
        vector<FlashCard> cards;    //A List that holds all the flashcards
        File *file; // A pointer to handle saving or loading from files
    
    public:
        FlashCardManager(){}
        FlashCardManager(File *f){
            file = f;
            cards = file->loadFromFile();   // Creates a box and fills it with cards from a file
        }

        void addcard(string &question, string &answer){
            FlashCard newcard(question, answer);    // Make a new flashcard
            cards.push_back(newcard);   // Add it to your collection
            file->saveToFile(cards);    // Save everything to file
        }

    // Get number of cards
    int getSize() const {
        return cards.size();
    }

    // Check if deck is empty
    bool isEmpty() const {
        return cards.empty();
    }

    // Get a specific card
    FlashCard& getCard(int index) {
        return cards[index];
    }

    // Get a random card
    FlashCard& getRandomCard() {
        int index = rand() % cards.size();
        return cards[index];
    }

    // Save current state
    void saveState() {
        file->saveToFile(cards);
    }

};

class UserInterface{
    private: 
        string username;
        int choice;
    public:
        UserInterface(){}
        void showWelcome(){
            cout << "Welcome to flashcard generator!" << endl;
            cout << "Enter your name: ";
            getline(cin, username);
        }

        void showMenu(){
            cout << "\nFlashcard Generator: " << endl;
            cout << "1. Add Flashcard" << endl;
            cout << "2. Review Flashcard" << endl;
            cout << "3. View Flashcard" << endl;
            cout << "4. Exit"<<endl;
            cout << "Enter your choice: ";
            cin>>choice;
        }

        int getChoice(){
            cin.ignore(); // Clear input buffer
            return choice;
        }

        string getUsername(){
            return username;
        }

        void showQuestion(const string& question) {
             cout << "\nQuestion: " << question << endl;
             cout << "Press Enter to see the answer...";
             cin.get();  // Waits for user to think about their answer
        }

        void showAnswer(const string& answer) {
            cout << "Answer: " << answer << endl;  // Reveals the correct answer
        }

        bool askIfCorrect() {
            char response;
            cout << "Was your answer correct? (y/n): ";
            cin >> response;
            cin.ignore();
            return (response == 'y' || response == 'Y');  // Returns true/false
        }

        void showCardStats(const FlashCard& card, int cardNumber) {
            cout << "Card " << cardNumber << ":" << endl;
            cout << "  Question: " << card.getQuestion() << endl;
            cout << "  Answer: " << card.getAnswer() << endl;
            cout << "  Total Attempts: " << card.getAttempt() << endl;
            cout << "  Correct Answers: " << card.getCorrect() << endl;
            cout << "  Success Rate: " << card.getSuccessRate() << "%" << endl;
        }

        string getText(const string& prompt) {
            string text;
            cout << prompt;
            getline(cin, text);
            return text;
        }

        void showMessage(const string& message) {
            cout << message << endl;
        }

        void waitForEnter() {
            cout << "Press Enter to continue...";
            cin.get();
        }

};

class FlashcardApp{

};

int main() {
    UserInterface ui;
    ui.showWelcome();
    ui.showMenu();
    return 0;
}
