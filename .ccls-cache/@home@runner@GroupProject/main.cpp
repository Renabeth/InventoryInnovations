//******************************************************************
// Group Project:  Restaurant Inventory
// Authors:        Andrew Carpio, Serena D'Avanzo, Jared Morales,  
//                 Demetrius Quintyne, Joelly Velasquez 
// Date:           5/15/2023 
// Version:        V1
// System Name:    Inventory Innovations
//*******************************************************************
#include "Product.h"
#include "User.h"
#include "PurchasedFood.h"
#include "Storage.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

//diff depart will get diff amounts

/*Function Prototypes*/

// Data Functions
void loadUsers(User users[], int size); //load Users.txt file
void loadProducts(Product products[], int size);//load Products.txt(product cost per lb)
void loadStorage(Storage storagelist[], int size);//load storage.txt file/data
void loadTransactions(vector<PurchasedFood> &pfs);


// Update Functions
void DeleteEmptyLines(string filename); // Deletes empty lines 
void updateUser(User users[], int size); // gets data to send to updateFile()
void updateProduct(Product products[], int size); // gets data to send to updateFile()
void updateStorage(Storage storagelist[], int size); // gets data to send to updateFile()
void updateFile(string file, string find, string newline); //update file when data changes(ex.purchase{add purchased item to storage},fund changes)


// Processing Functions

string getDate();
void viewInventory();//what is in storage.txt
void viewTransactions();//*!*// need to add total price
int countFilelines(string file); // gets number of lines file contains
void login(User users[], int size);// check if inputted login exists and logs them in
void displayMenu(User users[], int usize, Product products[], int psize, Storage storagelist[], int isize, vector<PurchasedFood> pfs);//for members
void displayMenuA(User users[], int usize, Product products[], int psize, Storage storagelist[], int isize, vector<PurchasedFood> pfs);//for admin
void DisperseFunds(User users[],int size);//for admin to distribute funds
void buyProducts(User users[], int usize, Product products[], int psize, Storage storagelist[], int isize, vector<PurchasedFood> pfs);// buy product then update files according to purchase
void viewFunds(User users[],int size);//balance of person logged in
void writePurchases(vector<PurchasedFood> pfs);// place purchases in txt file
bool DeptLimit (User users[], int choice); //Limit what dept members can buy in buyProducts()
bool GoodInputTest(float test); //Test to see if cin input is a number/valid
bool EmptyFileTest(string file); // Test to see if file is empty


// counter variables
int lif = -1; // logged in fitter
//int numt; //number of transactions
string dump = "";

int main() 
{
  // Manager Variables (fullname, username, password, dep, funds)
	const int USERSIZE = 6; 
	User users[USERSIZE]; // create array for all users
	loadUsers(users, USERSIZE);// enter/load user information into array

  // Product Variables (Id, name, type, price)
	const int PRODUCTSIZE = 10;  
	Product products[PRODUCTSIZE]; // create array for all product data
	loadProducts(products, PRODUCTSIZE);// enter/load product information into array

  // Storage Variables (Id, name, type, quantity)
	const int STORAGESIZE = 10; 
	Storage storagelist[STORAGESIZE]; // create array for Inventory data
	loadStorage(storagelist, STORAGESIZE);// enter/load Inventory information into array

  
  //Purchased Food - Transactions
	vector<PurchasedFood> pfs;
  loadTransactions(pfs);


  cout << "-------------------------------------------" << endl;
	cout << "  WELCOME TO INVENTORY INNOVATIONS SYSTEM " << endl;
	cout << "-------------------------------------------\n\n" << endl;
  
  
  //Call Functions
  login(users, USERSIZE);
  //displayMenu(users, USERSIZE, users[lif],);
  
  if (users[lif].getDepartment() == 0)//if person is admin display diff menu
    displayMenuA(users, USERSIZE, products, PRODUCTSIZE, storagelist, STORAGESIZE, pfs);
  else
    displayMenu(users, USERSIZE, products, PRODUCTSIZE, storagelist, STORAGESIZE, pfs);
  
} //end of main

