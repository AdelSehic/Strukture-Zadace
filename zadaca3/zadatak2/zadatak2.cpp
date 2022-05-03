#include <iostream>
#include "sorted_forward_list.hpp"

int generateId(){
    static int counter = 0;
    return ++counter;
}

struct toDoTask{
    size_t id{0};
    std::string title;
    std::string description;
    size_t priority{0};

    bool operator<(const toDoTask& other) const {return priority < other.priority;}
    bool operator==(const toDoTask& other) const {return id==other.id;}
    bool operator!=(const toDoTask& other) const {return id!=other.id;}
};

std::ostream& operator<<(std::ostream& out, toDoTask& a ){
    std::cout << "\nTitle: " << a.title << "\nDescription: " << a.description << "\nPriority: " << a.priority << std::endl;
    return out;
}

void tasksOutput(const list<toDoTask>& cont, int i = 0){
    auto it = cont.begin();
    while (it != cont.end()){
        std::cout << *it;
        if(i) std::cout << "Task id: " << it -> data.id << std::endl;
        ++it;
    }
}

void tasksRemove(list<toDoTask>& tasks){
    size_t input = 0;
    tasksOutput(tasks, 1);
    std::cout << "Select id of the task which you wish to mark as done : ";
    std::cin >> input;
    toDoTask temp = {input," ", " "};
    auto it = tasks.find(temp);
    if( it != tasks.end() )tasks.erase(it);
    else std::cout << "Task with that id does not exist";
}

toDoTask taskInput(){
    toDoTask temp;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter a new toDoTask:\nEnter the title of the task: ";
    std::getline(std::cin, temp.title);
    std::cout << "Enter the description of the task: ";
    std::getline(std::cin, temp.description);
    std::cout << "Enter a priority (>0): ";
    std::cin >> temp.priority;
    temp.id = generateId();
    return temp;
}

int main(int argc, char const *argv[])
{
    int input=1;
    list<toDoTask> tasks;

    while(input != 0 && std::cin){
        std::cout << "\nChoose one of the options\n****************************************\n1. Display the current list of toDoTask\n2. Enter a new toDoTask\n3. Mark toDoTask as done\nEnter your choice : ";
        std::cin >> input;
        std::cout << "\n****************************************\n";
        if(!std::cin) break;
        switch (input)
        {
        case 1:
            if(tasks.empty()) std::cout << "Your notes are empty" << std::endl;
            tasksOutput(tasks);
            break;
        case 2:
            tasks.push(taskInput());
            break;
        case 3:
            if(tasks.empty()) {
                std::cout << "Your notes are empty" << std::endl;
                break;
            }
            tasksRemove(tasks);
            break;
        default:
            break;
        }
        std::cout << "Enter number 0 to exit the program or something else to continue : ";
        std::cin >> input;
    }

    return 0;
}
