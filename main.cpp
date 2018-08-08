#include <iostream>
#include <stdio.h>
#include <fstream>
#include <errno.h>
#include "sqlite3.h"
#include <typeinfo>

using namespace std;

typedef struct
{
    char fname[20];
    char lname[20];
    int barcode; //employee ID used to access/modify DB and to prevent tampering
    bool admin;
}users;


//*****Functions*****

void loadUsers(){
    ifstream file;
    file.open("userData.csv");

    if(!file.is_open()) std::cout <<"ERROR: Couldn't Parse Users.." << '\n';
    if(file.is_open()) {
        std::cout <<"Success:" << '\n';
        string line;
        while( getline (file,line))
            {
            cout<< line << '\n';
        }
    file.close();
    }
}


void addUser(){

    string fname;
    string lname;
    bool admin;
    int userBarcode;


    cout<< "To Create A New User Please Enter Your User Barcode Number:", '\n';
    cin>> userBarcode;
    cout<< "Please Enter New Users First Name:", '\n';
    cin>> fname;
    cout<< "Please Enter New Users Last Name:", '\n';
    cin>> lname;
    cout<< "Is This New User A System Admin? (y/n)";

    ofstream file;
    file.open("userData.csv", ios::app);
    if(file.is_open()){
    file << fname <<","<< lname <<","<< "True" <<'\n';
    file.close();
    }
    else{cout<< "error";}


}
void errorCheck(){
    perror("Error Occurred");
    printf("Error Code: %d\n", errno);
    exit(0);
}

void logUpdate(){

}


void deleteItem(){
}




void findItem(){
    int barcode;
    int quantity;
    printf(" Please Enter Barcode:\n");
    scanf(" %d", &barcode);
    printf("Please Enter Quantity Of Item:\n");
    scanf(" %d",&quantity);
}

void menu(){

    int selection = 0;
    char updateReason[75];

    do{

        printf("\n Please Choose One Of the Following Options:");
        printf("\n---------------------------------------------\n\n");
        printf(" 1.) Add To Inventory\n");
        printf(" 2.) Reduce From Inventory \n");
        printf(" 3.) Update Quantity Due To Error \n");
        printf(" 4.) Delete Old Inventory Item \n");
        printf(" 5.) Search Inventory \n\n");
        printf(" 6.) Add New User \n");
        printf(" 9.) Quit\n");
        printf("Make Your Selection And Press Enter...\n");

        scanf(" %d", &selection);

    }while(selection < 1 || selection > 9);

    switch(selection){

        case(1) : printf("\n Adding To Inventory.. \n");
                    findItem();
                    break;

        case(2) : printf("\n Reducing Item Count From Inventory.. \n");
                    findItem();
                    break;

        case(3) : printf("\n Update Item Quantity Due to Error..  \n");
                    printf(" Please Type Reason For Correction:\n");
                    scanf(" %d", &updateReason);
                    printf(updateReason);
                    break;

        case(4) : printf("\n Deleting Item From Database..  \n");
                    break;

        case(5) : printf("\n Find Item.. \n");
                    break;
        case(6) : printf("\n Create New User..\n");
                    addUser();
                    break;

        case(9) : printf("\n GoodBye!\n");
                    exit(0);
                    break;
    }

}


static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i<argc; i++){
        printf("%s = %s\n", azColName[i],argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void newItem(){
    string barcode, description, itemName;
    string brand;
    string model;

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char* data = "Callback function called";
    rc = sqlite3_open("inventory.db", &db);

    if( rc ){
        fprintf(stderr, "Cannot Open Database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    else{
        fprintf(stderr, "Database Connection Established..\n");
        }

    rc = sqlite3_exec(db, "SELECT * FROM Table1", callback, 0, &zErrMsg);

    sqlite3_close(db);

}

void checkTable(){ //checks if database table "inventory" exists, if not it creates the table.
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    bool result;
    const char* data = "Callback function called";
    rc = sqlite3_open("inventory.db", &db);

    if( rc ){
        fprintf(stderr, "Cannot Open Database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }else{
        fprintf(stderr, "Database Connection Established..\n");
        //result = sqlite3_exec(db*,const char "WHERE EXISTS (SELECT barcode FROM inventory)",NULL,NULL,NULL);
//        cout<< typeid(sqlite3_exec(db* ,"WHERE EXISTS (SELECT barcode FROM inventory)")).name();
        if (result){
            printf("Table inventory Found in Database..");
        }
        else{
//            sqlite3_exec(db*, "CREATE TABLE inventory(column1 int,column2 varchar(200),column3 varchar(200),)");
        }
        }




}

//******** Global Variables **************






int main(int argc, char* argv[]){





    while(1){
    menu();
 }



    return 0;
}


