// This is a console based stock portfolio manager that allows the user to manage their investment portfolio, including adding, deleting, and viewing stocks, as well as calculating the total portfolio value.
// Language: C++
// Sources : Assistance with debugging the removal of stocks from the portfolio was provided by an AI chatbot (OpenAI's ChatGPT). ChatGPT helped me out in being able to make the menu neater and more user friendly, see the printport() function down below along with comments. ChatGPT helped guide me to implement essential functions such as stod() and the try{}catch{} functions which helped with the calculation of portfolio sum, see my new understanding of these functions and how they work below.

#include <iostream>
#include <iomanip> // Allows me to manipulate outputs for making the menu more aligned, see printport function down below. This is also used for the setprecision(2) function which helped allow my calculation for total portfolio value to have 2 decimal places. (sourced from ChatGPT)

using namespace std;

// Function Prototypes
void printport(string[][3], int, int);
bool checkfull(string[][3]);
bool checkempty(string[][3]);
bool checkduplicate(string[][3], string);
void printsymbols(string[][3]);
double calculatetotalportfolio(string[][3], int);

int main(){
    
    // Defining our variables and their classes
    bool keepgoing = true;
    int menu = 0;
    bool menu_stop = false;
    bool proceed = true;
    
    // Defining our Array as a string
    string portfolio[10][3] = {
        
        {"-", "-", "-"},
        {"-", "-", "-"},
        {"-", "-", "-"},
        {"-", "-", "-"},
        {"-", "-", "-"},
        {"-", "-", "-"},
        {"-", "-", "-"},
        {"-", "-", "-"},
        {"-", "-", "-"},
        {"-", "-", "-"}
        
        /* Example of what I want to be outputted
         {'A', '4', '23.43'},
         {'APPL', '2', '95.43'},
         {'AAD', '9', '340.39'},
         {'CCRN', '2', '89.34'},
         {'CCTG', '4', '32.43'},
         {'DG', '2', '1.23'},
         {'PP', '9', '43.23'},
         {'FN', '11', '54.34'},
         {'NFL', '12', '34.23'},
         {'RBLX', '19', '24.12'}
         */
    };
    
    // While loop to ensure that the menu will always be printed along with the option to choose an action after the user completes one task (that isn't to exit the menu)
    while(menu_stop == false){
        
        // I chose to personally go with the use of strings in the menu due to the complexities of having multiple different object classes within an array when using C++ (E.G having a string, integer, and double all in the same matrix)
        string symbol = " ";
        int shares = 0;
        double price = 0.00;
        string deletion = " ";
        
        cout << "  \n";
        cout << "************************************************* \n";
        cout << " \n";
        cout << "             Stock Portfolio Manager \n";
        cout << " \n";
        cout << "Please choose a number from the following options: \n";
        cout << " \n";
        cout << "1. Add Stock \n";
        cout << "2. Remove Stock \n";
        cout << "3. View Portfolio \n";
        cout << "4. Calculate Total Profit \n";
        cout << "5. Exit \n";
        cout << " \n";
        cout << "************************************************* \n";
        cout << " \n";
        // User can input their option which will take root in the int menu variable declared in the beginning of the code
        cin >> menu;
        
        // A switch statement connected to the menu variable being inputted above which will correlate with the given action called by the user
        switch(menu){
            // if the user wants to add a stock
            case 1:{
                
                // Turning the proceed and keepgoing boolean variables back to true in order to ensure consistency when the customer chooses to add another stock afterwards
                proceed = true;
                keepgoing = true;
                
                // If statement which will use our checkfull function below and if true will turn keepgoing to false if the portfolio is full therefore preventing the while loop below from running and going through the process of adding a stock, this was done to make sure the user can be safely returned to the menu in order to remove a stock
                if(checkfull(portfolio) == true){
                    cout << "Your portfolio is full and therefore you cannot add anymore stocks." << endl;
                    keepgoing = false;
                }
                // While loop where if keepgoing = true then we will proceed with allow the user to input their stock symbol
                while(keepgoing == true){
                
                cout << "Please enter the symbol held by the stock (E.G APPL, MCRSFT, TSLA, etc...): " << endl;
                cin >> symbol;
                    
                // While loop to prevent user from entering stock as "-" which could cause errors with the checking functions
                while(symbol == "-"){
                    cout << "You cannot add a stock as an empty space, please try again." << endl;
                    cin >> symbol;
                    }
                
                // If the stock symbol the user enters is already within the portfolio then the checkduplicate will return true and therefore stopping the code altogether
                while(checkduplicate(portfolio, symbol) == true){
                    cout << "You've entered a stock which already exists in the portfolio, please try again." << endl;
                    cin >> symbol;
                    // Nested while loop in the case that the user enters "-" again right after being within checkduplicate loop
                    while(symbol == "-"){
                        cout << "You cannot add a stock as an empty space, please try again." << endl;
                        cin >> symbol;
                        }
                }
                    // While loop which will run as long as proceed is = to true
                    while(proceed == true){
                        // checks for an empty space with portfolio[i][0] and will fill in that spot with the user inputted symbol
                        for(int i = 0; i < 10; i++){
                            if(portfolio[i][0] == "-"){
                                portfolio[i][0] = symbol;
                                break;
                            }
                        }
                        // Defining shareStr as our variable which we will use to input into our array along and the double assurance function below.
                        string sharesStr;
                        
                        // This is a function sourced from ChatGPT which will check to make sure the sure input for shares is an integer so we don't get incorrect submissions for the share count of the stock.
                        bool validInput_shares = false;
                        while (validInput_shares == false) { // While validInput_shares is == to false
                            cout << "Please enter the number of shares you have of this particular stock: " << endl; // Ask user to input their stock share count
                            cin >> sharesStr; // Putting user input into sharesStr
                            try { // Doing a try function which will check if a given piece of code will run or not
                                shares = stod(sharesStr); // Checking if it's possible for shares to possible to convert to a double using the stod() function
                                validInput_shares = true; // If the try is successful then it shares will be = to stoi(sharesStr) and the while loop will broken out of by setting validInput_shares to true.
                            } catch (const exception& e) { // catch will be called if the arguement above is invalid
                                cout << "Invalid input. Please enter a valid integer or double." << endl; // I don't mind having a double here as an individual can have a decimal amount of a share for instance, I can have 0.0234 shares of APPL.
                            }
                        }
                        
                        // For loop which loops through every row on column 1 and find an empty space to add the shares number
                        for(int i = 0; i < 10; i++){
                            if(portfolio[i][1] == "-"){
                                portfolio[i][1] = sharesStr; // We will use sharesStr here so it can be inputted into our array without an error, as we do not want to input an integer into our string based array.
                                break;
                            }
                        }
                        // Defining priceStr as our variable which will be used to input into the array along with converstion using the stod() function as seen below.
                        string priceStr;
                        
                        // This is a function sourced from ChatGPT which will check to make sure the sure input for shares is an integer so we don't get incorrect submissions for the share count of the stock.
                        bool validInput_price = false;
                        while (validInput_price == false) {
                            cout << "Please enter the price of each individual stock: " << endl;
                            cin >> priceStr; // Will allow user to input the price (a double)
                            try {
                                price = stod(priceStr); // the try function will try to run a code where price is converted to a double from the string, and if true will break out of the while loop by checking validInput_price to true.
                                validInput_price = true;
                            } catch (const exception& e) { // If the code above fails, the catch will run instead relooping back to the top of the while loop.
                                cout << "Invalid input. Please enter a valid integer or double." << endl;
                            }
                        }
                        
                        // For loop which loops through every row on column 2 and find an empty space to add the price
                        for(int i = 0; i < 10; i++){
                            if(portfolio[i][2] == "-"){
                                portfolio[i][2] = priceStr;
                                break;
                            }
                        }
                        // Setting proceed back to false in order to break us out of the nested while loop above
                        proceed = false;
                    }
                    // Setting keepgoing back to false in order to break us out of the while loop above
                    keepgoing = false;
                    cout << " " << endl;
                    cout << symbol << " has been added to your portfolio." << endl;
                }
                break;
            }
            // If the user wants to remove a stock
            case 2:{
                
                // Setting keepgoing back to true to ensure consistency if the user were to want to remove another stock right after removing one previously
                keepgoing = true;
                
                // checking if portfolio is empty or not
                if(checkempty(portfolio) == true){
                    cout << " " << endl;
                    cout << "Your portfolio is currently empty." << endl;
                    cout << " " << endl;
                    keepgoing = false; // If portfolio is empty we want the rest of the code not to run and to return the user back to the menu so they can add a stock
                }
                
                while(keepgoing == true) {
                    
                    // Having a for loop run to print out all of the symbols within the portfolio for user ease
                    cout << "Here is a list of all of the current stocks in your portfolio" << endl;
                    cout << " " << endl;
                    
                    printsymbols(portfolio);
                    
                    cout << " " << endl;
                    cout << "Enter the symbol of the stock you would like to remove." << endl;
                    cin >> deletion;
                    
                    // While loop to prevent user from entering "-" into the deletion variable
                    while(deletion == "-"){
                        cout << " " << endl;
                        cout << "You cannot delete an empty space please try again." << endl;
                        cin >> deletion;
                    }
                    
                    // For loop which will loop through every row to find all symbols
                    for(int i = 0; i < 10; i++){
                        if (portfolio[i][0] == deletion){
                            portfolio[i][0] = "-";
                            portfolio[i][1] = "-";
                            portfolio[i][2] = "-";
                            cout << " " << endl;
                            cout << deletion << " has been removed from your portfolio." << endl;
                        }
                    }
                // Setting keepgoing = false after the for statement above so we can break out of the while loop above and return to the menu
                 keepgoing = false;
                    }
                    break;
                }
            // User wants to print out their portfolio (matrix)
            case 3:{
                cout << " " << endl;
                // Calling upon our printport function
                printport(portfolio, 10, 3);
                cout << " " << endl;
                break;
            }
            // User wishes to know their total portfolio value
            case 4:{
                
                // Using our function which calculates total portfolio value
                double total = calculatetotalportfolio(portfolio, 10);
            
                // Outputting total portfolio value into the terminal (using setprecision to make sure that ouput has 2 decimal points)
                cout << "Your total portfolio value is: $" << fixed << setprecision(2) << total << endl;

                break;
            }
            // User wishes to exit the program
            case 5:{
                cout << " " << endl;
                cout << "Exiting..." << endl;
                menu_stop = true;
                break;
            }
            default:{
                cout << "Invalid Input, Please try again and choose from one of the numbers from the menu (1, 2, 3, 4, 5)" << endl;
                cout << " " << endl;
                break;
            }
        }
    }
        
        return 0;
}
    

    // Function to print the entire stock portfolio matrix neatly aligned with the assistance of Chatgpt. I originally used a basic function which loops through the rows and cols with a nested for loop but found that the output in the terminal looked less like a list and looked uneven depending on the length of the symbol names
    void printport(string array[][3], int rows, int cols){
        
        // Set the width for each field to ensure alignment no matter the input length
        int symbolWidth = 10; // Width for the symbol field
        int sharesWidth = 10; // Width for the shares field
        int priceWidth = 10; // Width for the price field
        
        // Loop through each row of the matrix
        for(int i = 0; i < rows; i++){
            // Print the symbol with appropriate width using setw()
            cout << setw(symbolWidth) << array[i][0] << " "; // col 0
            // Print the shares with appropriate width using setw()
            cout << setw(sharesWidth) << array[i][1] << " "; // col 1
            // Print the price with appropriate width using setw()
            cout << setw(priceWidth) << array[i][2] << " "; // col 2
            cout << endl; // Move to the next line after printing all fields of a stock
        }
        
        return;
    }
    
    
    // Checks if the stock manager is full or not (referenced from my Tic Tac Toe Code for checking for draws)
    bool checkfull(string array[][3]){
        
        for(int i = 0; i < 10; i++){ // Will loop through the rows of the array
            for(int j = 0; j < 3; j++){ // Will loop through the columns of the array
                if(array[i][j] == "-"){ // Will check if any row or column in the stock manager has a "-"
                    return false;
                }
            }
        }
        return true; // If matrix does not have any "-" left it will be considered true.
    }

    // Checks if the stock manager is empty or not (reference from Tic Tac Toe Code for checking for draws)
    bool checkempty(string array[][3]){
        
        for(int i = 0; i < 10; i++){ // loops through rows
            for(int j = 0; j < 3; j++){ // loops through columns
                if (array[i][j] != "-"){ // checks if rows are NOT equal to "-" and if so it will return false to show the array is not empty
                    return false; // If all rows are not equal to "-"
                }
            }
        }
        return true; // If all rows are equal to "-"
    }
    
    // Checks if there is a duplicate using the symol parameter as a holder for what the user will input when adding a new stock
    bool checkduplicate(string array[][3], string symbol){
    for(int i = 0; i < 10; i++){ // checks each row beginning and checks if the value is equal to the symbol the user inputted
        if(array[i][0] == symbol){
            return true; // Returns true if the already existing symbol is = to the user input
            }
        }
        return false; // Returns true if the already existing symbol is NOT equal to the user input
    }
    
    // Function which prints out all of the symbols within the array
    void printsymbols(string array[][3]){
        for(int i = 0; i < 10; i++){
            cout << array[i][0] << endl; // prints out every content of the array in row i and col 0
        }
        return;
    }

    // Function which will allow us to calculate the sum of all of the stocks within the portfolio
    double calculatetotalportfolio(string array[][3], int rows){
    // Defining our double variables of sum and totaly amount
    // Sum which will be added up after each loop of the for loop
    double sum = 0.0;
    // Total amount which will be the shares multiplied by the price of each individual stock to get an accurate sum of each row
        
        // For loop will loop through the rows of the matrix
        for(int i = 0; i < rows; i++){
            
            // we will use a try function, as there may be cases where the entire array is not full and therefore we don't want "-" values to break this function.
            try {
                // Price will be converted to doubles to allow us to do our calculations
                double price = stod(array[i][2]);
                // Shares will be converted to integers to allow us to do our calculations
                double shares = stod(array[i][1]);
                // We will multiply our shares by our prices to give an accurate estimated of the current worth of each row
                double totalamount = price*shares;
                // We add the totalamount to our sum variable and move onto the next row
                sum += totalamount;
            }
            // Will catch if there is an error in the code above such as "-" being the value of any of the prices and shares and ignoring those calculations
            catch(const exception& e){
            }
        }
    
    return sum;
    }

