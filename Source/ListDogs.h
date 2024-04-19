#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>

struct Date{
    int year;
    int month;
    int day;
};

struct Dog{
    int id;
    char name[50];
    char race[35];
    char birth[20];
    int price;
    int cage;
    Date* birth_date;
};

struct Nod{
    Dog* dog;
    Nod* next;
};

void Show_Dog_Info(Dog* dog){
    std::cout << dog->id << ' '
              << dog->name << ' ' 
              << dog->race << ' '
              << dog->birth << ' '
              << dog->price << ' '
              << dog->cage;
    std::cout << std::endl;
}

Date* StringToDate(char* date_string){
    Date* date = new Date;
    char string[4][20];
    int length = 0;

    int j = 0;
    for(int i = 0; date_string[i]; i++){
        if(strchr(" ./-", date_string[i])){ 
            string[j][length] = '\0'; 
            length = 0;
            j++; 
        }
        else string[j][length++] = date_string[i];
    }
    
    date->year = atoi(string[0]);
    date->month = atoi(string[1]);
    date->day = atoi(string[2]);

    return date;
}

Dog* GetDog_By_ID(int dog_id, Nod* list_head){
    for (; list_head->next != NULL; list_head = list_head->next){ 
        if(list_head->dog->id == dog_id) 
            break;
    }
    
    if(list_head->dog->id == dog_id) return list_head->dog;
        
    return NULL;
}

int GetLast_ID(Nod* list_head){
    if(list_head == NULL) return 0;
    for(; list_head->next != NULL; list_head = list_head->next);

    return list_head->dog->id; 
}

bool Dog_Exist(int dog_id, Nod* list_head){
    if(list_head->dog->id == dog_id) 
        return true;

    for (; list_head != NULL; list_head = list_head->next)
        if(list_head->dog->id == dog_id) 
            return true;
    
    return false;
}

int Show_List(Nod* list_head){
    if(list_head == NULL) return 0;

    while (list_head != NULL){
        Show_Dog_Info(list_head->dog);
        list_head = list_head->next;
    }

    return 1;
}

void Add_List(Dog* dog, Nod*& list_head){
    Nod* new_dog = new Nod({dog, NULL});
    Nod* head = list_head;

    if(list_head == NULL) { list_head = new_dog; return;}
    for(; head->next != NULL; head = head->next);
    
    head->next = new_dog;
}

void DeleteDog_By_ID(int dog_id, Nod*& list_head){
    Nod* target;
    if(dog_id == 0|| list_head->dog->id == dog_id) {
        target = list_head;
        list_head = list_head->next;
        delete target;

        return;
    }
    
    Nod* head = list_head;
    Nod* back;

    for (; head->next != NULL; head = head->next){ 
        if(head->dog->id == dog_id) break;
        back = head;
    }

    if(head == NULL) return;
    
    target = head;
    back->next = head->next;
    delete target;
}

bool File_Exists(char* file_name){
    std::ifstream FILE (file_name);
    if(!FILE) return false;
    FILE.close();

    return true;
}

int Load_From_File(char* file_name, Nod*& list_head, int& profit, Date*& current_date){
    std::ifstream FILE (file_name);
    if(!FILE) return 0;
    
    char line_buffer[55];

    FILE >> line_buffer;
    current_date = StringToDate(line_buffer);

    FILE >> line_buffer;
    profit = atoi(line_buffer);

    while (FILE){
        FILE.getline(line_buffer, 50);

        if(line_buffer[0] == '{'){
            Dog* dog = new Dog;

            int i = 0;
            while (line_buffer[0] != '}'){
                FILE.getline(line_buffer, 50);
                
                if(i == 0) dog->id = atoi(line_buffer);
                if(i == 1) strncpy(dog->name, line_buffer, 50);
                if(i == 2) strncpy(dog->race, line_buffer, 35);
                if(i == 3) strncpy(dog->birth, line_buffer, 20);
                if(i == 4) dog->price = atoi(line_buffer);
                if(i == 5) dog->cage = atoi(line_buffer);
                i++;
            }
            
            dog->birth_date = StringToDate(dog->birth);

            Add_List(dog, list_head);
        }
    }

    FILE.close();

    return 1;
}

int Save_In_File(char* file_name, Nod* list_head, int profit, Date*& current_date){
    std::ofstream FILE (file_name);
    
    if(!FILE) return 0;

    FILE << current_date->year << "." << current_date->month << "." << current_date->day;
    FILE << '\n';
    FILE << profit;
    FILE << '\n';
    while (list_head != NULL)
    {
        FILE << '\n';
        FILE << '{' << '\n';
        FILE << list_head->dog->id << '\n';
        FILE << list_head->dog->name << '\n';
        FILE << list_head->dog->race << '\n';
        FILE << list_head->dog->birth << '\n';
        FILE << list_head->dog->price << '\n';
        FILE << list_head->dog->cage << '\n';
        FILE << '}' << '\n';

        list_head = list_head->next;
    }

    FILE.close();

    return 1;
}