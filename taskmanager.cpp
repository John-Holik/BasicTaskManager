// File   : taskmanager.cpp
// Author : John Holik
// Desc   : Creating a basic task manager using the CLI in C++
// *********************************************************************************

#include <iostream>
#include <string>
#include <fstream>

// Functions
// *********************************************************************************

int chooseTask(){
    // Start by letting user choose what action they want to do.
    std::cout << "To view current tasks type '1', to add tasks type '2', to remove tasks type '3': ";
    bool validInput = false;
    int input;
    do
    {
        std::cin >> input;
        if (input >= 1 && input <= 3)
        {
            validInput = true;
        }
        else
        {
            std::cout << "Invalid Input. Please enter 1,2, or 3: ";
        }

    } while (!validInput);
    // return the valid input integer
    return input;
}// end chooseTask



// Main
// *********************************************************************************
int main(){
    // Let the User Choose their action:
    int input = -1;
    input = chooseTask();
    
    // Create/Override file where tasks will be stored. 
    //std::ofstream outfile['tasks.txt'];
    

    return 0;
}// end main