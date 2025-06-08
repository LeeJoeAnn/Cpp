#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

        string getQuestion(){return question;}
        string getAns(){return answer;}
        int getAttempt(){return attempt;}
        int getCorrect(){return correct;}

        void setQuestion(string q){
            question = q;
        }

        void setAnsw(string a){
            answer = a;
        }
    
        void AttemptStat(bool wasCorrect){
            attempt++;
            if(wasCorrect){
                correct++;
            }
        }

        int getSuccessRate(){
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
                file << card.getAns() << endl;
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

class FlashcardManager{

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
            cin >> choice;
        }

        int getChoice(){
            return choice;
        }

        string getUsername(){
            return username;
        }

};

class FlashcardApp{

};

int main() {
   //test class File
   File file("test_fc.dat");
   vector<FlashCard> cards;

   FlashCard c1("What is 2+2?", "4");
   FlashCard c2("Who are u?","idk");

   c1.AttemptStat(true);
   c1.AttemptStat(false);
   c1.AttemptStat(true);


   c2.AttemptStat(true);
   c2.AttemptStat(false);


   cards.push_back(c1);
   cards.push_back(c2);

    cout<< "Testing save..."<<endl;
    file.saveToFile(cards);

    cout << "Testing load..."<<endl;
    vector<FlashCard> loadcard;
    loadcard = file.loadFromFile();

    cout << "\nLoaded cards:" << endl;

    for(int i = 0; i<(int)loadcard.size() ; i++){

        cout << "Card " << i+1 << ":" << endl;
        cout << "Q: " << loadcard[i].getQuestion() << endl;
        cout << "A: " <<  loadcard[i].getAns() << endl;
        cout << "Attempts: " <<  loadcard[i].getAttempt() << endl;
        cout << "Correct: " <<  loadcard[i].getCorrect() << endl;
        cout << endl;
    }
    return 0;
}
