# sanjana_1772


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

5.screenshots
<img width="523" height="803" alt="Screenshot 2025-11-20 153202" src="https://github.com/user-attachments/assets/a960944b-deab-446b-9d71-79df1079fae7" />
<img width="395" height="389" alt="Screenshot 2025-11-20 153251" src="https://github.com/user-attachments/assets/ef3e3456-28c6-4747-a6cc-2dd824245f13" />
<img width="461" height="727" alt="Screenshot 2025-11-20 153317" src="https://github.com/user-attachments/assets/9b014ec5-7968-4e7d-aaa5-b12935e4bbfc" />
<img width="551" height="606" alt="Screenshot 2025-11-20 153414" src="https://github.com/user-attachments/assets/61b3a191-8b2c-4b2f-b8de-98cb0f415fe0" />



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