void login(User users[], int size) {

  string enterUsername = "";
  string enterPass = "";
  bool isValid = false;
  int numattempts = 0;
  int tries = 2;

  cout << "\n--------------------------------" << endl;
	cout << "          LOGIN SCREEN          " << endl;
	cout << "--------------------------------\n\n" << endl;

  cout << "----3 Attempt(s) Remaining----\n" << endl;
  
  do {
    cout << "Enter your user name: ";
    cin >> enterUsername;

    cout << "Enter your password: ";
    cin >> enterPass;

    for (int i = 0; i < size; i++) 
    { 
      if (enterUsername == users[i].getUsername() && enterPass == users[i].getPassword()) 
      { 
        cout << "Login Successful" << endl;
        isValid = true;
        lif = i;//find who is logged in and remember place in array
      }
    }
    if (tries!=0 && !isValid)
    cout<<"\nYou have " << tries << " attempts remaining.\n" <<endl;
    numattempts++;
    tries--;
  } while (numattempts < 3 && !isValid);

  if (!isValid) 
  {
    cout << "Number of attempts exceeded, Program Terminated!" << endl;
    exit(100);
  }

} // end of function

void displayMenu(User users[], int usize, Product products[], int psize, Storage storagelist[], int isize, vector<PurchasedFood> pfs) {
  int choice = 0;
  
  do{//loops displayMenu until they log out
  // Display Welcome Message and Menu

  cout << "\n-------------------------------" << endl;
	cout << "        MEMBER SCREEN " << endl;
	cout << "-------------------------------\n\n" << endl;

  cout << "=========================================" << endl;
  cout << "\nPlease select a menu option" << endl;
  cout << "1. View Inventory" << endl;
  cout << "2. Purchase Products/Update Inventory" << endl;
  cout << "3. Check Budget" << endl;
  cout << "4. View last 10 transactions" << endl;
  cout << "5. Log off" << endl;
  cout << "=========================================" << endl;
    
  // Get the menu choice
  
  cin >> choice;
  getline(cin,dump); //dumps remaining input
  GoodInputTest(choice); //If letter returns false but also resets choice to zero
  switch (choice) {
  case 1: {
    viewInventory();
    break;
  }
  case 2: {
    buyProducts(users, usize, products, psize, storagelist, isize, pfs);
    break;
  }
  case 3: {
    viewFunds(users, usize);
    break;
  }
  case 4: {
    viewTransactions();
    break;
  }
  case 5: {
    cout << "Logging off. Thank you." << endl;
    exit(0);
  }
  default: {
    cout << "Invalid Selection" << endl;
    continue;
  }
  }// end of choices
  } while (choice != 5);
} //

//************************ Menu Selections *******************************

void viewInventory() { 

  cout << "\n*****************************************\n" << endl;
  cout << "            Total Inventory              \n\n"<< endl;
  
  cout << left;
  cout << setw(6) << "ID" ;
  cout << setw(12) << "Name";
  cout << setw(10) << "Type";
  cout << "Quantity(lb)" << endl;
  
  cout << "=========================================" << endl;
  
  
  ifstream infile;
	infile.open("Storage.txt");
	int i = 0;

  string I = "";
  long productID = 0;
  string q = "";
  string pname = "";
  string type = "";
  float quantity = 0; 

  while (!infile.eof())//*!*//
	{
    getline(infile,I,',');
    productID = stol(I);
		getline(infile, pname,',');
		getline(infile, type, ',');
		getline(infile, q,'\n');
	  quantity = stol(q);
    

	//	storage[i] = Storage(productID, pname, type, quantity);
    
		i++;
    
    cout << I << "| ";
    cout << setw(12) << pname;
    cout << setw(13) << type;
    cout << q << endl;
 
	}
  cout  << "\n*****************************************" << endl;
  infile.close();
   
} // end of funtion? 

