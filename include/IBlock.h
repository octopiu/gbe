#pragma once
#include <cstdint>

namespace gbe {
namespace memory {

class IBlock {
    public:
        IBlock() = default;
        ~IBlock() = default;

        virtual void write8(uint16_t address, uint8_t value)=0;
        virtual void write16(uint16_t address, uint16_t value)=0;
        virtual uint8_t read8(uint16_t address)=0;
        virtual uint16_t read16(uint16_t address)=0;
};

}
}