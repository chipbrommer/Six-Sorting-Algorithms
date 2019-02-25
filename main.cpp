/***************************************************************************************************
 *
 * Author: Chip Brommer
 * Date: February 13, 2019
 * Contact: Fredrick.Brommer@usm.edu
 * Class: CSC 413 - Algorithms
 * Professor: Dr. Zhou
 *
 * Description: Create a program to use 6 sorting algorithsm: Merge, Insertion, Selection, Bubble,
                Quick, and Heap.
 
 ***************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <algorithm>


using namespace std;

void welcomeMessage(fstream&);
void mainMenu(fstream&);
void mainMenuSwitch(int, fstream&);
void elementMenu(fstream&);
void elementMenuSwitch(fstream&, int);
void premadeMenu(fstream&);
void premadeSwitch(fstream&, int);
void generationMenu(fstream&);
void sortMenu(fstream&, int[], int);
void sortMenuSwitch(fstream&, int[], int, int);
void insertionSort(fstream&, int[], int);
void selectionSort(fstream&, int[], int);
void bubbleSort(fstream&, int[], int);
void mergeSort(fstream&, int[], int);
void mergeSortRecursion(int[], int, int);
void mergeArrays(int[], int, int, int);
void quickSort(fstream&, int[], int);
void quickSortRecursion(int[], int, int);
int quickSortParter(int[], int, int);
void heapSort(fstream&, int[], int);
void heap(int[], int, int);
void arrayPrinter(fstream&, int[], int);
void useAgain(fstream&, int[], int);
bool integerVerify(int);
int integerSizeRestrictor(int);
int randomNumberGenerator();
void programEnd();


int main()
{
    //Time based random number generator for the program.
    //This is in main so it only gets called once and starts upon program run.
    srand((unsigned int) time(NULL));
    
    //Creating new txt file for console output
    fstream mytxtfile;
    mytxtfile.open("Project1 - Output.txt", fstream::out);
 
    //Calling the main welcome message
    welcomeMessage(mytxtfile);
    
    //Calling the main menu
    mainMenu(mytxtfile);
    
    //Calling the closing procedure for the program.
    programEnd();
    
    return 0;
}


//-------------------------------------------------------------------------------------------------
//welcomeMessage - This function holds the welcome message for the program and prints it to the
//                 console for the user.
//-------------------------------------------------------------------------------------------------
void welcomeMessage(fstream & mytxtfile)
{
    cout << "\t\t\t\t\tChips Sorting Project\n"
    << "\t\t------------------------------------------\n\n";
    mytxtfile << "\t\t\t\t\tChips Sorting Project\n"
    << "\t\t------------------------------------------\n\n";
}

//-------------------------------------------------------------------------------------------------
//mainMenu - This is the main menu for the project. Gives the user the option to input a group of
//           numbers, generate an array of random number, or exit.
//-------------------------------------------------------------------------------------------------
void mainMenu(fstream & mytxtfile)
{
    //Holds the users selection
    int userSelection = 0;
    
    //Displaying menu options
    cout << "Main Menu:" << endl;
    cout << "_______________________" << endl;
    cout << "  1: Enter an array to be sorted" << endl;
    cout << "  2: Use a pre-made array" << endl;
    cout << "  3: Randomly generate an array to be sorted" << endl;
    cout << "  4: Exit" << endl;
    
    //Displaying menu options to the txt file
    mytxtfile << "Main Menu:" << endl;
    mytxtfile << "_______________________" << endl;
    mytxtfile << "  1: Enter an array to be sorted" << endl;
    mytxtfile << "  2: Use a pre-made array" << endl;
    mytxtfile << "  3: Randomly generate an array to be sorted" << endl;
    mytxtfile << "  4: Exit" << endl;
    
    //Recieving the user selection
    cout << "\n\tYour Selection: ";
    cin >> userSelection;
    
    //Verifies input is an integer. IF NOT, requests new input
    while(!integerVerify(userSelection))
    {
        cout << "Please Enter a Selection: ";
        cin >> userSelection;
    }
    
    //Spacer Line
    cout << endl;
    
    //Displaying the user selection to the txt file
    mytxtfile << "\n\tYour Selection: " << userSelection << endl << endl;
    
    //Calling the main menu switch
    mainMenuSwitch(userSelection, mytxtfile);
}

//---------------------------------------------------------------------------------------
//mainMenuSwitch - This function uses a switch-case for the user entered selection
//                 in the main menu
//---------------------------------------------------------------------------------------
void mainMenuSwitch(int userSelection, fstream& mytxtfile)
{
    //Setting up the switch for the user selection
    switch (userSelection)
    {
        case 1://Enter an array
        {
            elementMenu(mytxtfile);
            break;
        }
        case 2://Use a pre-made array
        {
            premadeMenu(mytxtfile);
            break;
        }
        case 3://Randomly Generate an array
        {
            generationMenu(mytxtfile);
            break;
        }
        case 4://Exit
        {
            //Does not call anything, just breaks out, and by order in the main, exits program
            break;
        }
        default://Invalid selection
        {
            cout << "\t::Invalid Selection::\n";
            mainMenu(mytxtfile);
            break;
        }
    }
}

//-------------------------------------------------------------------------------------------------
//elementMenu - This is the menu for the user to select how many elements of an array they would
//              like to enter.
//-------------------------------------------------------------------------------------------------
void elementMenu(fstream & mytxtfile)
{
    int elementChoice = 0;  //Holds the users choice for the number of elements
    
    //DIsplaying options to the user
    cout << "Array Elements Selection:" << endl;
    cout << "_______________________" << endl;
    cout << "  1: 5" << endl;
    cout << "  2: 10" << endl;
    cout << "  3: 20" << endl;
    cout << "  4: Exit to Main Menu" << endl;
    
    //Displaying the options to the txt file
    mytxtfile << "Array Elements Selection:" << endl;
    mytxtfile << "_______________________" << endl;
    mytxtfile << "  1: 5" << endl;
    mytxtfile << "  2: 10" << endl;
    mytxtfile << "  3: 20" << endl;
    mytxtfile << "  4: Exit to Main Menu" << endl;
    
    cout << "\n\tYour Selection: ";
    cin >> elementChoice;
    
    //Verifies input is an integer. IF NOT, requests new input
    while(!integerVerify(elementChoice))
    {
        cout << "Please Enter a Selection: ";
        cin >> elementChoice;
    }
    
    //Displaying the user selection to the txt file
    mytxtfile << "\n\tYour Selection: " << elementChoice << endl;
    
    //Calling the switch
    elementMenuSwitch(mytxtfile, elementChoice);
}

//---------------------------------------------------------------------------------------
//elementMenuSwitch - This function uses a switch-case for the user entered selection
//                 in the number of elements function
//---------------------------------------------------------------------------------------
void elementMenuSwitch(fstream& mytxtfile, int elementChoice)
{
    int elementInput = 0;   //Holds the users input for the value to place in the array element
    int length = 0;         //Holds the length of the users choice for the array.
    
    int array[20];          //Holds the array created with a max size of 20.
    
    //Setting up the switch for the user selection
    switch (elementChoice)
    {
        case 1://Length = 5
        {
            length = 5;
            
            cout << "\nPlease enter a value for each element between -1000 to 1000.\n";
            mytxtfile << "\nPlease enter a value for each element between -1000 to 1000.\n";
            cout << endl;   //Spacer line
            
            //For loop for user to fill the array elements.
            for (int i = 0; i < length; i++)
            {
                cout << "\tEnter a number for element " << i+1 << ": ";
                cin >> elementInput;
                
                //Verifies input is an integer. IF NOT, requests new input
                while(!integerVerify(elementInput))
                {
                    cout << "\tPlease Enter a number: ";
                    cin >> elementInput;
                }
                
                //Checking to make sure the number is within size.
                //And then assigning it into the array
                array[i] = integerSizeRestrictor(elementInput);
                
                //Displaying the user input to the txt file
                mytxtfile << "\tEnter a number for element " << i+1 << ": " << array[i] << endl;
            }
            
            //Calling the switch for how the user wants to solve
            sortMenu(mytxtfile, array, length);
            break;
        }
        case 2://Length = 10
        {
            length = 10;
            
            cout << "\nPlease enter a value for each element between -1000 to 1000.\n";
            mytxtfile << "\nPlease enter a value for each element between -1000 to 1000.\n";
            cout << endl;   //Spacer line
            
            //For loop for user to fill the array elements.
            for (int i = 0; i < length; i++)
            {
                cout << "\tEnter a number for element " << i+1 << ": ";
                cin >> elementInput;
                
                //Verifies input is an integer. IF NOT, requests new input
                while(!integerVerify(elementInput))
                {
                    cout << "\tPlease Enter a number: ";
                    cin >> elementInput;
                }
                
                //Checking to make sure the number is within size.
                //And then assigning it into the array
                array[i] = integerSizeRestrictor(elementInput);
                
                //Displaying the user input to the txt file
                mytxtfile << "\tEnter a number for element " << i+1 << ": " << array[i] << endl;
            }
            
            //Calling the switch for how the user wants to solve
            sortMenu(mytxtfile, array, length);
            break;
        }
        case 3://Length = 20
        {
            length = 20;
            
            cout << "\nPlease enter a value for each element between -1000 to 1000.\n";
            mytxtfile << "\nPlease enter a value for each element between -1000 to 1000.\n";
            cout << endl;   //Spacer line
            
            //For loop for user to fill the array elements.
            for (int i = 0; i < length; i++)
            {
                cout << "\tEnter a number for element " << i+1 << ": ";
                cin >> elementInput;
                
                //Verifies input is an integer. IF NOT, requests new input
                while(!integerVerify(elementInput))
                {
                    cout << "\tPlease Enter a number: ";
                    cin >> elementInput;
                }
                
                //Checking to make sure the number is within size.
                //And then assigning it into the array
                array[i] = integerSizeRestrictor(elementInput);
                
                //Displaying the user input to the txt file
                mytxtfile << "\tEnter a number for element " << i+1 << ": " << array[i] << endl;
            }
            
            //Calling the switch for how the user wants to solve
            sortMenu(mytxtfile, array, length);
            break;
        }
        case 4://main Menu
        {
            mainMenu(mytxtfile);
            break;
        }
        default://Invalid selection
        {
            cout << "\t::Invalid Selection::\n\n";
            elementMenu(mytxtfile);
            break;
        }
    }
}

//-------------------------------------------------------------------------------------------------
//premadeMenu - This is the a menu for the user to pick from some pre made arrays.
//-------------------------------------------------------------------------------------------------
void premadeMenu(fstream & mytxtfile)
{
    int premadeSelection = 0;
    
    //Displaying options to the user
    cout << "Premade Arrays Selection:" << endl;
    cout << "_______________________" << endl;
    cout << "  1: 5 2 1 4 3" << endl;
    cout << "  2: 2 6 10 1 8" << endl;
    cout << "  3: 100 90 10 0 40" << endl;
    cout << "  4: 1 10 9 6 7 3 4 2 5 8" << endl;
    cout << "  5: 100 10 40 20 50 80 90 60 70 30" << endl;
    cout << "  6: Exit to Main Menu" << endl;
    
    //Displaying options to the txt file
    mytxtfile << "Premade Arrays Selection:" << endl;
    mytxtfile << "_______________________" << endl;
    mytxtfile << "  1: 5 2 1 4 3" << endl;
    mytxtfile << "  2: 2 6 10 1 8" << endl;
    mytxtfile << "  3: 100 90 10 0 40" << endl;
    mytxtfile << "  4: 1 10 9 6 7 3 4 2 5 8" << endl;
    mytxtfile << "  5: 100 10 40 20 50 80 90 60 70 30" << endl;
    mytxtfile << "  6: Exit to Main Menu" << endl;
    
    cout << "\n\tYour Selection: ";
    cin >> premadeSelection;
    
    //Verifies input is an integer. IF NOT, requests new input
    while(!integerVerify(premadeSelection))
    {
        cout << "Please Enter a Selection: ";
        cin >> premadeSelection;
    }
    
    //Displaying the user selection to the txt file
    mytxtfile << "\n\tYour Selection: " << premadeSelection << endl << endl;
    
    premadeSwitch(mytxtfile, premadeSelection);
}

//-------------------------------------------------------------------------------------------------
//premadeSwitch - Called by the premade options menu, sets the users array and then calls the sortmenu
//-------------------------------------------------------------------------------------------------
void premadeSwitch(fstream & mytxtfile, int premadeSelection)
{
    //Holds the length of the users picked array
    int length = 0;
    
    //Creating an array with 20 maximum elemenets
    int array[20];
    
    //Setting up the switch for the user selection
    switch (premadeSelection)
    {
        case 1://5,2,1,4,3
        {
            //Setting the length and the values of the array.
            length = 5;
            array[0] = 5;
            array[1] = 2;
            array[2] = 1;
            array[3] = 4;
            array[4] = 3;
            
            sortMenu(mytxtfile, array, length);
            break;
        }
        case 2://2,6,10,1,8
        {
            //Setting the length and the values of the array.
            length = 5;
            array[0] = 2;
            array[1] = 6;
            array[2] = 10;
            array[3] = 1;
            array[4] = 8;
            
            sortMenu(mytxtfile, array, length);
            break;
        }
        case 3://100,90,10,0,40
        {
            //Setting the length and the values of the array.
            length = 5;
            array[0] = 100;
            array[1] = 90;
            array[2] = 10;
            array[3] = 0;
            array[4] = 40;
            
            sortMenu(mytxtfile, array, length);
            break;
        }
        case 4://1,10,9,6,7,3,4,2,5,8
        {
            //Setting the length and the values of the array.
            length = 10;
            array[0] = 1;
            array[1] = 10;
            array[2] = 9;
            array[3] = 6;
            array[4] = 7;
            array[5] = 3;
            array[6] = 4;
            array[7] = 2;
            array[8] = 5;
            array[9] = 8;
            
            sortMenu(mytxtfile, array, length);
            break;
        }
        case 5://100,10,40,20,50,80,90,60,70,30
        {
            //Setting the length and the values of the array.
            length = 10;
            array[0] = 100;
            array[1] = 10;
            array[2] = 40;
            array[3] = 20;
            array[4] = 50;
            array[5] = 80;
            array[6] = 90;
            array[7] = 60;
            array[8] = 70;
            array[9] = 30;
            
            sortMenu(mytxtfile, array, length);
            break;
        }
        case 6://Back to main
        {
            mainMenu(mytxtfile);
            break;
        }
        default://Invalid selection
        {
            cout << "\t::Invalid Selection::\n";
            premadeMenu(mytxtfile);
            break;
        }
    }
}

//-------------------------------------------------------------------------------------------------
//generationMenu - This is the menu for option for the user to have an array filled with randomly
//                  generated numbers.
//-------------------------------------------------------------------------------------------------
void generationMenu(fstream & mytxtfile)
{
    //Creating an array with 20 maximum elemenets
    int array[20];
    
    //Setting the actual size of the size we are using.
    int length = 10;
    
    cout << "Randomly generating an array of 10 vales...\n";
    mytxtfile << "Randomly generating an array of 10 vales...\n";
    
    //For loop to fill the array while calling the random number generator
    for(int x = 0; x < length; x++)
    {
        array[x] = randomNumberGenerator();
    }
    
    //Calling the sorting algorithm
    sortMenu(mytxtfile, array, length);
}
    
//-------------------------------------------------------------------------------------------------
//sortMenu - This is the sorting menu for the project. Allows the user to select how they would
//              like the array to be sorted.
//-------------------------------------------------------------------------------------------------
void sortMenu(fstream & mytxtfile, int array[20], int length)
{
    int sortSelection = 0;
    
    //Displaying options to the user
    cout << "\nSorting Menu:" << endl;
    cout << "_______________________" << endl;
    cout << "  1: Insertion Sort" << endl;
    cout << "  2: Selection Sort" << endl;
    cout << "  3: Bubble Sort" << endl;
    cout << "  4: Merge Sort" << endl;
    cout << "  5: Quick Sort" << endl;
    cout << "  6: Heap Sort" << endl;
    cout << "  7: Exit to Main Menu" << endl << endl;
    
    //Displaying options to the txt file
    mytxtfile << "\nSorting Menu:" << endl;
    mytxtfile << "_______________________" << endl;
    mytxtfile << "  1: Insertion Sort" << endl;
    mytxtfile << "  2: Selection Sort" << endl;
    mytxtfile << "  3: Bubble Sort" << endl;
    mytxtfile << "  4: Merge Sort" << endl;
    mytxtfile << "  5: Quick Sort" << endl;
    mytxtfile << "  6: Heap Sort" << endl;
    mytxtfile << "  7: Exit to Main Menu" << endl;
    
    cout << "   Your Selection: ";
    cin >> sortSelection;
    
    //Verifies input is an integer. IF NOT, requests new input
    while(!integerVerify(sortSelection))
    {
        cout << "Please Enter a selection: ";
        cin >> sortSelection;
    }
    
    //Spacer Line
    cout << endl;
    
    //Displaying the user selection to the txt file
    mytxtfile << "\n\tYour Selection: " << sortSelection << endl << endl;
    
    sortMenuSwitch(mytxtfile, array, length, sortSelection);
}

//---------------------------------------------------------------------------------------
//sortMenuSwitch - This function uses a switch-case for the user entered selection
//                 in the msort menu, distributes the user to the preferred sort algorithm
//---------------------------------------------------------------------------------------
void sortMenuSwitch(fstream& mytxtfile, int array[20], int length, int sortSelection)
{
    //Setting up the switch for the user selection
    switch (sortSelection)
    {
        case 1://Insertion
        {
            insertionSort(mytxtfile, array, length);
            break;
        }
        case 2://Selection
        {
            selectionSort(mytxtfile, array, length);
            break;
        }
        case 3://Bubble
        {
            bubbleSort(mytxtfile, array, length);
            break;
        }
        case 4://Merge
        {
            mergeSort(mytxtfile, array, length);
            break;
        }
        case 5://Quick
        {
            quickSort(mytxtfile, array, length);
            break;
        }
        case 6://Heap
        {
            heapSort(mytxtfile, array, length);
            break;
        }
        case 7://Main Menu
        {
            mainMenu(mytxtfile);
            break;
        }
        default://Invalid selection
        {
            cout << "\t::Invalid Selection::\n";
            sortMenu(mytxtfile, array, length);
            break;
        }
    }
}

//-------------------------------------------------------------------------------------------------
//insertionSort - Sorts an array using an insertion algorithm.
//-------------------------------------------------------------------------------------------------
void insertionSort(fstream & mytxtfile, int array[20], int length)
{
    //Creating a temporary array for our sorting algorithm, so our original array does not get
    //touched. Therefor we can re-use it for another algorithm.
    int tempArray[20];
    
    //Copy the array into a temporary array
    for(int x = 0; x < length; x++)
    {
        tempArray[x] = array[x];
    }
    
    //Printing the pre-sorted array
    cout << "Array Pre- Insertion Sort: \n";
    mytxtfile << "Array Pre- Insertion Sort: \n";
    arrayPrinter(mytxtfile, tempArray, length);
    
    int value;  //holds a temp value for each element of the array to be checked.
    int j;

    //For loop to iterate through the array starting at the second element
    for (int i = 1; i < length; i++)
    {
        //Assigning the value in the element to a temp int.
        value = tempArray[i];
        
        //Assing j to the value of the element previous of i
        j = i-1;
        
        //While the element j is more than the temp value, moves the element.
        while (j >= 0 && tempArray[j] > value)
        {
            tempArray[j+1] = tempArray[j];
            j = j-1;
        }
        //Assining the element after j the temp value.
        tempArray[j+1] = value;
    }
    
    //Printing the sorted array
    cout << "Array Post- Insertion Sort: \n";
    mytxtfile << "Array Post- Insertion Sort: \n";
    arrayPrinter(mytxtfile, tempArray, length);
    
    //asking if the user wants to use the same array with a different algorithm
    //Here we send back our original array.
    useAgain(mytxtfile, array, length);
}

//-------------------------------------------------------------------------------------------------
//selectionSort - Sorts an array using a selection algorithm.
//-------------------------------------------------------------------------------------------------
void selectionSort(fstream & mytxtfile, int array[20], int length)
{
    //Creating a temporary array for our sorting algorithm, so our original array does not get
    //touched. Therefor we can re-use it for another algorithm.
    int tempArray[20];
    
    //Copy the array into a temporary array
    for(int x = 0; x < length; x++)
    {
        tempArray[x] = array[x];
    }
    
    //Printing the pre-sorted array
    cout << "Array Pre- Selection Sort: \n";
    mytxtfile << "Array Pre- Selection Sort: \n";
    arrayPrinter(mytxtfile, tempArray, length);
    
    int value;  //holds a temp value for each element of the array to be checked.
    int j;
    
    //Starting at the front of the array to initialize sorting
    for (int i = 0; i < length-1; i++)
    {
        //Holding the placement of the element we are checking
        value = i;
        
        // Finding the element with the lowest value in the array
        for (j = i + 1; j < length; j++)
        {
            if (tempArray[j] < tempArray[value])
            {
                value = j;
            }
        }
        // Swap the lowest value with the value in the element we were checking.
        //Using the C++ standard swap function.
        swap(tempArray[value], tempArray[i]);
    }
    
    //Printing the sorted array
    cout << "Array Post- Selection Sort: \n";
    mytxtfile << "Array Post- Selection Sort: \n";
    arrayPrinter(mytxtfile, tempArray, length);
    
    //asking if the user wants to use the same array with a different algorithm
    //Here we send back our original array.
    useAgain(mytxtfile, array, length);
}

//-------------------------------------------------------------------------------------------------
//bubbleSort - Sorts an array using a bubble algorithm.
//-------------------------------------------------------------------------------------------------
void bubbleSort(fstream & mytxtfile, int array[20], int length)
{
    //Creating a temporary array for our sorting algorithm, so our original array does not get
    //touched. Therefor we can re-use it for another algorithm.
    int tempArray[20];
    
    //Copy the array into a temporary array
    for(int x = 0; x < length; x++)
    {
        tempArray[x] = array[x];
    }
    
    //Printing the pre-sorted array
    cout << "Array Pre- Bubble Sort: \n";
    mytxtfile << "Array Pre- Bubble Sort: \n";
    arrayPrinter(mytxtfile, tempArray, length);
    
    int j;
    
    //Starting at the front of the array to initialize sorting
    for (int i = 0; i < length-1; i++)
    {
        //In this for loop, we are subtracting i from the length because the last elements
        //are already sorted.
        for (j = 0; j < length-i-1; j++)
        {
            //if the value in element represented by j, is larger than the one after j,
            //calls the c++ standard swap function to swap the values.
            if (tempArray[j] > tempArray[j+1])
            {
                swap(tempArray[j], tempArray[j+1]);
            }
        }
    }
    
    //Printing the sorted array
    cout << "Array Post- Bubble Sort: \n";
    mytxtfile << "Array Post- Bubble Sort: \n";
    arrayPrinter(mytxtfile, tempArray, length);
    
    //asking if the user wants to use the same array with a different algorithm
    //Here we send back our original array.
    useAgain(mytxtfile, array, length);
}

//-------------------------------------------------------------------------------------------------
//mergeSort - Sorts an array using a merging algorithm, splitting the array between L and R sides.
//-------------------------------------------------------------------------------------------------
void mergeSort(fstream & mytxtfile, int array[20], int length)
{
    //Creating a temporary array for our sorting algorithm, so our original array does not get
    //touched. Therefor we can re-use it for another algorithm.
    int tempArray[20];
    
    //Copy the array into a temporary array
    for(int x = 0; x < length; x++)
    {
        tempArray[x] = array[x];
    }
    
    //Printing the pre-sorted array
    cout << "Array Pre- Merge Sort: \n";
    mytxtfile << "Array Pre- Merge Sort: \n";
    arrayPrinter(mytxtfile, tempArray, length);
    
    //Calling the recursive function to find the solution.
    //When the recursive function recieves the length, it will be re-named to high
    //to represent the high side of the unsorted array.
    mergeSortRecursion(tempArray, 0, length-1);
    
    //Printing the sorted array
    cout << "Array Post- Merge Sort: \n";
    mytxtfile << "Array Post- Merge Sort: \n";
    arrayPrinter(mytxtfile, tempArray, length);
    
    //asking if the user wants to use the same array with a different algorithm
    //Here we send back our original array.
    useAgain(mytxtfile, array, length);
}

//-------------------------------------------------------------------------------------------------
//mergeSortRecursion - Uses recursion to split the array up until each element is by itself.
//-------------------------------------------------------------------------------------------------
void mergeSortRecursion(int array[20], int left, int right)
{
    //if left side is less than the right side,
    if (left < right)
    {
        // Setting the split, marking the middle of the array
        int split = left + (right - left) / 2;
        
        // Sort first and second halves
        mergeSortRecursion(array, left, split);
        mergeSortRecursion(array, split+1, right);
        
        mergeArrays(array, left, right, split);
    }
}

//-------------------------------------------------------------------------------------------------
//mergeArrays - This function will merge the arrays back together in sorted order
//-------------------------------------------------------------------------------------------------
void mergeArrays(int array[], int left, int right, int split)
{
    int i, j, k;    //Variables for function
    int leftSize = split - left + 1;    //Left side of the split
    int rightSize =  right - split;     //Right side of the split
    
    //Creating the temporary arrays
    int leftSide[leftSize];
    int rightSide[rightSize];
    
    //Copying data to the temporary arrays from the main array
    //For loop to iterate until the left side of the split is copied into the new array
    for (i = 0; i < leftSize; i++)
    {
        leftSide[i] = array[left + i];
    }

    //For loop to iterate until the right side of the split is copied into the new array
    for (j = 0; j < rightSize; j++)
    {
        rightSide[j] = array[split + 1+ j];
    }
    
    //Merging the temporary arrays back into the main array.
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    
    while (i < leftSize && j < rightSize)
    {
        if (leftSide[i] <= rightSide[j])
        {
            array[k] = leftSide[i];
            i++;
        }
        else
        {
            array[k] = rightSide[j];
            j++;
        }
        k++;
    }
    
     //If there are any elements left on the left side, they are copied back into the array.
    while (i < leftSize)
    {
        array[k] = leftSide[i];
        i++;
        k++;
    }
    
    //If there are any elements left on the right side, they are copied back into the array.
    while (j < rightSize)
    {
        array[k] = rightSide[j];
        j++;
        k++;
    }
}

//-------------------------------------------------------------------------------------------------
//quickSort - Sorts an array using a quick sorting algorithm, splitting the array between a low side
//            and a high side.
//-------------------------------------------------------------------------------------------------
void quickSort(fstream & mytxtfile, int array[20], int length)
{
    //Creating a temporary array for our sorting algorithm, so our original array does not get
    //touched. Therefor we can re-use it for another algorithm.
    int tempArray[20];
    
    //Copy the array into a temporary array
    for(int x = 0; x < length; x++)
    {
        tempArray[x] = array[x];
    }
    
    //Printing the pre-sorted array
    cout << "Array Pre- Quick Sort: \n";
    mytxtfile << "Array Pre- Quick Sort: \n";
    arrayPrinter(mytxtfile, tempArray, length);
    
    //Calling the recursive function to find the solution.
    //When quickSortRecursion recieves the length, it will be re-named 'high' according to the necessity
    //of the algorithm for using it as the high side of the array.
    quickSortRecursion(tempArray, 0, length-1);
    
    //Printing the sorted array
    cout << "Array Post- Quick Sort: \n";
    mytxtfile << "Array Post- Quick Sort: \n";
    arrayPrinter(mytxtfile, tempArray, length);
    
    //asking if the user wants to use the same array with a different algorithm
    //Here we send back our original array.
    useAgain(mytxtfile, array, length);
}

//-------------------------------------------------------------------------------------------------
//quickSortRecursion - Uses recursion to sort the array between a low side vs high side.
//-------------------------------------------------------------------------------------------------
void quickSortRecursion(int array[20], int low, int high)
{
    //Checking if the low side is less than the high side
    if (low < high)
    {
        //split is will store the location of the sorted side(low) from the unsorted side (high),
        //from the partition function
        int split = quickSortParter(array, low, high);
        
        //Sorting the elemenets again, we will not sort the low side and high side individually
        quickSortRecursion(array, low, split - 1);
        quickSortRecursion(array, split + 1, high);
    }
}

//-------------------------------------------------------------------------------------------------
// quickSortParter - This function takes last element(high) as a split element, places the spiit
//                   element at its correct position in the sorted array. It then places any value that
//                   is smaller than the split(low) to the left and all greater elements to right
//-------------------------------------------------------------------------------------------------
int quickSortParter(int array[], int low, int high)
{
    int split = array[high]; // Creating the split element from the high side location
    int x = (low - 1);      // Index of smaller element
    
    for (int y = low; y <= high- 1; y++)
    {
        // If current element is smaller than or equal to pivot
        if (array[y] <= split)
        {
            x++;    // increment index of smaller element
            
            //Swapping the elements using the c++ standard swap function
            swap(array[x], array[y]);
        }
    }
    
    //Swapping the elements so we know where the new location of the split is.
    swap(array[x + 1], array[high]);
    
    //returning the split of the sorted location
    return (x + 1);
}

//-------------------------------------------------------------------------------------------------
//heapSort - Sorts an array using a heap sorting algoritm. Creating a heap, the larger numbers will
//           be stored at the root of the heap, We then will extract the numbers in sorted order from
//           the leaves.
//-------------------------------------------------------------------------------------------------
void heapSort(fstream & mytxtfile, int array[20], int length)
{
    //Creating a temporary array for our sorting algorithm, so our original array does not get
    //touched. Therefor we can re-use it for another algorithm.
    int tempArray[20];
    
    //Copy the array into a temporary array
    for(int x = 0; x < length; x++)
    {
        tempArray[x] = array[x];
    }
    
    //Printing the pre-sorted array
    cout << "Array Pre- Quick Sort: \n";
    mytxtfile << "Array Pre- Quick Sort: \n";
    arrayPrinter(mytxtfile, tempArray, length);
    
    //Building the heap of the length of the array
    for (int x = length / 2 - 1; x >= 0; x--)
    {
        heap(tempArray, length, x);
    }
    
    //Pulling the elements of the array back from the heap one at a time.
    //At this point they will be in sorted order.
    for (int y = length-1; y >= 0; y--)
    {
        //Move the current root to the end of the array
        swap(tempArray[0], tempArray[y]);
        
        //recalling the heap
        heap(tempArray, y, 0);
    }
    
    //Printing the sorted array
    cout << "Array Post- Quick Sort: \n";
    mytxtfile << "Array Post- Quick Sort: \n";
    arrayPrinter(mytxtfile, tempArray, length);
    
    //asking if the user wants to use the same array with a different algorithm
    //Here we send back our original array.
    useAgain(mytxtfile, array, length);
}

//-------------------------------------------------------------------------------------------------
// heap - Utilizes a heap to sort the array with the largest number at the root and sorted to the
//        leaves.
//-------------------------------------------------------------------------------------------------
void heap(int array[], int length, int inputNumber)
{
    int largest = inputNumber; // Initialize largest as the root from the input number
    int leftSide = 2 * inputNumber + 1; // setting the size of the left side
    int rightSide = 2 * inputNumber + 2; // setting the size of the right side
    
    //Checking if the left leaf is larger than the root.
    //If it is, sets largest to the left side.
    if (leftSide < length && array[leftSide] > array[largest])
    {
        largest = leftSide;
    }
    
    //Checking if the right leaf is larger than the root.
    //If it is, sets largest to the right side.
    if (rightSide < length && array[rightSide] > array[largest])
    {
        largest = rightSide;
    }
    
    //If largest is not root we will utilize the c++ standard swap to swap the
    //values.
    if (largest != inputNumber)
    {
        swap(array[inputNumber], array[largest]);
        
        // Recursively heapify the affected sub-tree
        heap(array, length, largest);
    }
}

//---------------------------------------------------------------------------------------
//arrayPrinter - prints an array.
//---------------------------------------------------------------------------------------
void arrayPrinter(fstream & mytxtfile, int array[], int length)
{
    //Tab line
    cout << "\t";
    mytxtfile << "\t";
    
    //For loop to interate each element of the array and print it.
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
        mytxtfile << " " << array[i];
    }
    
    //New line
    printf("\n\n");
    mytxtfile << endl << endl;
}

//---------------------------------------------------------------------------------------
//useAgain - Asks the user if they would like to use the same array with a different
//           sorting algorithm, if yes, directs them back to the sorting menu
//---------------------------------------------------------------------------------------
void useAgain(fstream & mytxtfile, int array[], int length)
{
    char userSelection;     //Holds the user selection
    
    cout << "\nWould you like to use the same array with a different algorithm?\n";
    cout << "Enter Y for Yes, Else returns to main menu.\n";
    mytxtfile << "Would you like to use the same array with a different algorithm?\n";
    mytxtfile << "Enter Y for Yes, Else returns to main menu.\n";
    cout << "\tUser Input: ";
    cin >> userSelection;
    
    //converts to char input to an upper character and compares it,
    //if the input was a 'Y' then sends back to the sorting menu
    if(toupper(userSelection) == 'Y')
    {
        cout << endl;
        mytxtfile << "\tUser Input: " << userSelection << endl << endl;
        sortMenu(mytxtfile, array, length);
    }
    else //input was not a 'Y' , defaults back to main menu
    {
        cout << endl;
        mytxtfile << "\tUser Input: " << userSelection << endl << endl;
        mainMenu(mytxtfile);
    }
}

//---------------------------------------------------------------------------------------
//IntegerVerify - This function verifies
//---------------------------------------------------------------------------------------
bool integerVerify(int userInput)
{
    //This while loop ensures the user enters ONLY an integer. Anything else will
    //be kicked out.
    while(1)
    {
        if(cin.fail())
        {
            cin.clear();
            
            //If the input is not within numberic limits, throw error
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Please only enter a number.\n";
            return false;
        }
        if(!cin.fail())
            break;
    }
    
    return true;
}

//---------------------------------------------------------------------------------------
//integerSizeRestrictor - this function ensures that a number entered is within the bounds
//                        of -1000 - 1000.
//---------------------------------------------------------------------------------------
int integerSizeRestrictor(int numberEntered)
{
    while(numberEntered < -1000 || numberEntered > 1000)
    {
        cout << "\nThat number is out of bounds.";
        cout << "\nTry Again\n";
        cout << "\n\tNumber: ";
        cin >> numberEntered;
        cout << endl;
    }
    
    return numberEntered;
}

//-------------------------------------------------------------------------------------------------
//randomNumberGenerator - This function holds the random number generator for the array.
//-------------------------------------------------------------------------------------------------
int randomNumberGenerator()
{
    int randomNumber = 0;                       //Holds the random number
        
    randomNumber = rand() % (999 - 0) + 0;       //Generates random number between 0 and 99
        
    return randomNumber;                        //Returns the random number.
}

//-------------------------------------------------------------------------------------------------
//programEnd - Prompts the user to enter any key to close the program, then ends the program.
//-------------------------------------------------------------------------------------------------
void programEnd()
{
    cout << "\nPress any key to end...\n";
    cin.get();
}

