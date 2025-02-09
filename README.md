# Bank System

This program is a **Bank System** written in C++ that allows users to manage client records stored in a text file. The system supports functionalities like listing clients, adding new clients, updating client information, deleting clients, and searching for clients by account number.

## Features

1. **List All Clients**: Displays a list of all clients with their details.
2. **Add New Client**: Allows adding a new client with unique account details.
3. **Update Client Information**: Enables updating client details.
4. **Delete Client**: Marks a client for deletion and removes them from the records.
5. **Find Client**: Searches and displays client information by account number.

## File Structure

The client data is stored in a text file named `ClientsRecord.txt`, with each record formatted as follows:

```
AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance
```

**Important:** The file `ClientsRecord.txt` must be present in the project directory for the program to function correctly.

## Code Overview

### Main Components:

1. **`stClient` Structure**:

   - Represents a client with fields like account number, PIN code, name, phone, and account balance.

2. **Core Functions**:

   - `ShowMainMenu()`: Displays the main menu and handles user input.
   - `LoadDataFromFileToVector()`: Loads client data from the file into a vector.
   - `AddNewClient()`: Adds a new client to the file.
   - `UpdateClientByAccountNumber()`: Updates an existing client's information.
   - `DeleteClientByAccountNumber()`: Deletes a client from the records.
   - `ShowAllClientsScreen()`: Lists all clients.
   - `FindClientByAccountNumber()`: Finds and displays a client by their account number.

3. **File Handling**:

   - Client records are read from and written to `ClientsRecord.txt` using file I/O operations.

4. **Utility Functions**:

   - `SpiltEachWord()`: Splits a string by a delimiter.
   - `ConvertLineToRecord()` and `ConvertRecordToLine()`: Convert between string and `stClient` structures.

## How to Use

1. Compile the code using Visual Studio:

   - Open Visual Studio.
   - Create a new **Console App** (C++) project.
   - Copy and paste the code into the main `.cpp` file.
   - Build the project by pressing **Ctrl + Shift + B**.
   - Run the program by pressing **Ctrl + F5**.

2. Alternatively, using a C++ compiler (e.g., g++):

   ```bash
   g++ -o BankSystem BankSystem.cpp
   ./BankSystem
   ```

3. Follow the on-screen instructions to manage client records.

## Example

- **Adding a New Client**:

  - Enter account number, PIN code, name, phone, and balance.
  - The client will be saved to `ClientsRecord.txt`.

- **Listing Clients**:

  - Displays all clients with formatted details.

## Author

Developed by **Khalid Amri**.

## License

This project is open-source and available for personal and educational use.