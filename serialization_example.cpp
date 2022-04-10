/*
Copyright 2022 by Néstor Nahuatlato
<soy_nestor@hotmail.com>

Licensed under GNU General Public License 3.0 or later.
@license GPL-3.0+
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <algorithm>

class Person{
    private:
        std::string firstName;
        std::string lastName;
        int age;
        char gender;

    public:
        Person(){}
        Person(const std::string& f, const std::string& l, const int& a, bool g){
            firstName = f;
            lastName = l;
            age = a;
            gender = g ? 'm' : 'w';
        }
        ~Person(){}
        
        void setFirstName(const std::string& f){
            firstName = f;
        }

        void setLastName(const std::string& l){
            lastName = l;
        }

        void setAge(const int& a){
            age = a;
        }

        void setGender(bool g){
            gender = g ? 'm' : 'w';
        }

        std::string getFirstName() const{
            return firstName;
        }

        std::string getLastName() const{
            return lastName;
        }

        int getAge() const{
            return age;
        }

        char getGender() const{
            return gender;
        }

        bool operator < (const Person& p) const{
            return age < p.age;
        }

        bool operator > (const Person& p) const{
            return age > p.age;
        }

        bool operator == (const Person& p) const{
            return lastName == p.lastName and firstName == p.firstName;
        }

        bool operator != (const Person& p) const{
            return lastName != p.lastName and firstName != p.firstName;
        }

        friend std::ostream& operator << (std::ostream& out, const Person& e){
            out<<e.gender<<"|"<<e.age<<"|"<<e.lastName<<" "<<e.firstName;
            return out;
        }

        friend std::ofstream& operator << (std::ofstream& out, const Person& e){
            out<<e.gender<<"\n"<<e.age<<"\n"<<e.lastName<<"\n"<<e.firstName;
            return out;
        }

        friend std::ifstream& operator >> (std::ifstream& in, Person& e){
            in>>e.gender;
            in>>e.age;
            in>>e.lastName;
            in>>e.firstName;

            return in;
        }
};

std::vector<Person> people;

void savingData(){
    std::ofstream output_file;
    output_file.open("people.txt", std::ios::out);

    if(output_file.fail()){
        std::cerr<<"Error opening file."<<std::endl;
        exit(1);
    }

    for(const auto& i: people)
        output_file<<i<<std::endl;

    output_file.close();
}

void loadingData(){
    std::ifstream input_file;
    input_file.open("people.txt", std::ios::in);

    if(input_file.fail()){
        std::cerr<<"Error opening file."<<std::endl;
        exit(1);
    }

    while(!input_file.eof()){
        Person aux;
        input_file>>aux;

        people.push_back(aux);
    }

    people.erase(people.end());

    input_file.close();
}

void insertingData(){
    system("clear");
    std::cout<<"----INSERT----"<<std::endl;
    std::cout<<"Please type without spaces..."<<std::endl;

    std::string aux_ln, aux_fn;
    int aux_a;
    char aux_g;

    std::cout<<std::endl<<"Last name: ";
    std::cin>>aux_ln;

    std::cout<<"First name: ";
    std::cin>>aux_fn;

    std::cout<<"Age: ";
    std::cin>>aux_a;

    std::cout<<"Gender [m/w]: ";
    std::cin>>aux_g;

    bool flag(false);
    aux_g = tolower(aux_g);

    if(aux_g == 'm')
        flag = true;
    
    Person newPerson(aux_ln, aux_fn, aux_a, flag);
    people.push_back(newPerson);

    std::cout<<"Person added successfully."<<std::endl;
}

void findingData(const char& op){
    system("clear");
    std::cout<<"-----FIND-----"<<std::endl;
    std::cout<<"Please type without spaces..."<<std::endl;

    std::string aux_s;
    Person aux_p;

    std::cout<<std::endl<<"Last name: ";
    std::cin>>aux_s;
    aux_p.setLastName(aux_s);

    aux_s.clear();
    std::cout<<"First name: ";
    std::cin>>aux_s;
    aux_p.setFirstName(aux_s);

    bool flag(false);
    std::vector<Person>::iterator it;

    for(it = people.begin(); it != people.end(); it++)
        if(aux_p == *it){
            flag = true;
            break;
        }

    if(!flag){
        std::cout<<"This person wasn't found."<<std::endl;
    }else{
        std::cout<<"Person found -> "<<*it<<std::endl;

        //Deleting Data
        if(op == 'b'){
            char answer;

            std::cout<<"Please confirm with 'y' for delete: "<<std::endl;
            std::cin>>answer;

            answer = tolower(answer);
            if(answer == 'y'){
                people.erase(it);

                std::cout<<"Person deleted successfully."<<std::endl;
            }else{
                std::cout<<"Action cancelled."<<std::endl;
            }
        }
    }
}

int main(){
    char option;

    loadingData();
    std::sort(people.begin(), people.end());

    do{
        std::cout<<"-----------------"<<std::endl;
        std::cout<<"Select an option."<<std::endl;
        std::cout<<"a. Insert."<<std::endl;
        std::cout<<"b. Delete."<<std::endl;
        std::cout<<"c. Search."<<std::endl;
        std::cout<<"d. Print."<<std::endl;
        std::cout<<"e. Exit."<<std::endl;
        std::cout<<"-----------------"<<std::endl;
        std::cin>>option;
        
        option = tolower(option);
        switch (option){
            case 'a': insertingData(); break;
            case 'b': case 'c': findingData(option); break;
            case 'd':
                for(const auto& i: people)
                    std::cout<<i<<std::endl;
            break;
            case 'e': break;
            default: std::cout<<"Wrong option! Try again, please."<<std::endl;
        }
    }while(option != 'e');

    savingData();

    return 0;
}