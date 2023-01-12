#include <iostream>
#include <fstream>
#include <string> 
#include <iomanip>
#include <cstdlib>
using namespace std;

// Global constants
const int FOOD = 15;					// represents the row of the menu
const int COL = 4;						// represents the column of the menu

// Function prototype
void mainMenu(int[FOOD]);
void menuView(string[][COL], int&);

void managerView(string[][COL], int);
void menuUpdate(string[][COL], int);
void priceUpdate(string[][COL], int);
bool acceptOrder(string[][COL], int, int, int[FOOD]);
double totalPayments(string[][COL], int, double, double &);
int deliveryTime(string[][COL], int, int, int&);
void totalSalesDay(double, double&);
int popularDish(string[][COL], int, int, int[FOOD]);

void customerView(string[][COL], int, int[FOOD]);
void makeOrder(string[][COL], int, int[FOOD]);
void payment(string[][COL], int, double, int[FOOD], int, int);
void displayMessage (string[][COL], int, double, int);

// Main function	
int main(){					
		
	int popularFood[FOOD];						// initialise the popularFood array
	
	for (int i = 0; i < FOOD; i++){	
			
		popularFood[i] = 0;						// set all the content to 0 in the popularFood array
		
	}

	mainMenu(popularFood);						// call the mainMenu function

	return 0;
}

// **************************************************************************************
//									Main Menu Access
// **************************************************************************************

void mainMenu(int popularFood[FOOD]){
	
	int num_food = 0;							// initialise the number of food that will display in the menu to 0
	
	string nameFoodPrice[FOOD][COL];			// declare the two-dimensional array which contains the content of name of food,
//												// price of food, delivery time and the stock of food
												
	int choice;									// declare the user's choice

	cout <<"\t   __      __        __\n";
	cout <<"\t  /  \\    /  \\ ____ |  | ____  ____    _____   ____ \n";						// Greet the user				
	cout <<"\t  \\   \\/\\/   // __ \\|  |/ ___\\/  _ \\  /     \\ / __ \\\n";
	cout <<"\t   \\        /|  ___/|  |  \\__(  <_> )|  Y Y  | ___ /  \n";
	cout <<"\t    \\__/\\__/  \\____\\|__|\\_____>____/ |__|_|__|\\____\\\n";
	cout <<" ----------------------------------------------------------------- "<< endl; 

	cout << "\t		  Burger Restaurant	" << endl << endl;					// Display the message and ask user to select a choice
	cout << "1. Restaurant Manager" << endl;
	cout << "2. Customer " << endl;
	cout << "3. Exit" << endl << endl;
	cout << "Please enter the number to select the user or enter 3 to exit: ";
	cin >> choice;																// Enter the choice
	
	while (choice != 1 && choice != 2 && choice != 3){					// when the user's choice !=1 and !=2 and !=3
		cout << "Invalid number. Please try again!" << endl;			// Ask the user to enter the choice again
		cin >> choice;													// Enter the choice
	}
	
		if (choice == 1){										// If the choice is 1
			cout << endl << endl;										
			system("pause");									// clear the screen 
			system("CLS");
			managerView(nameFoodPrice, num_food);				// call managerView function

		}
			
		if (choice == 2){										// If the choice is 2
			cout << endl << endl;	
			system("pause");									// clear the screen		
			system("CLS");
			menuView(nameFoodPrice, num_food);					// call the menuView function
			customerView(nameFoodPrice, num_food, popularFood); // call the customerView function

		}

		if (choice == 3){										// If the choice is 3
			cout << "Thank you! Please come again! " << endl;	// Thanks the user
			cin.ignore();
		}	

}

// **************************************************************************************
//									Manager Access
// **************************************************************************************

