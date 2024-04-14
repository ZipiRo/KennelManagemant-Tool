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

void Read_Dog_Info(Dog* dog){
    std::cout << dog->id << ' '
              << dog->name << ' ' 
              << dog->race << ' '
              << dog->birth << ' '
              << dog->price << ' '
              << dog->cage;
    std::cout << std::endl;
}

Date* Get_Date_String(char* date_string){
    Date* date = new Date;
    char number_string[20];
    int length = 0;

    for(int i = 0; date_string[i]; i++){
        if(strchr("./-",date_string[i]));
        else number_string[length++] = date_string[i];
    }
    number_string[length] = '\0';

    int number_date; 
    number_date = atoi(number_string);

    date->day = number_date % 100;
    number_date /= 100;
    date->month = number_date % 100;
    number_date /= 100;
    date->year = number_date;
    
    return date;
}

Dog* Find_Dog(int dog_id, Nod* list_head){
    for (; list_head->next != NULL; list_head = list_head->next){ 
        if(list_head->dog->id == dog_id) 
            break;
    }

    if(!dog_id){
        return list_head->dog;
    }
    
    if(list_head->dog->id != dog_id) {
        std::cout << "Dog does not exist" << std::endl; 
        return NULL;
    }
    else return list_head->dog;
}

int Dog_Exists(int dog_id, Nod* list_head){
    if(list_head->dog->id == dog_id) 
        return 1;

    for (; list_head != NULL; list_head = list_head->next)
        if(list_head->dog->id == dog_id) 
            return 1;
    
    return 0;
}

int Read(Nod* list_head){
    Nod* head = list_head;

    if(head != NULL){
        while (head != NULL){
            Read_Dog_Info(head->dog);
            head = head->next;
        }

        return 1;
    }

    return 0;
}
void Create(Dog* dog, Nod*& list_head){
    list_head = new Nod({dog, NULL});
}
void Add(Dog* dog, Nod*& list_head){
    Nod* new_dog = new Nod({dog, NULL});
    Nod* head = list_head;
    if(list_head == NULL) list_head = new_dog;
    for(; head->next != NULL; head = head->next);
    head->next = new_dog;
}
void Delete(int dog_id, Nod*& list_head){
    if(!dog_id || list_head->dog->id == dog_id) {
        Nod* target = list_head;
        list_head = list_head->next;
        delete target;

        return;
    }
    
    Nod* head = list_head;
    Nod* back;

    for (; head->next != NULL; head = head->next){ 
        if(head->dog->id == dog_id) 
            break;
        back = head;
    }

    if(head == NULL) return;
    
    Nod* target = head;
    back->next = head->next;
    delete target;
}

int File_Exists(char* file_name){
    std::ifstream FILE (file_name);
    if(!FILE) return 0;
    FILE.close();

    return 1;
}
int Load_From_File(char* file_name, Nod*& list_head, int& profit, Date*& current_date){
    std::ifstream FILE (file_name);
    if(!FILE) return 0;
    
    bool list_created = false;
    char line[55];

    FILE.getline(line, 50);
    current_date = Get_Date_String(line);

    FILE.getline(line, 50);
    profit = atoi(line);

    while (FILE){
        FILE.getline(line, 50);

        if(line[0] == '{'){
            Dog* dog = new Dog;

            int i = 0;
            while (line[0] != '}'){
                FILE.getline(line, 50);
                
                if(i == 0) dog->id = atoi(line);
                if(i == 1) strncpy(dog->name, line, 50);
                if(i == 2) strncpy(dog->race, line, 35);
                if(i == 3) strncpy(dog->birth, line, 20);
                if(i == 4) dog->price = atoi(line);
                if(i == 5) dog->cage = atoi(line);
                i++;
            }
            
            dog->birth_date = Get_Date_String(dog->birth);

            if(!list_created){
                Create(dog, list_head); 
                list_created = true;
            }
            else Add(dog, list_head);
        }
    }

    FILE.close();

    return 1;
}
int Save_In_File(char* file_name, Nod* list_head, int profit, Date*& current_date){
    std::ofstream FILE (file_name);
    
    if(!FILE) return 0;
    
    FILE << current_date->year << ".0" << current_date->month << ".0" << current_date->day;
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