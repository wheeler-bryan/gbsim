#include <iostream>
#include <cstdint>
using namespace std;

#define BYTE 8
#define REG(idx) ((registers[(idx / 2)] & (0xFF00 >> (idx % 2 * BYTE))) >> (BYTE * !(idx % 2)))

//Function headers
void decode_opcode(uint8_t opcode);
void load(uint8_t r1, uint8_t r2);

// Defining registers
uint16_t registers[2] = {0x1234, 0x5678};
// B & C = 0

int main(void) {
    decode_opcode(0x58); //  01 011 000
    cout << "Hex: " << std::hex << registers[1];
}

void decode_opcode(uint8_t opcode) {
    // LD function: x01xxxyyy where x, y = r
    if ((opcode & 0xC0) == 0x40) {
        load(((opcode & 0x38) >> 3), (opcode & 0x07));
    }
    return;
}

void load(uint8_t r1, uint8_t r2) {

    // Checks if we are loading something that is not a register
    if (r1 == 0b110 || r2 == 0b110) {
        return;
    } else {
        /*
        Load register into another register
        - Take current register to be replaced
        - Create a bitmask to save the byte not being overwritten (if were replacing byte 0, create 0x00FF)
        - Bitwise or with the other register
        - Get the other register by calling our register wrapper and shifting it if necessary (based on first register location)
        */
        registers[(r1 / 2)] = registers[(r1 / 2)] & (0x00FF << (r1 % 2 * BYTE)) | (REG(r2) << (!(r1 % 2) * BYTE));
    }

    return;
}