void buyProducts(User users[], int usize, Product products[], int psize, Storage storagelist[], int isize, vector<PurchasedFood> pfs) {
  int choice = 0;
  int quantity = -1;
  int i = 0;

  do {
  cout << "----------------------------------" << endl;
  cout << "Choose a product to purchase(lb)" << endl;
  cout << "1. Lettuce" << endl;
  cout << "2. Tomato" << endl;
  cout << "3. Bread" << endl;
  cout << "4. Ground Beef" << endl;
  cout << "5. Chicken" << endl;
  cout << "6. Potato" << endl;
  cout << "7. Onion" << endl;
  cout << "8. Bacon" << endl;
  cout << "9. Eggs" << endl;
  cout << "10. Cheese" << endl;
  cout << "11. Return to menu" << endl;
  cout << "----------------------------------" << endl;
  
  cin >> choice; 
  getline(cin,dump); //dumps remaining input
  GoodInputTest(choice); //If letter, returns false but also resets choice to zero

  switch (choice) {
  case 1: {
   i = 1;
   break;
  }
  case 2: {
    i = 2;
    break;
  }
  case 3: {
    i = 3;
    break;
  }
  case 4: {
    i = 4;
    break;
  }
  case 5: {
    i = 5;
    break;
  }
  case 6: {
    i = 6;
    break;
  }
  case 7: {
    i = 7;
    break;
  }
  case 8: {
    i = 8;
    break;
  }
  case 9: {
    i = 9;
    break;
  }
  case 10: {
    i = 10;
    break;
  }
  case 11: {
    continue; // go to end of while loop
    break;
  }
  default: {
    cout << "Invalid Selection" << endl;
    continue;
  }
  }// end of choice
    --i;

    if (!DeptLimit(users,choice)) { //check Dept purchase authority
      cout << "Your Department does not allow for purchase of this product!" << endl;
      continue;
    }
    
    cout << "\nTotal Funds available: $" << users[lif].getFunds() << endl; 
    cout << "How much do you want to buy?(lb): costs $" << products[i].getPrice() << " per lb" << endl;

    cout << "Quantity: ";
    
    while (!(cin >> quantity)) { //If letter enter again
      GoodInputTest(quantity); 
      cout << "Error: Try Again!" << endl;
    }
    getline(cin,dump); //dumps remaining input

    
    float calcprice = products[i].getPrice()*quantity;
    cout << "\nTotal price: $" << calcprice << endl<<endl;
  
    if (calcprice > users[lif].getFunds() || quantity < 0) {
     
      cout << "Error: Non number entered or insufficient funds for purchase!\nTry again." << endl;
    }
    else {
      users[lif].setFunds(users[lif].getFunds() - calcprice);
      storagelist[i].setQuantity(storagelist[i].getQuantity()+quantity);
      pfs.push_back(PurchasedFood(products[i].getProductID() , quantity, calcprice, getDate()));
      updateUser(users,usize);
      updateStorage(storagelist,isize);
      writePurchases(pfs); //*!*//
    }
     
  } while (choice != 11);
    
} //end of function

void viewFunds(User users[],int size) {
    cout << "\nAvaliable Funds = $" << users[lif].getFunds() << endl;
} // end of function (all it needs?)

void viewTransactions() { // view last 10 Transactions

  cout << "\n*********************************************\n\n" << endl;
  cout << "----------------Transactions----------------\n\n" << endl;
  cout << left;
  cout << setw(7) << "ID";
  cout << setw(5) << "lb";
  cout << setw(19) << "Total";
  cout << "Date" << endl;
  cout << "=============================================" << endl;
  ifstream infile;
	infile.open("Transactions.txt");
  int start(0),line(0),i(0);
  string trash;
  string productID = "";
  string T = "";
  float total = 0;
  string productQ = "";
  string saleDate = "";
  
  
  line = countFilelines("Transactions.txt");
  line-=10;
  
  while (!infile.eof() && !EmptyFileTest("Transactions.txt"))
	{
    if (line == start || line<=0) // check if it's the last 10 lines then displays them
    {
             
      getline(infile, productID, ','); // gets line in file
		  getline(infile, productQ, ',');
      getline(infile, T, ',');
      total = stof(T);
	  	getline(infile, saleDate, '\n');
      
        
      cout << setw(7) << productID;
      cout << setw(5) << productQ;
      cout << "$" << fixed << setprecision(2) << setw(8) << total;
      cout << saleDate << endl;
      
       
    }
    else {
      getline(infile,trash);
    ++start;
    }
  }
  if (EmptyFileTest("Transactions.txt")) {cout << "No Previous Transactions to view" << endl;}
  cout << "\n*********************************************" << endl;
} //end of function? (add total price of transaction for file)

