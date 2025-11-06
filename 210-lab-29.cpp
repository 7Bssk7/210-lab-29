// COMSC-210 | Lab 29 | Arkhip Finski
// IDE used: Visual Studio
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <random>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Car{
    public:
        Car (){};
        Car(string m, int mile, int y, double p){
            make = m;
            mileage = mile;
            year = y;
            price = p;
        }

    private:
        string make;
        int mileage;
        int year;
        double price;
};

struct Car_Array{
    list<Car> car_S;
    list<Car> car_T;
    list<double> profit;
};

int main(){

    vector<Car> cars_s;
    vector<Car> cars_t;
    string file_in;
    fstream car_sell("sell.txt");
    fstream car_trade("trade.txt");

    if(!car_sell){
        return 1;
    }
    else if(!car_trade){
        return 1;
    }

    while(getline(car_sell, file_in)){
        stringstream ss(file_in);
        string make;
        int mileage;
        int year;
        double price;

        ss >> make >> mileage >> year >> price;

        Car car_temp(make, mileage, year, price);

        cars_s.push_back(car_temp);

    }

    car_sell.close();

    while(getline(car_trade, file_in)){

        // Same approach as for cars_s, but for cars_t

    }

    car_trade.close();

    map<Car, Car_Array> dealersData;



    



    return 0;
}