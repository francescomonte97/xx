#include "global.h"
#include "ppa.h"

u32 GetPpa(void)
{
    return gSaveBlock1Ptr->ppa;
}

void SetPpa(u32 amount)
{
    gSaveBlock1Ptr->ppa = amount;
}

void AddPpa(u32 amount)
{
    if ((u32)-1 - gSaveBlock1Ptr->ppa < amount)
        gSaveBlock1Ptr->ppa = (u32)-1;
    else
        gSaveBlock1Ptr->ppa += amount;
}

void SubPpa(u32 amount)
{
    if (gSaveBlock1Ptr->ppa < amount)
        gSaveBlock1Ptr->ppa = 0;
    else
        gSaveBlock1Ptr->ppa -= amount;
}
