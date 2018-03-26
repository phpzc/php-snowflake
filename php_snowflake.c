/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_php_snowflake.h"
#include "snowflake.h"
#include "php_globals.h"
#include "SAPI.h"


/* If you declare any globals in php_php_snowflake.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(php_snowflake)
*/

/* True global resources - no need for thread safety here */
static int le_php_snowflake;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("php_snowflake.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_php_snowflake_globals, php_snowflake_globals)
    STD_PHP_INI_ENTRY("php_snowflake.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_php_snowflake_globals, php_snowflake_globals)
PHP_INI_END()
*/
/* }}} */

PHP_FUNCTION(php_snowflake)
{
	uint64_t id = get_unique_id();

	RETURN_LONG(id);
}

/* {{{ php_php_snowflake_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_php_snowflake_init_globals(zend_php_snowflake_globals *php_snowflake_globals)
{
	php_snowflake_globals->global_value = 0;
	php_snowflake_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(php_snowflake)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	set_workid();
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(php_snowflake)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(php_snowflake)
{
	set_workid();
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(php_snowflake)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(php_snowflake)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "php_snowflake support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ php_snowflake_functions[]
 *
 * Every user visible function must have an entry in php_snowflake_functions[].
 */
const zend_function_entry php_snowflake_functions[] = {
	PHP_FE(php_snowflake,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in php_snowflake_functions[] */
};
/* }}} */

/* {{{ php_snowflake_module_entry
 */
zend_module_entry php_snowflake_module_entry = {
	STANDARD_MODULE_HEADER,
	"php_snowflake",
	php_snowflake_functions,
	PHP_MINIT(php_snowflake),
	PHP_MSHUTDOWN(php_snowflake),
	PHP_RINIT(php_snowflake),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(php_snowflake),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(php_snowflake),
	PHP_PHP_SNOWFLAKE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHP_SNOWFLAKE
ZEND_GET_MODULE(php_snowflake)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
