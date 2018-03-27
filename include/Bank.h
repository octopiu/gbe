#pragma once
#include <cstdint>
#include <memory>
#include <array>
#include "IBlock.h"

namespace gbe {
namespace memory {

template<bool READONLY, std::size_t SIZE>
class Bank: public IBlock {
    public:
        using Data = std::array<uint8_t, SIZE>;

        Bank(uint16_t position=0x000, std::shared_ptr<Data> data=nullptr);
        ~Bank() = default;

        void write8(uint16_t address, uint8_t value) override;
        void write16(uint16_t address, uint16_t value) override;
        uint8_t read8(uint16_t address) override;
        uint16_t read16(uint16_t address) override;
        void set_data(std::shared_ptr<Data> data);
        void set_position(uint16_t position);
        uint16_t get_position() const;
        bool is_readonly() const;
    protected:
        uint16_t position;
        std::shared_ptr<Data> data;
};

template<std::size_t SIZE> using RAM = Bank<false, SIZE>;
template<std::size_t SIZE> using ROM = Bank<true, SIZE>;

template<bool READONLY, std::size_t SIZE>
Bank<READONLY, SIZE>::Bank(uint16_t position, std::shared_ptr<Data> data):
    IBlock(), position(position), data(data) {
    if (data == nullptr)
        this->data = std::make_shared<Data>();
}

template<bool READONLY, std::size_t SIZE>
inline void Bank<READONLY, SIZE>::write8(uint16_t address, uint8_t value) {
    if (READONLY)
        return;
    (*this->data)[address - this->position] = value;
}

template<bool READONLY, std::size_t SIZE>
inline void Bank<READONLY, SIZE>::write16(uint16_t address, uint16_t value) {
    if (READONLY)
        return;
    (*this->data)[address - this->position] = value & 0xFF;
    (*this->data)[address - this->position + 1] = value >> 8;
}

template<bool READONLY, std::size_t SIZE>
inline uint8_t Bank<READONLY, SIZE>::read8(uint16_t address) {
    auto value = (*this->data)[address - this->position];
    return value;
}

template<bool READONLY, std::size_t SIZE>
inline uint16_t Bank<READONLY, SIZE>::read16(uint16_t address) {
    uint16_t value = (*this->data)[address - this->position + 1];
    value <<= 8;
    value |= (*this->data)[address - this->position];
    return value;
}

template<bool READONLY, std::size_t SIZE>
void Bank<READONLY, SIZE>::set_data(std::shared_ptr<Data> data) {
    this->data = data;
}

template<bool READONLY, std::size_t SIZE>
void Bank<READONLY, SIZE>::set_position(uint16_t position) {
    this->position = position;
}

template<bool READONLY, std::size_t SIZE>
uint16_t Bank<READONLY, SIZE>::get_position() const {
    return this->position;
}

template<bool READONLY, std::size_t SIZE>
inline bool Bank<READONLY, SIZE>::is_readonly() const {
    return READONLY;
}

}
}