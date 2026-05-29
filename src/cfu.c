#include "global.h"
#include "cfu.h"
#include "string_util.h"

#define CFU_MAX_TOTAL 180
#define CFU_MAX_FROM_CATCHES 90
#define CFU_MAX_FROM_STEPS 10
#define CFU_STEPS_PER_REWARD 10000
#define RUSTBORO_GYM_CFU_REQUIRED 8

u32 GetCfu(void)
{
    return min(gSaveBlock1Ptr->cfu, CFU_MAX_TOTAL);
}

void SetCfu(u32 amount)
{
    if (amount > CFU_MAX_TOTAL)
        gSaveBlock1Ptr->cfu = CFU_MAX_TOTAL;
    else
        gSaveBlock1Ptr->cfu = amount;
}

void AddCfu(u32 amount)
{
    if (gSaveBlock1Ptr->cfu >= CFU_MAX_TOTAL
     || CFU_MAX_TOTAL - gSaveBlock1Ptr->cfu < amount)
        gSaveBlock1Ptr->cfu = CFU_MAX_TOTAL;
    else
        gSaveBlock1Ptr->cfu += amount;
}

void TryAddCfuForNewCaughtSpecies(void)
{
    if (gSaveBlock1Ptr->cfuCatchRewards < CFU_MAX_FROM_CATCHES)
    {
        gSaveBlock1Ptr->cfuCatchRewards++;
        AddCfu(1);
    }
}

void Cfu_HandleStep(void)
{
    if (gSaveBlock1Ptr->cfuStepRewards >= CFU_MAX_FROM_STEPS)
        return;

    gSaveBlock1Ptr->cfuStepCounter++;
    if (gSaveBlock1Ptr->cfuStepCounter >= CFU_STEPS_PER_REWARD)
    {
        gSaveBlock1Ptr->cfuStepCounter -= CFU_STEPS_PER_REWARD;
        gSaveBlock1Ptr->cfuStepRewards++;
        AddCfu(1);
    }
}

u16 RustboroGymGetCfuStatus(void)
{
    u32 cfu = GetCfu();
    u32 missing = 0;

    if (cfu < RUSTBORO_GYM_CFU_REQUIRED)
        missing = RUSTBORO_GYM_CFU_REQUIRED - cfu;

    ConvertIntToDecimalStringN(gStringVar1, cfu, STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, missing, STR_CONV_MODE_LEFT_ALIGN, 2);

    return cfu >= RUSTBORO_GYM_CFU_REQUIRED;
}
