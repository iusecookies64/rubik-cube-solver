
#ifndef RUBIKS_CUBE_NIBBLE_ARRAY_H
#define RUBIKS_CUBE_NIBBLE_ARRAY_H

#include <bits/stdc++.h>
using namespace std;

class NibbleArray
{
private:
    uint32_t size;

    uint8_t one_4 = (1 << 4) - 1;

    vector<uint8_t> data;

public:
    NibbleArray(uint32_t _size, uint8_t init_value = 0);

    uint8_t get(const uint32_t index) const;

    void set(const uint32_t index, const uint8_t value);

    const uint8_t *getData() const;

    uint8_t *getData();

    size_t getSize() const;
};

#endif // RUBIKS_CUBE_NIBBLE_ARRAY_H