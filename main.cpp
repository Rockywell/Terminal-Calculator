
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

/* Calculator class that performs basic arithmetic operations
   and maintains a history of calculations */
class Calculator
{
private:
    // History of temporary calculations
    vector<string> history;

public:
    /* Perform basic arithmetic by matching the
       operation character and returning the result */
    double calculate(double a, double b, char operation)
    {
        switch (operation)
        {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0)
            {
                throw runtime_error("Cannot divide by zero.");
            }
            return a / b;
        default:
            throw runtime_error("Invalid operation.");
        }
    }

    // Stores calculations in a vector and file
    void saveCalculation(string calculation)
    {
        // Stores calculation in the vector at the end.
        history.push_back(calculation);

        // Create a file class object in append mode.
        ofstream file("history.txt", ios::app);

        if (file)
        {
            file << calculation << endl;
        }
        else
        {
            cout << "Could not save history to file." << endl;
        }
    }

    // Displays the full and recent history of calculations
    void showHistory()
    {
        // Full history from the file
        cout << "\n=== Full History ===\n";

        ifstream file("history.txt");
        string line;
        bool found = false;

        while (getline(file, line))
        {
            cout << line << endl;
            found = true;
        }

        if (!found)
        {
            cout << "No saved history." << endl;
        }

        // Recent history from RAM
        cout << "\n=== Recent History ===\n";

        if (history.empty())
        {
            cout << "No recent calculations." << endl;
        }
        else
        {
            for (const string &entry : history)
            {
                cout << entry << endl;
            }
        }
    }
};

/* Check whether the input is a valid number and returns
   the validation (true/false) and updates the number reference. */
bool getNumber(string prompt, double &number)
{
    while (true)
    {
        cout << prompt;

        string input;
        if (!getline(cin, input))
        {
            return false;
        }

        stringstream stream(input);
        char extra;

        if (stream >> number && !(stream >> extra))
        {
            return true;
        }

        cout << "Invalid number. Try again." << endl;
    }
}

// The main function that runs the calculator program
int main()
{
    Calculator calculator;
    string choice;

    while (true)
    {
        cout << "\n=== Calculator ===\n";
        cout << "+  Add\n";
        cout << "-  Subtract\n";
        cout << "*  Multiply\n";
        cout << "/  Divide\n";
        cout << "h  View history\n";
        cout << "q  Quit\n";
        cout << "Choose an option: ";

        // Breaks out of the loop if the user inputs 'q' or an EOF signal
        if (!getline(cin, choice) || choice == "q")
        {
            break;
        }

        if (choice == "h")
        {
            calculator.showHistory();
            continue;
        }

        if (choice != "+" && choice != "-" &&
            choice != "*" && choice != "/")
        {
            cout << "Invalid option." << endl;
            continue;
        }

        double first, second;

        // Breaks out of the loop if one of inputs is an invalid number
        if (!getNumber("First number: ", first) ||
            !getNumber("Second number: ", second))
        {
            break;
        }

        try
        {
            // Calculates the result based on the user's choice and inputs
            double result = calculator.calculate(
                first, second, choice[0]);

            cout << "Result: " << result << endl;

            // Stores the whole equation as a string e.g. "5 + 3 = 8"
            stringstream entry;
            entry << first << " " << choice
                  << " " << second << " = " << result;

            // Saves the equation to the history vector and file
            calculator.saveCalculation(entry.str());
        }
        catch (const runtime_error &error)
        {
            cout << "Error: " << error.what() << endl;
        }
    }

    cout << "Goodbye!" << endl;
    return 0;
}
