#pragma once
#include <string>
using namespace std;

class User // user's name and login credentials
{

private: // list varibles class will contain
  string fullname;
  string username;
  string password;
  int department;
  float funds; // total funds for department

public:
  User() // initialized values
  {
    fullname = "";
    username = "";
    password = "";
    department = -1;
    funds = 0; // update funds for all users if changed
  }
  User(string f, string u, string p, int d,
       float f2) // set access letter/position for variables
  {
    fullname = f;
    username = u;
    password = p;
    department = d;
    funds = f2;
  }

  // Prototypes
  string getFullname();
  string getUsername();
  string getPassword();
  int getDepartment();
  float getFunds();

  void setFullname(string f);
  void setUsername(string u);
  void setPassword(string p);
  void setDepartment(int d);
  void setFunds(float f);

}; // end of class

string User::getFullname() { return fullname; }
string User::getUsername() { return username; }
string User::getPassword() { return password; }
int User::getDepartment() { return department; }
float User::getFunds() { return funds; }

void User::setFullname(string f) { fullname = f; }
void User::setUsername(string u) { username = u; }
void User::setPassword(string p) { password = p; }
void User::setDepartment(int d) { department = d; }
void User::setFunds(float f) { funds = f; }
