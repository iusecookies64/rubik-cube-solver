
#include "NibbleArray.h"
#include <bits/stdc++.h>

NibbleArray::NibbleArray(uint32_t _size, uint8_t init_value)
{
    size = _size;
    data.assign(size / 2 + 1, init_value);
}

uint8_t NibbleArray::get(const uint32_t index) const
{
    uint32_t arrayIndex = index / 2;
    if (arrayIndex > size)
    {
        cout << "Out of bounds\n";
        return 0xf;
    }
    // if index is odd, then value stored in second nibble
    uint32_t val;
    if (index % 2)
    {
        val = (data[arrayIndex] >> 4);
    }
    else
    {
        val = (data[arrayIndex] & one_4);
    }

    return val;
}

void NibbleArray::set(const uint32_t index, const uint8_t value)
{
    uint32_t arrayIndex = index / 2;
    if (arrayIndex > size)
    {
        cout << "Out of bounds\n";
        return;
    }
    // if index is odd, then setting value in second nibble
    if (index % 2)
    {
        data[arrayIndex] = ((data[arrayIndex] & one_4) | (value << 4));
    }
    else
    {
        data[arrayIndex] = ((data[arrayIndex] & (one_4 << 4)) | value);
    }
}

const uint8_t *NibbleArray::getData() const
{
    return data.data();
}

size_t NibbleArray::getSize() const
{
    return data.size();
}

uint8_t *NibbleArray::getData()
{
    return data.data();
}
