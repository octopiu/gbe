#include "../include/Memory.h"

namespace gbe {
namespace memory {

Region::Region(int bottom, int top, std::shared_ptr<IBlock> block):
    bottom(bottom), top(top), block(block) {
}

Echo::Echo(int echo_bottom, int echo_top, int actual_bottom):
    echo_bottom(echo_bottom), echo_top(echo_top), 
    actual_bottom(actual_bottom) {
}

bool Echo::is_inside(uint16_t address) const {
    return address >= this->echo_bottom && address <= this->echo_top;
}

uint16_t Echo::convert(uint16_t address) const {
    if (address >= this->echo_bottom && address <= this->echo_top)
        return address - echo_bottom + actual_bottom;
    return address;
}

Memory::Memory():IBlock() {}

Memory::~Memory() {}

void Memory::insert(int bottom, int top, std::shared_ptr<IBlock> block) {
    this->regions.emplace_back(bottom, top, block);
}

uint16_t Memory::get_actual_address(uint16_t address) const {
    for (auto& echo: this->echos) {
        if (echo.is_inside(address)) {
            return echo.convert(address);
        }
    }
    return address;
}

void Memory::write8(uint16_t address, uint8_t value) {
    address = this->get_actual_address(address);
    for (auto& region: this->regions) {
        if (address >= region.bottom && address <= region.top) {
            region.block->write8(address, value);
            return;
        }
    }
}

void Memory::write16(uint16_t address, uint16_t value) {
    address = this->get_actual_address(address);
    for (auto& region: this->regions) {
        if (address >= region.bottom && address <= region.top) {
            region.block->write16(address, value);
            return;
        }
    }
}

uint8_t Memory::read8(uint16_t address) {
    address = this->get_actual_address(address);
    for (auto& region: this->regions) {
        if (address >= region.bottom && address <= region.top) {
            return region.block->read8(address);
        }
    }
    //TODO: throw exception
    return 0;
}

uint16_t Memory::read16(uint16_t address) {
    address = this->get_actual_address(address);
    for (auto& region: this->regions) {
        if (address >= region.bottom && address <= region.top) {
            return region.block->read16(address);
        }
    }
    //TODO: throw exception
    return 0;
}

}
}