// COMSC-210 | Lab 30 Unit Test | Arkhip Finski
// IDE used: Visual Studio

#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

class Car{
    public:
        Car(string m, string mo, int mile, int y, double p){
            make = m;
            model = mo;
            mileage = mile;
            year = y;
            price = p;
        }

        string getMake() const { return make;}
        string getModel() const { return model;}
        int getMile() const { return mileage;}
        int getYear() const { return year;}
        double getPrice() const { return price;}

    private:
        string make;
        string model;
        int mileage;
        int year;
        double price;
};