#pragma once
#include <cstdint>
#include <array>
#include "IBlock.h"

namespace gbe {
namespace memory {

template<std::size_t SIZE>
class RAM: public IBlock {
    public:
        RAM(uint16_t start_address);
        ~RAM() = default;

        void write8(uint16_t address, uint8_t value) override;
        void write16(uint16_t address, uint16_t value) override;
        uint8_t read8(uint16_t address) override;
        uint16_t read16(uint16_t address) override;
    protected:
        uint16_t start_address;
        std::array<uint8_t, SIZE> memory;
};

template<std::size_t SIZE>
RAM<SIZE>::RAM(uint16_t start_address):IBlock(), start_address(start_address) {
}

template<std::size_t SIZE>
void RAM<SIZE>::write8(uint16_t address, uint8_t value) {
    this->memory[address - this->start_address] = value;
}

template<std::size_t SIZE>
void RAM<SIZE>::write16(uint16_t address, uint16_t value) {
    this->memory[address - this->start_address] = value & 0xFF;
    this->memory[address - this->start_address + 1] = value >> 8;
}

template<std::size_t SIZE>
uint8_t RAM<SIZE>::read8(uint16_t address) {
    auto value = this->memory[address - this->start_address];
    return value;
}

template<std::size_t SIZE>
uint16_t RAM<SIZE>::read16(uint16_t address) {
    uint16_t value = this->memory[address - this->start_address + 1];
    value <<= 8;
    value |= this->memory[address - this->start_address];
    return value;
}

}
}