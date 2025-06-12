#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>

using namespace std;

enum Difficulty{
    EASY = 1,
    MODERATE = 2,
    DIFFICULT = 3
};


// Class for FlashCard
class FlashCard {
    private:
        string question;
        string answer;
        int attempt;
        int correct;
        Difficulty level;

    public:
        FlashCard() {}
        FlashCard(string q, string a) {
            question = q;
            answer = a;
            attempt = 0;
            correct = 0;
            level = MODERATE;
        }

        string getQuestion()const{return question;}
        string getAnswer()const{return answer;}
        int getAttempt()const{return attempt;}
        int getCorrect()const{return correct;}
        Difficulty getLevel(){return level;}

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

        void setLevel(Difficulty lvl){
            level = lvl;
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

                file >> total;
                file >> correct;        //output is int
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
        vector<FlashCard *> LvlCards;   //set a vector that store card based on the difficulty level

        for(auto &card: cards){
            int weight = 1;

            switch(card.getLevel()){
                case EASY:
                    weight = 1;
                    break;
                case MODERATE:
                    weight = 2;
                    break;
                case DIFFICULT:
                    weight = 3;
                    break;
            }
            for(int i = 0; i<weight; ++i){
                LvlCards.push_back(&card);
            }
        }

        int index = rand() % LvlCards.size();
        return *LvlCards[index];
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
            cout << "4. Quiz Mode" << endl;
            cout << "5. Exit"<<endl;
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

        Difficulty askLevel(){
            cout << "Rate the difficulty pf this card: "<<endl;
            cout << "1.Easy\n2.Moderate\n3.Difficult\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            cin.ignore();

            if(choice < 1 || choice > 3){
                choice = 2;
            }
            return static_cast<Difficulty>(choice);
        }

};

class FlashcardApp{
    private:
        UserInterface ui;
        File file;
        FlashCardManager *fm;

    //for case 1: Add Flashcard
    void addFlashcard(){
        string question = ui.getText("\nEnter the question: ");
        string answer = ui.getText("\nEnter the answer: ");

        fm->addcard(question,answer);
        cout << "\nFlashcard added successfully"<<endl;
    }

    //for case 2: review flash card 
    void reviewFlashcard(){
        if(fm->isEmpty()){
            cout << "\nNo flashcards available to review. Add some first!";
        }

        cout << "\nReview Session started!";
        cout << "\n---------------------------";

        int attempt = 0;
        int i;

        for(i=0; i<fm->getSize(); i++){
            FlashCard &card = fm->getCard(i);

            ui.showQuestion(card.getQuestion());
            cin.get();
            ui.showAnswer(card.getAnswer());
            bool correct = ui.askIfCorrect();
            card.AttemptStat(correct);

            Difficulty userRateLvl = ui.askLevel();
            card.setLevel(userRateLvl);
            attempt++;

            if(correct){
                cout << "\nGreat Job! You got it right!";
            }else{
                cout << "\nThat's okay. Keep practicing!";
            }

            if(i<(fm->getSize()-1)){
                char continueReview;
                cout << "\nContinue reviewing? (y/n): ";
                cin >> continueReview;
                cin.clear();

                if(continueReview != 'y' && continueReview != 'Y'){
                    break;
                }
            }
            fm->saveState();
        }
        cout << "\nReview session completed.";
    }

    // for case 3: view overall progress
    void viewProgress(){
        if(fm->isEmpty()){
            cout << "\nNo flashcards available. Add some first!";
        }

        cout << "\nProgress Report for"<< ui.getUsername();
        cout << "\n-----------------------------------------";

        int totalCards = fm->getSize();
        int totalAttempts = 0;
        int totalcorrect = 0;

        int easy = 0, moderate = 0, diff = 0;
        
        for(int i=0; i<totalCards; i++){
            FlashCard &card = fm->getCard(i);
            ui.showCardStats(card, i+1);

            totalAttempts += card.getAttempt();
            totalcorrect += card.getCorrect();

            switch(card.getLevel()){
                case EASY:
                    easy++;
                    break;
                case MODERATE:
                    moderate++;
                    break;
                case DIFFICULT:
                    diff++;
                    break;
            }
        }

        int overallrate;
        if(totalAttempts>0){
            overallrate = (totalcorrect*100)/totalAttempts;
        }else{
            overallrate = 0;
        }

        cout << "\nOverall Statistics: "<<endl;
        cout << "Total cards: "<< totalCards << endl;
        cout << "Total attempts: "<<totalAttempts<<endl;
        cout << "Total correct: "<<totalcorrect<<endl;
        cout << "Overall success rate: "<<overallrate<<"%"<<endl;

        //Difficulty distribution:
        cout << "\nDifficulty Distribution: "<<endl;
        cout << "Easy: "<< easy <<endl;
        cout << "Moderate: "<<moderate<< endl;
        cout << "Difficult: "<< diff << endl;
    }

    void quizMode(){
        if(fm->getSize() < 4){
            cout <<"\nNot enough flashcards to generate a quiz (minimum 4)."<<endl;
        }

        int numQuestions = max(4, fm->getSize());
        for(int q=0; q<numQuestions; ++q){
            FlashCard &correctcard = fm->getRandomCard();
            vector<string> options;
            options.push_back(correctcard.getAnswer());

            while(options.size() < 4){
                FlashCard &randomcard = fm->getRandomCard();
                string ans = randomcard.getAnswer();
                
                if(ans != correctcard.getAnswer()){
                    bool Exists = false;
                    for(string &answer: options){
                        if(answer == ans){
                            Exists = true;
                            break;
                        }
                    }
                    bool notAdded = !Exists;

                    if(notAdded){
                        options.push_back(ans); //add the option that hvnt in the list.
                    }
                }
            }
            random_shuffle(options.begin(), options.end());

            cout << "\nQ" <<(q+1)<<": "<<correctcard.getQuestion()<<endl;
            for(int i=0; i<4; i++){
                cout << i+1 <<". "<<options[i]<<endl;
            }

            cout << "Your answer (1-4): ";
            int choice;
            cin >> choice;
            cin.ignore();

            if(options[choice-1] == correctcard.getAnswer()){
                cout << "Correct!\n";
                correctcard.AttemptStat(true);
            }else{
                cout << "Incorrect. Correct answer: "<<correctcard.getAnswer()<<endl;
                correctcard.AttemptStat(false);
            }
        }
        fm->saveState();
        cout << "\nQuiz finished!\n";
    }

    public:
        FlashcardApp(){
            file = File("flashcard.dat");
            fm = new FlashCardManager(&file);
        }

        void start(){
            ui.showWelcome();

            bool running = true;
            while(running){
                ui.showMenu();
                int choice = ui.getChoice();
                
                switch(choice){
                    case 1:
                        addFlashcard();
                        break;
                    case 2:
                        reviewFlashcard();
                        break;
                    case 3:
                        viewProgress();
                        break;
                    case 4:
                        quizMode();
                        break;
                    case 5:
                        running = false;
                        break;
                    default:
                        cout << "\nInvalid choice. Please try again."<<endl;
                }
                cout << "\nThank you for using the Flashcard Generator "<<ui.getUsername()<<" !";
            }
        }



};

int main() {
    FlashcardApp app;
    app.start();
    // UserInterface ui;
    // ui.showWelcome();
    // ui.showMenu();
    return 0;
}
