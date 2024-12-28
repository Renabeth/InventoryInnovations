#pragma once
#include <string>
using namespace std;

class Product {//purchasable items
//categories: produce, meat, dairy, etc

private://list varibles class will contain

string pname;//name of product
string type;//is it meat, dairy, etc
float price;//how much each costs per pound


public:
Product()//initialized values
{
  pname = "";
  type = "";
  price = 0;  
  
}
Product(string n, string t, float p)//set access letter/position for variables
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

string   Product::getPname()
{
	 return pname;
}
string   Product::getType()
{
	 return type;
}

float    Product::getPrice()
{
	 return price;
}

void     Product::setPname(string n)
{
	 pname = n;
}
void     Product::setType(string t)
{
	 type = t;
}

void     Product::setPrice(float p)
{
	 price = p;
}









