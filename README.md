# sanjana_1772
#include <stdio.h>
#include <string.h>

#define FILE_NAME "rooms.dat"
#define MAX_NAME_LEN 100
#define MAX_ROOMS 200
// ------------------ STRUCT DEFINITION ------------------
typedef struct {
    int roomNo;
    int occupied;               // 0 = empty, 1 = occupied
    char patientName[MAX_NAME_LEN];
} Room;
// ------------------ FUNCTION DECLARATIONS ------------------
void assignRoom();
void viewRooms();
void searchRoom();
void updateRoom();
void dischargeRoom();
int roomExists(int roomNo);
void saveRoom(Room r);
void loadRooms(Room rooms[], int *count);
void writeAllRooms(Room rooms[], int count);
// ------------------ MAIN MENU ------------------
int main() {
    int choice;
    do {
        printf("\n===================================\n");
        printf("   HOSPITAL WARD / ROOM MANAGEMENT\n");
        printf("===================================\n");
        printf("1. Assign Patient to Room\n");
        printf("2. View All Rooms\n");
        printf("3. Search Room\n");
        printf("4. Update Room Details\n");
        printf("5. Discharge Patient\n");
        printf("6. Exit\n");
        printf("-----------------------------------\n");
        printf("Enter your choice: ");
     if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }
        getchar(); // clear newline
        switch (choice) {
            case 1: assignRoom(); break;
            case 2: viewRooms(); break;
            case 3: searchRoom(); break;
            case 4: updateRoom(); break;
            case 5: dischargeRoom(); break;
            case 6: printf("Exiting program... Goodbye!\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);
    return 0;
}
// ------------------ ASSIGN PATIENT TO ROOM ------------------
void assignRoom() {
    Room r;
    printf("\n--- Assign Patient to Room ---\n");
    printf("Enter Room Number: ");
    scanf("%d", &r.roomNo);
    getchar();
    if (roomExists(r.roomNo)) {
        printf("Error: Room already assigned! Use Update instead.\n");
        return;
    }
    printf("Enter Patient Name: ");
    fgets(r.patientName, sizeof(r.patientName), stdin);
    r.patientName[strcspn(r.patientName, "\n")] = '\0';
    r.occupied = 1;
    saveRoom(r);
    printf("Patient assigned to room successfully!\n");
}
// ------------------ SAVE ROOM ------------------
void saveRoom(Room r) {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }
    fwrite(&r, sizeof(Room), 1, fp);
    fclose(fp);
}
// ------------------ CHECK ROOM EXISTS ------------------
int roomExists(int roomNo) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) return 0;

    Room r;
    while (fread(&r, sizeof(Room), 1, fp)) {
        if (r.roomNo == roomNo && r.occupied == 1) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
// ------------------ VIEW ALL ROOMS ------------------
void viewRooms() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No room records found.\n");
        return;
    }
    Room r;
    printf("\n%-10s %-10s %-20s\n", "Room No", "Status", "Patient");
    printf("------------------------------------------\n");

    while (fread(&r, sizeof(Room), 1, fp)) {
        printf("%-10d %-10s %-20s\n",
               r.roomNo,
               r.occupied ? "Occupied" : "Empty",
               r.occupied ? r.patientName : "None");
    }
   fclose(fp);
}
// ------------------ SEARCH ROOM ------------------
void searchRoom() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No room records found.\n");
        return;
    }
    int rn, found = 0;
    Room r;
    printf("\nEnter Room Number to search: ");
    scanf("%d", &rn);
    while (fread(&r, sizeof(Room), 1, fp)) {
        if (r.roomNo == rn) {
            found = 1;
            printf("\nRoom Found:\n");
            printf("Room Number : %d\n", r.roomNo);
            printf("Patient     : %s\n", r.occupied ? r.patientName : "None");
            break;
        }
    }
    if (!found)
        printf("Room %d not found.\n", rn);
    fclose(fp);
}
// ------------------ UPDATE ROOM ------------------
void updateRoom() {
    Room rooms[MAX_ROOMS];
    int count = 0, rn, found = 0;
    loadRooms(rooms, &count);
    printf("\nEnter Room Number to update: ");
    scanf("%d", &rn);
    getchar();
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNo == rn) {
            found = 1;
            printf("Enter new patient name: ");
            fgets(rooms[i].patientName, sizeof(rooms[i].patientName), stdin);
            rooms[i].patientName[strcspn(rooms[i].patientName, "\n")] = '\0';
            break;
        }
    }
    if (found) {
        writeAllRooms(rooms, count);
        printf("Room updated successfully.\n");
    } else {
        printf("Room not found.\n");
    }
}
// ------------------ DISCHARGE ROOM ------------------
void dischargeRoom() {
    Room rooms[MAX_ROOMS];
    int count = 0, rn, found = 0;

    loadRooms(rooms, &count);

    printf("\nEnter Room Number to discharge: ");
    scanf("%d", &rn);
    getchar();
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNo == rn) {
            found = 1;
            printf("Are you sure you want to discharge %s (Room %d)? (y/n): ",
                   rooms[i].patientName, rn);
            char confirm = getchar();
            getchar();
            if (confirm == 'y' || confirm == 'Y') {
                for (int j = i; j < count - 1; j++)
                    rooms[j] = rooms[j + 1];
                count--;
                writeAllRooms(rooms, count);
                printf("Patient discharged successfully.\n");
            } else {
                printf("Discharge cancelled.\n");
            }
            break;
        }
    }
    if (!found)
        printf("Room not found.\n");
}
// ------------------ LOAD & WRITE ALL ROOMS ------------------
void loadRooms(Room rooms[], int *count) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { *count = 0; return; }
    *count = 0;
    while (*count < MAX_ROOMS && fread(&rooms[*count], sizeof(Room), 1, fp))
        (*count)++;
    fclose(fp);
}
void writeAllRooms(Room rooms[], int count) {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }
    fwrite(rooms, sizeof(Room), count, fp);
    fclose(fp);
}