void managerView(string nameFoodPrice[][COL], int num_food){			
	
	int managerChoice;											// declare the managerChoice variable
	
	cout << "\t\t Manager Access " << endl << endl;				// display the message
	cout << "1. Create / Update Menu " << endl;
	cout << "2. Update Prices " << endl << endl;
	
	cout << "Please select a number for further details: ";		// ask the user to select a number
	cin >> managerChoice;										// enter a number

	while(managerChoice != 1 && managerChoice !=2){				// If managerChoice is not equal to 1 and 2
		cout << endl;
		cout << "Invalid number! Please try again! " << endl;	// Print the message out to ask user enter the number again
		cin >> managerChoice;									// Enter the number again
		}	
		
		if(managerChoice == 1){									// If managerChoice is equal to 1
			cin.ignore();
			cout << endl << endl;
			system("pause");									// clear the screen
			system("CLS");
			menuUpdate(nameFoodPrice, num_food);				// call menuUpdate function
		}
		else{
			cout << endl << endl;
			system("pause");									// clear the screen
			system("CLS");
			menuView(nameFoodPrice, num_food);					// call menuView function
			priceUpdate(nameFoodPrice, num_food);				// call priceUpdate function
		}

	
}

// **************************************************************************************
//									Food Menu Access
// **************************************************************************************

void menuView(string nameFoodPrice[][COL], int &num_food){	
	
	ifstream inFile;								// Open the text file named MenuFood.txt to read through the file
	inFile.open("MenuFood.txt");	
	
	if (inFile){								
		
		int i = 0;									// Initialise i = 0
		
	while (inFile){
		
		int j = 0;									// Initialise j = 0
	
		getline(inFile, nameFoodPrice[i][j], '\t');			// Read the name of food 
		getline(inFile, nameFoodPrice[i][j+1], '\t');		// Read the price of food
		getline(inFile, nameFoodPrice[i][j+2], ' ');		// Read the delivery time of food
		getline(inFile, nameFoodPrice[i][j+3]);				// Read the stock of food
		i++;												// i = i + 1
		num_food++;											// number of food increment by 1

		inFile.ignore();
		}	
		
	}
	else{
		cout << "Error when opening the file " << endl;		// Display message when the file cannot be opened
		}		
		
}

// **************************************************************************************
//									Food Menu Updation 
// **************************************************************************************
 
void menuUpdate(string nameFoodPrice[][COL], int num_food){
	
	int timeDelivery, stockFood;							// timeDelivery represents the estimated delivert time 
//															//	and stockFood represent the stock of the food
	char choice;
	string newFoodName;
	double newFoodPrice;
		
	ofstream outFile;										// Open the file named MenuFood.txt
	outFile.open("MenuFood.txt", ios_base::app);			// append
	
	for (int i = 0; i < num_food; i++){						// check the condition (i < number of food ) and increment i by 1
		
		for (int j = 0; j < COL; j++){ 						// check the conditon ( i < column ) and increment j by 1
			
			if(j == 1){										// if j is 1
				outFile << '\t';							
				outFile << nameFoodPrice[i][j];				// Write the name of food into file
			}
			
			else if(j == 2){
				outFile << '\t';
				outFile << nameFoodPrice[i][j];				// Write the price of food into file
			}
			
			else if (j == 3){	
				outFile << ' ';
				outFile << nameFoodPrice[i][j];				// Write the delivery time of food into file
			}
			else{
				outFile << ' ' << nameFoodPrice[i][j];		// Write the stock of food into file
			}
		} 
		outFile << '\n';									// move to next line
	}
		
	do{
	cout << endl << "Please enter a new food name: " ;							// Ask the user to enter a new food name
	getline(cin, newFoodName); 													// Enter the new food name
	
	cout << "Please enter the price of the food: RM ";							// Ask the user to enter the price of the food
	cin >> newFoodPrice;														// Enter the price of the food
	cout << endl;
	
	while (newFoodPrice < 4 || newFoodPrice > 30){								// If the price of food is less than RM 4 or more than RM 30
		
		cout << "The price of the food must be set in the range from " 			// Display message to prompt user to enter the price of the food again
		<< "RM 4 to RM 30 " << endl; 
		cout << "Please set the price of the food again: RM ";					
		cin >> newFoodPrice;													// Enter the food price again
		cout << endl;
	}
	
	cout << "Please enter the estimated delivery time of the food (in minutes): ";	// Ask the user to enter the estimeated delivery time of the food
	cin >> timeDelivery;															// Enter the delivert time
	
	while (timeDelivery < 5 || timeDelivery > 30){									// If the estimated delivery time is less than 5 min or more than 30 min
		
		cout << "The delivery time for the food must be set in the range from " 	// Display message to prompt user to enter the delivery time of the food again
		<< "5 minutes to 30 minutes " << endl; 
		cout << "Please set the delivery time again: ";
		cin >> timeDelivery;														// Enter the estimated delivery time of the food again
		cout << endl;
		
	}
	
	cout << "Please enter the stock of the food: ";									// Ask the user to enter the stock of the food
	cin >> stockFood;																// Enter the stock of the food
	cout << endl;
	 
	outFile << setprecision(2) << fixed << showpoint;
	outFile << '\n';
	outFile << ' ' << newFoodName << '\t' << newFoodPrice << '\t' << timeDelivery << ' ' << stockFood;	// Write all the information into the file
	
	cout << "Would you like to add another food? (Y/N) Your choice: ";				// Ask user whether want to add another food or not
	cin >> choice;
	
	while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n'){		// If user enter other than 'Y', 'y', 'n' and 'N'
		cout << "Invalid ! Please try again! " << endl;								// Print out the invalid message and ask user to enter the choice again
		cin >> choice;																// Enter the choice
		}
		
	cin.ignore();
		
	} while (choice == 'Y' || choice == 'y');
	
	cout << endl << "Update Successfully! Please check the updated menu " << endl;	// Display the message that shows the menu is updated successfully
}

