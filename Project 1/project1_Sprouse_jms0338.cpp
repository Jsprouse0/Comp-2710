#include <iostream>
#include <iomanip>
#include <string>
// Jacob Sprouse
// Auburn ID: jms0338
// project1_Sprouse_jms0338.cpp
/* Compilation Instructions:
 * $> scp file/path/in/local/machine <auburn id>@scp.eng.auburn.edu:/file/destination/auburn id
 * copy file to auburn server.
 * $> g++ project1_Sprouse_jms0338.cpp
 * Compile the project
 * Find the a.out file
 * $> ./a.out
 * run the file in the terminal
 */

void print_table(int month, double balance, double payment, double rate, double interest, double principal) {
    /* Params: month - int type that is referenced in the calculate_table function to the variable in main to be printed
     * Params: payment - double type argument to print the monthly payment
     * Params: Rate - double type argument for the interest rate in %
     * Params: Interest - double type, interest accrued every month based on the loan amount
     * Params: Principal - double type argument for the principal paid to the loan after interest paid by monthly amount
     *
     * Description: Void function to print the month - rows; and values - columns, of the amortization loan table
     *
     * Return: None
     */

    std::cout << std::fixed << std::setprecision(2);  // sets the precision of the table to 2 decimal places

    // since the first month is the start of the payment, there is no interest nor payment made
    if (month == 0) {
        std::cout << std::left << std::setw(10) << month
                  << std::right << std::setw(3) << "$" << std::setw(5) << balance
                  << std::right << std::setw(10) << "N/A"
                  << std::right << std::setw(18) << "N/A"
                  << std::right << std::setw(12) << "N/A"
                  << std::right << std::setw(12) << "N/A" << std::endl;
    }
    else {
        std::cout << std::left << std::setw(10) << month
                  << std::right << std::setw(3) << "$" << std::setw(7) << balance
                  << std::right << std::setw(9) << "$" << std::setw(7) << payment
                  << std::right << std::setw(16) << rate
                  << std::right << std::setw(10) << "$" << std::setw(7) << interest
                  << std::right << std::setw(10) << "$" << std::setw(7) << principal
                  << std::endl;
    }
}



double calculate_loan(int& month, double loan_amount, double monthly_payment, double rate, double interest_total=0) {
    /* Params: month - reference type that increments the variable 'month' in main
     * Params: loan_amount - double type that holds the amount of the loan, is decremented by the principal paid after interest
     * Params: monthly_payment - double type for the monthly payment towards the loan & interest.
     * Params: rate - double type for the interest rate in %
     * Params: interest_total - double type that holds the total interest paid over the loan period
     *
     * Description: prints the amortization table, calculates the interest, loan amount, period, total interest paid,
     * and the principal put towards the loan every month till it's zero.
     *
     * Return: Double - Interest_total - returns the double variable interest_total for the total interest paid
     */

    // print the first month with N/A values
    print_table(0, loan_amount, 0, 0, 0, 0);

    // Loop to calculate the month, balance, payment, rate, interest, principal
    while (loan_amount >= 0) {
        double interest  = loan_amount * (rate / 100);
        double principal = monthly_payment - interest;

        // updates the loan amount by the principal and increases the monthly payment
        if (loan_amount < monthly_payment - interest) {
            principal = loan_amount;
            monthly_payment = loan_amount + interest;
        }

        loan_amount -= principal;    // will decrement the amount by the principal paid
        month++;                     // increases the month
        interest_total += interest;  // totals the amount of interest paid
        // calls void function to print the table
        print_table(month, loan_amount, monthly_payment, rate, interest, principal);

        // prevents while loop from entering an infinite loop
        if (loan_amount <= 0) {
            break;
        }
    }
    return interest_total;
}

void print_stars() {
    /*
     * params: none
     * Description: prints asterisks to the console for the table,
     * Return: none
     */
    for (int i = 0; i < 39; i++) {
        std::cout << std::setw(2) << '*';
    }
    std::cout << std::endl;
}


int main() {
    // Table labels in an array
    std::string labels[] = {"Month", "Balance", "Payment", "Rate", "Interest", "Principal"};

    double loan_amount;         // loan balance
    double rate;                // interest rate
    double monthly_payment;     // monthly payment towards the loan
    int month = 0;
    double interest_total = 0;  // Counter for the total interest accrued

    try {
        // Input the loan amount
        std::cout << "Loan amount: ";
        std::cin  >> loan_amount;

        // Throw an invalid argument error for an invalid loan amount
        if (loan_amount < 1) {
            throw std::invalid_argument("Invalid Loan amount");
        }

        // Input the interest amount
        std::cout << "Interest Rate (% per year): ";
        std::cin  >> rate;

        // Throw invalid interest rate argument
        if (rate <= 0) {
            throw std::invalid_argument("Invalid Interest Rate.");
        }

        // Input the monthly payment
        std::cout << "Monthly Payment: ";
        std::cin  >> monthly_payment;
        std::cout << "\n\n";

        // throw illegal argument if monthly payment is negative
        if (monthly_payment < 0) {
            throw std::invalid_argument("Invalid monthly payment.");
        }

        // If monthly payment is less than the monthly interest, throw an error
        if (monthly_payment < loan_amount * rate / 1000) {
            throw std::invalid_argument("Monthly payment is less than Interest accrued. Please Input a larger amount.");
        }

    }catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;  // print error to terminal with illegal argument
        return 1;
    }

    // calculate interest per year
    rate /= 10;

    // call print_stars function to print the '*' of the Amortization table
    print_stars();
    std::cout << std::setw(30) << "Amortization" << std::endl;
    print_stars();


    // Loop to print the first 3 labels of the table
    for (const auto & label : labels){
        // will print the label and separate them appropriately, if it's Rate then it will provide more spacing
        if (label == "Rate"){
            std::cout << std::setw(16) << label << std::setw(14);
        }
        else{
            std::cout << label << std::setw(14);
        }
    }

    // ends line for the labels
    std::cout << "\n";

    // call calculate loan function, return the interest total, save it in a variable.
    interest_total = calculate_loan(month, loan_amount, monthly_payment, rate);

    // print the last line of asterisks to mark the end of the Amortization table
    print_stars();
    std::cout << "\n";

    // Print the final output, how long it took and the total interest paid
    std::cout << "It takes " << month << " months to pay off the loan." << std::endl;
    std::cout << "Total interest paid is: $" << interest_total << std::endl;

    return 0;
}

