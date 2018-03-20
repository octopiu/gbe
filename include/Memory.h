#pragma once
#include <list>
#include <memory>
#include "IBlock.h"

namespace gbe {
namespace memory {

struct Region {
    int bottom, top;
    std::shared_ptr<IBlock> block;

    Region(int bottom, int top, std::shared_ptr<IBlock> block);
    ~Region() = default;
};

struct Echo {
    int echo_bottom, echo_top, actual_bottom;

    Echo(int echo_bottom, int echo_top, int actual_bottom);
    ~Echo() = default;

    bool is_inside(uint16_t address) const;
    uint16_t convert(uint16_t address) const;
};

class Memory: public IBlock {
    public:
        Memory();
        ~Memory();

        void insert(int bottom, int top, std::shared_ptr<IBlock> block);
        void make_echo(int echo_bottom, int echo_top, int actual_bottom);
        uint16_t get_actual_address(uint16_t address) const;
        
        void write8(uint16_t address, uint8_t value) override;
        void write16(uint16_t address, uint16_t value) override;
        uint8_t read8(uint16_t address) override;
        uint16_t read16(uint16_t address) override;
    protected:
        std::list<Region> regions;
        std::list<Echo> echos;
};

}
}