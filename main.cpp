#include <iostream>
#include <conio.h>
#include "Source\ListDogs.h"

#define clearCMD system("cls");
#define CMDblack system("color 0");
#define CMDblue system("color 1");
#define CMDgreen system("color 2");
#define CMDred system("color 4");
#define CMDwhite system("color 7");

char file[100] = "Data\\dogs_short.data";
Date* curent_date = NULL;
bool running = true;
bool save = false;
int profit = 0;

int Get_Months(Date* dog_birth){
    int months = (curent_date->year - dog_birth->year) * 12  + (curent_date->month - dog_birth->month);

    return months;
}

void Find_Dogs_By_Race(Nod* list_head, char* race){
    bool found = false;
    for(; list_head != NULL; list_head = list_head->next)
        if(strcmp(list_head->dog->race, race) == 0){
            found = true;
            Show_Dog_Info(list_head->dog);
        }

    if(!found)
        std::cout << "NONE" << '\n';
}

void Show_Dogs_From_Cage(Nod* list_head, int cage){
    bool found = false;
    int total_price = 0;

    for(; list_head != NULL; list_head = list_head->next)
        if(list_head->dog->cage == cage){
            Show_Dog_Info(list_head->dog);
            total_price += list_head->dog->price;
            found = true;
        }

    if(!found) std::cout << "NONE";
    else std::cout << "Total: " << total_price << " EUR";
}   

void Find_Dogs_By_Months(Nod* list_head, int min, int max){
    bool found = false;
    for(; list_head != NULL; list_head = list_head->next){
        Dog* dog = list_head->dog;
        int months = Get_Months(dog->birth_date);

        if(months <= max && months >= min){
            found = true;
            Show_Dog_Info(dog);
        }
    }

    if(!found) std::cout << "NONE" << '\n';
}

void Exterminate_Dogs_Age(Nod*& list_head, int max_age){
    bool exist = false;
    Nod* head = list_head;
    for(; head != NULL; head = head->next){
        Dog* dog = head->dog;
        int age = Get_Months(dog->birth_date) / 12;

        if(age >= max_age){
            Show_Dog_Info(dog);
            DeleteDog_By_ID(dog->id, list_head);
            exist = true;
        }
    }

    if(!exist) std::cout << "NONE" << '\n';
    else std::cout << "Dogs Exterminated" << '\n';
}

// SOFTWARE RELATED
void menu(){
    clearCMD

    std::cout << "---|KennelManagemant-Tool|---" 
        << curent_date->year << '.' << curent_date->month << '.' << curent_date->day 
        << "---" << file << "---" << '\n';
    std::cout << '\n';
    std::cout << "1...Show List Of Dogs" << '\n';
    std::cout << "2...Find Dogs By Race" << '\n';
    std::cout << "3...Show Dogs From Cage" << '\n';
    std::cout << "4...Find Dogs By (Min, Max)Months" << '\n';
    std::cout << "5...Kill Dogs By Max Age" << '\n';
    std::cout << "6...Sell Dog" << '\n';
    std::cout << "7...Add Dog" << '\n';
    std::cout << "8...Delete Dog" << '\n';
    std::cout << "9...Kennel Informatin" << '\n';
    std::cout << "10..Save State" << '\n';
    std::cout << "11..Change Load File" << '\n';
    std::cout << "12..Change Curent Date" << '\n';
    std::cout << '\n';
    std::cout << "0...Save & Quit" << '\n';
    std::cout << "\n-> ";
}

void back(){
    std::cout << '\n';
    std::cout << "1...Back" << '\n';
    std::cout << '\n';
    std::cout << "-> ";

    int option = 0;
    do{
        std::cin >> option;
    }while (option != 1);
}

void option1(Nod* list_head){
    clearCMD

    if(!Show_List(list_head))
        std::cout << "Empty" << '\n';
    
    back();
}

