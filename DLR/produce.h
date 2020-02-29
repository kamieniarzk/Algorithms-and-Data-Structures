#pragma once
#include "iterator.h"

template <typename Key, typename Info>
DLR<Key, Info> produce(const DLR<Key, Info>& r1, int start1, int step1 , bool dir1,
                        const DLR<Key, Info>& r2, int start2, int step2 , bool dir2,
                        int num, bool dir)
{
    DLR<Key, Info> produced;
    if(step1 < 0 && step2 < 0)
    {
        cout << "\nINVALID ARGUMENTS IN PRODUCE FUNCTION\n";
        return produced;
    }

    if(num < 0)
        return produced;

    typename DLR<Key, Info>::iterator i1 = r1.iter();
    typename DLR<Key, Info>::iterator i2 = r2.iter();

    if(!r1.isEmpty())
        i1 = i1 + (start1-1);
    if(!r2.isEmpty())
        i2 = i2 + (start2-1);

    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < step1; j++)
        {
            if(!r1.isEmpty())
            {
                produced.push(i1.getKey(), i1.getInfo());
                dir1 ? i1++ : i1--;
            }
        }

        for(int k = 0; k < step2; k++)
        {
            if(!r2.isEmpty())
            {
                produced.push(i2.getKey(), i2.getInfo());
                dir2 ? i2++ : i2--;
            }
        }
    }

    if(!dir)
        produced.inverse();

    return produced;


}
