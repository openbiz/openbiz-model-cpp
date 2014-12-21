//
//  Debugger.cpp
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/12/21.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "Debugger.h"
using namespace openbiz;

bool Debugger::_debugNetworkState = false;

void Debugger::setDebugNetworkEnabled(){
    _debugNetworkState = true;
}

const bool Debugger::isDebugNetworkEnabled()
{
    return _debugNetworkState;
}

Debugger::DatabaseDebugOptions Debugger::_debugDatabaseOptions;

void Debugger::setDebugDatabaseEnabled(DatabaseDebugOption option){
    switch(option){
        case DebugInsertOperation:
            _debugDatabaseOptions.DebugInsertOperation=true;
            break;
        case DebugUpdateOperation:
            _debugDatabaseOptions.DebugUpdateOperation=true;
            break;
        case DebugDeleteOperation:
            _debugDatabaseOptions.DebugDeleteOperation=true;
            break;
        case DebugFetchOperation:
            _debugDatabaseOptions.DebugFetchOperation=true;
            break;
    }
}

const Debugger::DatabaseDebugOptions* Debugger::getDebugDatabaseOption()
{
    return &_debugDatabaseOptions;
}