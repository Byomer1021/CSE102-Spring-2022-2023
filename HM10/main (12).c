#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Book Structure
typedef struct Book
{
	char isbn[20];
	char title[100];
	char author[100];
	int publicationYear;
	int reserved;
	struct Book *next;
} Book;

// Student Structure
typedef struct Student
{
	char name[100];
	int id;
	struct Book *borrowedBooks;
	struct Student *next;
} Student;

// Global variables
Book *bookList = NULL;
Student *studentList = NULL;

// Function Prototypes
void displayMenu();
void addBook(char *isbn, char *title, char *author, int publicationYear, int method);
void deleteBook(char *isbn);
void updateBook(char *isbn, char *feature, char *value);
void filterAndSortBooks(int filterChoice, char *filter, int sortChoice);
void reverseBookList();
void searchBooks(int searchChoice, char *searchValue);
void borrowBook(char *isbn);
void returnBook(char *isbn);
void displayStudentBooks(int studentId);

Student *findStudent(int id)
{
	Student *currentStudent = studentList;
	while (currentStudent != NULL)
	{
		if (currentStudent->id == id)
		{
			return currentStudent;
		}
		currentStudent = currentStudent->next;
	}
	return NULL;
}

// void readBookDataFromFile()
// {
// 	FILE *file = fopen("book.txt", "r");
// 	if (file == NULL)
// 	{
// 		printf("Error opening book.txt file.\n");
// 		return;
// 	}

// 	char line[256];
// 	while (fgets(line, sizeof(line), file))
// 	{
// 		// Parse the line to extract book information
// 		char *token = strtok(line, ",");
// 		if (token != NULL)
// 		{
// 			Book *newBook = (Book *)malloc(sizeof(Book));
// 			strcpy(newBook->isbn, token);

// 			token = strtok(NULL, ",");
// 			if (token != NULL)
// 			{
// 				strcpy(newBook->title, token);
// 			}

// 			token = strtok(NULL, ",");
// 			if (token != NULL)
// 			{
// 				strcpy(newBook->author, token);
// 			}

// 			token = strtok(NULL, ",");
// 			if (token != NULL)
// 			{
// 				newBook->publicationYear = atoi(token);
// 			}

// 			token = strtok(NULL, ",");
// 			if (token != NULL)
// 			{
// 				newBook->reserved = atoi(token);
// 			}

// 			newBook->next = NULL;

// 			// Add the book to the linked list
// 			if (bookList == NULL)
// 			{
// 				bookList = newBook;
// 			}
// 			else
// 			{
// 				Book *current = bookList;
// 				while (current->next != NULL)
// 				{
// 					current = current->next;
// 				}
// 				current->next = newBook;
// 			}
// 		}
// 	}

// 	fclose(file);
// }

void writeBookDataToFile()
{
	FILE *file = fopen("book.txt", "w");
	if (file == NULL)
	{
		printf("Error opening book_data.txt file.\n");
		return;
	}

	Book *current = bookList;
	while (current != NULL)
	{
		if (current->reserved == 0)
			fprintf(file, "ISBN:%s\nTITLE:%s\nAUTHOR:%s\nPUB YEAR:%d\nREZ:available\n ", current->isbn, current->title, current->author, current->publicationYear);
		else
		{
			fprintf(file, "ISBN:%s\nTITLE:%s\nAUTHOR:%s\nPUB YEAR:%d\nREZ:unavailable\n ", current->isbn, current->title, current->author, current->publicationYear);
		}

		current = current->next;
	}

	fclose(file);
}

void readStudentDataFromFile()
{
	FILE *file = fopen("student.txt", "r");
	if (file == NULL)
	{
		printf("Error opening student.txt file.\n");
		return;
	}

	char line[256];
	while (fgets(line, sizeof(line), file))
	{
		// Parse the line to extract student information
		char *token = strtok(line, ",");
		if (token != NULL)
		{
			Student *newStudent = (Student *)malloc(sizeof(Student));
			strcpy(newStudent->name, token);

			token = strtok(NULL, ",");
			if (token != NULL)
			{
				newStudent->id = atoi(token);
			}

			newStudent->borrowedBooks = NULL;
			newStudent->next = NULL;

			// Add the student to the linked list
			if (studentList == NULL)
			{
				studentList = newStudent;
			}
			else
			{
				Student *current = studentList;
				while (current->next != NULL)
				{
					current = current->next;
				}
				current->next = newStudent;
			}
		}
	}

	fclose(file);
}

