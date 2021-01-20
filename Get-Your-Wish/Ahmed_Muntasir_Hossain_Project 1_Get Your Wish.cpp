/*
Get Your Wish: 
The program asks the user to guess the rank and suit of a randomly generated card.
*/
//Ahmed Muntasir Hossain - 10/28/2020

#include <iostream>
#include <iomanip>
#include <string.h>
#include <ctype.h>

using namespace std;

void randomCardGenerator(int*, int*);           //generates a random index for the suit and rank arrays
void menu();                                    //welcomes the user to the program
void userGuessSuit(string[], int);              //prompts the user to guess the suit of the card
void menuSuits(string[]);                       //prints the name of the suits available in the deck
void userGuessRank(string[], int);              //prompts the user to guess the rank of the card
void menuRanks(string[]);                       //prints the ranks available in the deck 
void endScreen(string[], string[], int, int);   //prints the correct suit and rank of the card when the user guesses both correctly

int main() 
{
  int randomSuitIndex; //value of the random index generated for the suit array
  int randomRankIndex; //value of the random index generated for the rank array
  char response;

  string suit[] = {"HEARTS", "DIAMONDS", "CLUBS", "SPADES"}; //string array containing the suits
  string rank[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "JACK", "QUEEN", "KING", "ACE"}; //string array containing the ranks

  do
  {
  randomCardGenerator(&randomSuitIndex, &randomRankIndex);

  menu();

  userGuessSuit(suit, randomSuitIndex);

  userGuessRank(rank, randomRankIndex);

  endScreen(suit, rank, randomSuitIndex, randomRankIndex);

  cout << "\nDo you want to play again (Select 'Y' for yes or 'N' for no): " << flush; //asks the user if she/he wants to play again
  cin >> response;
  response = toupper(response);
  }
  while(response == 'Y'); //loops if the user says yes ('Y')
}


void randomCardGenerator(int* randomSuitIndexPointer, int* randomRankIndexPointer)
{
  srand(time(NULL)); 

  *randomSuitIndexPointer = rand() % 4;  //generates a random value between 0 - 3. Pointer to the randomSuitIndex
  *randomRankIndexPointer = rand() % 13; //generates a random value between 0 - 12. Pointer to the randomRankIndex

  //cout << *randomSuitIndexPointer << endl; //prints the random suit index for testing use
  //cout << *randomRankIndexPointer << endl; //prints the random rank index for testing use
}

void menu()
{
  //welcome message for the user
  cout << "\nGet Your Wish" << endl << endl;  
  cout << "I am a Genie!\nI can grant any wish of yours but there is a catch.\nI will choose a single card" 
  " from this deck of cards and you have to guess which card I chose."
  "\nIf you can guess the suit and rank of the card, your wish will be granted!" << endl << endl;

  cout << "Let's Begin:" << endl << endl;
}

void userGuessSuit(string suit[], int randomSuitIndex)
{
  string userSuitInput; //suit inputted by the user

  cout << "Here are the suits: " << endl; //prints the suits available in the deck for the user to guess from
  menuSuits(suit);

  cout << "Please guess the suit of the card that I chose: " << flush; //prompts the user to guess/type the name of the suit
  cin >> userSuitInput;

  if(userSuitInput == "0") //user exits the program if she/he selects 0
  {
    cout << "\nThank you for playing!" << endl;
    exit(0);
  }

  int flag;   //flag is equal 0 if the user's guess is within the range of available suits
  int check;  //check is equal 0 if user guesses the suit correctly
  
  do //loops until the user guesses the correct suit or quits
  {
    int inputLength = userSuitInput.length();
    char cstringUserSuitInput[inputLength + 1];
    strcpy(cstringUserSuitInput, userSuitInput.c_str()); //copies the C++ string (user's input) to a c_string

    for(int i = 0; i < userSuitInput.length(); i++) //converts the c_string to uppercase letters
    {
      cstringUserSuitInput[i] = toupper(cstringUserSuitInput[i]);
    }

    for(int i = 0; i < 4; i++) 
    {
      flag = strcmp(cstringUserSuitInput, suit[i].c_str()); //compares to see if the user's input matches any of the suits in the array
      if(flag == 0) //if true, the program checks if the user's input is correct or not
      {
        check = strcmp(cstringUserSuitInput, suit[randomSuitIndex].c_str()); //check = 0, if user guesses the suit correctly
        break;
      }
    }

    if(flag != 0) //if flag != 0, then the user's input is an invalid choice (not a suit).
    {
      cout << endl << "Invalid Choice." << endl << endl;
      cout << "Please choose from the following suits:" << endl; //prints the menu of suits to choose from
      menuSuits(suit);
    }

    else if(check != 0) //if check != 0, then the user's input is a valid suit but the user guessed incorrectly
    {
      cout << "\nWrong Choice!\nPlease try again." << endl; //asks the user to try again or quit
      cout << "OR select 0 to quit!" << endl << endl;
    }

    else //the user guessed the suit correctly and the program breaks out of the loop
      break;
    
    cout << "Please Choose an Option: " << flush; //prompts the user to choose an option
    cin >> userSuitInput;

    if(userSuitInput == "0") //user exits the program if she/he selects 0
    {
      cout << "\nThank you for playing!" << endl;
      exit(0);
    }
  }
  while(flag != 0 || check != 0); 
  cout << "You have guessed the correct suit of the card!" << endl; //prints message when the user guesses the suit correctly

}