// **************************************************************************************
//									Food Price Udpation
// **************************************************************************************

void priceUpdate(string nameFoodPrice[][COL], int num_food){	

	cout << "--------------------------------------------------" << endl;			// Display the food menu
	cout<<"          _____\n";
    cout<<"         /     \\   ____   ____    __ __\n";
    cout<<"        /  \\ /  \\_/ __ \\ /     \\ |  |  |\n";
    cout<<"       /    Y    \\  ___/|   |   \\|  |  |\n";
    cout<<"       \\____|____/\\____>____|____|_____|\n\n";
	cout << "--------------------------------------------------" << endl;
	
		for (int x = 0; x < num_food; x++){
			cout << "Food " << x + 1 << ": ";
			
			for (int y = 0; y < COL - 2; y++){
			
			cout <<	nameFoodPrice[x][y] << "\t\t";
		
			if (y = 1){
				
				if (x < 3){	
				cout << "RM " << nameFoodPrice[x][y];
				}
				
				else{
					cout << "\tRM " << nameFoodPrice[x][y];
				}
			}
		
		cout << endl;
			}
		
		}
		
	cout << endl;

	int updateChoice;																// Declaration of variable
	double updatePrice;

	cout << "Please enter the number available in order to update the food price: Food ";	// Ask user to enter the number available in food menu
	cin >> updateChoice;																	// Enter the choice
	
	while (updateChoice < 1 || updateChoice > num_food){							// If the choice < 1 or choice > number of food shown in food menu
		
		cout << "Invalid number. Please enter again: Food ";						// Ask the user to enter the choice again
		cin >> updateChoice; 
	}
	
	cout << "Please enter the new price for the dish: RM ";							// Ask the user to enter the new price of the dish
	cin >> updatePrice;
	
	while (updatePrice < 4 || updatePrice > 30){									// If the price is less than RM 4 or more than RM 30
		
		cout << "The price of the dish must be updated in the range from " 			// Display the message to prompt user to enter the price again
		<< "RM 4 to RM 30 " << endl; 
		cout << "Please update the price of the dish again: RM ";
		cin >> updatePrice;															// Enter the price again
		cout << endl;
	}
	
	updateChoice--;																	// The choice is decrement by 1 because the array is start from 0
		
	ifstream inFile;																// Open the file
	inFile.open("MenuFood.txt");
	
	ofstream outFile;																// Create another temporary file
	outFile.open("TempMenuFood.txt");
	
	if (inFile){
		
		int i = 0;
		
	while (inFile){
		
		int j = 0;
	
		getline(inFile, nameFoodPrice[i][j], '\t');									// Read the content of the file
		getline(inFile, nameFoodPrice[i][j+1], '\t');
		getline(inFile, nameFoodPrice[i][j+2], ' ');
		getline(inFile, nameFoodPrice[i][j+3]);
		
		outFile << setprecision(2) << fixed << showpoint;
		if (updateChoice == i){																			// if the choice is equal to i
			outFile << ' ' << nameFoodPrice[i][j] << '\t'
			<< updatePrice << '\t' << nameFoodPrice[i][j+2] << ' ' << nameFoodPrice[i][j+3] << '\n';	// Write all the information including the updated price
			}																							// into the file
			
		else{
			outFile << ' ' << nameFoodPrice[i][j];											// Write all the information into the file
			outFile << '\t' << nameFoodPrice[i][j+1] << '\t' << nameFoodPrice[i][j+2] 
			<< ' ' << nameFoodPrice[i][j+3] << '\n';
			}
			
		i++;
		
		inFile.ignore();
		}	
			
	}
	
	else{
		cout << "Error when opening the file..." << endl;							// Display error message when the file cannot be opened
		}

	inFile.close();																	// Close the file
	outFile.close();
	remove("MenuFood.txt");															// Remove the MenuFood text file
	rename("TempMenuFood.txt", "MenuFood.txt");										// Rename the TempMenuFood to MenuFood text file
	
	cout << "Update Successfully! Kindly check the updated menu " << endl;			// Display the message to show the menu is updated successfully
}

