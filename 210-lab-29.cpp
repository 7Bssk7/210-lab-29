// COMSC-210 | PSEUDOCODE Lab 29 | Arkhip Finski
// IDE used: Visual Studio

//Include all necessary headers
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <random>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

/*
 Define Car class
    Private members: make, mileage, year, price
    Constructor to initialize car private data members 
    Getter methods: getMake(), getMile(), getYear(), getPrice()
*/
class Car{
    public:
        Car (){};
        Car(string m, int mile, int y, double p){
            make = m;
            mileage = mile;
            year = y;
            price = p;
        }

        string getMake() const { return make;}
        int getMile() const { return mileage;}
        int getYear() const { return year;}
        double getPrice() const { return price;}

    private:
        string make;
        int mileage;
        int year;
        double price;
};

/*
 Define Car_Array struct
 Contains 3 lists:
    car_S — cars for sale
    car_T — trade-in cars
    profit — monthly profit values
*/
struct Car_Array{
    list<Car> car_S;
    list<Car> car_T;
    list<double> profit;
};

// Define randomCar() function
Car randomCar(const vector<Car>&);

// Begin main function
int main(){

    // Seed random number generator
    srand(time(0));

    // Declare vectors to hold Car objects 
    // vector cars_s to hold Car objects from sell.txt
    vector<Car> cars_s;

    // vector cars_t to hold Car objects from trade.txt
    vector<Car> cars_t;

    // Declare string to read lines from the files 
    string file_in;

    // Open sell.txt and trade.txt
    fstream car_sell("sell.txt");
    fstream car_trade("trade.txt");

    // Check if file sell.txt is open
    if(!car_sell){
        return 1;
    }
    // Check if file trade.txt is open
    else if(!car_trade){
        return 1;
    }

    // Read sell.txt line by line
    while(getline(car_sell, file_in)){

        // For each line extract make, mileage, year, price
        stringstream ss(file_in);
        string make;
        int mileage;
        int year;
        double price;

        ss >> make >> mileage >> year >> price;

        // Create Car object and push to cars_s
        Car car_temp(make, mileage, year, price);

        cars_s.push_back(car_temp);

    }

    // Close the file sell.txt
    car_sell.close();

    // Read trade.txt line by line
    while(getline(car_trade, file_in)){

        // For each line extract make, mileage, year, price
        stringstream ss(file_in);
        string make;
        int mileage;
        int year;
        double price;

        ss >> make >> mileage >> year >> price;

        // Create Car object and push to cars_t
        Car car_temp(make, mileage, year, price);

        cars_t.push_back(car_temp);


    }

    // Close the file trade.txt
    car_trade.close();

    map<string, Car_Array> dealersData;

    Car_Array dealer1;
    
    for(int i = 0; i < 5; ++i){
        dealer1.car_S.push_back(randomCar(cars_s));
    }
    for(int i = 0; i < 3; ++i){
        dealer1.car_T.push_back(randomCar(cars_t));
    }
    dealer1.profit.push_back(10000);

    dealersData["Dealer #1"] = dealer1;

    cout << "Dealer's #1 Inventory for sale: " << endl;
    for( const auto& car: dealersData["Dealer #1"].car_S){
        cout << car.getMake() << " " << car.getMile() << " " << car.getYear() << " $" << car.getPrice() << endl;
    }
    cout << "Dealer's #1 Inventory after trade: " << endl;
    for( const auto& car: dealersData["Dealer #1"].car_T){
        cout << car.getMake() << " " << car.getMile() << " " << car.getYear() << " $" << car.getPrice() << endl;
    }
    cout << "Dealer's #1 profit: " << endl;
    for( const auto& p: dealersData["Dealer #1"].profit){
        cout << " $"<< p << endl;
    }

    return 0;
}


/*
randomCar() function
   argument: vector of Car objects
   returns: randomly selected Car from the vector
*/
Car randomCar(const vector<Car>& list){
    return list.at(rand() % list.size());
}