// Function to write student data to a text file
void writeStudentDataToFile()
{
	FILE *file = fopen("student.txt", "w");
	if (file == NULL)
	{
		printf("Error opening student data file.\n");
		return;
	}

	Student *currentStudent = studentList;
	while (currentStudent != NULL)
	{
		fprintf(file, "%d,%s\n", currentStudent->id, currentStudent->name);
		currentStudent = currentStudent->next;
	}

	fclose(file);
}

void initializeLibrary()
{
	// readBookDataFromFile();
	readStudentDataFromFile();
}

// Function to display the main menu
void displayMenu()
{
	printf("\n==== Library ====\n");
	printf("1. Add a Book\n");
	printf("2. Delete a Book\n");
	printf("3. Update a Book\n");
	printf("4. Filter and Sort Books\n");
	printf("5. Reverse Book List\n");
	printf("6. Search Books\n");
	printf("7. Borrow a Book\n");
	printf("8. Return a Book\n");
	printf("9. Display Student's Borrowed Books\n");
	printf("10. Register a Student\n");
	printf("0. Exit\n");
	printf("========================================\n");
	printf("Enter your choice: ");
}

// Function to add a new book to the library
void addBook(char *isbn, char *title, char *author, int publicationYear, int method)
{
	Book *newBook = (Book *)malloc(sizeof(Book));
	strcpy(newBook->isbn, isbn);
	strcpy(newBook->title, title);
	strcpy(newBook->author, author);
	newBook->publicationYear = publicationYear;
	newBook->reserved = 0;
	newBook->next = NULL;

	if (bookList == NULL)
	{
		bookList = newBook;
	}
	else
	{
		if (method == 0)
		{ // FIFO
			Book *temp = bookList;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = newBook;
		}
		else if (method == 1)
		{ // LIFO
			newBook->next = bookList;
			bookList = newBook;
		}
	}
	writeBookDataToFile();

	printf("Book added successfully.\n");
}

// Function to delete a book from the library
void deleteBook(char *isbn)
{
	if (bookList == NULL)
	{
		printf("Library is empty. No book to delete.\n");
		return;
	}

	Book *current = bookList;
	Book *prev = NULL;

	while (current != NULL)
	{
		if (strcmp(current->isbn, isbn) == 0)
		{
			if (prev == NULL)
			{
				bookList = current->next;
			}
			else
			{
				prev->next = current->next;
			}
			free(current);
			printf("Book deleted successfully.\n");
			return;
		}
		prev = current;
		current = current->next;
	}
	writeBookDataToFile();

	printf("Book not found.\n");
}

// Function to update the information of a book in the library
void updateBook(char *isbn, char *feature, char *value)
{
	if (bookList == NULL)
	{
		printf("Library is empty. No book to update.\n");
		return;
	}

	Book *current = bookList;
	while (current != NULL)
	{
		if (strcmp(current->isbn, isbn) == 0)
		{
			if (strcmp(feature, "isbn") == 0)
			{
				printf("ISBN number cannot be updated.\n");
				return;
			}
			else if (strcmp(feature, "title") == 0)
			{
				strcpy(current->title, value);
			}
			else if (strcmp(feature, "author") == 0)
			{
				strcpy(current->author, value);
			}
			else if (strcmp(feature, "publication year") == 0)
			{
				current->publicationYear = atoi(value);
			}
			printf("Book updated successfully.\n");
			return;
		}
		current = current->next;
	}
	writeBookDataToFile();
	printf("Book not found.\n");
}

