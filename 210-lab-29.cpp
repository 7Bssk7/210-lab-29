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
bool chance(const int&);
void setupDealer(Car_Array& , const vector<Car>&);

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
        string model;
        int mileage;
        int year;
        double price;

        ss >> make >> model >> mileage >> year >> price;

        // Create Car object and push to cars_s
        Car car_temp(make, model, mileage, year, price);

        cars_s.push_back(car_temp);

    }

    // Close the file sell.txt
    car_sell.close();

    // Read trade.txt line by line
    while(getline(car_trade, file_in)){

        // For each line extract make, mileage, year, price
        stringstream ss(file_in);
        string make;
        string model;
        int mileage;
        int year;
        double price;

        ss >> make >> model >> mileage >> year >> price;

        // Create Car object and push to cars_t
        Car car_temp(make, model, mileage, year, price);

        cars_t.push_back(car_temp);


    }

    // Close the file trade.txt
    car_trade.close();

    // Declare map<string, Car_Array> dealersData
    map<string, Car_Array> dealersData;

    // Create array for one dealership ("Dealer #1")
    Car_Array dealer1;
    Car_Array dealer2;
    Car_Array delaer3;

    setupDealer(dealer1);
    
    /*
    // Add 5 random cars from cars_s to car_S
    for(int i = 0; i < 5; ++i){
        dealer1.car_S.push_back(randomCar(cars_s));
    }
    // Add 3 random cars from cars_t to car_T
    for(int i = 0; i < 3; ++i){
        dealer1.car_T.push_back(randomCar(cars_t));
    }
    // Push one dummy profit value (e.g., 10000.0) to profit list
    dealer1.profit.push_back(10000);

    // Assign dealer "Dealer #1" with array dealer1;
    */
    dealersData["Dealer #1"] = dealer1;





    // Output dealers "Dealer #1" inventory
    cout << "Dealer's #1 Inventory for sale: " << endl;
    // Output every single car for sale in "Dealer #1" inventory
    for( const auto& car: dealersData["Dealer #1"].car_S){
        // Print make, mileage, year, price
        cout << car.getMake() << " " << car.getModel()  <<" " << car.getMile() << " " << car.getYear() << " $" << car.getPrice() << endl;
    }

    // Output every single car for trade in "Dealer #1" inventory
    cout << "Dealer's #1 Inventory after trade: " << endl;
    for( const auto& car: dealersData["Dealer #1"].car_T){
        // Print make, mileage, year, price
        cout << car.getMake() << " " << car.getModel() << " " << car.getMile() << " " << car.getYear() << " $" << car.getPrice() << endl;
    }

    // Output each profit value of "Dealer #1"
    cout << "Dealer's #1 profit: " << endl;
    for( const auto& p: dealersData["Dealer #1"].profit){
        //Print the amount 
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

bool chance( const int& p){
    int random = rand()% 100 + 1;

    return ( random <= p);
    
}

void setupDealer( Car_Array& dl, const vector<>){

}