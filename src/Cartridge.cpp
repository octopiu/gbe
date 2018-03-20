#include "../include/Cartridge.h"
#include <cstring>
#include <cmath>

namespace gbe {

Cartridge::Cartridge():banks_count(0) {
}

void Cartridge::load(const std::string& path) {
    std::ifstream rom(path);
    uint8_t bank0[ROM_BANK_SIZE];
    rom.read((char*)bank0, ROM_BANK_SIZE);
    memcpy(&this->header, &(bank0[0x100]), sizeof(this->header));
    switch(this->header.rom_size) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            this->banks_count = pow(2, this->header.rom_size+1);
            break;
        case 0x52:
            this->banks_count = 72;
            break;
        case 0x53:
            this->banks_count = 80;
            break;
        case 0x54:
            this->banks_count = 96;
            break;
        default:
            //TODO: throw an error
            break;
    };
    this->banks = new uint8_t[this->banks_count][ROM_BANK_SIZE];
    memcpy(this->banks[0], bank0, ROM_BANK_SIZE);
    for (int i=1; i<this->banks_count; ++i)
        rom.read((char*)this->banks[i], ROM_BANK_SIZE);
}

RomHeader Cartridge::get_header() const {
    return this->header;
}

Cartridge::~Cartridge() {
    delete[] this->banks;
}

}