// Function to filter and sort books in the library
void filterAndSortBooks(int filterChoice, char *filter, int sortChoice)
{
	if (bookList == NULL)
	{
		printf("Library is empty. No books to filter and sort.\n");
		return;
	}

	// Filter books
	Book *filteredList = NULL;
	Book *current = bookList;

	while (current != NULL)
	{
		if ((filterChoice == 0 && strcmp(current->author, filter) == 0) ||
			(filterChoice == 1 && current->publicationYear == atoi(filter)))
		{
			Book *newBook = (Book *)malloc(sizeof(Book));
			strcpy(newBook->isbn, current->isbn);
			strcpy(newBook->title, current->title);
			strcpy(newBook->author, current->author);
			newBook->publicationYear = current->publicationYear;
			newBook->reserved = current->reserved;
			newBook->next = NULL;

			if (filteredList == NULL)
			{
				filteredList = newBook;
			}
			else
			{
				Book *temp = filteredList;
				while (temp->next != NULL)
				{
					temp = temp->next;
				}
				temp->next = newBook;
			}
		}
		current = current->next;
	}

	if (filteredList == NULL)
	{
		printf("No books found matching the filter criteria.\n");
		return;
	}

	// Sort books
	Book *sortedList = NULL;
	while (filteredList != NULL)
	{
		Book *minBook = filteredList;
		current = filteredList;
		Book *prev = NULL;
		Book *prevMin = NULL;

		while (current != NULL)
		{
			if ((sortChoice == 0 && strcmp(current->title, minBook->title) < 0) ||
				(sortChoice == 1 && strcmp(current->author, minBook->author) < 0) ||
				(sortChoice == 2 && current->publicationYear < minBook->publicationYear))
			{
				minBook = current;
				prevMin = prev;
			}
			prev = current;
			current = current->next;
		}

		if (prevMin == NULL)
		{
			filteredList = minBook->next;
		}
		else
		{
			prevMin->next = minBook->next;
		}

		minBook->next = NULL;

		if (sortedList == NULL)
		{
			sortedList = minBook;
		}
		else
		{
			Book *temp = sortedList;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = minBook;
		}
	}

	// Display sorted books
	current = sortedList;
	printf("\nFiltered and Sorted Book List:\n");
	while (current != NULL)
	{
		printf("ISBN: %s\n", current->isbn);
		printf("Title: %s\n", current->title);
		printf("Author: %s\n", current->author);
		printf("Publication Year: %d\n", current->publicationYear);
		printf("Reserved: %s\n", current->reserved ? "Yes" : "No");
		printf("-----------------------------\n");
		current = current->next;
	}

	// Free memory
	current = sortedList;
	while (current != NULL)
	{
		Book *temp = current;
		current = current->next;
		free(temp);
	}
}

// Function to reverse the order of books in the linked list
void reverseBookList()
{
	if (bookList == NULL)
	{
		printf("Library is empty. No books to reverse.\n");
		return;
	}

	Book *current = bookList;
	Book *prev = NULL;
	Book *next = NULL;

	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	bookList = prev;

	// Display reversed book list
	current = bookList;
	printf("\nReversed Book List:\n");
	while (current != NULL)
	{
		printf("ISBN: %s\n", current->isbn);
		printf("Title: %s\n", current->title);
		printf("Author: %s\n", current->author);
		printf("Publication Year: %d\n", current->publicationYear);
		printf("Reserved: %s\n", current->reserved ? "Yes" : "No");
		printf("-----------------------------\n");
		current = current->next;
	}

	writeBookDataToFile();
}

// Function to search for books based on the given criteria
void searchBooks(int searchChoice, char *searchValue)
{
	if (bookList == NULL)
	{
		printf("Library is empty. No books to search.\n");
		return;
	}

	Book *current = bookList;
	int found = 0;

	while (current != NULL)
	{
		if ((searchChoice == 0 && strcmp(current->isbn, searchValue) == 0) ||
			(searchChoice == 1 && strcmp(current->author, searchValue) == 0) ||
			(searchChoice == 2 && strcmp(current->title, searchValue) == 0))
		{
			printf("ISBN: %s\n", current->isbn);
			printf("Title: %s\n", current->title);
			printf("Author: %s\n", current->author);
			printf("Publication Year: %d\n", current->publicationYear);
			printf("Reserved: %s\n", current->reserved ? "Yes" : "No");
			printf("-----------------------------\n");
			found = 1;
		}
		current = current->next;
	}

	if (!found)
	{
		printf("Book not found.\n");
	}
}

