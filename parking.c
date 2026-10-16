
#include <stdio.h>
#include <string.h>

#define PARK 5
#define SIZE 10

// Parking slots
char cars[PARK][20];
int occupied[PARK] = {0};

// Circular waiting queue
char waiting[SIZE][20];
int front = 0, rear = -1, count = 0;

void parkCar() {
    char car[20];
    int i;

    printf("Enter car number: ");
    scanf("%19s", car);

    // Check duplicate
    for (i = 0; i < PARK; i++) {
        if (occupied[i] && strcmp(cars[i], car) == 0) {
            printf("Car already parked!\n");
            return;
        }
    }

    for (i = 0; i < count; i++) {
        if (strcmp(waiting[(front + i) % SIZE], car) == 0) {
            printf("Car already in waiting list!\n");
            return;
        }
    }

    // Find an empty parking slot
    for (i = 0; i < PARK; i++) {
        if (!occupied[i]) {
            strcpy(cars[i], car);
            occupied[i] = 1;
            printf("Car parked in slot %d.\n", i + 1);
            return;
        }
    }

    // Parking full: add to circular queue
    if (count == SIZE) {
        printf("Waiting list is full!\n");
        return;
    }

    rear = (rear + 1) % SIZE;
    strcpy(waiting[rear], car);
    count++;

    printf("Parking full! Car added to waiting list.\n");
}

void removeCar() {
    char car[20];
    int i, j, found = 0;

    printf("Enter car number to remove: ");
    scanf("%19s", car);

    // Search parked cars
    for (i = 0; i < PARK; i++) {
        if (occupied[i] && strcmp(cars[i], car) == 0) {
            occupied[i] = 0;
            found = 1;
            printf("Car removed from slot %d.\n", i + 1);

            // Move first waiting car into the free slot
            if (count > 0) {
                strcpy(cars[i], waiting[front]);
                occupied[i] = 1;

                printf("Car %s moved from waiting list to slot %d.\n",
                       cars[i], i + 1);

                front = (front + 1) % SIZE;
                count--;
            }
            return;
        }
    }

    // Search and remove any car from waiting queue
    for (i = 0; i < count; i++) {
        int pos = (front + i) % SIZE;

        if (strcmp(waiting[pos], car) == 0) {
            found = 1;

            for (j = i; j < count - 1; j++) {
                int current = (front + j) % SIZE;
                int next = (front + j + 1) % SIZE;
                strcpy(waiting[current], waiting[next]);
            }

            rear = (rear - 1 + SIZE) % SIZE;
            count--;

            printf("Car removed from waiting list.\n");
            return;
        }
    }

    if (!found)
        printf("Car number not found!\n");
}

void display() {
    int i;

    printf("\n--- Parking Slots ---\n");

    for (i = 0; i < PARK; i++) {
        if (occupied[i])
            printf("Slot %d: %s\n", i + 1, cars[i]);
        else
            printf("Slot %d: EMPTY\n", i + 1);
    }

    printf("\n--- Waiting List ---\n");

    if (count == 0)
        printf("No cars waiting.\n");

    for (i = 0; i < count; i++)
        printf("%s\n", waiting[(front + i) % SIZE]);
}

int main() {
    int choice;

    do {
        printf("\n--- Parking Management System ---\n");
        printf("1. Park Car\n");
        printf("2. Remove Car by Number\n");
        printf("3. Display Parking and Waiting List\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
            return 0;

        switch (choice) {
            case 1: parkCar(); break;
            case 2: removeCar(); break;
            case 3: display(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
