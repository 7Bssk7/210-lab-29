// COMSC-210 | Lab 29 | Arkhip Finski
// IDE used: Visual Studio
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <random>
#include <string>
#include <vector>

using namespace std;

class Car{
    public:
    
    private:
}

int main(){

    vector<Car> cars_s;
    vector<Car> cars_t;
    string car;
    fstream car_sell("sell.txt");
    fstream car_trade("trade.txt");

    if(!car_sell){
        return 1;
    }
    else if(!car_trade){
        return 1;
    }

    



    return 0;
}