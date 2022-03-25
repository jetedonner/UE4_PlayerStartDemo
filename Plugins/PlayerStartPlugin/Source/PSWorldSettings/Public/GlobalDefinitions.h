//
//  GlobalDefinitions.h
//  UE4_PlayerStartDemo
//
//  Created by Kim David Hauser on 22.03.22.
//  Copyright (c.) 2022 kimhauser.ch, DaVe Inc. (Kim David Hauser) - All rights reserved.
//

#ifndef GlobalDefinitions_h
#define GlobalDefinitions_h

#include <string.h>

DECLARE_LOG_CATEGORY_EXTERN(DaVeLog, Log, All);
DEFINE_LOG_CATEGORY(DaVeLog);

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define DAVE_LOG_GENERAL UE_LOG(DaVeLog, Log, TEXT("%s - Line: %i - Func: %s"), *FString(__FILENAME__), __LINE__, *FString(__FUNCTION__));
#define DAVE_LOG_PARAM(pn, pv) UE_LOG(DaVeLog, Log, TEXT("%s - Line: %i - Func: %s => %s:%s"), *FString(__FILENAME__), __LINE__, *FString(__FUNCTION__), pn, pv);

#endif /* GlobalDefinitions_h */

