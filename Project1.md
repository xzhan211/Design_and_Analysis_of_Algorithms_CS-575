# Project 1: Phone Directory (Sorting and Searching)
## Requirement
### A:
Your program should be able to create a new phone directory by reading from a text file. To do this, implement a “void create(String filePath)” function. In the text file, the name and phone number of a person should be separated by a comma, and there should be only one pair of a name and phone number per line. For example, see below:

### B:
Once a phone directory is created as described above, sort all entries and display all the entries in alphabetical order of the Last name. If multiple persons in the directory have the same Last name, sort them based on their First name. If they have the same first and last name, sort them based on their phone number. For this, implement “void sortDirectory()” function. In the function,implement the merge sort algorithm to sort names and implement the randomized quicksort algorithm to sort phone numbers of the persons with the same name.

### C:
After displaying the sorted phone directory, search for a given name, e.g., Bob Smith. If found, print its location in the directory, the name, and phone number. If multiple persons in the directory have the same name, print all of them. Otherwise, return “Name not found” message. Use the binary search algorithm to do this. For this, implement “void searchDirectory(char* name)” function.

### D:
Implement “void deleteEntry(char* name)” function that searches for the name passed as the parameter, and delete the name and phone number found by search. If multiple persons with the same name are found, only delete the name and phone number of the parson who appears last in the sorted order. If not found, print “unable to delete as entry not found”

### E:
Implement “void insertEntry(char* name, char* phone_number)” to insert a new pair of a name and phone number to the directory, and make sure to keep the directory sorted after the insertion. If the directory already has the same name and phone number, print a message “entry already exist in the directory”

## How to run
### Compile:
Compile: “make” command will only compile the source code files and it should not run any of the program. After executing “make” command it should create an object file with named <userid>_phone_directory.out

### Execution: 
Your program should be executable by running the below command: ./<user_id>_phone_directory.out <input file name>”
If its not running by these commands then no credit will be given.
During execution your program should display the menu options.
Based on users input it will perform the desired operation and call the appropriate function required.
