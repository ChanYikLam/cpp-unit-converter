#include <iostream>
#include <cstdlib>
#include "converter_base.h"
#include "converter_factory.h"

static const int NUM_CATEGORIES = 13;

static void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

static void resetInput() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

static void showMainMenu() {
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "          Unit Converter  \n";
    std::cout << "========================================\n";
    for (int i = 1; i <= NUM_CATEGORIES; ++i) {
        const char* name = getCategoryNameById(i);
        std::cout << "   " << i << ". " << name << std::endl;
    }
    std::cout << "   0. Exit\n";
    std::cout << "========================================\n";
    std::cout << "Select category (0-" << NUM_CATEGORIES << "): ";
}

static void doConversion(AbstractConverter* conv) {
    const std::vector<std::string>& units = conv->getUnits();
    int fromIdx, toIdx;
    double value;

    std::cout << "\n--- " << conv->getCategoryName() << " ---\n";
    std::cout << "Available units:\n";
    for (std::size_t i = 0; i < units.size(); ++i) {
        std::cout << "   " << (i + 1) << ". " << units[i] << std::endl;
    }

    std::cout << "Select source unit (1-" << units.size() << "): ";
    if (!(std::cin >> fromIdx) || fromIdx < 1 || fromIdx > static_cast<int>(units.size())) {
        std::cout << "Error: invalid unit selection!\n";
        resetInput();
        return;
    }

    std::cout << "Select target unit (1-" << units.size() << "): ";
    if (!(std::cin >> toIdx) || toIdx < 1 || toIdx > static_cast<int>(units.size())) {
        std::cout << "Error: invalid unit selection!\n";
        resetInput();
        return;
    }

    std::cout << "Enter value: ";
    if (!(std::cin >> value)) {
        std::cout << "Error: please enter a valid number!\n";
        resetInput();
        return;
    }

    double result = conv->convert(value, units[fromIdx - 1], units[toIdx - 1]);
    if (result == -1.0 && value != -1.0) {
        std::cout << "Error: conversion failed, unit mismatch!\n";
    } else {
        std::cout << "\n  " << value << " " << units[fromIdx - 1]
                  << " = " << result << " " << units[toIdx - 1] << std::endl;
    }
    resetInput();
}

int main() {
    while (true) {
        clearScreen();
        showMainMenu();

        int choice;
        if (!(std::cin >> choice)) {
            resetInput();
            continue;
        }

        if (choice == 0) {
            std::cout << "\nThank you, goodbye!\n" << std::endl;
            break;
        }

        if (choice < 1 || choice > NUM_CATEGORIES) {
            std::cout << "Error: invalid choice, please retry!\n";
            resetInput();
            std::cout << "Press Enter to continue...";
            std::cin.get();
            continue;
        }

        AbstractConverter* conv = createConverter(choice);
        if (conv == NULL) {
            std::cout << "Error: failed to create converter!\n";
            resetInput();
            std::cout << "Press Enter to continue...";
            std::cin.get();
            continue;
        }

        doConversion(conv);
        delete conv;

        std::cout << "\nPress Enter to return to main menu...";
        std::cin.get();
    }

    return 0;
}