// **************************************************************************************
//									Accept Order Function
// **************************************************************************************

bool acceptOrder(string nameFoodPrice[][COL], int num_food, int arrFoodChoice, int stockFood[FOOD]){
	
	bool status = true;													// initialise the status to true
	

	for (int i = 0; i < FOOD; i++){
			
		if (i == arrFoodChoice){										// If i is equal to the arrchoice made by customer
			stockFood[i]--;												// Stock of the food is decrement by 1
				
			if (stockFood[i] < 0){										// If the stock of the food is less than 0
				status = false;											// Set status to false
			}
				
			else{
				status = true;											// Set status to true
			}
		}
			
	}

	return status;														// Return the status to makeOrder function
}

// **************************************************************************************
//								Total Payments Calculation
// **************************************************************************************

double totalPayments(string nameFoodPrice[][COL], int arrFoodChoice, double orderPrice, double &newOrderPrice){
	

	orderPrice = strtod(nameFoodPrice[arrFoodChoice][1].c_str(), NULL);			// Change the price stored in array from string to double 
//																				// and assign it to orderPrice
	newOrderPrice += orderPrice;					// the new order price is always updated	
	
	return newOrderPrice;							// return the new order price and back to makeOrder function
	
}

// **************************************************************************************
//							Total Estimated Delivery Time Calculation
// **************************************************************************************

int deliveryTime(string nameFoodPrice[][COL], int arrFoodChoice, int estimatedTime, int &newEstimatedTime){
	
	estimatedTime = strtod(nameFoodPrice[arrFoodChoice][2].c_str(), NULL);			// convert from string to integer
	newEstimatedTime += estimatedTime;									// Updation
	
	return newEstimatedTime;						// return the integer value which represent the estimated delivery time
}

// **************************************************************************************
//									Customer Menu Access
// **************************************************************************************

