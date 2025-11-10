// COMSC-210 | Lab 30 | Arkhip Finski
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
#include <iomanip> 
#include <chrono>
#include <thread>  

using namespace std;

const int INIT_SIZE = 10, SIM = 36;

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
void setupDealer(Car_Array& , const vector<Car>&, int);
void outputDealerInit(const Car_Array& );
void outputDealerFin(const Car_Array&, const Car_Array&, const Car_Array& );
void simulation(Car_Array&,const vector<Car>&, const vector<Car>&); 
void outputMenu(const Car_Array& , const Car_Array& , const Car_Array&);

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
        cout << "Error: Was't able to open the file with the cars for sale!" << endl;
        return 1;
    }
    // Check if file trade.txt is open
    else if(!car_trade){
        cout << "Error: Was't able to open the file with the trade-in cars!" << endl;
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

    if(cars_s.empty() || cars_t.empty()){
        cout << "Error: One or both input files are empty or invalid. Simulation could not be started." << endl;

        return 1;
    }

    // Declare map<string, Car_Array> dealersData
    map<string, Car_Array> dealersData;

    // Create array for one dealership ("Dealer #1")
    Car_Array dealer1;
    Car_Array dealer2;
    Car_Array dealer3;

    setupDealer(dealer1, cars_s, 1);
    setupDealer(dealer1, cars_t, 0);
    setupDealer(dealer2, cars_s, 1);
    setupDealer(dealer2, cars_t, 0);
    setupDealer(dealer3, cars_s, 1);
    setupDealer(dealer3, cars_t, 0);

    // Assign dealer "Dealer #1" with array dealer1;

    dealersData["Dealer #1"] = dealer1;
    dealersData["Dealer #2"] = dealer2;
    dealersData["Dealer #3"] = dealer3;

    outputMenu(dealersData["Dealer #1"], dealersData["Dealer #2"], dealersData["Dealer #3"]);

    cout << "\n*** SIMULATION ***" << endl;
    for(int i = 0; i < SIM; i++){
        this_thread::sleep_for(std::chrono::seconds(1));
        cout << "\nDealer #1" << endl;
        cout << "MONTH #" << i+1 << endl;
        simulation(dealersData["Dealer #1"],cars_s,cars_t);
        cout << "\nDealer #2" << endl;
        cout << "MONTH #" << i+1 << endl;
        simulation(dealersData["Dealer #2"],cars_s,cars_t);
        cout << "\nDealer #3" << endl;
        cout << "MONTH #" << i+1 << endl;
        simulation(dealersData["Dealer #3"],cars_s,cars_t);
    }

    cout << "\n" << endl;

    outputDealerFin(dealersData["Dealer #1"], dealersData["Dealer #2"], dealersData["Dealer #3"]);


    return 0;
}


