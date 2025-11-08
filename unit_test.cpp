// COMSC-210 | Lab 30 Unit Test | Arkhip Finski
// IDE used: Visual Studio

#include <iostream>
#include <vector>
#include <list>
#include <map>
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

struct Car_Array {
    list<Car> car_S;
    list<Car> car_T;
    list<double> profit;
};

bool chance(const int&);
void simulation(Car_Array& , const vector<Car>& , const vector<Car>& );

int main(){
    vector<Car> cars_s = { Car("Toyota", "Camry", 50000, 2018, 15000.0) };
    vector<Car> cars_t = { Car("Honda", "Civic", 60000, 2016, 8000.0) };

    map<string, Car_Array> dealersData;
    Car_Array dealer1;



}

bool chance(const int&){
    return true;
}