//************************ Menu Selections *******************************

//***************************** Admin ************************************

void displayMenuA(User users[], int usize, Product products[], int psize, Storage storagelist[], int isize, vector<PurchasedFood> pfs) {
  int choice = 0;

  do{//loops displayMenu until they log out or relogin
  // Display Welcome Message and Menu

  cout << "\n--------------------------------" << endl;
	cout << "         ADMIN SCREEN           " << endl;
	cout << "--------------------------------\n\n" << endl;

  cout << "=========================================" << endl;
  cout << "\nPlease select a menu option" << endl;
  cout << "1. Set funds for departments(5 Dept.)" << endl;
  cout << "2. View Funds" << endl;
  cout << "3. View stored items" << endl;
  cout << "4. View last 10 transactions" << endl;
  cout << "5. Relogin with another account" << endl;
  cout << "6. Log off" << endl;
  cout << "=========================================" << endl;

  // Get the menu choice
  cin >> choice;
  getline(cin,dump); //dumps remaining input
  GoodInputTest(choice); //If letter returns false but also resets choice to zero
  
  switch (choice) {
  case 1: {
    DisperseFunds(users, usize);
    break;
  }
  case 2: {
    viewFunds(users, usize);
    break;
  }
  case 3: {
    viewInventory();
    break;
  }
  case 4: {
    viewTransactions();
    break;
  }
  case 5: {
    login(users, usize);
    displayMenu(users, usize, products, psize, storagelist, isize, pfs);
    break;
  }
  case 6: {
    cout << "Logging off. Thank you." << endl;
    exit(0);
  }
  default: {
    cout << "Invalid Selection" << endl;
    continue;
  }
  }//end of choices
  }while (choice != 6 || choice != 5);
} //

void DisperseFunds(User users[],int size) { //set funds for deparments
  int choice;
  float amount = -1;
  int dep;
  bool again = false;
  do { //loops if invalid choice/input

  // display
  cout << "\nTotal Funds: $"<< users[lif].getFunds()<<endl;
  cout << "1. set amount to divide evenly" << endl;
  cout << "2. set amount for each deparment manually" << endl;
  cout << "3. Return to menu" << endl;
  cin >> choice;
  getline(cin,dump); //dumps remaining input
  GoodInputTest(choice); //If letter returns false but also resets choice to zero
    
  switch (choice) {
  case 1: {
    
    do { //loops if invalid input
      cout << "\nFunds available to disperse: $"<< users[lif].getFunds()<<endl;
      cout << "Amount: $";
      amount = 0;
      while (!(cin >> amount)) { //if letter try again
        GoodInputTest(amount); 
        cout << "Error: Try Again!" << endl;
      }
      getline(cin,dump); //dumps remaining input

      if (amount > users[lif].getFunds() || amount < 0) {
        cout << "Error. Non number entered or insufficient funds.Try again." << endl;
        again=true;
      }
      else 
      {
         
        users[lif].setFunds(users[lif].getFunds()-amount);
        amount /= size-1;
        cout <<"Divided: $"<< amount << endl;
        for (int i=1;i<size;i++)
        {
          users[i].setFunds(users[i].getFunds()+amount);
        }
        cout << "Funds successfully dispersed." <<endl;
        again=false;
      }
      amount = 0;
    } while (again || amount < 0);
    
    break;
  } //case 1
    case 2: {
    
    do { //loops if invalid input
      cout << "Funds available to disperse: $"<<users[lif].getFunds()<<endl;
      cout << "Enter Dept. number(0 to quit): "<<endl;
      
      while(!(cin >> dep)) { //if letter try again
        GoodInputTest(dep);
        cout <<"Error: Try Again!" << endl;
      }
      getline(cin,dump); //dumps remaining input
      if (dep > size || dep < 0)
      {
        cout << "Error. Try again." << endl;
        again = true;
        continue;
      }
      else if (dep == 0) {again=false; continue;} //exit loop
      
      cout << "Funds available to disperse: $"<<users[lif].getFunds()<<endl;
      cout << "Amount: ";
      while (!(cin >> amount)) { //if letter try again
        GoodInputTest(amount);
        cout << "Error Try Again" << endl;
      }
      getline(cin,dump); //dumps remaining input
      if (amount > users[lif].getFunds() || amount < 0) {
        cout << "Error. Non number entered or insufficient funds.Try again." << endl;
        again = true;
        continue;
      }
      
        cout << "Funds successfully dispersed." << endl;
        again = false;
      
    } while (again);

    users[lif].setFunds(users[lif].getFunds()-amount); //deducts amount from Admin
    users[dep].setFunds(users[dep].getFunds()+amount); //increases funds of member
    break;
      
    }//case 2
    case 3: {
      continue;
      break;
    }
  default: {
    cout << "Invalid Selection" << endl;
    continue;
  }
    
  }//end of choice selection
  } while (choice > 3 || choice < 1);
  updateUser(users, size);
  
} //end of function

