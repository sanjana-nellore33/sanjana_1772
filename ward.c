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