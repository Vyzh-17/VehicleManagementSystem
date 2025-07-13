#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string brand, model;
    int mileage;


public:
    Vehicle(string b, string m, int mi) : brand(b), model(m), mileage(mi) {}
    virtual ~Vehicle() {}
    virtual void displayDetails() {
        cout << "Brand: " << brand << ", Model: " << model
             << ", Mileage: " << mileage << " kmpl" << endl;
    }
    void calculateCost(int distance) {
        cout << "Cost for " << distance << " km (default rate): $" << distance * 1.5 << endl;
    }
    void calculateCost(int distance, float fuelCost) {
        cout << "Cost for " << distance << " km at $" << fuelCost << "/km: $" << distance * fuelCost << endl;
    }
};

class Car : public Vehicle {
public:
    Car(string b, string m, int mi) : Vehicle(b, m, mi) {}
    void displayDetails() override {
        cout << "Car - ";
        Vehicle::displayDetails();
    }
};

class Bike : public Vehicle {
public:
    Bike(string b, string m, int mi) : Vehicle(b, m, mi) {}
    void displayDetails() override {
        cout << "Bike - ";
        Vehicle::displayDetails();
    }
};

class Truck : public Vehicle {
    int loadCapacity;

public:
    Truck(string b, string m, int mi, int load) : Vehicle(b, m, mi), loadCapacity(load) {}
    void displayDetails() override {
        cout << "Truck - ";
        Vehicle::displayDetails();
        cout << "Load Capacity: " << loadCapacity << " kg" << endl;
    }

    Truck operator+(const Truck& other) {
        int avgMileage = (this->mileage + other.mileage) / 2;
        return Truck("Combined", "Truck", avgMileage, this->loadCapacity + other.loadCapacity);
    }
};
int main() {
    int n;
    cout << "Enter number of vehicles to input: ";
    cin >> n;
    Vehicle* vehicles[100];  
    int count = 0;

    for (int i = 0; i < n; i++) {
        cout << "\nSelect Vehicle Type for vehicle #" << (i + 1) << ":\n";
        cout << "1. Car\n2. Bike\n3. Truck\nEnter choice: ";
        int choice;
        cin >> choice;

        string brand, model;
        int mileage;

        switch (choice) {
            case 1: {
                cout << "\nEnter Car Brand: ";
                cin >> brand;
                cout << "Enter Car Model: ";
                cin >> model;
                cout << "Enter Mileage (kmpl): ";
                cin >> mileage;

                vehicles[count] = new Car(brand, model, mileage);
                cout << "\n--- Vehicle Details ---\n";
                vehicles[count]->displayDetails();
                count++;
                break;
            }
            case 2: {
                cout << "\nEnter Bike Brand: ";
                cin >> brand;
                cout << "Enter Bike Model: ";
                cin >> model;
                cout << "Enter Mileage (kmpl): ";
                cin >> mileage;

                vehicles[count] = new Bike(brand, model, mileage);
                cout << "\n--- Vehicle Details ---\n";
                vehicles[count]->displayDetails();
                count++;
                break;
            }
            case 3: {
                string brand1, model1, brand2, model2;
                int mileage1, mileage2, load1, load2;

                cout << "\nEnter First Truck Brand: ";
                cin >> brand1;
                cout << "Enter First Truck Model: ";
                cin >> model1;
                cout << "Enter First Truck Mileage (kmpl): ";
                cin >> mileage1;
                cout << "Enter First Truck Load Capacity (kg): ";
                cin >> load1;

                cout << "\nEnter Second Truck Brand: ";
                cin >> brand2;
                cout << "Enter Second Truck Model: ";
                cin >> model2;
                cout << "Enter Second Truck Mileage (kmpl): ";
                cin >> mileage2;
                cout << "Enter Second Truck Load Capacity (kg): ";
                cin >> load2;

                Truck* t1 = new Truck(brand1, model1, mileage1, load1);
                Truck* t2 = new Truck(brand2, model2, mileage2, load2);
                Truck combined = *t1 + *t2;

                cout << "\n\n--- First Truck Details ---\n";
                t1->displayDetails();

                cout << "\n\n--- Second Truck Details ---\n";
                t2->displayDetails();

                cout << "\n\n--- Combined Truck (t1 + t2) ---\n";
                combined.displayDetails();

                
                vehicles[count++] = t1;  // store first truck
                vehicles[count++] = t2;  // clean second truck pointer since not stored
                break;
            }
            default:
                cout << "Invalid choice. Skipping vehicle.\n";
                i--;
        }
    }

    for (int i = 0; i < count; i++) {
        cout << "\nEnter distance (km) for vehicle #" << (i + 1) << ": ";
        int dist;
        cin >> dist;

        cout << "Enter fuel cost per km (0 for default) for vehicle #" << (i + 1) << ": ";
        float rate;
        cin >> rate;

        if (rate == 0)
            vehicles[i]->calculateCost(dist);
        else
            vehicles[i]->calculateCost(dist, rate);
    }
    for (int i = 0; i < count; i++) {
        delete vehicles[i];
    }
    return 0;
}