void customerView(string nameFoodPrice[][COL], int num_food, int popularFood[FOOD]){
	
	char orderFoodChoice;									// Represent the choice made by customer
	
	cout << "--------------------------------------------------" << endl;				// Display the menu
	cout<<"          _____\n";
    cout<<"         /     \\   ____   ____    __ __\n";
    cout<<"        /  \\ /  \\_/ __ \\ /     \\ |  |  |\n";
    cout<<"       /    Y    \\  ___/|   |   \\|  |  |\n";
    cout<<"       \\____|____/\\____>____|____|_____|\n\n";
	cout << "--------------------------------------------------" << endl;
	
		for (int x = 0; x < num_food; x++){
			cout << "Food " << x + 1 << ": ";
			
			for (int y = 0; y < COL - 2; y++){
			
			cout <<	nameFoodPrice[x][y] << "\t\t";
		
			if (y = 1){
				
				if (x < 3){	
				cout << "RM " << nameFoodPrice[x][y];
				}
				
				else{
					cout << "\tRM " << nameFoodPrice[x][y];
				}
			}
		
		cout << endl;
			}
		
		}
	cout << endl << "Welcome! New Customer! :)" << endl;							// Welcome the customer
	cout << "Would you like to make food order? (Y/N) " << endl;					// Ask the user to enter the choice
	cout << "Press Y or to make food order or press N to exit. Your choice: ";	
	cin >> orderFoodChoice;
		
		while(orderFoodChoice != 'Y' && orderFoodChoice != 'y' && orderFoodChoice != 'N' && orderFoodChoice != 'n'){  // IF the user the choice other than Y,y,N and n
		cout << "Invalid choice ! Please try again! Your choice: ";												// Ask the user to enter again
		cin >> orderFoodChoice;
		}
		
		if (orderFoodChoice == 'Y' || orderFoodChoice == 'y'){						// If choice is equal to Y or y
			makeOrder(nameFoodPrice, num_food, popularFood);						// Call makeOrder function
		}
		
		else {
		cout << endl << "Thank you! Please come again! :D" << endl;					// Thanks the customer 
		}
	
}

// **************************************************************************************
//									Customers make order
// **************************************************************************************

void makeOrder(string nameFoodPrice[][COL], int num_food, int popularFood[FOOD]){
	
	// Declaration of variable
	const int NUM_ORDER = 15;
	char confirm, paymentChoice;
	int foodChoice, arrFoodChoice;
	int totalDeliveryTime, estimatedTime, newEstimatedTime = 0;
	static int num_customers = 0;
	int num_orders_customers = 0;
	double orderPrice, newOrderPrice = 0, totalPay;
	bool orderFlag;
	int num_most_popular_dish;
	int stockFood[FOOD];
		
	for (int i = 0; i < num_food; i++){						
	
		if (i < num_food){	
		
			stockFood[i] = stoi(nameFoodPrice[i][3]);			// Write the stock of food into stockFood array
		}
		
		else{
			stockFood[i] = 0;									// Set stockFood[i] to 0 if  i is more than the number of food shown in menu
		}
	}


	do{	
		cout << endl;
		cout << "Please enter the number as shown in menu to order the food: "; 	// Ask the user to enter the number shown in food menu
		cin >> foodChoice;
	
		while (foodChoice < 1 || foodChoice > num_food){							// If the choice is less than 1 or more the number of food shown in food menu
		
		cout << "Invalid number. Please enter the number again: Food ";				// Ask the user to enter the number again
		cin >> foodChoice; 
		}
		
		arrFoodChoice = foodChoice - 1;										// The choice made by customer is decrement by 1 to access the array
	
		cout << setprecision(2) << fixed << showpoint;
		cout << "You order of food is " << nameFoodPrice[arrFoodChoice][0] << endl;		// Display the order food made by customer
		
		totalPay = totalPayments(nameFoodPrice, arrFoodChoice, orderPrice, newOrderPrice);					// Call totalPayments function
		totalDeliveryTime = deliveryTime(nameFoodPrice, arrFoodChoice, estimatedTime, newEstimatedTime);	// Call deliveryTime funciton
		num_most_popular_dish = popularDish(nameFoodPrice, num_food, arrFoodChoice, popularFood);			// Call popularDISH funciton
		orderFlag = acceptOrder(nameFoodPrice, num_food, arrFoodChoice, stockFood);							// Call acceptOrder funciton
	
		if (orderFlag == true){											// If the return bool value is true
		cout << "Order Accepted! " << endl;								// Print the message which is "order accepted"
		}
		
		else{
		cout << "Out of stock! You will be returned to main menu " << endl;	// Display the message and return to the main menu 
		system("pause");
		system("CLS");					// clear the screen
		mainMenu(popularFood);			// call mainMenu function
		}
		
		cout << "The total price is RM" << totalPay << endl << endl;			// Display the total price of order
		cout << "Would you like to add more? (Y/N)" << endl;					// Ask the user whether the user want to add another order or not
		cin >> confirm;
		
		while(confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n'){   // IF the user the choice other than Y,y,N and n 
		cout << "Invalid ! Please try again! " << endl;								// Ask the user to enter the choice again
		cin >> confirm;
		
		}
		
		num_orders_customers++;													// Number of orders made by customer is increment by 1
		} while (confirm == 'Y' || confirm == 'y');
		
		num_customers++;														// Number of customer is increment by 1
		
		cout << endl << "You have ordered " << num_orders_customers << " dish(es) " << endl;		// Display the message of number of orders,
		cout << "Estimated delivery time is " << totalDeliveryTime << " minutes" << endl;		 	// estimated delivery time,	
		cout << "The total payment is RM " << totalPay << endl << endl;								// total payment 
		cout << "Press P to make your payment: ";									// Ask user enter 'P' to make payment
		cin >> paymentChoice;
		
		while(paymentChoice != 'P' && paymentChoice != 'p'){						// If the user enter alphabet is not equal to 'p' and 'P'
			cout << "Invalid! Please try again! " << endl;						// Ask the user to enter again
			cin >> paymentChoice;
		}
		
		cout << endl << endl;
		system("pause");
		system("CLS");														// clear the screen
		payment(nameFoodPrice, num_food, totalPay, popularFood, num_customers, num_most_popular_dish);		// Call the payment function
}

