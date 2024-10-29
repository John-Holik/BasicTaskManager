// File   : taskmanager.cpp
// Author : John Holik
// Desc   : Creating a basic task manager using the CLI in C++
// *********************************************************************************

#include <iostream>
#include <string>
#include <fstream> // For file handling
#include <cstdlib> // For exit()

// Functions
// *********************************************************************************
int isFileCreated(){
    // Checks if the file used for storing tasks is already created, if not it will create it
    // ios::out opens the file in write mode 
    // ios::app opens the file in append mode
    std::fstream file("tasks.txt", std::ios::out | std::ios::app); 

    if(file.is_open()){
        file.close();
    }else{
        std::cerr << "Error opening or creating file. Program Aborting" << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;

}// end isFileCreated



int getLineCount(){
    // Used to read the number of lines in the text file. Each line should be a task.
    std::ifstream file("tasks.txt");
    int lineCount = 0;
    std::string line;

    if(file.is_open()){
        while(std::getline(file, line)){
            lineCount++;
        }
    }else{
        std::cerr << "Error opening file. Program Aborting" << std::endl;
        exit(EXIT_FAILURE);
    }

    file.close();

    return lineCount;
}// end getLineCount



int chooseTask(){
    // Start by letting user choose what action they want to do.
    std::cout << "To view current tasks type '1', to add tasks type '2', to remove tasks type '3': ";
    bool validInput = false;
    int input;
    do{
        std::cin >> input;
        if (input >= 1 && input <= 3){
            validInput = true;
        }
        else{
            std::cout << "Invalid Input. Please enter 1,2, or 3: ";
        }

    } while (!validInput);
    // return the valid input integer
    return input;
}// end chooseTask



void viewTasks(){
    // Display the contents of the file:
    std::ifstream file("tasks.txt");
    std::string line; 

    if(file.is_open()){
        while(std::getline(file, line)){
            std::cout << line << std::endl;
        }
    }else{
        std::cerr << "Error opening file. Program Aborting" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    return;
}// end viewTasks



void addTasks(){

}//end addTasks



void removeTasks(){

}//end removeTasks



bool continueInput(){
    char doContinue;
    std::cout << "Would you like to continue? (y/n): ";

    // Check if input is valid
    bool validInput = false;
    do{
        std::cin >> doContinue;
        if (doContinue == 'y' || doContinue == 'Y' || doContinue == 'n' || doContinue == 'N'){
            validInput = true;
        }
        else{
            std::cout << "Invalid Input. Please enter 'y' or 'n': ";
        }

    } while (!validInput);
    
    // If they do not want to continue they will enter 'n' and the program loop will stop
    if (doContinue == 'n' || doContinue == 'N'){
        return false;
    }else{ // otherwise they entered 'y' and they want to do another action
        return true;
    }
}//end continueInput



// Main
// *********************************************************************************
int main(){
    // check if tasks.txt file is present
    isFileCreated();

    // Create a loop to let the user switch between actions after completion
    bool keepRunning = true;

    do{
        // Let the User Choose their action:
        int input = -1;
        input = chooseTask();

        switch (input)
        {
        // View tasks in file
        case 1:
            viewTasks();
            break;
        // Add tasks to file
        case 2:
            addTasks();
            break;
        // Remove tasks from file
        case 3:
            removeTasks();
            break;
        }
        
        // After action is completed, see if user wants to continue or exit the program
        keepRunning = continueInput();

    }while(keepRunning);
    

    return 0;
}// end main