🧑‍⚕️Ward/Room Management System (C Program)


A simple menu-driven Hospital Room Management System written in C.

This program allows hospital staff to store, manage, update, and search room–patient allocation details using structures, arrays, and binary file storage.




👉 Abstract

The Ward/Room Management System is a lightweight, terminal-based C application designed to manage hospital room assignments effectively. The system enables users to assign patients to rooms, update assigned details, view all room statuses (occupied or empty), search for a specific room, and discharge patients when necessary. All room records are stored persistently in a binary .dat file, ensuring data remains available even after the program exits.

With a simple menu-driven interface, the program is easy to operate, making it suitable for beginners and small healthcare facilities. It demonstrates essential C programming concepts such as structures, binary file handling, loops, conditional logic, and text-based user interaction. This project provides a practical solution for managing ward and room information in a clear and efficient manner.


---

👉Features of the Program

Assign a patient to a hospital room

View all rooms with their status (Occupied / Empty)

Search for a room by room number

Update patient details for a specific room

Discharge a patient (remove room entry)

Persistent storage using a binary .dat file (rooms.dat)

Menu-driven interface with easy navigation

Automatically creates storage file if it does not exist

Uses struct for structured room information

Beginner-friendly implementation using core C concepts




👉Technical Requirements

1. System Requirements

Operating System : Windows / Linux / macOS

Terminal/command-line environment

Minimum RAM: 4 MB

Small disk space for rooms.dat



2. Software Requirements

C Compiler : GCC / Clang / MinGW / MSVC

Any code editor or IDE (VS Code, Code::Blocks, Dev-C++, Vim, etc.)

Optional : Make tool (if using a Makefile)



3. Programming Requirements

Language: C

Supported Standards: C89 / C99 / C11


Standard Libraries Used

#include <stdio.h>     // input/output and file handling

#include <string.h>    // string operations (fgets, strcspn, etc.)

(Note: <stdlib.h> is NOT required since no dynamic memory or system functions are used.)



4. File Handling Requirements

Program uses a binary file: rooms.dat

Each Room structure is stored using:

fwrite() → write binary structure

fread() → read binary structure


Program automatically creates the file if missing

All room assignment, update, and discharge operations modify this file



5. Compilation Requirements

Code must compile with zero errors

Recommended warning flag:

-Wall -Wextra



👉 Functional Requirements

1. User Interface

Fully terminal-based

Displays clear menu options

Validates user inputs

Uses looping menu until user selects Exit





2. Room Management Operations

✔ Assign Room

Enter room number

Check if room already exists

Input patient name

Save new room record into binary file


✔ View All Rooms

Displays:

Room No

Status (Occupied / Empty)

Patient Name (or “None”)

Reads records directly from the file


✔ Search Room

Search by room number

Displays room details if found

Shows error message if not found


✔ Update Room Details

Loads all records into an array

Allows editing patient name for the selected room

Saves updated list back to binary file


✔ Discharge Patient

Loads all records

Confirms discharge

Removes the room record

Writes modified list back to file




3. Data Management

All room data stored persistently in rooms.dat

Supports multiple program sessions

Handles empty or missing files safely

Uses an array fallback when rewriting records




4. Program Flow

Menu-driven loop

Repeats until user selects Exit

Displays success or error messages

Enables smooth navigation between options



👉 How to Run the Program

1. Compile the Program

Open terminal inside project folder and run:

gcc ward_management.c -o ward_management

2. Run the Executable

On Linux/macOS:

./ward_management

On Windows:

 Ward_management.exe


3. Data File

Program automatically creates rooms.dat if missing

All room records are saved and retrieved from this file