// **************************************************************************************
//									Customers make payment
// **************************************************************************************

void payment(string nameFoodPrice[][COL], int num_food, double totalPay, int popularFood[FOOD], int num_customers, int num_most_popular_dish){
	
	double pay; 														
	static double sales = 0;
	
	cout << "Please enter the amount of your payment: RM ";			// Ask the user the enter the amount of payment
	cin >> pay;
	
	while (pay != totalPay){										// If the payment entered is not the same as the amount of payment of order
		
		cout << "Invalid amount! Please enter the exact amount of your payment: RM ";	// Ask the user to enter the amount of payment again
		cin >> pay; 
	}
	
	totalSalesDay(totalPay, sales);														// Call totalSalesDay function
	displayMessage(nameFoodPrice, num_customers, sales, num_most_popular_dish);			// Call displayMessage function
	
	cout << "Payment successful! " << endl;									// Display message which indicates the payment is made successfully
	cout << "Please come again! :D " << endl;
	
	cout << endl << endl;
	system("pause");
	system("CLS");														// clear the screen
	customerView(nameFoodPrice, num_food, popularFood);					// call customerView function
	
}

// **************************************************************************************
//									Total Sales Calculation
// **************************************************************************************

void totalSalesDay(double totalPay, double &sales){
	
	sales += totalPay;											// The total sales is always updated when this funciton is called
		
}

// **************************************************************************************
//									Determine Popular Dish
// **************************************************************************************

int popularDish(string nameFoodPrice[][COL], int num_food, int arrFoodChoice, int popularFood[FOOD]){	
	
	int mostPopular, numMostPopular;					// Declaration of variable
	
	
	popularFood[arrFoodChoice]++;						// popularFood array is increment by 1 for the food order made by customer
		
	mostPopular = popularFood[0];						// Default most popular dish	
	
	
	for (int x = 1; x < FOOD; x++){
			
		if (mostPopular < popularFood[x]){				// Find the most popular dish
				
			mostPopular = popularFood[x];				// set the number of most popular dish 
			numMostPopular = x;							
				
			}
			
	}
	
	return numMostPopular;								// return the numbering of the most popular food
}

// **************************************************************************************
//									Output the file 
// **************************************************************************************

void displayMessage (string nameFoodPrice[][COL], int num_customers, double sales, int num_most_popular_dish){
	
	ofstream outFile;									// open the OutputFile text file
	outFile.open("OutputFile.txt");
	
	outFile << "Number of customers for the day: " << num_customers << endl;					// Write the number of customer for the day
	outFile << setprecision(2) << fixed << showpoint;
	outFile << "The total sales is RM " << sales << endl;										// Write the total sales
	outFile << "The most popular dish is " << nameFoodPrice[num_most_popular_dish][0] << endl;	// Write the most popular dish
	
	outFile.close();									// Close the file
}
