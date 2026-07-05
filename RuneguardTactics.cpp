#include <iostream>
#include "debugtools.h"
#include "gridlogic.h"
using namespace debugtools;

gridlogic grid(16,16);

int main()
{
    std::cout << "Rune Guard Tactics launched\n";
    std::cout << "Testing Grid Generation\n";
    auto generateGridns = debugtools::timeNano([&]() {
    grid.generategrid(false);
});
    printFormattedNano(generateGridns);
    return 0;
}
