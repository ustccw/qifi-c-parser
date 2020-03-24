/*
* MIT License
* 
* Copyright (c) 2020 ustccw
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include <stdio.h>
#include <string.h>
#include "qifi_parser.h"

static uint8_t *string[] = {
    "WIFI:T:WPA;S:mynetwork;P:mypass;;",
    "WIFI:T:WEP;S:mynetwork;P:mypass;H:true;",
    "WIFI:T:nopass;S:12345678901234567890123456789012;P:1234567890123456789012345678901234567890123456789012345678901234;H:true;",
    "WIFI:T:omit;S:中文测试;P:中文密码;H:false;",
    "WIFI:T:omit;S:S:\\;\\,\\:\\\\end;P:中文密码;H:false;",
// "WIFI:T:WPA;S:123456789012345678901234567890123;P:12345678901234567890123456789012345678901234567890123456789012345;H:false;",
};

static const char *TAG = "main";

int main(int argc, char *argv[])
{
    qifi_parser_t parser;
    qifi_err_t ret = QIFI_PARSE_OK;
    uint32_t test_counts = sizeof(string) / sizeof(string[0]);

    for (int i = 0; i < test_counts; ++i) {
        qifi_parser_init(&parser);
        QIFI_LOGD(TAG, "Start Parse String[%d]: %s", i, string[i]);
        ret = qifi_parser_parse(&parser, string[i], strlen(string[i]));

        if (ret == QIFI_PARSE_OK) {
            QIFI_LOGD(TAG, "String[%d] Parse OK!\n------\nTYPE:%d\nSSID(%d):%.*s\nPASSWORD(%d):%.*s\nHIDDEN:%d\n------",
                     i, parser.type, parser.ssid_len, parser.ssid_len, parser.ssid,
                     parser.password_len, parser.password_len, parser.password, parser.ssid_hidden);
        } else {
            QIFI_LOGD(TAG, "ret:0x%x", ret);
        }
    }

    QIFI_LOGD(TAG, "TEST DONE");
    return 0;
}