//***************************** Admin ************************************

//***************************** Load Data ********************************

void loadUsers(User users[], int size) {	// open a file in read mode.

  DeleteEmptyLines("Users.txt");

	ifstream infile;
	infile.open("Users.txt");
	int i = 0;
  
  //fields of Users.txt
	string fullname = "";
  string username = "";
  string password = "";
  string d = "";
  int department = 0;
  string f = "";
  float funds = 0;

	while (!infile.eof()) //goes through file adding all fields to a User class array
	{
    
		getline(infile, fullname, ',');
		getline(infile, username, ',');
		getline(infile, password, ',');
		getline(infile, d, ',');
    department = stol(d); //convert string to int
		getline(infile, f, '\n');
    funds = stof(f); //convert string to float
    
		//add to the User users[] array
		users[i] = User(fullname, username, password, department, funds);
		i++;

	}
	cout << "Users Loaded" << endl;

	infile.close();
} //end of function

void loadProducts(Product products[], int size) { // open a file in read mode
  
  DeleteEmptyLines("Products.txt");
  
  ifstream infile;
	infile.open("Products.txt");
	int i = 0;
  
  //fields of Products.txt
  string I = "";
  long productID = 0;
	string pname = "";
  string type = "";
  string p = "";
  float price = 0;


	while (!infile.eof())//goes through file adding all fields to a Product class array
	{
    getline(infile, I, ',');
		productID= stol(I);
		getline(infile, pname, ',');
		getline(infile, type, ',');
		getline(infile, p, '\n');
		price = stof(p);

		//add to the Product products[] array
		products[i] = Product(productID, pname, type, price);
		i++;

	}
	cout << "Products Loaded" << endl;

	infile.close();
} //end of function

void loadStorage(Storage storagelist[], int size) { // open a file in read mode

  DeleteEmptyLines("Storage.txt");
  
  ifstream infile;
	infile.open("Storage.txt");
	int i = 0;

  //fields of Products.txt
  string I = "";
  long productID = 0;
	string pname = "";
  string type = "";
  string q = "";
  int quantity = 0;


	while (!infile.eof())//goes through file adding all fields to a Storage class array 
	{
    getline(infile, I, ',');
		productID= stol(I);
		getline(infile, pname, ',');
		getline(infile, type, ',');
		getline(infile, q, '\n');
		quantity = stol(q);

		//add to the Storage storagelist[] array
		storagelist[i] = Storage(productID, pname, type, quantity);
		i++;

	}
	cout << "Storage Loaded" << endl;

	infile.close();
} //end of function

void loadTransactions(vector<PurchasedFood> &pfs) {

  DeleteEmptyLines("Transactions.txt");

  ifstream infile;
	infile.open("Transactions.txt");
  

  //fields of actions.txt
  string I = "";
  long productID = 0;
  string T = "";
  float total = 0;
  string q = "";
  int quantity = 0;
  string Date = "";


  
	while (!infile.eof() && !EmptyFileTest("Transactions.txt"))
	{
    
    getline(infile, I, ',');
		productID = stol(I);
		getline(infile, q, ',');
		quantity = stol(q);
    getline(infile, T, ',');
		total = stof(T);
    getline(infile,Date,'\n');

      
    pfs.push_back(PurchasedFood(productID, quantity, total, Date));


	}
	cout << "Transaction.txt Loaded" << endl;

	infile.close();
  
}

