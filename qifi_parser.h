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
#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "qifi_port.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
--------------------------------------------------------------------------------------------------------
Wi-Fi Network config (Android, iOS 11+)
We propose a syntax like "MECARD" for specifying wi-fi configuration.
Scanning such a code would, after prompting the user, configure the device's Wi-Fi accordingly. Example:

WIFI:T:WPA;S:mynetwork;P:mypass;;

--------------------------------------------------------------------------------------------------------
Parameter       Example         Description
--------------------------------------------------------------------------------------------------------
    T           WPA         Authentication type; can be WEP or WPA, or 'nopass' for no password. Or, omit for no password.
    S           mynetwork   Network SSID. Required.
                            Enclose in double quotes if it is an ASCII name, but could be interpreted as hex (i.e. "ABCD")
    P           mypass      Password, ignored if T is "nopass" (in which case it may be omitted).
                            Enclose in double quotes if it is an ASCII name, but could be interpreted as hex (i.e. "ABCD")
    H           true        Optional. True if the network SSID is hidden.
--------------------------------------------------------------------------------------------------------

Order of fields does not matter. Special characters \, ;, , and : should be escaped with a backslash (\) as in MECARD encoding.
For example, if an SSID was literally "foo;bar\baz" (with double quotes part of the SSID name itself)
then it would be encoded like: WIFI:S:\"foo\;bar\\baz\";;
more details see as: https://github.com/zxing/zxing/wiki/Barcode-Contents#wi-fi-network-config-android-ios-11
*/

/*******************************************************
 *                Constants
 *******************************************************/

/**
 * @brief Input string length to parse
 */
#define QIFI_STRING_MAX                 128         /*!< Maximum length of input string */
#define QIFI_STRING_MIN                 16          /*!< Minimum length of input string */

/**
 * @brief Mesh error code definition
 */
#define QIFI_SSID_LEN_MAX               32          /*!< Minimum SSID length of WiFi configuration */
#define QIFI_PASSWORD_LEN_MAX           64          /*!< Minimum password length of WiFi configuration */

/**
 * @brief QiFi parse error code definition
 */
#define QIFI_PARSE_OK                 0             /*!< Parse success */
#define QIFI_PARSE_ERR_BASE           0x10000       /*!< Starting number of QiFi error codes */
#define QIFI_PARSE_ERR_INVLALID_ARGS  (QIFI_PARSE_ERR_BASE + 1)     /*!< Parsed invalid arguments */
#define QIFI_PARSE_ERR_NO_SCHEME      (QIFI_PARSE_ERR_BASE + 2)     /*!< Scheme missing */
#define QIFI_PARSE_ERR_NO_AUTH_TYPE   (QIFI_PARSE_ERR_BASE + 3)     /*!< Auth type missing */
#define QIFI_PARSE_ERR_NO_SSID        (QIFI_PARSE_ERR_BASE + 4)     /*!< SSID missing */
#define QIFI_PARSE_ERR_NO_PASSWORD    (QIFI_PARSE_ERR_BASE + 5)     /*!< Password missing */
#define QIFI_PARSE_ERR_NO_HIDDEN      (QIFI_PARSE_ERR_BASE + 6)     /*!< Hidden missing */
#define QIFI_PARSE_ERR_PARSE_FAILED   (QIFI_PARSE_ERR_BASE + 7)     /*!< Parse failed */

/**
 * @brief QiFi parse return value redefinition
 */
typedef int32_t qifi_err_t;

/**
 * @brief WiFi authentication type definition
 */
typedef enum {
    QIFI_WEP,           /*!< WEP authentication type */
    QIFI_WPA,           /*!< WPA authentication type */
    QIFI_NOPASS,        /*!< No password authentication type */
    QIFI_OMIT,          /*!< Omit authentication type */
} auth_type_t;

/**
 * @brief Used to store resolution results
 */
typedef struct {
    auth_type_t type: 8;                        /*!< WiFi authentication type */
    bool ssid_hidden;                           /*!< SSID hidden or not */
    uint8_t ssid[QIFI_SSID_LEN_MAX];            /*!< SSID of WiFi */
    uint8_t ssid_len;                           /*!< SSID length */
    uint8_t password[QIFI_PASSWORD_LEN_MAX];    /*!< Password of WiFi */
    uint8_t password_len;                       /*!< Password length */
} qifi_parser_t;

/**
 * @brief       Init QiFi parser
 *
 * @param[in]   parser: configuration to initialize
 *
 * @noreturn
*/
void qifi_parser_init(qifi_parser_t *parser);

/**
 * @brief       Parse QRCode of WiFi string
 *
 * @param[in]   buf: WiFi string
 * @param[in]   buflen: WiFi string length
 * @param[out]  parser: parse result
 *
 * @return
 *          - QIFI_PARSE_OK: if parse OK
 *          - others: see as QIFI_PARSE_ERR_XX
*/
qifi_err_t qifi_parser_parse(qifi_parser_t *parser, uint8_t *buf, size_t buflen);

#ifdef __cplusplus
}
#endif
