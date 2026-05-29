#ifndef GUARD_CFU_H
#define GUARD_CFU_H

#include "global.h"

u32 GetCfu(void);
void SetCfu(u32 amount);
void AddCfu(u32 amount);
void TryAddCfuForNewCaughtSpecies(void);
void Cfu_HandleStep(void);
u16 RustboroGymGetCfuStatus(void);

#endif // GUARD_CFU_H
