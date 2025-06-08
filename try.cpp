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

        // void saveToFile(string filename) {
        //         ofstream file(filename);
        //         if (file.is_open()) {
        //             file << question << endl;
        //             file << answer << endl;
        //             file.close();
        //             cout << "Flashcard saved successfully!\n";
        //         } else {
        //             cout << "Error saving file.\n";
        //         }
        //     }

        // void loadFromFile(string filename) {
        //     ifstream file(filename);
        //     if (file.is_open()) {
        //         getline(file, question);
        //         getline(file, answer);
        //         file.close();
        //         cout << "Flashcard loaded successfully!\n";
        //     } else {
        //         cout << "Error loading file.\n";
        //     }
        // }
};

class FlashcardManager{

};

class UserInterface{

};

class FlashcardApp{

};

int main() {
    FlashCard card("What is 2+2? ","4");

    cout << "Question: "<<card.getQuestion()<<endl;
    cout << "Answer: "<<card.getAns()<<endl;

    card.AttemptStat(true);
    card.AttemptStat(false);
    card.AttemptStat(true);

    cout << "Attempts: "<<card.getAttempt()<<endl;
    cout << "Correcct: "<<card.getCorrect()<<endl;
    cout << "Success Rate: "<<card.getSuccessRate()<<endl;
 

    return 0;
}
