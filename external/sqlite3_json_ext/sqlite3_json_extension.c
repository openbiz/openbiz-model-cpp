//
//  pcre.c
//  test
//
//  Created by Jixian Wang on 14/10/29.
//  Copyright (c) 2014年 GAPP AS. All rights reserved.
//

#include "sqlite3_json_extension.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>
#include <sqlite3.h>


static void sqlite3_json_contains( sqlite3_context *context, int argc, sqlite3_value **argv ) {
    assert(argc == 2);
    char *pcre_err = NULL;
    int pcre_erroffset, pcre_errcode;
    const char *keyword = (const char *) sqlite3_value_text(argv[0]);
    const char *pattern_template = "\"[^\"]*?\"\\s?:\\s?\"[^\"]*?(?i)%s[^\"]*?\"\\s?,";
    char pattern_str[strlen(pattern_template)+strlen(keyword)];
    sprintf(pattern_str, pattern_template, keyword);
    pcre *pattern = pcre_compile2(pattern_str, PCRE_UTF8, &pcre_errcode, (const char **) &pcre_err, &pcre_erroffset, NULL);
    if( pattern == NULL ) {
        // pcre error code 21 is out of memory as per pcreapi(3)
        if( pcre_errcode == 21 ) {
            sqlite3_result_error_nomem(context);
        } else {
            sqlite3_result_error(context, pcre_err, (int)strlen(pcre_err));
        }
    } else {
        const unsigned char *subject = sqlite3_value_text(argv[1]);
        pcre_errcode = pcre_exec(pattern, NULL, (const char *) subject, (int)strlen((const char *) subject), 0, 0, NULL, 0);
        if( pcre_errcode < 0 ) {
            char *errmsg;
            switch( pcre_errcode ) {
                case PCRE_ERROR_NOMATCH:
                    sqlite3_result_int(context, 0);
                    break;
                case PCRE_ERROR_NOMEMORY:
                    sqlite3_result_error_nomem(context);
                    break;
                default:
                    errmsg = sqlite3_mprintf("pcre_exec: Error code %d\n", pcre_errcode);
                    if( errmsg == NULL ) {
                        sqlite3_result_error_nomem(context);
                    } else {
                        sqlite3_result_error(context, errmsg, (int)strlen(errmsg));
                    }
                    sqlite3_free(errmsg);
            }
        } else {
            sqlite3_result_int(context, 1);
        }
        
        pcre_free(pattern);
    }
}

int sqlite3_json_extension_init( sqlite3 *db, char **pzErrMsg ) {
    int code;
    if( pcre_config(PCRE_CONFIG_UTF8, &code) != 0 ) assert(0);
    if( code != 1 ) {
        if( pzErrMsg ) *pzErrMsg = sqlite3_mprintf("PCRE does not support UTF-8");
        return SQLITE_ERROR;
    }
    return sqlite3_create_function(db, "json_contains", 2, SQLITE_UTF8, 0, sqlite3_json_contains, 0, 0);
}