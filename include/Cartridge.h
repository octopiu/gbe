#pragma once
#include <cstdint>
#include <fstream>
#include <string>

namespace gbe {

struct RomHeader {
    uint8_t start[4];
    uint8_t graphic[48];
    char title[16];
    uint8_t is_color;
    uint8_t licensee_new[2];
    uint8_t is_super;
    uint8_t cart_type;
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t dest_code;
    uint8_t licensee_old;
    uint8_t mask_rom_version;
    uint8_t complement_check;
    uint8_t checksum;
};

class Cartridge {
    public:
        Cartridge();
        ~Cartridge();

        void load(const std::string& path);
        RomHeader get_header() const;

        static const size_t ROM_BANK_SIZE=0x4000;
        static const size_t RAM_BANK_SIZE=0x2000;

    protected:
        RomHeader header;
        uint8_t (*banks)[ROM_BANK_SIZE];
        int banks_count;
};

}
