#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept> // For std::runtime_error

class Functions {
private:
    static const int pvSIZE = 4;
    const std::string pvOPEARTION[pvSIZE] = { "+", "-", "*", "%" };

    bool eventer = true;

public:
    std::string cool() {
        std::string result;
        char buffer[128];

        // Create a unique_ptr with a custom deleter for the FILE pointer
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen("whoami", "r"), _pclose);

        if (!pipe) {
            throw std::runtime_error("_popen() failed!");
        }
        while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
            result += buffer;
        }

        // Remove the newline character from the end of the result
        if (!result.empty() && result[result.size() - 1] == '\n') {
            result.erase(result.size() - 1);
        }
        return "[" + result + "]: ";
    }

    void displayInstructions() {
        for (int j = 0; j < pvSIZE; j++) {
            std::cout << pvOPEARTION[j] << " ";
        }
        std::cout << "\n==========================================================/\n";
        std::cout << "+ : for Addition\n";
        std::cout << "- : for Subtraction\n";
        std::cout << "* : for Multiplication\n";
        std::cout << "% : for Division (also displays the remainder)\n";
        std::cout << "Run: 'help' to get help.\n";
        std::cout << "==========================================================/\n\n";
    }

    void checkUserInput(const std::string& input) {
        for (int opr = 0; opr < pvSIZE; opr++) {
            if (input == pvOPEARTION[opr]) {
                eventer = true;
                return;
            }
        }

        if (input == "exit") {
            eventer = false;
        }
        else if (input == "help") {
            displayHelp();
        }
        else if (input == "calc") {
            calculate();
        }
        else if (input == "clear") {
            system("cls");
        }
        else if (input == "instructions") {
            displayInstructions();
        }
        else {
            system("cls");
            displayInstructions();
            std::cout << "Please specify one from the included operations\n";
        }
    }

    void calculate() {
        int num1, num2;
        char pbOPERATOR;

        std::cout << cool() << "Enter the first number: ";
        std::cin >> num1;
        std::cout << cool() << "Enter your operator symbol: ";
        std::cin >> pbOPERATOR;
        std::cout << cool() << "Enter another number: ";
        std::cin >> num2;

        switch (pbOPERATOR) {
        case '+':
            std::cout << cool() << "The result is: " << num1 + num2 << std::endl;
            break;
        case '-':
            std::cout << cool() << "The result is: " << num1 - num2 << std::endl;
            break;
        case '*':
            std::cout << cool() << "The result is: " << num1 * num2 << std::endl;
            break;
        case '%':
            std::cout << cool() << "The result is: " << num1 / num2 << std::endl;
            std::cout << cool() << "The remainder is: " << num1 % num2 << std::endl;
            break;
        default:
            std::cout << "Please enter one of the operators shown above.\nRun 'help' for more information.\n";
            calculate();
            break;
        }
    }

    void displayHelp() {
        std::cout << "\n\n========================================================= \n";
        std::cout << "Currently, there are only a few commands available :( \n";
        std::cout << "========================================================= \n";
        std::cout << "Run: 'exit' to exit the program \n";
        std::cout << "Run: 'calculate' to calculate some integers ONLY (for now).\n";
        std::cout << "Run: 'instructions' to display the program instructions\n";
        std::cout << "Run: 'clear' to clear the console\n\n";
    }

    void start() {
        std::string inp;
        while (eventer) {
            std::cout << cool();
            std::getline(std::cin, inp);
            checkUserInput(inp);
        }
    }
};

int main() {
    Functions tui;
    tui.displayInstructions();
    tui.start();
    return 0;
}
