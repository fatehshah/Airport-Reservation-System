#include <stdio.h>
#include <string.h>

#define MAX_FLIGHTS 50
#define MAX_PASSENGERS 200
#define NAME_LEN 50
#define DEST_LEN 50
#define TIME_LEN 20

// Flight structure
typedef struct {
    int id;
    char origin[DEST_LEN];
    char destination[DEST_LEN];
    char departure[TIME_LEN];
    char arrival[TIME_LEN];
    int capacity;
    int bookedSeats;
} Flight;

// Passenger structure
typedef struct {
    char name[NAME_LEN];
    int flightId; // Which flight this passenger booked
} Passenger;

// Global arrays
Flight flights[MAX_FLIGHTS];
Passenger passengers[MAX_PASSENGERS];
int flightCount = 0;
int passengerCount = 0;

// Add a flight
void addFlight() {
    if (flightCount >= MAX_FLIGHTS) {
        printf("Cannot add more flights!\n");
        return;
    }
    Flight f;
    f.id = flightCount + 1;

    printf("Enter origin: ");
    scanf(" %[^\n]", f.origin);
    printf("Enter destination: ");
    scanf(" %[^\n]", f.destination);
    printf("Enter departure time: ");
    scanf(" %[^\n]", f.departure);
    printf("Enter arrival time: ");
    scanf(" %[^\n]", f.arrival);
    printf("Enter seat capacity: ");
    scanf("%d", &f.capacity);

    f.bookedSeats = 0;

    flights[flightCount] = f;
    flightCount++;

    printf("Flight added successfully! Flight ID: %d\n", f.id);
}

// List all flights
void listFlights() {
    if (flightCount == 0) {
        printf("No flights available.\n");
        return;
    }
    printf("\n--- List of Flights ---\n");
    printf("ID  Origin       Destination  Departure       Arrival         Capacity  Booked\n");
    for (int i = 0; i < flightCount; i++) {
        printf("%-3d %-12s %-12s %-14s %-14s %-8d %-6d\n",
               flights[i].id, flights[i].origin, flights[i].destination,
               flights[i].departure, flights[i].arrival,
               flights[i].capacity, flights[i].bookedSeats);
    }
}

// Book a ticket
void bookTicket() {
    int id;
    printf("Enter flight ID to book: ");
    scanf("%d", &id);

    if (id < 1 || id > flightCount) {
        printf("Invalid flight ID.\n");
        return;
    }

    Flight *f = &flights[id - 1];

    if (f->bookedSeats >= f->capacity) {
        printf("Sorry, flight is full!\n");
        return;
    }

    Passenger p;
    printf("Enter passenger name: ");
    scanf(" %[^\n]", p.name);
    p.flightId = id;

    passengers[passengerCount] = p;
    passengerCount++;
    f->bookedSeats++;

    printf("Ticket booked for %s on flight %d (%s -> %s)\n",
           p.name, id, f->origin, f->destination);
}

// List passengers for a specific flight
void listPassengersForFlight() {
    int id;
    printf("Enter flight ID: ");
    scanf("%d", &id);

    if (id < 1 || id > flightCount) {
        printf("Invalid flight ID.\n");
        return;
    }

    printf("\nPassengers for flight %d (%s -> %s):\n",
           id, flights[id - 1].origin, flights[id - 1].destination);

    int found = 0;
    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].flightId == id) {
            printf("- %s\n", passengers[i].name);
            found = 1;
        }
    }
    if (!found) {
        printf("No passengers booked yet.\n");
    }
}

// Main menu
int main() {
    int choice;
    while (1) {
        printf("\n=== Airport Management System ===\n");
        printf("1. Add Flight\n");
        printf("2. List Flights\n");
        printf("3. Book Ticket\n");
        printf("4. List Passengers for a Flight\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addFlight(); break;
            case 2: listFlights(); break;
            case 3: bookTicket(); break;
            case 4: listPassengersForFlight(); break;
            case 0: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}

