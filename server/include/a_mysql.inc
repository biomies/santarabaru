#if defined _samp_mysql_included
	#endinput
#endif
#define _samp_mysql_included

/**
 * <library name="a_mysql" summary="MySQL Plugin R41-4 for SA-MP">
 */

#define MYSQL_INVALID_HANDLE (MySQL:0)

enum MySQLOpt {
	AUTO_RECONNECT,
	MULTI_STATEMENTS,
	POOL_SIZE,
	SSL_ENABLE,
	SSL_KEY_FILE,
	SSL_CERT_FILE,
	SSL_CA_FILE,
	SSL_CA_PATH,
	SSL_CIPHER
};

native MySQLOpt:mysql_init_options();
native bool:mysql_set_option(MySQLOpt:opt_id, MySQLOpt:option, {Float,_}:...);
native MySQL:mysql_connect(const host[], const user[], const password[], const database[], MySQLOpt:opt_id = MySQLOpt:0, port = 3306);
native MySQL:mysql_connect_file(const file_name[] = "mysql.ini", MySQLOpt:opt_id = MySQLOpt:0);
native bool:mysql_close(MySQL:handle);
native mysql_errno(MySQL:handle);
native mysql_format(MySQL:handle, output[], len, const format[], {Float,_}:...);
native bool:mysql_tquery(MySQL:handle, const query[], const callback[] = "", const format[] = "", {Float,_}:...);

native cache_num_rows();
native cache_num_fields();
native cache_insert_id();
native bool:cache_get_value_name_int(row_idx, const column_name[], &destination);
native bool:cache_get_value_name_float(row_idx, const column_name[], &Float:destination);
native bool:cache_get_value_name(row_idx, const column_name[], destination[], max_len = sizeof (destination));
native bool:cache_get_value_index_int(row_idx, column_idx, &destination);
native bool:cache_get_value_index_float(row_idx, column_idx, &Float:destination);
native bool:cache_get_value_index(row_idx, column_idx, destination[], max_len = sizeof (destination));