void option2(Nod* list_head){
    clearCMD

    char race[20];
    std::cout << "Race: ";
    std::cin >> race;

    clearCMD
    std::cout << "Dogs Found: " << '\n';
    Find_Dogs_By_Race(list_head, race);

    back();
}

void option3(Nod* list_head){
    clearCMD

    int cage;
    std::cout << "Cage: " << '\n';
    std::cin >> cage;

    clearCMD
    std::cout << "Cage " << cage << ": " <<'\n';
    Show_Dogs_From_Cage(list_head, cage);
    
    back();
}

void option6(Nod*& list_head){
    clearCMD

    Dog* dog;
    Nod* head = list_head;
    int dog_id;

    std::cout << "Dog ID: " << '\n';
    std::cin >> dog_id;
    
    clearCMD
    if(Dog_Exist(dog_id, list_head)){
        dog = GetDog_By_ID(dog_id, head);

        Show_Dog_Info(dog);
        std::cout << "Are you sure?"<< '\n';
        std::cout << "1...Yes" << '\n';
        std::cout << "2...No" << '\n';
        std::cout << '\n';
        std::cout << "-> ";

        int option = 0;
        do{
            std::cin >> option;
        }while (option >= 2 && option <= 1);

        clearCMD
        if(option == 1) {
            save = true;
            std::cout << "Dog sold for: " << dog->price << " EUR" << '\n';
            profit += dog->price;
            DeleteDog_By_ID(dog_id, list_head);
        }
    }else{
        std::cout << "Dog not found" << '\n';
    }
    
    back();
}

void option7(Nod*& list_head){
    clearCMD

    Dog* dog = new Dog;
    
    std::cin.get();
    std::cout << "Dog Name: " << '\n';
    std::cin.getline(dog->name, 50);
    clearCMD
    std::cout << "Dog Race: " << '\n';
    std::cin.getline(dog->race, 35);
    clearCMD
    std::cout << "Dog Birth: " << '\n';
    std::cin.getline(dog->birth, 20);
    clearCMD
    std::cout << "Dog Price: " << '\n';
    std::cin >> dog->price;
    clearCMD
    std::cout << "Dog Cage: " << '\n';
    std::cin >> dog->cage;

    dog->id = GetLast_ID(list_head) + 1;

    clearCMD
    Show_Dog_Info(dog);
    std::cout << "Are you sure?"<< '\n';
    std::cout << "1...Yes" << '\n';
    std::cout << "2...No" << '\n';
    std::cout << '\n';
    std::cout << "-> ";

    int option;
    do{
        std::cin >> option;
    }while (option >= 2 && option <= 1);

    clearCMD

    if(option == 1) {
        save = true;
        Add_List(dog, list_head);
        std::cout << "Dog added"<< '\n';
    }else{
        std::cout << "Dog was not good enough"<< '\n';
    }

    back();
}

void option8(Nod*& list_head){
    clearCMD

    int dog_id;
    std::cout << "Dog ID: " << '\n';
    std::cin >> dog_id;

    clearCMD
    if(Dog_Exist(dog_id, list_head)){
        Show_Dog_Info(GetDog_By_ID(dog_id, list_head));
        std::cout << "Are you sure?"<< '\n';
        std::cout << "1...Yes" << '\n';
        std::cout << "2...No" << '\n';
        std::cout << '\n';
        std::cout << "-> ";

        int option = 0;
        do{
            std::cin >> option;
        }while (option >= 2 && option <= 1);

        clearCMD
        if(option == 1) {
            save = true;
            DeleteDog_By_ID(dog_id, list_head);
            std::cout << "Dog deleted"<< '\n';
        }
    }else{
        std::cout << "Dog not found"<< '\n';
    }
    
    back();
}

void option4(Nod* list_head){
    clearCMD

    int min, max;
    std::cout << "Min Months: " << '\n';
    std::cin >> min;
    clearCMD
    std::cout << "Max Months: " << '\n';
    std::cin >> max;
    
    clearCMD
    std::cout << "Dogs Found: " << '\n';
    Find_Dogs_By_Months(list_head, min, max);
    
    back();
}

