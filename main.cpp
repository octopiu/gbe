#include <iostream>
#include <memory>
#include "include/Cartridge.h"
#include "include/Memory.h"
#include "include/Bank.h"
#include "include/MBC1.h"

int main(int argc, char** argv){
    gbe::Cartridge cart;
    cart.load("../roms/cpu_instrs.gb");
    gbe::memory::Memory memory;
    auto ram = std::make_shared<gbe::memory::RAM<8192>>(0xC000);
    return 0;
}
