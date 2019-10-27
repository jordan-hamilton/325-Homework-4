#!/usr/bin/env python3

from mergesort import mergeSort


def openFile(fileName):
    with open(fileName, 'r') as file:
        contents = file.readlines()
    return contents


def schedule(activities):
    # Start by adding the event with the latest start time to our optimal schedule
    optimalSchedule = [activities[0]]
    # Initialize the most recently selected activity for our schedule, so we can track its starting
    # time and compare that to the end time of other elements sorted by their latest start time
    lastSelected = activities[0]
    for i, activity in enumerate(activities):
        # If an activity doesn't overlap with our most recent addition to the schedule, add it to
        # the schedule and set it as our most recently added activity to the basis of our comparison
        # for a non-overlapping activity
        if activity['endTime'] <= lastSelected['startTime']:
            optimalSchedule.append(activities[i])
            lastSelected = activity

    return optimalSchedule


def printSchedule(activities, setNumber):
    print('Set %d' % setNumber)
    print('Number of activities selected = %d' % len(activities))
    print('Activities: ', end='')
    for activity in activities:
        print(activity['activityNumber'], end=' ')
    print('\n')


def main():
    activityFile = openFile('act.txt')
    readLine = 0
    setNumber = 1

    while readLine < len(activityFile):
        # Get the number of lines in our text file, whether a line is listing the number of
        # activities in a set or describing a specific activity
        activitySetSize = int(activityFile[readLine])
        # Increment the number of lines we've read from the activity text file
        readLine += 1
        # Initialize an empty list of activities
        activitySet = []

        for activity in range(activitySetSize):
            # Initialize an empty dictionary so we can map the integers on each line to specific keys
            activityDict = {}
            # Convert each line into a list each integer as its own element
            activity = activityFile[readLine].split()
            # Convert the data type to integer for each element in the list (readlines() in openFile
            # gave us strings to start)
            activity = list(map(int, activity))
            # Make sure each value from each line corresponds to the correct info about the activity
            activityDict['activityNumber'] = activity[0]
            activityDict['startTime'] = activity[1]
            activityDict['endTime'] = activity[2]
            # Add the activity to our complete list of activities to schedule
            activitySet.append(activityDict)
            # Increment the number of lines we've read after we've completed parsing the data
            readLine += 1

        # Use merge sort to return a list of dictionaries based on the the start time key in
        # descending order
        activitySet = mergeSort(activitySet, 'startTime', False)
        # Pass the activity list to our optimizeSchedule function to get a list of activities
        # that don't overlap based on their latest start times
        optimalSchedule = schedule(activitySet)
        # Output the formatted results of the optimized schedule to the terminal
        printSchedule(optimalSchedule, setNumber)
        # Increment the number of activity sets we've processed during the while loop
        setNumber += 1


if __name__ == "__main__":
    main()