void option5(Nod*& list_head){
    system("color 4");
    clearCMD

    int age;
    std::cout << "Max age: " << '\n';
    std::cin >> age;
    
    std::cout << "Result: " << '\n';
    Exterminate_Dogs_Age(list_head, age);
    
    back();
}

void option9(Nod* list_head){
    clearCMD
    int worth = 0;
    int dogs_count = 0;

    for(; list_head != NULL; list_head = list_head->next){
        worth += list_head->dog->price;
        dogs_count++;
    }

    std::cout << "--------Kennel-Information--------" << '\n';
    std::cout << '\n';
    std::cout << "Kennel worth: " << worth << " EUR" << '\n';
    std::cout << "Dogs in stock: " << dogs_count << '\n';
    std::cout << '\n';
    std::cout << "Profit: " << profit << " EUR" << '\n';
    std::cout << "Total: " << profit + worth << " EUR" << '\n';
    
    back();
}

void option11(Nod*& list_head, char file[]){
    CMDred
    char* past_file = file;
    char new_file[100];

    do{
        clearCMD
        std::cout << "New File Name (.data) & to stop write 0" << '\n';
        std::cin >> new_file;
    if(new_file[0] == '0') return;
    }while (!File_Exists(new_file));


    std::cout << "The program will load from: " << new_file << '\n';
    std::cout << "Things will save if needed" << '\n';
    std::cout << "Are you sure?" << '\n';
    std::cout << '\n';
    std::cout << "1...Yes" << '\n';
    std::cout << "2...No" << '\n';
    std::cout << '\n';
    std::cout << "-> ";
    
    int option = 0;
    do{
        std::cin >> option;
    }while (option >= 2 && option <= 1);

    if(option == 1) {
        if(save)
            Save_In_File(file, list_head, profit, curent_date);

        strncpy(file, new_file, 100);
        list_head = NULL;
        Load_From_File(new_file, list_head, profit, curent_date);
    }
}

void option12(){
    char new_date[20];
    do{
        clearCMD
        std::cout << "New Date (yyyy.mm.dd)" << '\n';
        std::cin >> new_date;
    }while (strlen(new_date) < 10);
    

    std::cout << "The program's current date will change to: " << new_date << '\n';
    std::cout << "Are you sure?" << '\n';
    std::cout << '\n';
    std::cout << "1...Yes" << '\n';
    std::cout << "2...No" << '\n';
    std::cout << '\n';
    std::cout << "-> ";
    
    int option = 0;
    do{
        std::cin >> option;
    }while (option >= 2 && option <= 1);

    if(option == 1) {
        save = true;
        curent_date = StringToDate(new_date);
    }
}

int main(){
    Nod* list_head = NULL;
    if(!Load_From_File(file, list_head, profit, curent_date)){
        CMDblue
        running = false;
        std::cout << "------------------NO FILE-------------------" << '\n';
        std::cout << "---Change file path in code and recompile---" << '\n';
        std::cout << "--------------------------------------------" << '\n';

        getch();
    }

    while (running){
        CMDgreen
        menu();

        int option = -1; 
        do
            std::cin >> option;
        while (option <= 0 && option >= 10);
        
        if(option == 1) option1(list_head);
        if(option == 2) option2(list_head);
        if(option == 3) option3(list_head);
        if(option == 4) option4(list_head);
        if(option == 5) option5(list_head);
        if(option == 6) option6(list_head);
        if(option == 7) option7(list_head);
        if(option == 8) option8(list_head);
        if(option == 9) option9(list_head);
        if(option == 10) {Save_In_File(file, list_head, profit, curent_date); save = false;}
        if(option == 11) option11(list_head, file);
        if(option == 12) option12();
        if(option == 0) running = false;
    }
    
    if(save)
        if(!Save_In_File(file, list_head, profit, curent_date));
        
    return 0;
}