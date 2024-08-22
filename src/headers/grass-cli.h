#ifndef _GRASS_H
#define _GRASS_H
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include "ctmath.h"
#include <vector>



class Cli {
private:
    static const int pvSIZE = 4;
    const std::string pvOPEARTION[pvSIZE] = { "+", "-", "*", "%" };

    bool eventer = true;

    Math math;
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

    void calculatorInstructions() {
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
        std::vector<std::string> commands;

        for (int opr = 0; opr < pvSIZE; opr++) {
            if (input == pvOPEARTION[opr]) {
                eventer = true;
                return;
            }
        }
        commands.push_back("exit"); // 0
        commands.push_back("help"); // 1
        commands.push_back("calc"); // 2
        commands.push_back("clear"); // 3
        commands.push_back("calc -h"); // 4 

        if (input == commands[0]) {
            eventer = false;
        }
        else if (input == commands[1]) {
            displayHelp();
        }
        else if (input == commands[2]) {
            calculate();
        }
        else if (input == commands[3]) {
            system("cls");
        }
        else if (input == commands[4]) {
            calculatorInstructions();
        }
        else {
            system("cls");
            calculatorInstructions();
            std::cout << "Please specify one from the included operations\n";
        }
    }

    void calculate() {
        auto num1 = 0, num2 = 0;
        char pbOPERATOR;

        std::cout << cool() << "Enter the first number: ";
        std::cin >> num1;
        std::cout << cool() << "Enter your operator symbol: ";
        std::cin >> pbOPERATOR;
        std::cout << cool() << "Enter another number: ";
        std::cin >> num2;

        if (!(isdigit(num1)) || !(isdigit(num2)) ) {

            switch (pbOPERATOR) {
            case '+':
                std::cout << "The result is: " << addition(num1 , num2) << std::endl;
                std::cin.get();
                break;
            case '-':
                std::cout << "The result is: " << subtraction(num1 , num2) << std::endl;
                std::cin.get();
                break;
            case '*':
                std::cout << "The result is: " << multiplication(num1 , num2) << std::endl;
                std::cin.get();
                break;
            case '%':
                std::cout << "The result is: " << division(num1 , num2) << std::endl;
                std::cin.get();
                break;

            default:
                std::cout << "Please enter one of the operators shown above.\nRun 'help' for more information.\n";
                calculate();
            }
        }
        else {
            std::cout << num1 << " and " << num2 << " are not numbers\n";
        }
    
}

void displayHelp() {
    std::cout << "=========================================================\n";
    std::cout << "Currently, there are only a few commands available :( \n";
    std::cout << "=========================================================\n";
    std::cout << "Run: 'exit' to exit the program\n";
    std::cout << "Run: 'calc' to calculate some integers ONLY (for now).(you can type 'calc -h' for help)\n";
    std::cout << "Run: 'clear' to clear the console\n\n";
    }

    void start() {
        std::cout << "Run 'help' for more help.\n";
        std::string inp;
        while (eventer) {
            std::cout << cool();
            std::getline(std::cin, inp);
            checkUserInput(inp);
        }
    }
};

#endif _GRASS_H