//***************************** Load Data ********************************

//************************ Update Functions ******************************

void updateUser(User users[], int size) { // gets current users[] data and sends to updateFile() to update

  if (users[lif].getDepartment()==0) {
  cout << left;
  cout << "\n-----------------Updated-----------------" << endl;
  cout << "\n" << setw(10) << "Dept.#";
  cout << setw(20) << "FullName" << "Funds" <<endl;
  cout << "=========================================" << endl;
  }
  
  for (int i=0;i<size;i++) {
      
    string newline = ""; //string line that will replace old data
    string find = ""; // string that will be used to find line to replace
    int value; //*!*//

    newline+=users[i].getFullname();
    newline+=","+users[i].getUsername();
    newline+=","+users[i].getPassword();
    newline+=","+to_string(users[i].getDepartment());
    newline+=","+to_string(users[i].getFunds());
    
    find+=users[i].getFullname()+",";// search line for "find" string to change(this changes data based on fullname)

    if (users[lif].getDepartment()==0) { //If admin then show updated info
    cout << "Dept." << setw(5) << users[i].getDepartment(); 
    cout << setw(20) << users[i].getFullname();
    cout << "$" << users[i].getFunds() << endl; //(Not needed) Displays updated Funds
    }
    updateFile("Users.txt",find,newline);
 
  }//update file
  
} //end of function

void updateProduct(Product products[], int size) { // gets current products[] data and sends to updateFile() to update
  
  for (int i=0;i<size;i++) {
      
    string newline = ""; //string line that will replace old data
    string find = ""; // string that will be used to find line to replace
    int value; // try to change number type length

    newline+=to_string(products[i].getProductID());
    newline+=","+products[i].getPname();
    newline+=","+products[i].getType();
    newline+=","+to_string(products[i].getPrice());
      
    
    find+=to_string(products[i].getProductID())+",";// search line for "find" string to change(this changes data based on ProductID)

    
    updateFile("Products.txt",find,newline);
 
  }//update file
  
} // end of function

void updateStorage(Storage storagelist[], int size) { // gets current storagelist[] data and sends to updateFile() to update
  
  for (int i=0;i<size;i++) {
      
    string newline = ""; //string line that will replace old data
    string find = ""; // string that will be used to find line to replace
    int value;  // try to change number type length //*!*//

    newline+=to_string(storagelist[i].getProductID());
    newline+=","+storagelist[i].getPname();
    newline+=","+storagelist[i].getType();
    newline+=","+to_string(storagelist[i].getQuantity());
    
    find+=to_string(storagelist[i].getProductID())+",";// search line for "find" string to change(this changes data based on ProductID)

    
    updateFile("Storage.txt",find,newline);
 
  }//update file
  
} // end of function

void updateFile(string file, string find, string newline) { //update file contents
  //(file, line that contains this string will be changed, new string line)
  string currentline;
  string buffer = "";
  string n = "\n";
  int dataEnd=0;
  int line=1;

  dataEnd = countFilelines(file.c_str()); //line length of file 
  
  ifstream myfile2; //for reading records
   myfile2.open(file.c_str());//open old file to read
    
    ofstream temp; 
    temp.open("temp.txt"); //create file temp.txt to place new/updated data into
  
    while (getline(myfile2, currentline))
    {
      if (line==dataEnd) {n="";} // if this is last line set n="" to prevent additional line being created
      
      if (currentline.find(find)==string::npos && !currentline.empty()) // check if line needs to be changed(if it contains "find" string)
      {buffer+= currentline + n;}//if no change needed leave line(enter old line)
        
      else if (!currentline.empty()) {buffer+= newline + n;}//change old line to newline
      
      ++line;
    }
    temp << buffer; // send buffer string full of new data to empty temp.txt file
  
    myfile2.close();
    temp.close();
    remove(file.c_str()); // delete old file
    rename("temp.txt", file.c_str()); // rename temp.txt file to old file name

} // end of function

