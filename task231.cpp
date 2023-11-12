#include <iostream>
using namespace std;

const int Num_Trips = 8;
const int Trains = 4;
const int PerTrain_Couch = 6;
const int Seats_Per_Couch = 80;
const double Ticket_Price = 25.0;
const int LastTrain_Per_Couch = 8;

struct Start_of_day {
    int availableSeatsForUp[Trains], availableSeatsForDown[Trains];
    int TotalPassengerOfTheDay = 0;
    double TotalMoneyOfTheDay = 0;
    string journeyUp[Trains] = {"09:00", "11:00", "13:00", "15:00"};
    string journeyDown[Trains] = {"10:00", "12:00", "14:00", "16:00"};

    Start_of_day() {
        SeatsPerTrainForJourneyUp();
        SeatsPerTrainForJourneyDown();
    }

    void SeatsPerTrainForJourneyUp() {
        for (int i = 0; i < Trains - 1; i++) {
            availableSeatsForUp[i] = PerTrain_Couch * Seats_Per_Couch;
        }
             availableSeatsForUp[3] = LastTrain_Per_Couch * Seats_Per_Couch;
    }

    void SeatsPerTrainForJourneyDown() {
        for (int i = 0; i < Trains - 1; i++) {
            availableSeatsForDown[i] = PerTrain_Couch * Seats_Per_Couch;
        }
            availableSeatsForDown[3] = LastTrain_Per_Couch * Seats_Per_Couch;
    }

    void displayScheduleForJourneyUp() {
        cout << "Displaying Schedule of train for 'Journey Up'" << endl;
        cout << "Journeys \t Departure time \t Available seats " << endl;
        cout << "......................................................." << endl;
        for (int i = 0; i < Trains; i++) {
            cout << "  " << i + 1 << "   \t   \t   " << journeyUp[i] << "   \t   \t   " << availableSeatsForUp[i] << "  seats " << endl;
        }
        cout << "......................................................." << endl << endl;
    }

    void displayScheduleForJourneyDown() {
        cout << "Displaying Schedule of train for 'Journey Down' " << endl;
        cout << "Journeys \t Departure time \t Available seats " << endl;
        cout << "......................................................." << endl;
        for (int i = 0; i < Trains; i++) {
            cout << "  " << i + 1 << "   \t   \t   " << journeyDown[i] << "   \t   \t   " << availableSeatsForDown[i] << "  seats " << endl;
        }
        cout << "......................................................." << endl;
    }

    void BookTicket() {
        int choosetime, seatsQuantity;
        cout << "Select the Departure time: \nTrain 1. 09:00\nTrain 2. 11:00 \nTrain 3. 13:00 \nTrain 4. 15:00" << endl;

        do {
            cin >> choosetime;
            if (choosetime > 0 && choosetime <= Trains) {
                choosetime--; // Adjust the index

                cout << "How many seats you want to reserve? ";
                cin >> seatsQuantity;

                if (seatsQuantity <= availableSeatsForUp[choosetime]) {
                    int freeTickets =  seatsQuantity/ 10;
                    int paidTickets = seatsQuantity - freeTickets;
                    double totalCost = paidTickets * Ticket_Price;                     // Calculate the total cost for paid tickets
                    cout << "Your seats are reserved for the Journey Up." << endl;

                    if (freeTickets > 0) {
                        cout << "Congratulations! You get " << freeTickets << " free ticket(s) for the journey." << endl;
                        cout << "Total Expense for paid tickets is $" << totalCost << "." << endl;

                    }

                    availableSeatsForUp[choosetime] -= seatsQuantity;
                    TotalPassengerOfTheDay += seatsQuantity;

                    cout << "Updated Available Seats for Train " << choosetime + 1 << " (Journey Up): " << availableSeatsForUp[choosetime] << " seats" << endl;

                    // Now select the return journey
                    cout << "\nSelect the return Departure time: \nTrain 1. 10:00\nTrain 2. 12:00\nTrain 3. 14:00\nTrain 4. 16:00" << endl;
                    cin >> choosetime;

                    if (choosetime > 0 && choosetime <= Trains) {
                        choosetime--; // Adjust the index

                        if (seatsQuantity <= availableSeatsForDown[choosetime]) {
                            cout << "Your seats are reserved for the return journey as well." << endl;

                            // Calculate the total cost for the return journey
                            double totalReturnCost = paidTickets * Ticket_Price;
                            double totalPayout = totalCost + totalReturnCost;

                            cout << "Total Expense for the return journey is $" << totalReturnCost << "." << endl;
                            cout << "Your Total payout is $" << totalPayout << "." << endl;

                            availableSeatsForDown[choosetime] -= seatsQuantity;
                            TotalMoneyOfTheDay += totalPayout;

                            cout << "Updated Available Seats for Train " << choosetime + 1 << " (Journey Down): " << availableSeatsForDown[choosetime] << " seats" << endl;
                        } else {
                            cout << "Seats in this cohort are unavailable. Please choose another departure for the return journey." << endl;
                        }
                    } else {
                        cout << "Invalid Selection! Please select a number between 1 and 4 for the return journey." << endl;
                    }
                } else {
                    cout << "Seats in this cohort are unavailable. Please choose from another departure. Thank you." << endl;
                }
            } else {
                cout << "Invalid Selection! Please select a number between 1 and 4 for the Journey Up." << endl;
            }
        } while (choosetime < 0 || choosetime >= Trains);
    }
};

int main() {
    char choice, ch;
    cout << "Press A for Admin or C for Customer." << endl;
    cin >> ch;

    Start_of_day s;

    do {
        if (ch == 'C' || ch == 'c') {
            s.displayScheduleForJourneyUp();
            s.displayScheduleForJourneyDown();

            cout << "Press Y to Book Ticket" << endl;
            do {
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    s.BookTicket();
                } else {
                    cout << "Invalid Entry... Press Y to Book Ticket" << endl;
                }
            } while (choice != 'Y' && choice != 'y');
        }

        if (ch == 'A' || ch == 'a') {
            string password;
            cout << "Enter Password: ";
            cin >> password;
            if (password == "admin123") {
                cout << "Total Passengers of the day: " << s.TotalPassengerOfTheDay << endl;
                cout << "Total Money Collected is: $" << s.TotalMoneyOfTheDay << endl;
            } else {
                cout << "Wrong Password" << endl;
            }
        }

        cout << "\nPress A for Admin or C for Customer." << endl;
        cin >> ch;
    } while (ch == 'A' || ch == 'a' || ch == 'c' || ch == 'C');

    return 0;
}
