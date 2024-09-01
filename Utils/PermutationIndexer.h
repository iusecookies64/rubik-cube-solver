
#ifndef RUBIKS_CUBE_PERMUTATION_INDEXER_H
#define RUBIKS_CUBE_PERMUTATION_INDEXER_H

#include <bits/stdc++.h>
using namespace std;

template <size_t N>
class PermutationIndexer
{
private:
    vector<uint32_t> factorial;
    vector<bitset<N>> bitOnes;

public:
    PermutationIndexer()
    {
        factorial.push_back(1);
        for (int i = 1; i < N; i++)
        {
            uint32_t curr = factorial[i - 1] * i;
            factorial.push_back(curr);
        }
        bitset<N> curr;
        for (int i = 0; i < N; i++)
        {
            curr.set(i);
            bitOnes.push_back(curr);
        }
    }

    uint32_t getPermutationIndex(const vector<uint32_t> &perm)
    {
        // perm contains integers in range 0 to N-1
        int n = perm.size();
        assert(n <= N);
        bitset<N> seen;
        uint32_t lehmer[n];
        for (int i = 0; i < n; i++)
        {
            // counting the number of elements smaller to its left
            int smallerCount = (seen & (bitOnes[perm[i]])).count();
            lehmer[i] = perm[i] - smallerCount;
            // setting perm[i] as seen
            seen.set(perm[i]);
        }

        uint32_t index = 0;

        for (int i = 0; i < n; i++)
        {
            index += lehmer[i] * factorial[n - i - 1];
        }

        return index;
    }
};

#endif // RUBIKS_CUBE_PERMUTATION_INDEXER_H