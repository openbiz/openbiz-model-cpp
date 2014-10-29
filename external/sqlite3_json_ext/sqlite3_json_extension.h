//
//  pcre.h
//  test
//
//  Created by Jixian Wang on 14/10/29.
//  Copyright (c) 2014年 GAPP AS. All rights reserved.
//

#ifndef __test__pcre__
#define __test__pcre__

#include <sqlite3.h>
#ifdef __cplusplus
extern "C" {
#endif
    int sqlite3_json_extension_init( sqlite3 *db, char **pzErrMsg );
#ifdef __cplusplus
}
#endif
#endif /* defined(__test__pcre__) */
