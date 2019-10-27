#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::ofstream;
using std::string;
using std::vector;

vector<int> mergeSort(vector<int>* list);
vector<int> merge(vector<int>* list1, vector<int>* list2);

int main() {

  ifstream inputFile;
  ofstream outputFile;
  string inFileName, outFileName;
  istringstream stream;
  string tempString;
  vector<int> numbers;
  int toSort;

  // Prompt for a file name until the specified name can be opened.
  do {
    std::cout << "Please enter the name of a file to read: " << endl;
    getline(cin, inFileName);
    inputFile.open(inFileName);
  } while (!inputFile);

  while (getline(inputFile, tempString)) {
    // Loop through each line of the file, putting the line into a string stream
    stream.str(tempString);
    stream >> tempString;
    // Set the first integer in the line as the number of integers to sort
    toSort = stoi(tempString);

    // Loop through the remainder of the string stream, adding the specified
    // number of integers to the back of a vector
    for (int i = 0; i < toSort; i++) {
      stream >> tempString;
      numbers.push_back(stoi(tempString));
    }

    //DEBUG
    cout << "Vector:" << endl;
    for (int i = 0; i < numbers.size(); i++) {
      cout << numbers.at(i) << endl;
    }
    numbers = mergeSort(&numbers);
    //DEBUG
    cout << "Vector:" << endl;
    for (int i = 0; i < numbers.size(); i++) {
      cout << numbers.at(i) << endl;
    }

    outputFile.open("merge.txt", std::ios_base::app);
    for (int i = 0; i < numbers.size(); i++) {
      outputFile << numbers.at(i) << " ";
    }
    outputFile << "\n";
    outputFile.close();

    numbers.clear();
    stream.clear();
  }

  inputFile.close();

  return 0;

}

vector<int> mergeSort(vector<int>* list) {
  if (list->size() == 1) {
    // Handle the base case
    return *list;
  } else {
    // Split the vector into two vectors, then call mergeSort on each half
    int half = list->size() / 2;
    //DEBUG: Pass subarray (using iterator?) to mergeSort without making more vectors?
    vector<int> firstHalf (list->begin(), list->begin() + half);
    vector<int> secondHalf (list->begin() + half, list->end());
    firstHalf = mergeSort(&firstHalf);
    secondHalf = mergeSort(&secondHalf);
    return merge(&firstHalf, &secondHalf);
  }
}

vector<int> merge(vector<int>* list1, vector<int>* list2) {
  if (list1->size() == 0) {
    return *list2;
  }
  if (list2->size() == 0) {
    return *list1;
  }

  vector<int> temp;
  int i = 0, j = 0;

  //DEBUG: Remove from list? Value/reference?
  while (i < list1->size() && j < list2->size()) {
    if (list1->at(i) < list2->at(j)) {
      temp.push_back(list1->at(i));
      i++;
    } else {
      temp.push_back(list2->at(j));
      j++;
    }
  }

  // After exhausting one vector, add any remaining numbers to the end of our
  // temporary vector
  while (i < list1->size()) {
    temp.push_back(list1->at(i));
    i++;
  }
  while (j < list2->size()) {
    temp.push_back(list2->at(j));
    j++;
  }
  // Return our vector after iterating through both of the passed vectors
  return temp;
}
