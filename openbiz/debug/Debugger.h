//
//  Debugger.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/12/21.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __Openbiz_RestModel__Debugger__
#define __Openbiz_RestModel__Debugger__

#include <stdio.h>
namespace openbiz
{
    class Debugger
    {
    public:
        static void setDebugNetworkEnabled();
        static const bool isDebugNetworkEnabled();
        
        typedef enum  {
            DebugInsertOperation,
            DebugUpdateOperation,
            DebugDeleteOperation,
            DebugFetchOperation,
        } DatabaseDebugOption;
        
        typedef struct {
            bool DebugInsertOperation = false;
            bool DebugUpdateOperation = false;
            bool DebugDeleteOperation = false;
            bool DebugFetchOperation = false;            
        } DatabaseDebugOptions;
        
        static void setDebugDatabaseEnabled(DatabaseDebugOption);
        static const DatabaseDebugOptions* getDebugDatabaseOption();
    private:
        static bool _debugNetworkState;
        static DatabaseDebugOptions _debugDatabaseOptions;
    };
}
#endif /* defined(__Openbiz_RestModel__Debugger__) */
