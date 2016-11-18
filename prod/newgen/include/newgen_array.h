/*

  $Id: newgen_array.h 1357 2016-03-02 08:18:50Z coelho $

  Copyright 1989-2016 MINES ParisTech

  This file is part of NewGen.

  NewGen is free software: you can redistribute it and/or modify it under the
  terms of the GNU General Public License as published by the Free Software
  Foundation, either version 3 of the License, or any later version.

  NewGen is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
  License for more details.

  You should have received a copy of the GNU General Public License along with
  NewGen.  If not, see <http://www.gnu.org/licenses/>.

*/

struct _gen_array_chunk_t;
typedef struct _gen_array_chunk_t * gen_array_t;

#define gen_array_undefined ((gen_array_t) -12)
#define gen_array_undefined_p(a) ((a)==gen_array_undefined)

/* declarations...
 */
gen_array_t gen_array_make(size_t);
void gen_array_free(gen_array_t);
void gen_array_full_free(gen_array_t);
void gen_array_addto(gen_array_t, size_t, void *);
void gen_array_remove(gen_array_t, size_t);
void gen_array_dupaddto(gen_array_t, size_t, void *);
void gen_array_append(gen_array_t, void *);
void gen_array_dupappend(gen_array_t, void *);
void ** gen_array_pointer(gen_array_t);
size_t gen_array_nitems(gen_array_t);
size_t gen_array_size(gen_array_t);
void * gen_array_item(gen_array_t, size_t);
void gen_array_sort(gen_array_t);
void gen_array_sort_with_cmp(gen_array_t, int (*)(const void *, const void *));

gen_array_t gen_array_from_list(list);
list list_from_gen_array(gen_array_t);
string string_array_join(gen_array_t array, string separator);

#define GEN_ARRAY_FOREACH(type, s, array)                               \
  gen_array_t NGMID(a) = (array);                                       \
  size_t NGMID(n) = gen_array_nitems(NGMID(a));                         \
  type s = NGMID(n) > 0 ? (type) gen_array_item(NGMID(a), 0): NULL;     \
  for (size_t NGMID(i) = 0;                                              \
       NGMID(i) < NGMID(n) &&                                           \
        ((s = (type) gen_array_item(NGMID(a), NGMID(i))), 1);           \
      NGMID(i) ++)
