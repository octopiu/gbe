#pragma once
#include <vector>
#include "defines.h"
#include "IBlock.h"
#include "Bank.h"

namespace gbe {
namespace memory {

class MBC1: public IBlock {
    public:
        using GB_ROM = ROM<ROM_BANK_SIZE>;
        using GB_RAM = RAM<RAM_BANK_SIZE>;
        using ROMS = std::vector<GB_ROM::Data>;
        using RAMS = std::vector<GB_RAM::Data>;
        using Shared_ROMS = std::vector<std::shared_ptr<GB_ROM::Data>>;
        using Shared_RAMS = std::vector<std::shared_ptr<GB_RAM::Data>>;

        MBC1(const ROMS &rom_data, int ram_banks_count);
        ~MBC1() = default;

        void write8(uint16_t address, uint8_t value) override;
        void write16(uint16_t address, uint16_t value) override;
        uint8_t read8(uint16_t address) override;
        uint16_t read16(uint16_t address) override;
    protected:
        GB_RAM ram;
        Shared_RAMS ram_data;
        GB_ROM rom0, rom1;
        Shared_ROMS rom_data;
};

}
}