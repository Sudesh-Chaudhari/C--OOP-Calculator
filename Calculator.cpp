// CLI Calculator – OOP-based, handles multiple operations (arithmetic, percentage, loan EMI).
/* This program performs basic arithmetic operations: addition, subtraction, multiplication, and division. It also includes advanced functionalities like percentage calculation and loan EMI computation. The program is designed using Object-Oriented Programming (OOP) principles, encapsulating functionalities. Within classes and methods for better organization and reusability. */

#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

class Calculator
{
public:
    double calculate(double num1, double num2, int operation)
    {
        switch (operation)
        {
        case 1:
            return num1 + num2;
        case 2:
            return num1 - num2;
        case 3:
            return num1 * num2;
        case 4:
            if (num2 != 0)
                return num1 / num2;
            else
                throw runtime_error("Division by zero is not allowed.");
        default:
            throw runtime_error("Invalid operation.");
        }
    }

    void clearInputBuffer()
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    template <typename T>
    void checkInput(T &num)
    {
        while (true)
        {
            cin >> num;
            if (cin.fail())
            {
                clearInputBuffer();
                cout << "Invalid input. Please enter valid input: ";
            }
            else
            {
                break;
            }
        }
    }
};

class AdvancedCalculator : public Calculator
{
public:
    double calculatePercentage(double num1, double num2, double percentage)
    {
        double total = (num1 + num2);
        return (total * percentage) / 100.0;
    }

    double calculateEMI(double principal, double annualRate, double tenureMonths)
    {
        double monthlyRate = annualRate / (12 * 100);
        return (principal * monthlyRate * pow(1 + monthlyRate, tenureMonths)) /
               (pow(1 + monthlyRate, tenureMonths) - 1);
    }
};

void promptExit(string &exitChoice)
{
    cout << "Do you want to exit? (yes/no): ";
    cin >> exitChoice;
    transform(exitChoice.begin(), exitChoice.end(), exitChoice.begin(), ::tolower);
}

int main()
{
    Calculator calc;
    int operation, calc_choice, adv_choice;
    double num1, num2, result, percentage, principal, annualRate, tenureMonths;
    string exitChoice;
    do
    {
        cout << "\n================= Calculator Menu =================\n";
        cout << "Select Calculator Type:\n1. Basic Calculator\n2. Advanced Calculator\nChoose: ";
        calc.checkInput(calc_choice);
        switch (calc_choice)
        {
        case 1:
            cout << "Basic Calculator Selected.\n";
            cout << "================= Basic Calculator ================\n";

            cout << "Enter first number: ";
            calc.checkInput(num1);

            cout << "Enter second number: ";
            calc.checkInput(num2);

            cout << "Enter operation:\n"
                 << "1. Addition (+)\n"
                 << "2. Subtraction (-)\n"
                 << "3. Multiplication (*)\n"
                 << "4. Division (/)\n"
                 << "Choose: ";
            calc.checkInput(operation);
            while (operation < 1 || operation > 4)
            {
                cout << "Invalid choice. Please enter (1-4): ";
                calc.checkInput(operation);
            }
            try
            {
                result = calc.calculate(num1, num2, operation);
                cout << fixed << setprecision(2);
                cout << "Result: " << result << endl;
            }
            catch (runtime_error &e)
            {
                cout << "Error: " << e.what() << endl;
            }
            promptExit(exitChoice);
            break;
        case 2:
            cout << "Advanced Calculator Selected.\n";
            AdvancedCalculator advCalc;
            cout << "================= Advanced Calculator ================\n";
            cout << "Select Operation:\n1. Percentage Calculation\n2. Loan EMI Calculation\nChoose: ";
            calc.checkInput(adv_choice);
            while (adv_choice < 1 || adv_choice > 2)
            {
                cout << "Invalid choice. Please enter (1-2): ";
                calc.checkInput(adv_choice);
            }
            if (adv_choice == 1)
            {
                cout << "Enter first number: ";
                calc.checkInput(num1);
                cout << "Enter second number: ";
                calc.checkInput(num2);
                cout << "Enter percentage to calculate: ";
                calc.checkInput(percentage);
                result = advCalc.calculatePercentage(num1, num2, percentage);
                cout << fixed << setprecision(2);
                cout << "Percentage Result: " << result << endl;
            }
            else if (adv_choice == 2)
            {
                cout << "Enter principal amount: ";
                calc.checkInput(principal);
                cout << "Enter annual interest rate (in %): ";
                calc.checkInput(annualRate);
                cout << "Enter tenure (in months): ";
                calc.checkInput(tenureMonths);
                result = advCalc.calculateEMI(principal, annualRate, tenureMonths);
                cout << fixed << setprecision(2);
                cout << "Monthly EMI: " << result << endl;
            }
            promptExit(exitChoice);
            break;
        default:
            cout << "Select Calculator Type:\n1. Basic Calculator\n2. Advanced Calculator\nChoose: ";
            calc.checkInput(calc_choice);
            while (calc_choice < 1 || calc_choice > 2)
            {
                cout << "Invalid choice. Please enter (1-2): ";
                calc.checkInput(calc_choice);
            }
            continue;
        }

    } while (exitChoice == "no" || exitChoice == "n");
    cout << "Thank you for using the Calculator!" << endl;
    cin.get();
    return 0;
}