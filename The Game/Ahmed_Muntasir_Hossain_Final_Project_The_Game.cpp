/*
The Game: 
The program has a list of randomly generated 50 numbers. The program asks students to enter their student ID number. If the last 3 digits of their ID number matches any one of the randomly generated numbers, then the student wins a prize, provided that 10 prizes are remaining. 
*/
//Ahmed Muntasir Hossain - 12/08/2020

#include <iostream>
#include <ctype.h>
#include <iomanip>
#include <fstream>

#define sizeArray 50          //sizeArray is the size of 50 potential winners
#define ioFile "output.txt"   //ioFile is the input output file 

using namespace std;

void welcomeMessage();                //welcome message for the student
void seed();                          //generates a seed for the rand function
int randomStudentID();                //generates random numbers from 0 to 999
void listRandomWinners(int[]);        //inputs 50 randomly generated numbers in the studentWinners array
void sortRandomWinners(int[]);        //sorts the randomly generated numbers in the array (in ascending order) using insertion sort
void openFileToWrite(ofstream&);      //checks that the file can be opened for output
void outputToFile(ofstream&, int[]);  //writes to file the sorted array of the 50 randomly generated numbers

//reads from the sorted array and compares the last 3 digits of the inputted student ID number with all the numbers in the file
//if the number matches and any of the 10 prizes remain then the student is awarded a prize
void findWinner(int[]);      

int main() 
{
  int studentWinners[100]; //studentWinners array with expansion of up to a 100 students
  ofstream outFile;        //output file stream outFile

  welcomeMessage();
  
  listRandomWinners(studentWinners);
  sortRandomWinners(studentWinners);

  openFileToWrite(outFile);
  outputToFile(outFile, studentWinners);

  findWinner(studentWinners);

  return 0;
}

void welcomeMessage()
{
  cout << "Welcome to Prizes!" << endl; //prints a welcome message for the student
}

void seed()
{
  srand(time(NULL)); //sets the seed for the rand function
}

int randomStudentID()
{
  return rand() % 1000; //returns a random number (last 3 digits of a student ID) from 0 to 999
}

void listRandomWinners(int studentWinners[])
{
  seed(); //calls seed function

  for(int i = 0; i < sizeArray; i++) //input 50 randomly generated numbers in the studentWinners array
  {
    studentWinners[i] = randomStudentID();
  }
}

void sortRandomWinners(int studentWinners[]) //sorts the numbers in the studentWinners array using insertion sort
{  
  int i, key, j;  
  for (i = 1; i < sizeArray; i++) 
  {  
    key = studentWinners[i];  
    j = i - 1;

    //move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position 
    while (j >= 0 && studentWinners[j] > key) 
    {  
      studentWinners[j + 1] = studentWinners[j];  
      j = j - 1;  
    }

    studentWinners[j + 1] = key;  
  }  
}  

void openFileToWrite(ofstream& outFile)
{
  //checks that the ioFile is open for output
  outFile.open(ioFile);   
  if(!outFile.is_open())  
  {
    cerr << "File cannot be opened for output!" << endl;
    exit(1);
  }
}

void outputToFile(ofstream& outFile, int studentWinners[])
{
  outFile << "Student ID Numbers (Last 3 Digits) of Potential Winners:" << endl << endl;
  
  //prints a list of the 50 randomly generated numbers (potential winners) to the output file
  for(int i = 0; i < sizeArray; i++) 
  {
    outFile << setfill(' ') << setw(2) << i+1 << ". " << setfill('0') << setw(3) << studentWinners[i] << endl;
  }
  
  outFile << setfill(' ') << right; //resets iomanip to default
  
  outFile.close(); //close the output file after writing to file is complete
}

void findWinner(int studentWinners[])
{
  int studentID;  //student ID number
  int count = 0;  //counts the number of students who have received prizes
  int flag;       //flag is changed to 1 when a student wins a prize
  char response;  //response from the student 

  do
  {
    flag = 0;   //flag is initally set to 0

    cout << "\nPlease enter your Student ID number: " << flush; //prompts the student to enter their student ID number
    cin >> studentID;

    studentID = studentID % 1000;  //computes the last 3 digts of the student ID and sets studentID to that value

    //loops through the array and checks if the last 3 digits of the student ID matches any of the numbers in the array
    for(int i = 0; i < sizeArray && count < 10; i++) 
    {
      if(studentID == studentWinners[i]) //if the number matches, the student won the prize 
      {
        cout << "\nCongratulations! You have won the prize!" << endl; //print the following message
        flag = 1;                                                     //set flag to 1
        count++;                                                      //increment count of students who have won the prize
        break;                                                        //break from the loop
      }
    }

    if(count == 10) //if 10 prizes have been given out, print the following message and exit
    {
      cout << "\n10 prizes have already been given out! Thank you for playing! Please try again next week." << endl;
      exit(1);
    }

    if(flag == 0) //if flag is equal to 0, then the student did not win a prize
    {
      cout << "\nSorry! You have not won a prize." << endl; //print the following message
    }
    
    //ask the student if they would like to continue
    cout << "\nDo you want to continue (Select 'Y' for yes or 'N' for no): " << flush; 
    cin >> response;
    response = toupper(response);
  }
  while(response == 'Y'); //loops if the student says yes (Y)

  //if the student decides to not play, print the following thank you message
  cout << "\nThank you for playing! Come again next week." << endl; 
}