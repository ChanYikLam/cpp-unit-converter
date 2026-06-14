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
    std::cout << "            单位转换程序\n";
    std::cout << "========================================\n";
    for (int i = 1; i <= NUM_CATEGORIES; ++i) {
        const char* name = getCategoryNameById(i);
        std::cout << "   " << i << ". " << name << std::endl;
    }
    std::cout << "   0. 退出程序\n";
    std::cout << "========================================\n";
    std::cout << "请选择类别 (0-" << NUM_CATEGORIES << "): ";
}

static void doConversion(AbstractConverter* conv) {
    const std::vector<std::string>& units = conv->getUnits();
    int fromIdx, toIdx;
    double value;

    clearScreen();
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "        " << conv->getCategoryName() << " 转换\n";
    std::cout << "========================================\n";
    std::cout << "可选单位:\n";
    for (std::size_t i = 0; i < units.size(); ++i) {
        std::cout << "   " << (i + 1) << ". " << units[i] << std::endl;
    }
    std::cout << "----------------------------------------\n";

    std::cout << "请选择原单位 (1-" << units.size() << "): ";
    if (!(std::cin >> fromIdx) || fromIdx < 1 || fromIdx > static_cast<int>(units.size())) {
        std::cout << "错误: 无效的单位选择!\n";
        resetInput();
        return;
    }

    std::cout << "请选择目标单位 (1-" << units.size() << "): ";
    if (!(std::cin >> toIdx) || toIdx < 1 || toIdx > static_cast<int>(units.size())) {
        std::cout << "错误: 无效的单位选择!\n";
        resetInput();
        return;
    }

    std::cout << "请输入数值: ";
    if (!(std::cin >> value)) {
        std::cout << "错误: 请输入有效的数字!\n";
        resetInput();
        return;
    }

    double result = conv->convert(value, units[fromIdx - 1], units[toIdx - 1]);
    std::cout << "\n";
    std::cout << "========================================\n";
    if (result == -1.0 && value != -1.0) {
        std::cout << "  转换失败，单位不匹配!\n";
    } else {
        std::cout << "  " << value << " " << units[fromIdx - 1]
                  << " = " << result << " " << units[toIdx - 1] << "\n";
    }
    std::cout << "========================================\n";
    resetInput();
}

int main() {
    while (true) {
        clearScreen();
        showMainMenu();

        int choice;
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                std::cout << "\n输入结束，程序退出。\n" << std::endl;
                break;
            }
            resetInput();
            continue;
        }

        if (choice == 0) {
            std::cout << "\n感谢使用，再见！\n" << std::endl;
            break;
        }

        if (choice < 1 || choice > NUM_CATEGORIES) {
            std::cout << "错误: 无效的选择，请重新输入!\n";
            resetInput();
            std::cout << "按回车键继续...";
            std::cin.ignore(10000, '\n');
            continue;
        }

        AbstractConverter* conv = createConverter(choice);
        if (conv == NULL) {
            std::cout << "错误: 创建转换器失败!\n";
            resetInput();
            std::cout << "按回车键继续...";
            std::cin.ignore(10000, '\n');
            continue;
        }

        doConversion(conv);
        delete conv;

        std::cout << "\n按回车键返回主菜单...";
        std::cin.ignore(10000, '\n');
    }

    return 0;
}
