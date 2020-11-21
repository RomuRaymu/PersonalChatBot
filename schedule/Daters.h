#ifndef __DATERS_H__
#define __DATERS_H__

#include "common.h"

void PrintDate ( DATE date );
void ModifyMonth ( DATE *pDate , int nMonth );
void ModifyDay ( DATE *pDate , int nDay );

int CompareDate ( DATE target , DATE compare );
int CompareDateAndTime ( DATE target , DATE compare );

DATE InputDate ( void );
DATE GetToday ( void );


#endif
