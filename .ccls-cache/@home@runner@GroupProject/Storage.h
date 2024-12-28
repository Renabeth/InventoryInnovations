#pragma once
#include <string>
using namespace std;

class Storage {//items in storage
//categories: produce, meat, dairy, etc

private://list varibles class will contain

long productID;
string pname;//name of product
string type;//is it meat, dairy, etc
int quantity;//how many we currently have


public:
Storage()//initialized values
{
  productID = 0;
  pname = "";
  type = "";
  quantity = 0; 
  
  
}
Storage(long I, string n, string t, int q)//set access letter/position for variables
{
  productID = I;
  pname = n;
  type = t;
  quantity = q;
  
}
//Prototypes
long getProductID();
string getPname();
string getType();
int getQuantity();

void setProductID(long p);
void setPname(string n);
void setType(string t);
void setQuantity(int q);


};// end of class

long     Storage::getProductID()
{
	return productID;
}
string   Storage::getPname()
{
	 return pname;
}
string   Storage::getType()
{
	 return type;
}
int      Storage::getQuantity()
{
	 return quantity;
}


void     Storage::setProductID(long p)
{
	productID = p;
}
void     Storage::setPname(string n)
{
	 pname = n;
}
void     Storage::setType(string t)
{
	 type = t;
}
void     Storage::setQuantity(int q)
{
	 quantity = q;
}










