#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cstdio>

using namespace std;

struct Person{
    int id;
    string name, lastname, phoneNumber, mail, adress;
};

string getWholeLine (){
    cin.sync();
    string input = "";
    getline(cin, input);
    return input;
}

char getChar (){
    char sign;
    cin.sync();
    sign = getchar();
    return sign;
}

int fromFile (vector <Person>& persons){

    Person contact;
    int signPosition = 0;
    int amountOfContacts = 0;
    string line, stringPom;

    fstream file;
    file.open ("TEST.txt", ios::in);

    if (file.good() == true){
        while (getline(file, line)){
        signPosition = 0;
            for (int i = 0; i < 6; ++i){
                stringPom = "";
                while (line[signPosition] != '|'){
                    stringPom += line[signPosition];
                    ++ signPosition;
                }
                switch (i){
                    case 0: contact.id = stoi(stringPom); break;
                    case 1: contact.name = stringPom; break;
                    case 2: contact.lastname = stringPom; break;
                    case 3: contact.phoneNumber = stringPom; break;
                    case 4: contact.mail = stringPom; break;
                    case 5: contact.adress = stringPom; break;
                }
                ++ signPosition; // Przeskakujemy za '|'
            }
            persons.push_back(contact);
            amountOfContacts += 1;
        }
        file.close();
        return amountOfContacts;
    }
    else return 0;
}

void toFile (Person osoba){

    fstream file;
    file.open ("TEST.txt", ios::out | ios::app);
    file << osoba.id << "|" << osoba.name << "|" << osoba.lastname << "|" << osoba.phoneNumber << "|" << osoba.mail << "|" << osoba.adress << "|" << endl;
    file.close();
}

void goUpper (Person& singleContact){
    transform(singleContact.name.begin(), singleContact.name.end(), singleContact.name.begin(), :: toupper);
    transform(singleContact.lastname.begin(), singleContact.lastname.end(), singleContact.lastname.begin(), :: toupper);
}

int getID (vector <Person> persons){

    int newID;
    for (auto osoba : persons){
       newID = osoba.id;
    }
    return newID + 1;
}

int addContact (int amountOfUsers, vector <Person>& persons){

    system("cls");
    Person newContact;

    cout << "Enter name: "; newContact.name = getWholeLine();
    cout << "Enter last name: "; newContact.lastname = getWholeLine();
    cout << "Enter phone number: "; newContact.phoneNumber = getWholeLine();
    cout << "Enter mail adress: "; newContact.mail = getWholeLine();
    cout << "Enter adress: "; newContact.adress = getWholeLine();
    newContact.id = getID(persons);

    goUpper (newContact); // name + lastname
    toFile (newContact);
    persons.push_back(newContact);
    cout << endl << "Successful!" << endl;

    system ("pause");
    return amountOfUsers += 1;
}

void searchContact (vector <Person>& persons, int parametr){ // 0 for name, 1 for lastname

    bool isFindAnyone = false;
    string name, lastname;

    system ("cls");
    switch (parametr){
        case 0:
            cout << "Enter name: "; cin >> name;
            transform(name.begin(), name.end(), name.begin(), :: toupper);
            for (auto contact : persons){
                if (name == contact.name){
                    cout << "ID:           " << contact.id << endl;
                    cout << "Name:         " << contact.name << endl;
                    cout << "Lastname:     " << contact.lastname << endl;
                    cout << "Phone number: " << contact.phoneNumber << endl;
                    cout << "Mail adress:  " << contact. mail << endl;
                    cout << "Adress:       " << contact.adress << endl;
                    cout << endl;
                    isFindAnyone = true;
                }
            }
            if (isFindAnyone == false){
                cout << "Sorry, Cant find anyone.\n\n";
            }
            system("pause");
            break;
        case 1:
            cout << "Enter lastname: "; cin >> lastname;
            transform(lastname.begin(), lastname.end(), lastname.begin(), :: toupper);
            for (auto contact : persons){
                if (lastname == contact.lastname){
                    cout << "ID:           " << contact.id << endl;
                    cout << "Name:         " << contact.name << endl;
                    cout << "Lastname:     " << contact.lastname << endl;
                    cout << "Phone number: " << contact.phoneNumber << endl;
                    cout << "Mail adress:  " << contact. mail << endl;
                    cout << "Adress:       " << contact.adress << endl;
                    cout << endl;
                    isFindAnyone = true;
                }
            }
            if (isFindAnyone == false){
                cout << "Sorry, Cant find anyone.\n" << endl;
            }
            system("pause");
            break;
    }
}

