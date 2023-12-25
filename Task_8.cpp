#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// Constants
const int OPENING_HOUR = 10;
const int CLOSING_HOUR = 17;
const int HOURLY_RATE = 20;
const int HALF_HOUR_RATE = 12;

// Structure to store hire records for each boat
struct BoatRecord
{
    double totalMoney;
    double totalHours;
    int returnTime;
};

// Function to calculate money taken for one boat in a day
void calculateDailyProfit(int boatNumber, vector<BoatRecord> &boatRecords)
{
    double totalMoney = 0.0;
    double totalHours = 0.0;
    cout << "Boat " << boatNumber << " - Daily Profit Calculation\n";
    // Loop to calculate money taken for the boat
    while (true)
    {
        int startHour, startMinute, endHour, endMinute, durationChoice;
        double payment = 0.0;

        // Input start time
        cout << "Enter the start time for boat " << boatNumber << " (in HH MM format, -1 to exit): ";
        cin >> startHour;

        // Check for exit condition
        if (startHour == -1)
        {
            break;
        }

        cin >> startMinute;

        // Validate start time
        if (startHour < OPENING_HOUR || startHour >= CLOSING_HOUR || startMinute < 0 || startMinute >= 60)
        {
            cout << "Error: Invalid start time. Must be between 10:00 and 17:00.\n";
            continue;
        }

        // Choose duration
        cout << "Choose duration for boat " << boatNumber << " (1 for 1 hour, 2 for half an hour): ";
        cin >> durationChoice;

        // Validate duration choice
        if (durationChoice != 1 && durationChoice != 2)
        {
            cout << "Error: Invalid duration choice. Enter 1 for 1 hour or 2 for half an hour.\n";
            continue;
        }

        // Calculate payment based on user's duration choice
        if (durationChoice == 1)
        {
            // 1 hour rental
            endHour = startHour + 1;
            endMinute = startMinute;

            // Validate end time
            if (endHour > CLOSING_HOUR || (endHour == CLOSING_HOUR && endMinute > 0))
            {
                cout << "Error: Invalid end time. Must be between 10:30 and 17:00.\n";
                continue;
            }

            payment = HOURLY_RATE;
            totalHours += 1.0;
        }
        else
        {
            // Half-hour rental
            endHour = startHour;
            endMinute = startMinute + 30;

            // Adjust end time if it exceeds 60 minutes
            if (endMinute >= 60)
            {
                endHour += 1;
                endMinute -= 60;
            }

            // Validate end time
            if (endHour > CLOSING_HOUR || (endHour == CLOSING_HOUR && endMinute > 0))
            {
                cout << "Error: Invalid end time. Must be between 10:30 and 17:00.\n";
                continue;
            }

            payment = HALF_HOUR_RATE;
            totalHours += 0.5;
        }

        // Update total money and record return time
        totalMoney += payment;
        BoatRecord &record = boatRecords[boatNumber - 1];
        record.totalMoney += payment;
        record.totalHours += (durationChoice == 1) ? 1.0 : 0.5;
        record.returnTime = endHour;

        cout << "Boat " << boatNumber << " rented for " << ((durationChoice == 1) ? "1 hour" : "half an hour") << ". Payment: $" << payment << "\n";

        // Output end time
        cout << "Boat " << boatNumber << " returned at " << endHour << ":" << setfill('0') << setw(2) << endMinute << "\n";
    }

    // Output total money and hours at the end of the day for the boat
    cout << "Total money taken for boat " << boatNumber << ": $" << totalMoney << "\n";
    cout << "Total hours rented for boat " << boatNumber << ": " << fixed << setprecision(1) << totalHours << " hours\n\n";
}

// Function to find the next available boat
void findNextAvailableBoat(const vector<BoatRecord> &boatRecords)
{
    int currentHour;

    // Input current hour
    cout << "Enter the current hour (between 10 and 17): ";
    cin >> currentHour;

    // Validate current hour
    if (currentHour < OPENING_HOUR || currentHour >= CLOSING_HOUR)
    {
        cout << "Error: Invalid current hour. Must be between 10 and 17.\n";
        return;
    }

    bool foundAvailable = false;
    int earliestAvailableTime = CLOSING_HOUR;

    // Check each boat's availability based on their return time
    for (int boatNumber = 1; boatNumber <= 10; ++boatNumber)
    {
        const BoatRecord &record = boatRecords[boatNumber - 1];

        if (record.returnTime <= currentHour)
        {
            foundAvailable = true;
            cout << "Boat " << boatNumber << " is available now.\n";
        }
        else
        {
            earliestAvailableTime = min(earliestAvailableTime, record.returnTime);
        }
    }

    // If no boats are available, display the earliest available time
    if (!foundAvailable)
    {
        cout << "No boats are currently available. The earliest available time is at " << earliestAvailableTime << ":00.\n";
    }
}

// Function to calculate total money taken and additional information
void calculateTotalMoney(const vector<BoatRecord> &boatRecords)
{
    double totalMoney = 0.0;
    double totalHours = 0.0;
    int boatsNotUsed = 0;
    int boatUsedMost = 0;
    double maxHours = 0.0;

    // Calculate total money and additional information
    for (int boatNumber = 1; boatNumber <= 10; ++boatNumber)
    {
        const BoatRecord &record = boatRecords[boatNumber - 1];

        totalMoney += record.totalMoney;
        totalHours += record.totalHours;

        if (record.totalHours == 0.0)
        {
            boatsNotUsed++;
        }

        if (record.totalHours > maxHours)
        {
            maxHours = record.totalHours;
            boatUsedMost = boatNumber;
        }
    }

    // Output the total money and additional information
    cout << "\nTotal money taken for all boats: $" << totalMoney << "\n";
    cout << "Total number of hours boats were hired: " << fixed << setprecision(1) << totalHours << " hours\n";
    cout << "Number of boats not used today: " << boatsNotUsed << "\n";
    cout << "Boat " << boatUsedMost << " was used the most, hired for " << fixed << setprecision(1) << maxHours << " hours.\n";
}

int main()
{
    // Initialize boat records for each boat
    vector<BoatRecord> boatRecords(10, {0.0, 0.0, OPENING_HOUR});

    // Test the program for each boat
    for (int boatNumber = 1; boatNumber <= 10; ++boatNumber) {
        calculateDailyProfit(boatNumber, boatRecords);
    }

    // Find the next available boat
    findNextAvailableBoat(boatRecords);

    // Calculate total money taken and additional information
    calculateTotalMoney(boatRecords);

    return 0;
}