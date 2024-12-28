//******************************************************************
// Group Project:  Restaurant Inventory
// Authors:        Andrew Carpio, Serena D'Avanzo, Jared Morales, Demetrius Quintyne, Joelly Velasquez 
// Date:           4/XX/23 
// Version:        V1
// System Name:
//******************************************************************
#include "Product.h"
#include "User.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//a(11),n(8),d(3),r(9),e(12),w(1),c(1),p(1),i(4),o(5),s(4),d(4),v(3),z(2)
//j(2),m(2),l(4),t(5),q(2),u(3),y(3)

//e,a,r,n,o,t,i,s,d,l (make name out of leters?)
//d,v,u,y
//z,j,m,q
//w,c,p

//rationalised Duty
//READLISTON
//RELOAD N SIT
//idk
  
/*Function Prototypes*/

//Data Functions
void loadUsers(User users[], int size);
void loadProducts(Product products[], int size);


// Processing Functions
void login(User users[], int size);
void displayMenu();//
void viewInventory();//
void buyProducts();//
void viewFunds();//
void checkFunds();//

// counter variables
int lif = -1; // logged in fitter


int main() 
{
  
  // Manager Variables
	const int USERSIZE = 5; // maybe change to vector 
	User users[USERSIZE]; // create array for all users
	loadUsers(users, USERSIZE);// enter/load user information into array

  // Product Variables (name,type price)
	const int PRODUCTSIZE = 10;  // vector?
	Product products[PRODUCTSIZE]; // create array for all product data
	loadProducts(products, PRODUCTSIZE);// enter/load product information into array

  //Use function to store products into a storage class(not loading data)

  cout << users[4].getFullname()<<endl;

  

  //Call Functions
  login(users, USERSIZE);
  //displayMenu(users, USERSIZE, users[lif],);
 
} //end of main

void login(User users[], int size) {

  string enterUsername = "";
  string enterPass = "";
  bool isValid = false;
  int numattempts = 0;

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
    numattempts++;
  } while (numattempts < 3 && !isValid);

  if (!isValid) 
  {
    cout << "Number of attempts exceeded, Program Terminated!" << endl;
    exit(100);
  }

} // end of function

void displayMenu() {
  int choice = 0;
  // Display Welcome Message and Menu
  cout << "Please select a menu option" << endl;
  cout << "1. View Inventory" << endl;
  cout << "2. Purchase Products/Update Inventory" << endl;
  cout << "3. Update/Check Budget" << endl;
  cout << "4. Log off" << endl;

  // Get the menu choice
  cin >> choice;
  switch (choice) {
  case 1: {
    viewInventory();
    break;
  }
  case 2: {
    buyProducts();
    break;
  }
  case 3: {
    viewFunds();
    break;
  }
  case 4: {
    cout << "Logging off. Thank you." << endl;
    exit(0);
  }
  default: {
    cout << "Invalid Selection" << endl;
  }
  }
} //

void viewInventory() { cout << "Total Inventory: " << endl; } //

void buyProducts() {
  int choice = 0;
  cout << "Choose a product to purchase" << endl;
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
  cin >> choice;
} //

void checkBudget(User &user) {
  
  cout << "Avaialable Funds = " << user.getFunds() << endl;
  
} //

void viewFunds(){
  
} //
//*****************************Load Data*********************************
void loadUsers(User users[], int size) {	// open a file in read mode.
	ifstream infile;
	infile.open("Users.txt");
	int i = 0;


	string fullname = "";
  string username = "";
  string password = "";
  string d = "";
  int department = 0;
  string f = "";
  float funds = 0;


	while (!infile.eof())//*!*//
	{
		getline(infile, fullname, ',');
		getline(infile, username, ',');
		getline(infile, password, ',');
		getline(infile, d, ',');
    department = stol(d);
		getline(infile, f, '\n');
    funds = stol(f);

		//add to the User users array
		users[i] = User(fullname, username, password, department, funds);
		i++;

	}
	cout << "Users Loaded" << endl;

	infile.close();
} //end of function

void loadProducts(Product products[], int size) {
  ifstream infile;
	infile.open("Products.txt");
	int i = 0;


	string pname = "";
  string type = "";
  string p = "";
  float price = 0;


	while (!infile.eof())//*!*// means to look back and check(or something)
	{
		getline(infile, pname, ',');
		getline(infile, type, ',');
		getline(infile, p, '\n');
		price = stol(p);

		//add to the Product products array
		products[i] = Product(pname, type, price);
		i++;

	}
	cout << "Products Loaded" << endl;

	infile.close();
} //end of function
//*****************************Load Data*********************************