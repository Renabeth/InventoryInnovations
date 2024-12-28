#pragma once
#include <string>
using namespace std;

class PurchasedFood
{
private:
	long productID;
	int productQ; // how much was bought
  float total;
	string saleDate;

public:
	PurchasedFood()
	{
		productID = 0;
		productQ = 0;
    total = 0;
		saleDate = "";

	}
	PurchasedFood(long p, int q, float t, string d)
	{
		productID = p;
		productQ = q;
    total = t;
		saleDate = d;
	}
	//Prototypes
	long getProductID();
	int getProductQ();
  float getTotal();
	string getSaleDate();

	void setProductID(long p);
	void setProductQ(int q);
  void setTotal(float t);
	void setSaleDate(string d);

}; //end of class

long PurchasedFood::getProductID()
{
	return productID;
}
int PurchasedFood::getProductQ()
{
	return productQ;
}
float PurchasedFood::getTotal()
{
	return total;
}
string PurchasedFood::getSaleDate()
{
	return saleDate;
}

void PurchasedFood::setProductID(long p)
{
	productID = p;
}
void PurchasedFood::setProductQ(int q)
{
	productQ = q;
}
void PurchasedFood::setTotal(float t)
{
	total = t;
}
void PurchasedFood::setSaleDate(string d)
{
	saleDate = d;
}
