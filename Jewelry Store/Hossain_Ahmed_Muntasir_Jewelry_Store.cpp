/*
Jewelry Store: 
The program computes the individual and total price of the jewelries.
*/
//Ahmed Muntasir Hossain - 11/04/2020

#include <iostream>
#include <fstream>
#define jewelFile "jewels.txt" 
#define output "output.txt"
using namespace std;

void individualPrice(string[], string[], double[], double[], int, ofstream&); // caculates the individual price of each jewelry
double totalPrice(double[], int); //calculates total price
int main() 
{

  cout << "Welcome! My name is Muntasir Hossain" <<
  " and this is the Jewelry Store." << endl;


  ifstream dataFile (jewelFile); //checks that input file is open
  if(!dataFile.is_open())
  {
    cerr << "\nFile cannot be opened for input." << endl;
    exit(1);
  }

  ofstream outFile (output); //checks that output file is open
  if(!outFile.is_open())
  {
    cerr << "\nFile cannot be opened for output." << endl;
    exit(1);
  }

  outFile << "Welcome! My name is Muntasir Hossain" <<
  " and this is the Jewelry Store." << endl;

  string jewelTypeV; //jewel type variable
  string metalTypeV; //metal type var
  double caratWeightV; // carat weight var

  string jewelType[100]; // arrays to hold information for each typer
  string metalType[100];
  double caratWeight[100];

  int size;

  for(int i = 0; !dataFile.eof(); i++)
  {
    dataFile >> jewelTypeV >> metalTypeV >> caratWeightV;

    if((jewelTypeV == "ruby" || jewelTypeV == "diamond" || jewelTypeV == "opal") && (metalTypeV == "gold" || metalTypeV == "platinum" || metalTypeV == "silver") && (caratWeightV > 0))
    {
      jewelType[i] = jewelTypeV;
      metalType[i] = metalTypeV;
      caratWeight[i] = caratWeightV;
    }
    else
    {
    cout << "\nError! Invalid data inputted. Jewel Type: " << jewelTypeV << ", Metal Type: " << metalTypeV << ", Carat Weight: " << caratWeightV << endl << endl;
    outFile << "\nError! Invalid data inputted. Jewel Type: " << jewelTypeV << ", Metal Type: " << metalTypeV << ", Carat Weight: " << caratWeightV << endl << endl;
    i--;
    }
    size = i + 1; //size of the arrays. Arrays only contain valid data
  }

double price[100];
double weight;

//loops through and checks the type of jewel and weight. if weight is greater than or equal 2, the price is multiplied by 2
//price is stored in the price array
for(int i = 0; i < size; i++)
{
  weight = caratWeight[i];

  if(jewelType[i] == "ruby" && weight >=2)
  {
    price[i] = 8000 * 2 * weight;
  }

  else if(jewelType[i] == "ruby" && weight < 2)
  {
    price[i] = 8000 * weight;
  }

  else if(jewelType[i] == "diamond" && weight >=2)
  {
    price[i] = 5000 * 2 * weight;
  }

  else if(jewelType[i] == "diamond" && weight < 2)
  {
    price[i] = 5000 * weight;
  }

  else if(jewelType[i] == "opal" && weight >=2)
  {
    price[i] = 3000 * 2 * weight;
  }

  else if(jewelType[i] == "opal" && weight < 2)
  {
    price[i] = 3000 * weight;
  }
}

//loops through and calculates total price based on metal type

for(int i = 0; i < size; i++) 
{
  if(metalType[i] == "gold")
  {
    price[i] += 1500;
  }

  else if(metalType[i] == "platinum")
  {
    price[i] += 3000;
  }

  else if(metalType[i] == "silver")
  {
    price[i] += 250;
  }
}

individualPrice(metalType, jewelType, caratWeight, price, size, outFile);

cout << "\nTotals: " << size  <<  " pieces of jewelry for $" <<  totalPrice(price, size) << endl;
outFile << "\nTotals: " << size  <<  " pieces of jewelry for $" <<  totalPrice(price, size) << endl;

cout << "\nThank you for coming to the Jewelry Store" << endl;
outFile << "\nThank you for coming to the Jewelry Store" << endl;

return 0;
}

void individualPrice(string metalType[], string jewelType[], double caratWeight[], double price[], int size, ofstream& outFile)
{
  for(int i = 0; i < size; i++)
  {
    cout << "Your jewelry will be " << metalType[i] << " metal with a " << caratWeight[i] << " carat " << jewelType[i] << " and the price is $" << price[i] << endl;

    
    outFile << "Your jewelry will be " << metalType[i] << " metal with a " << caratWeight[i] << " carat " << jewelType[i] << " and the price is $" << price[i] << endl;
    
  }
}

double totalPrice(double price[], int size)
{
  double sum = 0;

  for(int i = 0; i < size; i++)
  {
    sum += price[i];
  }

  return sum;
}