void DeleteEmptyLines(string filename) { //deletes empty lines
  string currentline;
  string buffer = "";
  string n = "\n";
  int dataEnd=0;
  int line=1;
  
  dataEnd = countFilelines(filename.c_str()); //line length of file 
  
  ifstream myfile2; //for reading records
   myfile2.open(filename.c_str());//open old file to read
    
    ofstream temp; 
    temp.open("temp.txt"); //create file temp.txt to place new/updated data with deleted lines
  
    while (getline(myfile2, currentline))
    {
      if (line==dataEnd) {n="";} // if this is last line set n="" to prevent additional line being created
      
      if (!currentline.empty()) //check if line is empty(skips if empty)
      {buffer+= currentline + n;}
      
      ++line;
    }
    temp << buffer; // send non empty lines to temp.txt file
  
    myfile2.close();
    temp.close();
    remove(filename.c_str()); // delete old file
    rename("temp.txt", filename.c_str()); // rename temp.txt file to old file

} // end of function [extra stuff]

//************************ Update Functions ******************************

//***************************** Others ***********************************

string getDate() {	// current date/time based on current system
	time_t now = time(0);

	// convert now to string form
	char* dt = ctime(&now);
	string timestamp = dt; //Create a string to hold the date

	return timestamp;
} //end of function

void writePurchases(vector<PurchasedFood> pfs) {	// open a file in write mode.
	ofstream outfile;
	outfile.open("Transactions.txt");
   
	int i = 0;
  int line = 1;
  string n = "\n";
  
	for (int i = 0; i < pfs.size(); i++)
	{
    if (line == pfs.size()) {n="";}
      
		PurchasedFood pf(pfs.at(i));
		outfile << pf.getProductID() << ",";
		outfile << pf.getProductQ() << ",";
    outfile << pf.getTotal() << ",";
		outfile << pf.getSaleDate() << n;
    ++line;
	}

	cout << "\nPurchased Food Transaction File Written" << endl;
	outfile.close();
  
  DeleteEmptyLines("Transactions.txt");
} // end of function? (unsure how exactly works,was told the way it worked that it will always overwrite) 

int countFilelines(string file) { //returns total lines in file

  string trash;
  int dataEnd = 0;
  
  ifstream myfile;
  myfile.open(file.c_str());

   while (getline(myfile, trash)) { 
      ++dataEnd;
    } // Increment dataEnd after every line

  myfile.close();
  return dataEnd;
} //end of function

//***************************** Others ***********************************

bool DeptLimit (User users[], int choice) { //sets what choices each dep can choose (for BuyProducts)

  bool test = false;
  int Dept = users[lif].getDepartment();
  vector<int>choicelimit;
  
  if (Dept == 1) {choicelimit = {1,2};}
    
  else if (Dept == 2) {choicelimit = {3,4};}
    
  else if (Dept == 3) {choicelimit = {5,6};}
    
  else if (Dept == 4) {choicelimit = {7,8};}
    
  else if (Dept == 5) {choicelimit = {9,10};}

  for (int i=0;i<choicelimit.size();i++) {
    if (choice == choicelimit[i])
    test = true;
  }
  if (test == true)
    return true;
  else 
    return false;
} //end of function

bool GoodInputTest(float test) { //Test to see if cin input is a number/valid

  //if the input is a letter the variable is set to 0
  int test2 = test;
  string trash = "";
  if (!(test)||!(test2)) {
    cin.clear(); //clear fail status caused by letter
    getline(cin,trash); //clear letter from input
    return false;
  }
  else {
    return true;
  } 
} //end of function

bool EmptyFileTest(string file) {

  string currentline = "";
  string buffer = "";

  ifstream myfile2; //for reading record
  myfile2.open(file.c_str());

  while (getline(myfile2,currentline)) {
    buffer+=currentline;
  }
  if (buffer == "") //if file is empty return true
    return true;
  else
    return false;
  
} //end of function