void simulation(Car_Array& dl, const vector<Car>& cs, const vector<Car>& ct){
    int count = 0;
    double profit = 0;
    int num_trade = 0;
    int num_random_trades = 0;
    int num_sold = 0;
    
    cout << "\nCars added to inventory this month: \n" << endl;
    for(int i = 0; i < (rand()% 5 + 1); i++){
            Car carAdded = randomCar(cs);
            dl.car_S.push_back(carAdded);
            cout << carAdded.getMake()<< " " << carAdded.getModel() << " " << carAdded.getMile() << " "  << carAdded.getYear() << " $" << carAdded.getPrice() << endl;
    }
    cout << endl;

    auto it = dl.car_S.begin();
    while(it != dl.car_S.end()){
        if(chance(20)){
            double salePrice = it->getPrice();

            if(chance(30)){
                Car tradeIn = randomCar(ct);
                double tradeValue = tradeIn.getPrice();
                profit += (salePrice - tradeValue);
                dl.car_T.push_back(tradeIn);
                num_trade +=1;

                cout << "Sold: " << it->getMake() << " " << it->getModel() << " for $" << salePrice << endl;
                cout << "Trade-in: " << tradeIn.getMake() << " " << tradeIn.getModel()<< " valued at $" << tradeValue << endl;
                cout << "Profit: $" << (salePrice - tradeValue) << endl;
            }
            else{
                profit += salePrice;
                cout << "Sold: " << it->getMake() << " " << it->getModel() << " for $" << salePrice << endl;
                cout << "No Trade-in" << endl;
                cout << "Profit: $" << salePrice << endl;
            }

            it = dl.car_S.erase(it);
            num_sold +=1;
        }
        else{
            ++it;
        }    
    
    }
    if(chance(10)){
        int trades = 1;
        if(chance(40)){    
            trades = 2;
        }
        else if(chance(20)){
            trades = 3;
        }
        else if(chance(10)){
            trades = 4;

        }
        else if(chance(5)){
            trades = 5;
        }

        cout << "Random trade-in(s) this month:" << endl;
        for(int i = 0; i < trades; ++i){
            Car tradeIn = randomCar(ct);
            cout << tradeIn.getMake()<< " " << tradeIn.getModel() << " " << tradeIn.getMile() << " "  << tradeIn.getYear() << " $" << tradeIn.getPrice() << endl;
            dl.car_T.push_back(tradeIn);
            profit -= tradeIn.getPrice();
            num_random_trades += 1;
        }

    }

    cout << "Cars sold: " << num_sold << endl;
    cout << "Trade-ins during sales: " << num_trade << endl;
    cout << "Random trade-ins: " << num_random_trades << endl;
    cout << "Profit this month: $" << profit << endl;


    dl.profit.push_back(profit);

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

void setupDealer( Car_Array& dl, const vector<Car>& list, int check){
    if(check == 1){
        for(int i = 0; i < (rand()% 10 + 1); i++){
            dl.car_S.push_back(randomCar(list));
        }
    }
    else{
        for(int i = 0; i < (rand()% 5 + 1); i++){
            dl.car_T.push_back(randomCar(list));
        }

    }


}

void outputDealerInit(const Car_Array& dealer){
    cout << "\nInventory for sale: " << endl;
    for (const auto& car : dealer.car_S) {
        cout << car.getMake() << " " << car.getModel() << " "<< car.getMile() << " " << car.getYear() << " $"<< car.getPrice() << endl;
    }

    cout << "\nInventory traded: " << endl;
    for (const auto& car : dealer.car_T) {
        cout << car.getMake() << " " << car.getModel() << " "<< car.getMile() << " " << car.getYear() << " $"<< car.getPrice() << endl;
    }

    // Output each profit value of "Dealer #1"
    cout << "\nProfit: $0 (There is no profit, this is just a presentation of the initial inventory)" << endl;
    

}

void outputDealerFin( const Car_Array& dl1,const Car_Array& dl2, const Car_Array& dl3){
    double profitDl1 = 0;
    double profitDl2 = 0;
    double profitDl3 = 0;

    cout << "Dealer's #1 inventory to sell after 36 months: " << endl;
    for (const auto& car : dl1.car_S) {
        cout << car.getMake() << " " << car.getModel() << " "<< car.getMile() << " " << car.getYear() << " $"<< car.getPrice() << endl;
    }
    cout << endl;
    cout << "Dealer's #1 traded inventory after 36 months: " << endl;
    for (const auto& car : dl1.car_T) {
        cout << car.getMake() << " " << car.getModel() << " "<< car.getMile() << " " << car.getYear() << " $"<< car.getPrice() << endl;
    }
    cout << endl;
    cout << "Dealer's #2 inventory to sell after 36 months: " << endl;
    for (const auto& car : dl2.car_S) {
        cout << car.getMake() << " " << car.getModel() << " "<< car.getMile() << " " << car.getYear() << " $"<< car.getPrice() << endl;
    }
    cout << endl;
    cout << "Dealer's #2 traded inventory after 36 months: " << endl;
    for (const auto& car : dl2.car_T) {
        cout << car.getMake() << " " << car.getModel() << " "<< car.getMile() << " " << car.getYear() << " $"<< car.getPrice() << endl;
    }
    cout << endl;
    cout << "Dealer's #3 inventory to sell after 36 months: " << endl;
    for (const auto& car : dl3.car_S) {
        cout << car.getMake() << " " << car.getModel() << " "<< car.getMile() << " " << car.getYear() << " $"<< car.getPrice() << endl;
    }
    cout << endl;
    cout << "Dealer's #3 traded inventory after 36 months: " << endl;
    for (const auto& car : dl3.car_T) {
        cout << car.getMake() << " " << car.getModel() << " "<< car.getMile() << " " << car.getYear() << " $"<< car.getPrice() << endl;
    }
    cout << endl;

    auto it1 = dl1.profit.begin();
    auto it2 = dl2.profit.begin();
    auto it3 = dl3.profit.begin();


    cout << setw(50) <<"*** LET SEE THE PROFITS! ***" << endl;
    cout << setw(10) <<"MONTH #X" << setw(20) << "DEALER #1" << setw(20) << "DEALER #2" <<setw(20) << "DEALER #3" << endl;

    for(int i = 1; i <= SIM; ++i){
        stringstream ss1, ss2, ss3;
        ss1 << '$' << *it1;
        ss2 << '$' << *it2;
        ss3 << '$' << *it3;
        string s1;
        ss1 >> s1;
        string s2;
        ss2 >> s2;
        string s3;
        ss3 >> s3;

        cout << right << setw(9) << "Month #" << left << setw(3) << i<< right << setw(16) << s1  << setw(21) << s2<< setw(21) << s3<< endl;

        profitDl1 += *it1;
        profitDl2 += *it2;
        profitDl3 += *it3;
        ++it1;
        ++it2;
        ++it3;
    }

    cout << endl; 

    cout << fixed << setprecision(0);
    cout << right << setw(9) << "TOTAL PROFIT: "<< right << setw(8) << "$" << profitDl1  << setw(13) << "$" << profitDl2 << setw(15) << "$" << profitDl3 << endl;

}

void outputMenu(const Car_Array& dl1,const Car_Array& dl2, const Car_Array& dl3){

    string choice;

    cout << "*** Welcome to the car dealership simulation! ***" << endl;

    cout << "\nMenu:" << endl;

    cout << "1. View starting inventory" << endl;
    cout << "2. Start the simulation" << endl;

    cout << "Choice-> ";

    cin >> choice;

    while( choice != "2"){

        if(choice == "1"){
            cout << "\nDealer #1 Initial Inventory" << endl;
            outputDealerInit(dl1);
            cout << "\nDealer #2 Initial Inventory" << endl;
            outputDealerInit(dl2);
            cout << "\nDealer #3 Initial Inventory" << endl;
            outputDealerInit(dl3);

            cout << "\nMenu:" << endl;

            cout << "1. View starting inventory" << endl;
            cout << "2. Start the simulation" << endl;

            cout << "Choice-> ";

            cin >> choice;
        }
        else{
            cout << "Invalid input, please choose again: " << endl;

            cout << "\nMenu:" << endl;

            cout << "1. View starting inventory" << endl;
            cout << "2. Start the simulation" << endl;

            cout << "Choice-> ";

            cin >> choice; 

        }

        

    }


}