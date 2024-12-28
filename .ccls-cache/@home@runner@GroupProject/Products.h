#pragma once
#include <string>
using namespace std;

class Products {//purchasable items
//categories: produce, meat, dairy, etc

private://list varibles class will contain

string pname;//name of product
string type;//is it meat, dairy, etc
float price;//how much each costs per pound


public:
Products()//initialized values
{
  pname = "";
  type = "";
  price = 0;  
  
}
Products(string n, string t, float p)//set access letter/position for variables
{
  pname = n;
  type = t;
  price = p;
}
//Prototypes
string getPname();
string getType();
int getQuantity();
float getPrice();

void setPname(string n);
void setType(string t);
void setQuantity(int q);
void setPrice(float p);

};// end of class

string   Products::getPname()
{
	 return pname;
}
string   Products::getType()
{
	 return type;
}

float    Products::getPrice()
{
	 return price;
}

void     Products::setPname(string n)
{
	 pname = n;
}
void     Products::setType(string t)
{
	 type = t;
}

void     Products::setPrice(float p)
{
	 price = p;
}