void borrowBook(char *isbn)
{
	int studentId;
	printf("Enter student ID: ");
	scanf("%d", &studentId);

	// Student *newStudent = (Student *)malloc(sizeof(Student));
	// strcpy(newStudent,->id, isbn);

	// Find the student in the linked list
	Student *currentStudent = studentList;
	while (currentStudent != NULL)
	{
		if (currentStudent->id == studentId)
		{
			// Find the book in the linked list
			Book *currentBook = bookList;
			while (currentBook != NULL)
			{
				if (strcmp(currentBook->isbn, isbn) == 0)
				{
					if (currentBook->reserved == 0)
					{
						currentBook->reserved = 1;

						// Add the borrowed book to the student's linked list
						Book *borrowedBook = (Book *)malloc(sizeof(Book));
						strcpy(borrowedBook->isbn, currentBook->isbn);
						strcpy(borrowedBook->title, currentBook->title);
						strcpy(borrowedBook->author, currentBook->author);
						borrowedBook->publicationYear = currentBook->publicationYear;
						borrowedBook->reserved = currentBook->reserved;
						borrowedBook->next = NULL;

						if (currentStudent->borrowedBooks == NULL)
						{
							currentStudent->borrowedBooks = borrowedBook;
						}
						else
						{
							Book *currentBorrowedBook = currentStudent->borrowedBooks;
							while (currentBorrowedBook->next != NULL)
							{
								currentBorrowedBook = currentBorrowedBook->next;
							}
							currentBorrowedBook->next = borrowedBook;
						}

						printf("Book with ISBN %s borrowed by student with ID %d.\n", isbn, studentId);
						writeBookDataToFile();	  // Update book data file
						writeStudentDataToFile(); // Update student data file
						return;
					}
					else
					{
						printf("Book with ISBN %s is already reserved.\n", isbn);
						return;
					}
				}
				currentBook = currentBook->next;
			}

			printf("Book with ISBN %s not found.\n", isbn);
			return;
		}
		currentStudent = currentStudent->next;
	}

	printf("Student with ID %d not found.\n", studentId);
}

// Function to return a book
void returnBook(char *isbn)
{
	int studentId;
	printf("Enter student ID: ");
	scanf("%d", &studentId);

	// Find the student in the linked list
	Student *currentStudent = studentList;
	while (currentStudent != NULL)
	{
		if (currentStudent->id == studentId)
		{
			// Find the borrowed book in the student's linked list
			Book *currentBorrowedBook = currentStudent->borrowedBooks;
			Book *previousBorrowedBook = NULL;
			while (currentBorrowedBook != NULL)
			{
				if (strcmp(currentBorrowedBook->isbn, isbn) == 0)
				{
					// Mark the book as available
					Book *currentBook = bookList;
					while (currentBook != NULL)
					{
						if (strcmp(currentBook->isbn, isbn) == 0)
						{
							currentBook->reserved = 0;
							break;
						}
						currentBook = currentBook->next;
					}

					// Remove the borrowed book from the student's linked list
					if (previousBorrowedBook == NULL)
					{
						currentStudent->borrowedBooks = currentBorrowedBook->next;
					}
					else
					{
						previousBorrowedBook->next = currentBorrowedBook->next;
					}

					free(currentBorrowedBook);
					printf("Book with ISBN %s returned by student with ID %d.\n", isbn, studentId);
					return;
				}
				previousBorrowedBook = currentBorrowedBook;
				currentBorrowedBook = currentBorrowedBook->next;
			}

			printf("Book with ISBN %s not borrowed by student with ID %d.\n", isbn, studentId);
			return;
		}
		currentStudent = currentStudent->next;
	}

	printf("Student with ID %d not found.\n", studentId);
}

// Function to display a students borrowed books
void displayStudentBooks(int studentId)
{
	// Find the student in the linked list
	Student *currentStudent = studentList;
	while (currentStudent != NULL)
	{
		if (currentStudent->id == studentId)
		{
			// Print the student's borrowed books
			Book *currentBorrowedBook = currentStudent->borrowedBooks;
			if (currentBorrowedBook == NULL)
			{
				printf("Student with ID %d has not borrowed any books.\n", studentId);
			}
			else
			{
				printf("Books borrowed by student with ID %d:\n", studentId);
				while (currentBorrowedBook != NULL)
				{
					printf("ISBN: %s, Title: %s, Author: %s, Publication Year: %d\n",
						   currentBorrowedBook->isbn, currentBorrowedBook->title,
						   currentBorrowedBook->author, currentBorrowedBook->publicationYear);
					currentBorrowedBook = currentBorrowedBook->next;
				}
			}
			return;
		}
		currentStudent = currentStudent->next;
	}

	printf("Student with ID %d not found.\n", studentId);
}