void menuSuits(string suit[])
{
  for(int i = 0; i < 4; i++) //prints the name of the suits in a deck
  {
    cout << i+1 << ". " << suit[i] << endl;  
  }
  cout << "OR select 0 to quit!" << endl << endl; //last option in the menu is to select 0 to quit
}

void userGuessRank(string rank[], int randomRankIndex)
{
  string userRankInput; //rank inputted by the user

  cout << "\nHere are the ranks: " << endl; //prints the ranks available in the deck for the user to guess from
  menuRanks(rank);

  cout << "Please guess the rank of the card that I chose: " << flush; //prompts the user to guess/type the rank
  cin >> userRankInput;

  if(userRankInput == "0") //user exits the program if she/he selects 0
  {
    cout << "\nThank you for playing!" << endl;
    exit(0);
  }

  int flag;  //flag is equal 0 if the user's guess is within the range of available ranks
  int check; //check is equal 0 if user guesses the rank correctly
  
  do //loops until the user guesses the correct rank or quits
  {
    int inputLength = userRankInput.length();
    char cstringUserRankInput[inputLength + 1];
    strcpy(cstringUserRankInput, userRankInput.c_str()); //copies the C++ string (user's input) to a c_string

    for(int i = 0; i < userRankInput.length(); i++) //converts the c_string to uppercase letters
    {
      cstringUserRankInput[i] = toupper(cstringUserRankInput[i]);
    }

    for(int i = 0; i < 13; i++)
    {
      flag = strcmp(cstringUserRankInput, rank[i].c_str()); //compares to see if the user's input matches any of the ranks in the array
      if(flag == 0) //if true, the program checks if the user's input is correct or not
      {
        check = strcmp(cstringUserRankInput, rank[randomRankIndex].c_str()); //check = 0, if user guesses the suit correctly 
        break; 
      }
    }

    if(flag != 0) //if flag != 0, then the user's input is an invalid choice (not a rank).
    {
      cout << endl << "Invalid Choice." << endl << endl;
      cout << "Please choose from the following ranks:" << endl; //prints the menu of ranks to choose from
      menuRanks(rank);
    }

    else if(check != 0) //if check != 0, then the user's input is a valid rank but the user guessed incorrectly
    {
      cout << "\nWrong Choice!\nPlease try again." << endl; //asks the user to try again or quit
      cout << "OR select 0 to quit!" << endl << endl;
    }

    else //the user guessed the rank correctly and the program breaks out of the loop
      break;
    
    cout << "Please Choose an Option: " << flush; //prompts the user to choose an option
    cin >> userRankInput;

    if(userRankInput == "0") //user exits the program if she/he selects 0
    {
      cout << "\nThank you for playing!" << endl;
      exit(0);
    }
  }
  while(flag != 0 || check != 0);
  cout << "You have guessed the correct rank of the card!" << endl; //prints message when the user guesses the rank correctly
}

void menuRanks(string rank[])
{
  for(int i = 0; i < 13; i++) //prints the ranks in a deck
  {
    cout << setw(2) << i+1 << ". " << rank[i] << endl;  
  }
  cout << "OR select 0 to quit!" << endl << endl; //last option in the menu is to select 0 to quit
}

void endScreen(string suit[], string rank[], int randomSuitIndex, int randomRankIndex)
{
  //prints the end message when the user guesses the suit and rank (card) correctly. Prints the suit and rank of the guessed card. 
  cout << "\nCongratulations! You have guessed the correct card: " << rank[randomRankIndex] << " of " << suit[randomSuitIndex] << endl;
  cout << "Thank you for playing!" << endl;
}

