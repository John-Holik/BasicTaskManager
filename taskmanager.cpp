// File   : taskmanager.cpp
// Author : John Holik
// Desc   : Creating a basic task manager using the CLI in C++
// *********************************************************************************



#include <iostream>
#include <string>
#include <fstream> // For file handling
#include <cstdlib> // For exit()
#include <vector>
#include <limits>



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



int chooseAction(){
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
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    } while (!validInput);
    // return the valid input integer
    return input;
}// end chooseAction



void viewTasks(){
    // Display the contents of the file:
    std::ifstream file("tasks.txt");
    std::string line; 

    if(file.is_open()){ 
        // Check if tasks list is empty
        if(getLineCount() == 0){
            std::cout << std::endl;
            std::cout << "You have no tasks left to do!" << std::endl;
        }else{
            std::cout << std::endl;
            std::cout << "Current Tasks: " << std::endl;
            while (std::getline(file, line)){
                std::cout << line << std::endl;
            }
        }
    }else{
        std::cerr << "Error opening file. Program Aborting" << std::endl;
        exit(EXIT_FAILURE);
    }

   

    return;
}// end viewTasks



void addTasks(){
    // open the file in write mode. 
    std::ofstream file("tasks.txt", std::ios::app);
    std::string taskToAdd;
    int taskNum = getLineCount() + 1; // For formatting task numbers

    if(file.is_open()){
        std::cout << std::endl;
        std::cout << "Enter the name/description of the task you would like to add: ";
        std::cin.ignore();
        std::cin.sync();
        std::getline(std::cin, taskToAdd);
        file << taskNum << ") " << taskToAdd << "\n";
        std::cout << "Task added. \n";
    }else{
        std::cerr << "Error opening file. Program Aborting" << std::endl;
        exit(EXIT_FAILURE);
    }
    return;
}//end addTasks



void writeTasks(const std::vector<std::string> &tasks){
    std::ofstream file("tasks.txt");
    if (file.is_open()){
        for (size_t i = 0; i < tasks.size(); i++){
            // Add proper numbering and task description
            file << (i + 1) << ") " << tasks[i] << '\n';
        }
    }else{
        std::cerr << "Error opening file. Program Aborting" << std::endl;
        exit(EXIT_FAILURE);
    }
    file.close();
}//end writeTasks



std::vector<std::string> readTasks(){
    std::vector<std::string> tasksVec;
    std::ifstream file("tasks.txt");
    std::string line;

    if (file.is_open()){
        while (std::getline(file, line)){
            // Find the first space after the task number and skip past it
            size_t pos = line.find(" ");
            if (pos != std::string::npos){
                tasksVec.push_back(line.substr(pos + 1)); // Skip number and space
            }else{
                tasksVec.push_back(line); // Add unformatted line as fallback
            }
        }
    }else{
        std::cerr << "Error opening file. Program Aborting" << std::endl;
        exit(EXIT_FAILURE);
    }
    file.close();

    return tasksVec;
}//end readTasks



void deleteTasks(){
    // Make sure that there are tasks to delete;
    if(getLineCount() == 0){
        // If not, return
        std::cout << "You have no tasks to delete. Please add some before continuing. \n";
        return; 
    } 
    
    // Display current tasks:
    viewTasks();
    std::cout << std::endl;
    int numOfTasks = getLineCount();
    int taskNum = -9;
    // Get valid task number to delete
    bool validInput = false;
    std::cout << "Enter the task number you wish to delete: ";
    do{

        std::cin >> taskNum;
        if (taskNum >= 1 && taskNum <= numOfTasks){
            validInput = true;
        }else{
            std::cout << "Invalid task number. Valid task numbers are 1 - " << numOfTasks << ": ";
        }
    } while (!validInput);

    // Now we have a valid input, so we need to delete the task
    std::vector<std::string> tasksVec = readTasks();
    tasksVec.erase(tasksVec.begin() + taskNum - 1); // Remove task by its position
    writeTasks(tasksVec);                           // Rewrite tasks with updated numbering

    return;
}//end deleteTasks



bool continueInput(){
    char doContinue;
    std::cout << std::endl;
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
        input = chooseAction();

        switch (input){

        // View tasks in file
        case 1:
            viewTasks();
            break;

        // Add tasks to file
        case 2:
            addTasks();
            viewTasks();
            break;

        // Remove tasks from file
        case 3:
            deleteTasks();
            break;
        }
        
        // After action is completed, see if user wants to continue or exit the program
        keepRunning = continueInput();

    }while(keepRunning);
    

    return 0;
}// end main