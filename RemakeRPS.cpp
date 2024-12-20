#include <iostream>
#include <iomanip>
#include <ctime>
#include <unistd.h>
#include <unordered_map>

#define OSClear "clear" // Use "cls" for Windows

using namespace std;

void SleepFunction() 
{
    sleep(1);
}

void gameload(char LetterArray[], void (*SleepFun)(), int num)
{
    SleepFun();
    cout << LetterArray[num];
}

void load() 
{
    char loadingletter[] = {'L', 'o', 'a', 'd', 'i', 'n', 'g'};
    for (int i = 0; i < 7; ++i) 
    {
        gameload(loadingletter, SleepFunction, i);
        
    }
    system(OSClear);
}

void Menu(void (*Sleep1)())
 {
    string menu[] = 
    {
        "|__________remake___________menu______game_______|",
        "|                                                |",
        "|  Hello this is a rock, paper,and scissors game,|",
        "|  The rules are simple:                         |",
        "|  - Rock beats scissors                         |",
        "|  - Paper beats rock                            |",
        "|  - Scissors beats paper                        |",
        "|  Enter 'hc' for Human vs Computer              |",
        "|  Enter 'cc' for Computer vs Computer           |",
        "|________________________________________________|"};

    for (const auto &line : menu) {
        cout << setfill(' ') << setw(85) << line << endl;
        Sleep1();
    }
}

string get_computer_move() 
{
    const string moves[] = {"rock", "paper", "scissors"};
    return moves[rand() % 3];
}

string determine_winner(const string &move1, const string &move2) {
    unordered_map<string, unordered_map<string, string>> rules =
     {
        {"rock", {{"rock", "Tie"}, {"paper", "Computer 2 wins"}, {"scissors", "Computer 1 wins"}}},
        {"paper", {{"rock", "Computer 1 wins"}, {"paper", "Tie"}, {"scissors", "Computer 2 wins"}}},
        {"scissors", {{"rock", "Computer 2 wins"}, {"paper", "Computer 1 wins"}, {"scissors", "Tie"}}}
     };

    return rules[move1][move2];
}

void play_game(bool GameSwitch, void (*Sleep1)()) 
{
    static int round = 0;
    static int HumanPlayer1Points = 0;
    static int ComputerPlayer1Points = 0;
    static int ComputerPlayer2Points = 0;
    static int HumanMistake = 0;
    string WhoIsPlaying;

    if (round == 0) 
    {
        cout << "Enter 'hc' for Human vs Computer or 'cc' for Computer vs Computer: ";
        cin >> WhoIsPlaying;
    }

    while (GameSwitch) 
    {
        srand(time(NULL));
        string HumanInput, ComputerPlayer1Move, ComputerPlayer2Move;
        int HumanPlayer1Choice;
        
        if (WhoIsPlaying == "hc") 
        {
            system(OSClear);
            cout << "Human Points: " << HumanPlayer1Points << " | Computer Points: " << ComputerPlayer2Points << " | Mistakes: " << HumanMistake << " | Round: " << round << "\n\n";
            cout << "Enter your move (rock, paper, scissors): ";
            cin >> HumanInput;
        } 
        else if (WhoIsPlaying == "cc") 
        {
            system(OSClear);
            cout << "Computer 1 Points: " << ComputerPlayer1Points << " | Computer 2 Points: " << ComputerPlayer2Points << " | Round: " << round << "\n\n";
        }

        if (WhoIsPlaying == "hc") 
        {
            unordered_map<string, int> move_map = {{"rock", 0}, {"paper", 1}, {"scissors", 2}};
            if (move_map.find(HumanInput) != move_map.end()) 
            {
                HumanPlayer1Choice = move_map[HumanInput];
            } 
            else
             {
                HumanMistake++;
                if (HumanMistake >= 3) 
                {
                    cout << "Too many mistakes. Game Over.\n";
                    GameSwitch = false;
                    break;
                } 
                else
                 {
                    cout << "Invalid input. Try again.\n";
                    continue;
                }
            }
        }

        ComputerPlayer1Move = get_computer_move();
        ComputerPlayer2Move = get_computer_move();

        if (WhoIsPlaying == "hc") {
            string result = determine_winner(HumanInput, ComputerPlayer2Move);
            cout << "You chose: " << HumanInput << ", Computer chose: " << ComputerPlayer2Move << " - " << result << endl;
            if (result == "Computer 2 wins") {
                ComputerPlayer2Points++;
            } else if (result == "Computer 1 wins") {
                HumanPlayer1Points++;
            }
        } else if (WhoIsPlaying == "cc") {
            string result = determine_winner(ComputerPlayer1Move, ComputerPlayer2Move);
            cout << "Computer 1 chose: " << ComputerPlayer1Move << ", Computer 2 chose: " << ComputerPlayer2Move << " - " << result << endl;
            if (result == "Computer 2 wins") {
                ComputerPlayer2Points++;
            } else if (result == "Computer 1 wins") {
                ComputerPlayer1Points++;
            }
        }

        round++;
        if (ComputerPlayer2Points >= 3 || HumanPlayer1Points >= 3 || ComputerPlayer1Points >= 3) 
        {
            if (ComputerPlayer2Points >= 3) 
            {
                cout << "Computer 2 wins the game!\n";
            } 
            else if (HumanPlayer1Points >= 3) 
            {
                cout << "Human wins the game!\n";
            } 
            else if (ComputerPlayer1Points >= 3)
             {
                cout << "Computer 1 wins the game!\n";
             }
            GameSwitch = false;
        }

        Sleep1();
    }
}

int main() 
{
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    bool GameSwitch = true;
    system(OSClear);
    load();
    Menu(SleepFunction);
    play_game(GameSwitch, SleepFunction);
    return 0;
}