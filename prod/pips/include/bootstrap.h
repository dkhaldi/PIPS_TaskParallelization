/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/bootstrap/bootstrap-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  bootstrap_header_included
#define  bootstrap_header_included
/*

  $Id: bootstrap-local.h 23065 2016-03-02 09:05:50Z coelho $

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

/* should be some properties to accomodate cray codes?? */
#define INT_LENGTH 4
#define REAL_LENGTH 4
#define DOUBLE_LENGTH 8
#define COMPLEX_LENGTH 8
#define DCOMPLEX_LENGTH 16

/* context for type checking. */
typedef struct 
{
    hash_table types;
    stack stats;
    int number_of_error;
    int number_of_conversion;
    int number_of_simplication;
} type_context_t, * type_context_p;

typedef basic (*typing_function_t)(call, type_context_p);

typedef void (*switch_name_function)(expression, type_context_p);

/* The following data structure describes an intrinsic function: its
   name and its arity and its type, a function to type it (?) and a
   function to obtain its name if it is different from the entity user
   name, e.g. because of special characters or name collisions. */

typedef struct IntrinsicDescriptor
{
  string name;
  int nbargs;
  type (*intrinsic_type)(int);
  typing_function_t type_function;
  switch_name_function name_function;
} IntrinsicDescriptor;
/* bootstrap.c */
extern void CreateAreas(void);
extern void type_loop_range(basic /*index*/, range /*r*/, type_context_p /*context*/);
extern call convert_constant(call /*c*/, basic /*to_basic*/);
extern expression cast_constant(expression /*exp_constant*/, basic /*to_basic*/, type_context_p /*context*/);
extern expression insert_cast(basic cast, basic /*from*/, expression /*exp*/, type_context_p /*context*/);
extern bool arguments_are_compatible(call /*c*/, hash_table /*types*/);
extern type MakeVoidResult(void);
extern parameter MakeVoidParameter(void);
extern type pointer_to_overloaded_type(int /*n*/);
extern type integer_to_overloaded_type(int /*n*/);
extern type longinteger_to_overloaded_type(int /*n*/);
extern type longlonginteger_to_overloaded_type(int /*n*/);
extern type integer_to_void_type(int /*n*/);
extern type void_to_overloaded_type(int /*n*/);
extern type overloaded_to_void_type(int /*n*/);
extern type void_to_integer_type(int /*n*/);
extern typing_function_t get_typing_function_for_intrinsic(const char */*name*/);
extern switch_name_function get_switch_name_function_for_intrinsic(const char */*name*/);
extern entity FindOrMakeIntrinsic(string /*name*/, int /*arity*/, type (* /*intrinsic_type*/)(int));
extern entity FindOrMakeDefaultIntrinsic(string /*name*/, int /*arity*/);
extern void register_intrinsic_type_descriptor(IntrinsicDescriptor */*p*/);
extern void CreateIntrinsics(set /*module_list*/);
extern bool bootstrap(const string /*workspace*/);
extern value MakeValueLitteral(void);
extern string MakeFileName(char */*prefix*/, char */*base*/, char */*suffix*/);
extern entity MakeIoFileArray(entity /*f*/);
/* type_checker.c */
extern bool check_loop_range(range /*r*/, hash_table /*types*/);
extern void typing_of_expressions(string /*name*/, statement /*s*/);
extern bool type_checker(const string /*name*/);
#endif /*  bootstrap_header_included */
