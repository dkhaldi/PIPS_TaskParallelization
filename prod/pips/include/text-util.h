/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/text-util/text-util-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  text_util_header_included
#define  text_util_header_included
/*

  $Id: text-util-local.h 23065 2016-03-02 09:05:50Z coelho $

  Copyright 1989-2016 MINES ParisTech

  This file is part of PIPS.

  PIPS is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  PIPS is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.

  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with PIPS.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "text.h"
#include "linear.h" // needed for ri.h
#include "ri.h" // FC: bad, for "language", to avoid a cycle on ri-util

#define FORESYS_CONTINUATION_PREFIX "C$&" "    "

#define MAKE_SWORD(s) strdup(s)
#define MAKE_IWORD(i) int2a(i)
#define MAKE_FWORD(f) f2a(f)

#define CHAIN_SWORD(l,s) gen_nconc(l, CONS(STRING, MAKE_SWORD(s), NIL))
#define CHAIN_IWORD(l,i) gen_nconc(l, CONS(STRING, MAKE_IWORD(i), NIL))
#define CHAIN_FWORD(l,f) gen_nconc(l, CONS(STRING, MAKE_FWORD(f), NIL))

#define MAKE_ONE_WORD_SENTENCE(m, s)					\
  make_sentence(is_sentence_unformatted,				\
		make_unformatted((char *) NULL, 0, m, CHAIN_SWORD(NIL, s)))

#define ADD_SENTENCE_TO_TEXT(t,p)					\
  do {									\
    text _t_ = (t);							\
    text_sentences(_t_) =						\
      gen_nconc(text_sentences(_t_), CONS(SENTENCE, (p), NIL));		\
  } while(0)

#define MERGE_TEXTS(r,t)					\
  do {								\
    text _r_ = (r); text _t_ = (t);				\
    text_sentences(_r_) =					\
      gen_nconc(text_sentences(_r_), text_sentences(_t_));	\
    text_sentences(_t_) = NIL;					\
    free_text(_t_);						\
  } while(0)

/* maximum length of a line when prettyprinting...
 * from 0 to 69, i.e. 70 chars, plus "\n\0"
 */
#define MAX_LINE_LENGTH 72
/* text_print.c */
extern void print_sentence(FILE */*fd*/, sentence /*s*/);
extern void print_text(FILE */*fd*/, text /*t*/);
extern void dump_sentence(sentence /*s*/);
extern void dump_text(text /*t*/);
extern string words_join(list /*ls*/, const char */*sep*/);
extern string words_to_string(list /*ls*/);
extern string sentence_to_string(sentence /*sen*/);
extern string text_to_string_gen(text /*t*/, bool /*with_newline*/);
extern string text_to_string(text /*t*/);
extern string text_to_string_nl(text /*t*/);
extern void print_words(FILE */*fd*/, list /*lw*/);
extern void dump_words(list /*lw*/);
extern void debug_words(list /*l*/);
extern void debug_sentence(sentence /*s*/);
extern void debug_text(text /*t*/);
/* util.c */
extern char *int2a(int /*i*/);
extern char *f2a(float /*f*/);
extern void add_one_unformated_printf_to_text(text /*r*/, string /*a_format*/, ...);
extern string first_word_of_sentence(sentence /*s*/);
extern string last_word_of_sentence(sentence /*s*/);
extern void add_to_current_line(string /*buffer*/, const char */*append*/, string /*continuation*/, text /*txt*/);
extern void close_current_line(string /*buffer*/, text /*txt*/, string /*continuation*/);
extern void add_words_to_text(text /*t*/, list /*wl*/);
/* language.c */
extern language get_prettyprint_language(void);
extern enum language_utype get_prettyprint_language_tag(void);
extern bool prettyprint_language_is_fortran_p(void);
extern bool prettyprint_language_is_fortran95_p(void);
extern bool prettyprint_language_is_c_p(void);
extern void set_prettyprint_language_from_property(enum language_utype /*native*/);
extern void set_prettyprint_language(language /*lang*/);
extern void set_prettyprint_language_tag(enum language_utype /*lang*/);
extern string get_C_label_printf_format(const char */*label*/);
/* attachment_pretty_print.c */
extern list attachments_before_sorting;
extern void begin_attachment_prettyprint(void);
extern void end_attachment_prettyprint(void);
extern void attach_loop_to_sentence_up_to_end_of_text(sentence /*s*/, text /*t*/, loop /*l*/);
extern sentence attach_head_to_sentence(sentence /*s*/, entity /*module*/);
extern void attach_reference_to_word_list(string /*begin_word*/, string /*end_word*/, reference /*r*/);
extern void attach_regular_call_to_word(string /*word*/, call /*c*/);
extern void attach_declaration_to_words(list /*l*/, entity /*e*/);
extern void attach_declaration_type_to_words(list /*l*/, string /*declaration_type*/);
extern void attach_declaration_size_type_to_words(list /*l*/, string /*declaration_type*/, int /*size*/);
extern void attach_statement_information_to_text(text /*t*/, statement /*s*/);
extern void attach_decoration_to_text(text /*t*/);
extern void attach_cumulated_effects_decoration_to_text(text /*t*/);
extern void attach_proper_effects_decoration_to_text(text /*t*/);
extern void attach_preconditions_decoration_to_text(text /*t*/);
extern void attach_total_preconditions_decoration_to_text(text /*t*/);
extern void attach_transformers_decoration_to_text(text /*t*/);
extern void deal_with_attachments_at_this_character(char */*a_character*/, int /*position_in_the_output*/);
extern void deal_with_attachments_in_this_string(string /*a_string*/, int /*position_in_the_output*/);
extern void deal_with_attachments_in_this_string_length(string /*a_string*/, int /*position_in_the_output*/, int /*a_length*/);
extern void relocate_attachments(char */*source*/, char */*new_position*/);
extern char *strcat_word_and_migrate_attachments(char */*target*/, const char */*source*/);
extern char *strdup_and_migrate_attachments(char */*a_string*/);
extern void write_an_attachment_file(string /*file_name*/);
#endif /*  text_util_header_included */
