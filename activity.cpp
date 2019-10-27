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

struct activity {
  int activityNumber;
  int startTime;
  int finishTime;
  bool inOptimal = false;
};

vector<activity> schedule(vector<activity>* activities);
void printSchedule(vector<activity>* schedule, int* setNumber);
vector<activity> mergeSort(vector<activity>* list);
vector<activity> merge(vector<activity>* list1, vector<activity>* list2);

int main() {

  ifstream inputFile;
  ofstream outputFile;
  string inFileName, outFileName, tempString;
  istringstream stream;
  vector<activity> activities, optimalSchedule;
  int set = 1, toSort;

  // Prompt for a file name until the specified name can be opened
  do {
    std::cout << "Please enter the name and extension of a text file to read: " << endl;
    getline(cin, inFileName);
    inputFile.open(inFileName);
  } while (!inputFile);

  while (getline(inputFile, tempString)) {
    toSort = stoi(tempString);

    while (toSort > 0) {
      getline(inputFile, tempString);
      stream.str(tempString);

      activities.push_back(activity());
      stream >> activities.at(activities.size() - 1).activityNumber;
      stream >> activities.at(activities.size() - 1).startTime;
      stream >> activities.at(activities.size() - 1).finishTime;

      stream.clear();
      toSort--;
    }

    // Sort activities by start time in descending order
    activities = mergeSort(&activities);

    // Pass the sorted vector by reference to get an optimal schedule
    optimalSchedule = schedule(&activities);

    // Output an optimal schedule to the screen
    printSchedule(&optimalSchedule, &set);

    // Empty the vectors to prepare for the next set of activities to schedule
    activities.clear();
    optimalSchedule.clear();
    set++;

  }

  inputFile.close();
  return 0;

}

vector<activity> schedule(vector<activity>* activities) {
  vector<activity> optimalSchedule;

  // Start by adding the activity with the latest start time to our schedule
  optimalSchedule.push_back(activities->at(0));
  activities->at(0).inOptimal = true;

  // Track the most recently added activity in variable i, loop through the
  // remaining activities, and continue adding the activity with the next latest
  // start time that doesn't have an overlapping finish time with our most
  // recently added activity. Update i to the index of a newly added activity
  // so we're comparing with the most recently added activity for each new
  // addition to the schedule
  int i = 0;
  for (int j = 1; j < activities->size(); j++) {
    if (activities->at(j).finishTime <= activities->at(i).startTime) {
      optimalSchedule.push_back(activities->at(j));
      activities->at(j).inOptimal = true;
      i = j;
    }
  }

  return optimalSchedule;

}

void printSchedule(vector<activity>* schedule, int* setNumber) {
  cout << "Set " << *setNumber << endl;
  cout << "Number of activities selected: " << schedule->size() << endl;
  cout << "Activities: ";

  for (int i = schedule->size() - 1; i >= 0; i--) {
    cout << schedule->at(i).activityNumber;
    if (i != 0) {
      cout << ",";
    }
    cout << " ";
  }

  cout << endl << endl;
}

vector<activity> mergeSort(vector<activity>* list) {
  if (list->size() == 1) {
    // Handle the base case
    return *list;
  } else {
    // Split the vector into two vectors, then call mergeSort on each half
    int half = list->size() / 2;

    vector<activity> firstHalf (list->begin(), list->begin() + half);
    vector<activity> secondHalf (list->begin() + half, list->end());
    firstHalf = mergeSort(&firstHalf);
    secondHalf = mergeSort(&secondHalf);
    return merge(&firstHalf, &secondHalf);
  }
}

vector<activity> merge(vector<activity>* list1, vector<activity>* list2) {
  // Return the entirety of one of our vectors if the other is empty
  if (list1->size() == 0) {
    return *list2;
  }
  if (list2->size() == 0) {
    return *list1;
  }

  vector<activity> temp;
  int i = 0, j = 0;

  while (i < list1->size() && j < list2->size()) {
    if (list1->at(i).startTime > list2->at(j).startTime) {
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
