#include <iostream>
#include <iomanip>
// Jacob Sprouse
// Auburn ID: 904034415
// project1_Sprouse_jms0338.cpp
// <Add the compilation instructions later>


int main() {
    // Table labels in an array
    std::string labels[] = {"Month", "Balance", "Payment", "Rate", "Interest", "Principal"};


    double loan_amount;
    double rate;
    double monthly_payment;
    int month = 0;
    double interest_total = 0;

    int title_rows = 3;

    // Input the loan amount
    std::cout << "Loan amount: ";
    std::cin >> loan_amount;

    // Input the interest amount
    std::cout << "Interest Rate (% per year): ";
    std::cin >> rate;

    // calculate interest per year
    rate /= 1000;

    // Input the monthly payment
    std::cout << "Monthly Payment: ";
    std::cin >> monthly_payment;

    // Loop to print the title Amortization table
    for (int i = 0; i < title_rows; i++){
        if (i == 1){
            std::cout << std::setw(30)
                      << "Amortization Table" << std::endl;
        }
        else{
            for (int j = 0; j < 39; j++){
                std::cout << "* ";
            }
            std::cout << std::endl;
        }
    }

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

    // Loop to calculate the month, balance, payment, rate, interest, principal
    while (loan_amount >= 0){
        double interest = loan_amount * rate;
        double principal = monthly_payment - interest;


        // prints the month, loan amount, payment, rate, interest and principal
        std::cout << std::setw(12) << std::left << month << "$" << loan_amount << std::endl;
                  /*<< std::setw(13) << monthly_payment << std::setw(18)
                  << rate << std::setw(14) << interest << std::setw(14) << principal
                  << std::endl; */


        // updates the loan amount by the principal and increases the month
        loan_amount -= principal;
        month++;
        interest_total += interest;
    }

    // print the last line of asterisks to mark the end of the Amortization table
    for (int i = 0; i < 39; i++){
        std::cout << "* ";
    }
    std::cout << "\n\n";

    // Print the final output, how long it took and the total interest paid
    std::cout << "It takes " << month << " months to pay off the loan." << std::endl;
    std::cout << "Total interest paid is: $" << interest_total << std::endl;

    return 0;
}