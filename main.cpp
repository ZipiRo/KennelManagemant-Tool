#include <iostream>
#include "Source\ListsDogs.h"

char file[100] = "Data\\dogs_long.data";
Date* curent_date = NULL;
bool running = true;
bool save = false;
int profit = 0;

int Get_Months(Date* dog_birth){
    int months = 0;

    months = abs(curent_date->year - dog_birth->year) * 12;
    months += abs(curent_date->month - dog_birth->month);

    return months;
}

void Find_Dogs_By_Race(Nod* list_head, char* race){
    bool found = false;
    for(; list_head != NULL; list_head = list_head->next)
        if(strstr(list_head->dog->race, race)){
            found = true;
            Read_Dog_Info(list_head->dog);
        }

    if(!found)
        std::cout << "NONE" << '\n';
}

void Show_Dogs_From_Cage(Nod* list_head, int cage){
    bool cage_ocupied = false;
    int total_price = 0;

    for(; list_head != NULL; list_head = list_head->next)
        if(list_head->dog->cage == cage){
            cage_ocupied = true;
            total_price += list_head->dog->price;
            Read_Dog_Info(list_head->dog);
        }

    if(!cage_ocupied) std::cout << "Empty";
    else std::cout << "Total: " << total_price << " EUR";
    
    std::cout << std::endl;
}   

void Find_Dogs_By_Months(Nod* list_head, int min, int max){
    bool found = false;
    for(; list_head != NULL; list_head = list_head->next){
        Dog* dog = list_head->dog;
        int months = Get_Months(dog->birth_date);

        if(months <= max && months >= min){
            found = true;
            Read_Dog_Info(dog);
        }
    }

    if(!found) std::cout << "No Dogs in that range" << '\n';
}

void Exterminate_Dogs_Age(Nod*& list_head, int max_age){
    bool exist = false;
    Nod* head = list_head;
    for(; head != NULL; head = head->next){
        Dog* dog = head->dog;
        int age = Get_Months(dog->birth_date) / 12;

        if(age >= max_age){
            Delete(dog->id, list_head);
            exist = true;
        }
    }

    if(!exist) std::cout << "There are no dogs at that age!" << '\n';
    else std::cout << "Dogs Exterminated" << '\n';
}

// SOFTWARE RELATED
void menu(){
    system("cls");

    std::cout << "---|KennelManagemant-Tool|---" 
        << curent_date->year << '.' << curent_date->month << '.' << curent_date->day 
        << "---" << file << "---" << '\n';
    std::cout << '\n';
    std::cout << "1...Show Dogs" << '\n';
    std::cout << "2...Find Dogs By Race" << '\n';
    std::cout << "3...Show Dogs From Cage" << '\n';
    std::cout << "4...Find Dogs By Months" << '\n';
    std::cout << "5...Exterminate Dogs By Age" << '\n';
    std::cout << "6...Sell Dog" << '\n';
    std::cout << "7...Add Dog" << '\n';
    std::cout << "8...Delete Dog" << '\n';
    std::cout << "9...Kennel Informatin" << '\n';
    std::cout << "10...Change Load File" << '\n';
    std::cout << "11...Change Curent Date" << '\n';
    std::cout << '\n';
    std::cout << "0...Save & Quit" << '\n';
    std::cout << "\n-> ";
}

void option1(Nod* list_head){
    system("cls");

    if(!Read(list_head))
        std::cout << "Empty" << '\n';
    
    std::cout << '\n';
    std::cout << "1...Back" << '\n';
    std::cout << '\n';
    std::cout << "-> ";

    int option = 0;
    do{
        std::cin >> option;
    }while (option != 1);
}

void option2(Nod* list_head){
    system("cls");

    char race[20];
    std::cout << "Race: " << '\n';
    std::cin >> race;

    system("cls");
    std::cout << "Dogs Found: " << '\n';
    Find_Dogs_By_Race(list_head, race);

    std::cout << '\n';
    std::cout << "1...Back" << '\n';
    std::cout << '\n';
    std::cout << "-> ";

    int option = 0;
    do{
        std::cin >> option;
    }while (option != 1);
}

void option3(Nod* list_head){
    system("cls");

    int cage;
    std::cout << "Cage: " << '\n';
    std::cin >> cage;

    system("cls");
    std::cout << "Cage " << cage << ": " <<'\n';
    Show_Dogs_From_Cage(list_head, cage);
    
    std::cout << '\n';
    std::cout << "1...Back" << '\n';
    std::cout << '\n';
    std::cout << "-> ";

    int option = 0;
    do{
        std::cin >> option;
    }while (option != 1);
}

void option6(Nod*& list_head){
    system("cls");

    Dog* dog;
    Nod* head = list_head;
    int dog_id;

    std::cout << "Dog ID: " << '\n';
    std::cin >> dog_id;
    
    system("cls");
    if(Dog_Exists(dog_id, list_head)){
        dog = Find_Dog(dog_id, head);

        Read_Dog_Info(dog);
        std::cout << "Are you sure?"<< '\n';
        std::cout << "1...Yes" << '\n';
        std::cout << "2...No" << '\n';
        std::cout << '\n';
        std::cout << "-> ";

        int option = 0;
        do{
            std::cin >> option;
        }while (option >= 2 && option <= 1);

        system("cls");
        if(option == 1) {
            save = true;
            std::cout << "Dog sold for: " << dog->price << " EUR" << '\n';
            profit += dog->price;
            Delete(dog_id, list_head);
        }
    }else{
        std::cout << "Dog not found" << '\n';
    }
    
    std::cout << '\n';
    std::cout << "1...Back" << '\n';
    std::cout << '\n';
    std::cout << "-> ";

    int option = 0;
    do{
        std::cin >> option;
    }while (option != 1);
}

