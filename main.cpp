#include <iostream>
#include <memory>
#include "include/Cartridge.h"
#include "include/Memory.h"
#include "include/RAM.h"

int main(int argc, char** argv){
    gbe::Cartridge cart;
    cart.load("../roms/cpu_instrs.gb");
    gbe::memory::Memory memory;
    auto ram = std::make_shared<gbe::memory::RAM<8192>>(0xC000);
    memory.insert(0xC000, 0xE000, ram);
    memory.write16(0xC000, 300);
    std::cout << (int)memory.read8(0xC000) << std::endl;
    return 0;
}
