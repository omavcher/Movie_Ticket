#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MOVIES 5
#define MAX_TICKETS 10

FILE *op;

struct Casting {
    char director[100];
    char actors[500];
};

struct Movie {
    char name[100];
    float rating;
    int price;
    int availableSeats;
    struct Casting casting;
};

struct Ticket {
    char movieName[100];
    int seatNumber;
};

void displayMovies(struct Movie movies[], int numMovies) {
    printf("\n================================================ Movie Listing ================================================\n\n");
    printf("%-20s%-10s%-10s%-20s%-50s\n", "Movie Name", "Rating", "Price", "Director", "Cast");
    printf("--------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < numMovies; i++) {
        printf("%-20s%-10.2f%-10d%-20s%-50s\n", movies[i].name, movies[i].rating, movies[i].price, movies[i].casting.director, movies[i].casting.actors);
    }

    printf("--------------------------------------------------------------------------------------------------------------\n");
}

void displayBookedTickets(struct Ticket tickets[], int numTickets) {
    printf("\n================================================ Booked Tickets ================================================\n\n");
    printf("%-20s%-10s\n", "Movie Name", "Seat Number");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < numTickets; i++) {
        printf("%-20s%-10d\n", tickets[i].movieName, tickets[i].seatNumber);
    }

    printf("-----------------------------------------------------------\n");
}

int bookTicket(struct Movie movies[], int numMovies, struct Ticket tickets[], int numTickets) {
    char movieName[100];
    int seatNumber;

    displayMovies(movies, numMovies);

    printf("\nEnter the name of the movie you want to book: ");
    scanf("%s", movieName);

    int movieIndex = -1;
    for (int i = 0; i < numMovies; i++) {
        if (strcmp(movies[i].name, movieName) == 0) {
            movieIndex = i;
            break;
        }
    }

    if (movieIndex == -1) {
        printf("Movie not found.\n");
        return numTickets;
    }

    printf("Enter the seat number (1-%d): ", movies[movieIndex].availableSeats);
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > movies[movieIndex].availableSeats) {
        printf("Invalid seat number.\n");
        return numTickets;
    }

    strcpy(tickets[numTickets].movieName, movieName);
    tickets[numTickets].seatNumber = seatNumber;

    movies[movieIndex].availableSeats--;

    printf("\nTicket booked successfully!\n");

    
    FILE *op = fopen("ticket.txt", "a");
    if (op == NULL) {
        printf("Error opening file for writing.\n");
        return numTickets;
    }

    
    fprintf(op, "\n================================================ Booked Tickets ================================================\n\n");
    fprintf(op, "%-20s%-10s\n", "Movie Name", "Seat Number");
    fprintf(op, "-----------------------------------------------------------\n");
    fprintf(op, "%-20s%-10d\n", tickets[numTickets].movieName, tickets[numTickets].seatNumber);

    
    fclose(op);

    return numTickets + 1;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    op = fopen("writing.txt", "w");
    if (op == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    struct Movie movies[MAX_MOVIES] = {
        {"Dunki", 7.4, 243, 5, {"Rajkumar Hirani", "Shah Rukh Khan, Taapsee Pannu"}},
        {"Salaar", 8.3, 345, 9, {"Prahanth Neel", "Prabhas, Shruti Haasan"}},
        {"Animal", 8.2, 395, 3, {"Sandeep Reddy Vanga", "Ranbir Kapoor, Rashmika Mandanna"}},
        {"12th FAIL", 9.6, 265, 10, {"Vidhu Chopra", "Vikrant Massey, Medha Shankr"}},
        {"HANUMAN", 9.9, 390, 8, {"Prashanth Varma", "Teja Sajja, Varalaxmi Sarathkumar"}},
    };

    struct Ticket tickets[MAX_TICKETS];
    int numTickets = 0;

    int choice;
    do {
        printf("\n============================== Movie Ticket Booking System ==============================\n");
        printf("1. Display Movies\n");
        printf("2. Book a Ticket\n");
        printf("3. Display Booked Tickets\n");
        printf("4. Exit\n");
        printf("=======================================================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        clearScreen();

        switch (choice) {
     case 1:
         displayMovies(movies, MAX_MOVIES);
         break;
     case 2:
         numTickets = bookTicket(movies, MAX_MOVIES, tickets, numTickets);
         break;
     case 3:
         displayBookedTickets(tickets, numTickets);
         break;
     case 4:
         printf("Exiting...\n");
         break;
     default:
         printf("Invalid choice. Please try again.\n");
        }

     printf("Press Enter to continue...");
     getchar();
        getchar();

        clearScreen();

    } while (choice != 4);

    
    fclose(op);

    return 0;
}
