#include "../include/MBC1.h"

namespace gbe {
namespace memory {

MBC1::MBC1(const ROMS &rom_data, int ram_banks_count):
    IBlock(), ram(SWITCH_RAM_POS), rom0(ROM0_POS), rom1(SWITCH_ROM_POS)
{
    this->rom_data = Shared_ROMS(rom_data.size());
    for (int i=0; i<rom_data.size(); ++i)
        this->rom_data.push_back(std::make_shared<GB_ROM::Data>(rom_data[i]));
    this->rom0.set_data(this->rom_data[0]);
    this->rom1.set_data(this->rom_data[1]);
}

void MBC1::write8(uint16_t address, uint8_t value) {
    if (address >= SWITCH_RAM_POS && address <= SWITCH_RAM_END)
        return this->ram.write8(address, value);
}

void MBC1::write16(uint16_t address, uint16_t value) {
    if (address >= SWITCH_RAM_POS && address <= SWITCH_RAM_END)
        return this->ram.write16(address, value);
}

uint8_t MBC1::read8(uint16_t address) {
    if (address >= ROM0_POS && address <= ROM0_END)
        return this->rom0.read8(address);
    else if (address >= SWITCH_ROM_POS && address <= SWITCH_ROM_END)
        return this->rom1.read8(address);
    else if (address >= SWITCH_RAM_POS && address <= SWITCH_RAM_END)
        return this->ram.read8(address);
}

uint16_t MBC1::read16(uint16_t address) {
    if (address >= ROM0_POS && address <= ROM0_END)
        return this->rom0.read16(address);
    else if (address >= SWITCH_ROM_POS && address <= SWITCH_ROM_END)
        return this->rom1.read16(address);
    else if (address >= SWITCH_RAM_POS && address <= SWITCH_RAM_END)
        return this->ram.read16(address);
}

}
}