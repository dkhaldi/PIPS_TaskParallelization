/* string.c */
extern string gen_strndup(string /*s*/, size_t /*n*/);
extern string gen_strndup0(string /*s*/, size_t /*n*/);
extern char *i2a(int /*i*/);
extern void init_the_buffer(void);
extern string append_to_the_buffer(const char */*s*/);
extern string get_the_buffer(void);
extern string concatenate(const char */*next*/, ...);
extern string strupper(string /*s1*/, const char */*s2*/);
extern string strlower(string /*s1*/, const char */*s2*/);
extern string bool_to_string(bool /*b*/);
extern string nth_suffix(int /*i*/);
extern string find_suffix(const string /*s*/, const string /*suffix*/);
extern string chop_newline(string /*s*/, bool /*flg*/);
extern string remove_newline_of_string(string /*s*/);
extern list strsplit(const char */*s*/, const char */*d*/);
extern int gen_qsort_string_cmp(const void */*s1*/, const void */*s2*/);
extern void str_prepend(string */*dst*/, string /*prefix*/);
extern void str_append(string */*dst*/, string /*suffix*/);
