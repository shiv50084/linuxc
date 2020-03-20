#include <glib.h>

/* gcc  glib-example01.c `pkg-config --cflags --libs glib-2.0` */
int main(int argc, char *argv[])
{
	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);

	char *key1 = "Virginia";
	char *val1 = "Richmond";
	char *key2 = "China";
	char *val2 = "BeiJin";

	g_hash_table_insert(hash, key1, val1);
	g_hash_table_insert(hash, key2, val2);
	g_hash_table_insert(hash, "Ohio", "Columbus");

	g_printf("There are %d keys in the hash\n", g_hash_table_size(hash));
	g_printf("The capital of %s is %s\n", key2, g_hash_table_lookup(hash, key2));
	gboolean found = g_hash_table_remove(hash, key1);
	g_printf("The value '%s' was %sfound and removed, %d items left\n", key1, found ? "" : "not ", g_hash_table_size(hash));
	g_hash_table_destroy(hash);

	return 0;
}