void viewAll (vector <Person> persons){

    system ("cls");
    for (auto contact : persons){
        cout << "ID:           " << contact.id << endl;
        cout << "Name:         " << contact.name << endl;
        cout << "Lastname:     " << contact.lastname << endl;
        cout << "Phone number: " << contact.phoneNumber << endl;
        cout << "Mail adress:  " << contact. mail << endl;
        cout << "Adress:       " << contact.adress << endl;
        cout << endl;
    }
    system ("pause");
}

void createNewFileAndReplace (vector <Person> persons) {

    fstream file;
    file.open ("TEMP.txt", ios::out | ios::app);

    for (auto osoba : persons){
        file << osoba.id << "|" << osoba.name << "|" << osoba.lastname << "|" << osoba.phoneNumber << "|" << osoba.mail << "|" << osoba.adress << "|" << endl;
    }
    file.close();

    remove("TEST.txt");
    rename("TEMP.txt", "TEST.txt");
}

int deleteContact (vector <Person>& persons, int amountOfUser){

    int id;
    auto position = persons.begin(); //alternatywa : vector <Person> :: iterator position = persons.begin();
    cout << "Enter ID: "; cin >> id;

    for (auto a : persons){
        if (id == a.id){
            cout << "Confirm -> 't' / Declaind -> any key ";
            if (getChar() == 't'){
                position = persons.erase(position);
                cout << "Contact has been deleted.\n";
                system ("pause");
            }
            else{
                cout << "Contact has not been deleted.\n";
                system ("pause");
                break;
            }
        }
        ++position;
    }
    createNewFileAndReplace (persons);
    return -- amountOfUser;
}

void editPerson (vector <Person>& persons){

    int id, choice;
    string newName, newLastname, newPhoneNumber, newMail, newAdress;
    system ("cls");
    cout << "Enter ID: "; cin >> id;
    cout << "Choose: " << endl;
    cout << "1. name" << endl;
    cout << "2. Lastname" << endl;
    cout << "3. Phone number" << endl;
    cout << "4. Mail" << endl;
    cout << "5. Adress" << endl;
    cout << "6. Back to menu" << endl;
    cin >> choice;

    for (auto & a : persons){
        if (id == a.id){
            switch (choice){
                case 1: cout << "Enter new name: "; cin >> newName; transform(newName.begin(), newName.end(), newName.begin(), :: toupper); a.name = newName; break;
                case 2: cout << "Enter new lastname: "; cin >> newLastname; transform(newLastname.begin(), newLastname.end(), newLastname.begin(), :: toupper); a.lastname = newLastname; break;
                case 3: cout << "Enter new phone number: "; cin >> newPhoneNumber; a.phoneNumber = newPhoneNumber; break;
                case 4: cout << "Enter new mail: "; cin >> newMail; a.mail = newMail; break;
                case 5: cout << "Enter new adress: "; cin >> newAdress; a.adress = newAdress; break;
                case 6: break;
            }
            break;
        }
    }
    createNewFileAndReplace (persons);
}

int main(){

    vector <Person> persons;
    char choice;
    int amountOfUsers;

    amountOfUsers = fromFile(persons); //Loading data after fired up

    while (1){
        system ("cls");
        cout << "------------------\n" << "KSIAZKA ADRESOWA\n" << "------------------\n\n";
        cout << "MAIN MENU:\n";
        cout << "1. Add contact\n";
        cout << "2. Search Adress by name\n";
        cout << "3. Search Adress by lastname\n";
        cout << "4. View all contacts\n";
        cout << "5. Delete contact\n";
        cout << "6. Edit contact\n";
        cout << "7*. Amount of contacts\n";
        cout << "0. Close app\n\n";

        cout << "Enter a choice: ";
        cin >> choice;

        switch (choice){
            case '1' : amountOfUsers = addContact (amountOfUsers, persons);
                break;
            case '2' : searchContact (persons, 0); // 0 for name
                break;
            case '3' : searchContact (persons, 1); // 1 for lastname
                break;
            case '4' : viewAll (persons);
                break;
            case '5' : amountOfUsers = deleteContact (persons, amountOfUsers);
                break;
            case '6' : editPerson (persons);
                break;
            case '7' : cout << amountOfUsers << endl; system ("pause");
                break;
            case '0' : exit(0);
                break;
            default : cout << "\nNie ma takiej opcji\n"; system ("pause");
        }
    }
    return 0;
}