void option7(Nod*& list_head){
    system("cls");

    Nod* head = list_head;
    Dog* dog = new Dog;

    std::cout << "Dog Name: " << '\n';
    std::cin >> dog->name;
    system("cls");
    std::cout << "Dog Race: " << '\n';
    std::cin >> dog->race;
    system("cls");
    std::cout << "Dog Birth: " << '\n';
    std::cin >> dog->birth;
    system("cls");
    std::cout << "Dog Price: " << '\n';
    std::cin >> dog->price;
    system("cls");
    std::cout << "Dog Cage: " << '\n';
    std::cin >> dog->cage;

    dog->id = Find_Dog(0, head)->id + 1;

    system("cls");
    Read_Dog_Info(dog);
    std::cout << "Are you sure?"<< '\n';
    std::cout << "1...Yes" << '\n';
    std::cout << "2...No" << '\n';
    std::cout << '\n';
    std::cout << "-> ";

    int option;
    do{
        std::cin >> option;
    }while (option >= 2 && option <= 1);

    system("cls");
    if(option == 1) {
        save = true;
        Add(dog, head);
        std::cout << "Dog added"<< '\n';
    }else{
        std::cout << "Dog was not good enough"<< '\n';
    }

    
    std::cout << '\n';
    std::cout << "1...Back" << '\n';
    std::cout << '\n';
    std::cout << "-> ";

    option = 0;
    do{
        std::cin >> option;
    }while (option != 1);
}

void option8(Nod*& list_head){
    system("cls");

    int dog_id;
    std::cout << "Dog ID: " << '\n';
    std::cin >> dog_id;

    system("cls");
    if(Dog_Exists(dog_id, list_head)){
        Read_Dog_Info(Find_Dog(dog_id, list_head));
        std::cout << "Are you sure?"<< '\n';
        std::cout << "1...Yes" << '\n';
        std::cout << "2...No" << '\n';
        std::cout << '\n';
        std::cout << "-> ";

        int option = 0;
        do{
            std::cin >> option;
        }while (option >= 2 && option <= 1);

        system("cls");
        if(option == 1) {
            save = true;
            Delete(dog_id, list_head);
            std::cout << "Dog deleted"<< '\n';
        }
    }else{
        std::cout << "Dog not found"<< '\n';
    }
    
    std::cout << '\n';
    std::cout << "1...Back" << '\n';
    std::cout << '\n';
    std::cout << "-> ";

    int option = 0;
    do{
        std::cin >> option;
    }while (option != 1);
}

void option4(Nod* list_head){
    system("cls");

    int min, max;
    std::cout << "Min Months: " << '\n';
    std::cin >> min;
    system("cls");
    std::cout << "Max Months: " << '\n';
    std::cin >> max;
    
    system("cls");
    std::cout << "Dogs Found: " << '\n';
    Find_Dogs_By_Months(list_head, min, max);
    
    std::cout << '\n';
    std::cout << "1...Back" << '\n';
    std::cout << '\n';
    std::cout << "-> ";

    int option = 0;
    do{
        std::cin >> option;
    }while (option != 1);
}

void option5(Nod* list_head){
    system("color 4");
    system("cls");

    int age;
    std::cout << "Max age: " << '\n';
    std::cin >> age;
    
    std::cout << "Result: " << '\n';
    Exterminate_Dogs_Age(list_head, age);
    
    std::cout << '\n';
    std::cout << "1...Back" << '\n';
    std::cout << "2...Exit" << '\n';
    std::cout << '\n';
    std::cout << "-> ";

    save = true;
    int option = 0;
    do{
        std::cin >> option;
    }while (option >= 2 && option <= 1);

    if(option == 2) running = false;
}

void option9(Nod* list_head){
    system("cls");
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
    
    std::cout << '\n';
    std::cout << "1...Back" << '\n';
    std::cout << '\n';
    std::cout << "-> ";

    int option = 0;
    do{
        std::cin >> option;
    }while (option != 1);
}

void option10(Nod*& list_head, char file[]){
    char* past_file = file;
    char new_file[100];

    do{
        system("cls");
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
        strncpy(file, new_file, 100);
        if(save)
            Save_In_File(past_file, list_head, profit, curent_date);

        Load_From_File(new_file, list_head, profit, curent_date);
    }
}

void option11(){
    char new_date[20];
    do{
        system("cls");
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
        curent_date = Get_Date_String(new_date);
    }
}

int main(){
    Nod* list_head;

    if(!Load_From_File(file, list_head, profit, curent_date)){
        running = false;
        std::cout << "------------------NO FILE-------------------" << '\n';
        std::cout << "...Change file path in code and recompile..." << '\n';
        std::cout << "........The file should not be empty........" << '\n';

        int anykey;
        std::cin >> anykey;
    }

    while (running){
        system("color 2");
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
        if(option == 10) option10(list_head, file);
        if(option == 11) option11();
        if(option == 0) running = false;
    }
    
    if(save)
        if(!Save_In_File(file, list_head, profit, curent_date));

    return 0;
}