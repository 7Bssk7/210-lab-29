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

        string getMake () const{ return make;}
        void setMake(string m) { make = m;}
        int getMiles () const { return mileage;}
        void setMiles(int mile) { mileage = mile;}
        int getYear() const  { return year;}
        void setYear(int y) { year = y;}
        double getPrice() const { return price;}
        void setPrice( double p) { price = p;}

    private:
        string make;
        int mileage;
        int year;
        double price;
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
        Car car_temp;
        stringstream ss(file_in);
        string make;
        int mileage;
        int year;
        double price;

        ss >> make >> mileage >> year >> price;

        car_temp.setMake(make);
        car_temp.setMiles(mileage);
        car_temp.setYear(year);
        car_temp.setPrice(price);

        cars_s.push_back(car_temp);

    }

    car_sell.close();

    while(getline(car_trade, file_in)){

    }

    car_trade.close();

    



    return 0;
}