void registerStudent()
{
	int id;
	printf("Enter student ID: ");
	scanf("%d", &id);

	// Check if the student already exists
	if (findStudent(id) != NULL)
	{
		printf("Student with ID %d already exists.\n", id);
		return;
	}

	char name[100];
	printf("Enter student name: ");
	scanf("%s", name);

	// Create a new student
	Student *newStudent = (Student *)malloc(sizeof(Student));
	newStudent->id = id;
	strcpy(newStudent->name, name);
	newStudent->borrowedBooks = NULL;
	newStudent->next = NULL;

	// Add the new student to the student list
	if (studentList == NULL)
	{
		studentList = newStudent;
	}
	else
	{
		Student *currentStudent = studentList;
		while (currentStudent->next != NULL)
		{
			currentStudent = currentStudent->next;
		}
		currentStudent->next = newStudent;
	}

	printf("Student with ID %d registered successfully.\n", id);
	writeStudentDataToFile(); // Update student data file
}

int main()
{
	int choice;
	char isbn[20];
	char title[100];
	char author[100];
	int publicationYear;
	char feature[20];
	char value[100];
	int filterChoice;
	char filter[100];
	int sortChoice;
	int searchChoice;
	char searchValue[100];
	int studentId;
	char a;
	initializeLibrary();

	do
	{
		displayMenu();
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("\nEnter the ISBN: ");
			scanf("%s", isbn);
			printf("Enter the title: ");
			scanf(" %[^\n]s", title);
			printf("Enter the author: ");
			scanf(" %[^\n]s", author);
			printf("Enter the publication year: ");
			scanf("%d", &publicationYear);
			printf("Enter the method (0 for FIFO, 1 for LIFO): ");
			int method;
			scanf("%d", &method);
			addBook(isbn, title, author, publicationYear, method);
			break;
		case 2:
			printf("\nEnter the ISBN of the book to delete: ");
			scanf("%s", isbn);
			deleteBook(isbn);
			break;
		case 3:
			printf("\nEnter the ISBN of the book to update: ");
			scanf("%s", isbn);
			printf("Enter the feature to update (title, author, publication year): ");
			scanf(" %[^\n]s", feature);
			printf("Enter the new value: ");
			scanf(" %[^\n]s", value);
			updateBook(isbn, feature, value);
			break;
		case 4:
			printf("\nFilter and Sort Options:\n");
			printf("0. Filter by Author\n");
			printf("1. Filter by Publication Year\n");
			printf("Enter your choice: ");
			scanf("%d", &filterChoice);
			printf("Enter the filter value: ");
			scanf(" %[^\n]s", filter);
			printf("\nSort Options:\n");
			printf("0. Sort by Title\n");
			printf("1. Sort by Author\n");
			printf("2. Sort by Publication Year\n");
			printf("Enter your choice: ");
			scanf("%d", &sortChoice);
			filterAndSortBooks(filterChoice, filter, sortChoice);
			break;
		case 5:
			reverseBookList();
			break;
		case 6:
			printf("\nSearch Options:\n");
			printf("0. Search by ISBN\n");
			printf("1. Search by Author\n");
			printf("2. Search by Title\n");
			printf("Enter your choice: ");
			scanf("%d", &searchChoice);
			printf("Enter the search value: ");
			scanf(" %[^\n]s", searchValue);
			searchBooks(searchChoice, searchValue);
			break;

		case 7:
			printf("\nEnter the ISBN of the book to borrow: ");
			scanf("%s", isbn);
			borrowBook(isbn);
			break;

		case 8:
			printf("\nEnter the ISBN of the book to return: ");
			scanf("%s", isbn);
			returnBook(isbn);
			break;

		case 9:
			printf("\nEnter the student ID: ");
			scanf("%d", &studentId);
			displayStudentBooks(studentId);

			break;
		case 10:
			registerStudent();
			break;
		case 0:
			printf("\nThank you for using the library!\n");
			break;
		default:
			printf("\nInvalid choice. Please try again.\n");
			break;
		}

		printf("\n");
	} while (choice != 0);

	return 0;
}
