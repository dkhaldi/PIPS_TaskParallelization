/*

 $Id: html_prettyprinter.c 22686 2015-07-21 07:31:15Z coelho $

 Copyright 1989-2009 MINES ParisTech

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
#ifdef HAVE_CONFIG_H
#include "pips_config.h"
#endif
/*

 Try to prettyprint the RI in C.
 Very basic at the time.
 Functionnal.
 All arguments are assumed newly allocated.
 It might be really slow, but it should be safe.
 I should use some kind of string accumulator (array/list...)

 html_print_crough > MODULE.crough
 < PROGRAM.entities
 < MODULE.code

 html_print_c_code  > MODULE.c_printed_file
 < MODULE.crough
 */

#include <stdio.h>
#include <ctype.h>

#include "genC.h"
#include "linear.h"

#include "misc.h"
#include "pipsdbm.h"
#include "properties.h"

#include "ri-util.h"

#define NL "\n"
/**************************************************************** MISC UTILS */

#define current_module_is_a_function()            \
(entity_function_p(get_current_module_entity()))

static void html_print_expression(expression e, bool cr);
static void html_print_range(range r);
static void html_print_statement(statement r);
static void html_print_type(type t);
static void html_print_value(value v);

// Output
static FILE *out_fp = 0;

// Define output
static void html_set_output(FILE *new_fp) {
  out_fp = new_fp;
}

/*
 * Print to the defined output the format string and an optional string argument
 */
#define html_print(format, args...) \
{ \
  pips_assert("Output is set",out_fp); \
  fprintf(out_fp,format,##args); \
}


static void begin_block(const char *block, bool cr) {
  if(cr) {
    html_print("<li class=\"%s blocked\"><span>%s</span><ul class=\"inlined\">" NL,
           block,
           block);
  } else {
    html_print("<li class=\"%s inlined\"><span>%s</span><ul class=\"inlined\">" NL,
           block,
           block);
  }
}

static void end_block(const char *block, bool cr) {
  if(cr) {
    html_print("</ul></li><!-- %s -->" NL, block);
  } else
    html_print("</ul></li><!-- %s -->" NL, block);
}

void html_output(const char *out, bool cr) {
  if(cr) {
    html_print("<li><span>%s</span></li>" NL, out);
  } else {
    html_print("<li class=\"inlined\"><span>%s</span></li>" NL, out);
  }
}

static void html_print_entity_name(entity e) {
  begin_block("entity", false);
  html_output(entity_name( e ), false);
  end_block("entity", false);
}

static void html_print_ram(ram r) {
  begin_block("ram", true);

  begin_block("Function", true);
  html_print_entity_name(ram_function( r ));
  end_block("Function", true);

  html_output(NL, false);

  begin_block("Section", true);
  html_print_entity_name(ram_section( r ));
  end_block("Section", true);

  string buf;
  pips_assert("Asprintf !",
      asprintf( &buf, "Offset : %d", (int) ram_offset( r ) ) > 0 );
  html_output(buf, true);
  free(buf);
  FOREACH(entity, e, ram_shared( r ) ) {
    html_print_entity_name(e);
  }

  end_block("ram", true);
}

static void html_print_formal(formal f) {
  begin_block("formal", true);

  begin_block("Function", false);
  html_print_entity_name(formal_function( f ));
  end_block("Function", false);

  string buf;
  pips_assert("Asprintf !",
      asprintf( &buf, "Offset : %d", (int) formal_offset( f ) ) > 0);
  html_output(buf, true);

  end_block("formal", true);
}

static void html_print_rom(_UNUSED_ unit r) {
  begin_block("rom", false);

  html_output("unit ? (not implemented)", false);

  end_block("rom", false);
}

static void html_print_code(code c) {
  begin_block("code", true);

  list l = code_declarations(c);
  if(l) {
    begin_block("declarations", true);
    if(!ENDP(l)) {
      FOREACH(entity, e, l )
      {
        begin_block("", true);
        html_print_entity_name(e);
        end_block("", true);
      }
    }
    end_block("declarations", true);
  }
  end_block("code", true);
}

static void html_print_storage(storage s) {
  begin_block("storage", true);
  if(storage_undefined_p(s)) {
    html_output("undefined", false);
  } else {
    switch(storage_tag( s )) {
      case is_storage_return:
        html_output("Return", false);
        html_print_entity_name(storage_return( s ));
        break;
      case is_storage_ram:
        html_print_ram(storage_ram( s ));
        break;
      case is_storage_formal:
        html_print_formal(storage_formal( s ));
        break;
      case is_storage_rom:
        html_print_rom(storage_rom( s));
        break;
      default:
        html_output("Unknown storage", true);
        break;
    }
  }
  end_block("storage", true);
}

static void html_print_basic(basic b) {
  begin_block("basic", false);
  string buf;

  if(!b || b == basic_undefined) {
    html_output("undefined", false);
  } else {
    switch(basic_tag( b )) {
      case is_basic_int:
        html_output("int", false);
        pips_assert("Asprintf !", asprintf( &buf, "%d", (int)basic_int(b) ));
        html_output(buf, false);
        free(buf);
        break;
      case is_basic_float:
        html_output("float", false);
        pips_assert("Asprintf !", asprintf( &buf, "%f", (float)basic_int(b) ));
        html_output(buf, false);
        free(buf);
        break;
      case is_basic_logical:
        html_output("logical", false);
        pips_assert("Asprintf !", asprintf( &buf, "%d", (int)basic_int(b) ));
        html_output(buf, false);
        free(buf);
        break;
      case is_basic_overloaded:
        html_output("overloaded", false);
        html_output("unimplemented", false);
        break;
      case is_basic_complex:
        html_output("complex", false);
        html_output("unimplemented", false);
        break;
      case is_basic_string:
        html_output("string", false);
        html_print_value(basic_string(b));
        break;
      case is_basic_bit:
        html_output("bit", false);
        html_output("unimplemented", false);
        break;
      case is_basic_pointer:
        html_output("pointer", false);
        html_print_type(basic_pointer(b));
        break;
      case is_basic_derived:
        html_output("derived", false);
        html_print_entity_name(basic_derived(b));
        break;
      case is_basic_typedef:
        html_output("typedef", false);
        html_print_entity_name(basic_typedef(b));
        break;
      default:
        html_output("unknown", false);
        break;
    }
  }
  end_block("basic", false);
}

static void html_print_area(area a) {
  begin_block("area", false);

  string buf;
  pips_assert("Asprintf !",
      asprintf( &buf, "Size : %d", (int) area_size( a ) ) > 0);
  html_output(buf, false);
  free(buf);

  html_output("Layout", false);
  FOREACH(entity, e, area_layout( a ) ) {
    html_print_entity_name(e);
  }

  end_block("area", false);
}

static void html_print_qualifier(qualifier q) {
  begin_block("qualifier", false);

  switch(qualifier_tag( q )) {
    case is_qualifier_const:
      html_output("const", false);
      break;
    case is_qualifier_restrict:
      html_output("restrict", false);
      break;
    case is_qualifier_volatile:
      html_output("volatile", false);
      break;
    case is_qualifier_register:
      html_output("register", false);
      break;
    case is_qualifier_auto:
      html_output("auto", false);
      break;
    default:
      html_output("unknown", false);
      break;
  }

  end_block("qualifier", false);
}

static void html_print_dimension(dimension d) {
  begin_block("dimension", true);
  html_print_expression(dimension_lower( d ), true);
  html_print_expression(dimension_upper( d ), true);
  end_block("dimension", true);
}

static void html_print_variable(variable v) {
  begin_block("variable", true);

  html_print_basic(variable_basic( v ));
  FOREACH(dimension, d, variable_dimensions( v ) ) {
    html_print_dimension(d);
  }
  FOREACH(qualifier, q, variable_qualifiers( v ) ) {
    html_print_qualifier(q);
  }

  end_block("variable", true);
}

static void html_print_mode(mode m) {
  begin_block("mode", false);

  switch(mode_tag( m )) {
    case is_mode_value:
      html_output("value", false);
      break;
    case is_mode_reference:
      html_output("reference", false);
      break;
    default:
      html_output("unknown", false);
      break;
  }

  end_block("mode", false);
}

static void html_print_parameter(parameter p) {
  begin_block("parameter", true);

  html_print_type(parameter_type( p ));
  html_print_mode(parameter_mode( p ));
  html_output("Dummy :  not implemented", true);

  end_block("parameter", true);
}

static void html_print_functional(functional f) {
  begin_block("functional", true);
  FOREACH(parameter, param, functional_parameters( f ) ) {
    html_print_parameter(param);
  }

  begin_block("return", false);
  html_print_type(functional_result( f ));
  end_block("return", false);

  end_block("functional", true);
}

static void html_print_type(type t) {
  begin_block("type", true);
  if(t == type_undefined) {
    html_output("*undefined*", true);
  } else {
    switch(type_tag( t )) {
      case is_type_statement:
        html_output("Statement (unit ?) ", true);
        break;
      case is_type_area:
        html_print_area(type_area( t ));
        break;
      case is_type_variable:
        html_print_variable(type_variable( t ));
        break;
      case is_type_functional:
        html_print_functional(type_functional( t ));
        break;
      case is_type_varargs:
        html_output("VarArgs", true);
        html_print_type(type_varargs( t ));
        break;
      case is_type_unknown:
        html_output("Unknown", true);
        break;
      case is_type_void:
        html_output("Void", true);
        break;
      case is_type_struct:
        begin_block("Struct", true);
        FOREACH(entity, e, type_struct( t ) )
        {
          begin_block("field", true);
          html_print_entity_name(e);
          end_block("field", true);
        }
        end_block("Struct", true);
        break;
      case is_type_union:
        html_output("Union", true);
        FOREACH(entity, e, type_union( t ) )
        {
          html_print_entity_name(e);
        }
        break;
      case is_type_enum:
        html_output("Enum", true);
        FOREACH(entity, e, type_enum( t ) )
        {
          html_print_entity_name(e);
        }
        break;
      default:
        break;
    }
  }
  end_block("type", true);
}

static void html_print_constant(constant c) {
  begin_block("constant", false);
  if(!c || c == constant_undefined) {
    html_output("undefined", false);
  } else {
    switch(constant_tag( c )) {
      case is_constant_int: {
        string buf;
        pips_assert("Asprintf !",
            asprintf( &buf, "int : %d", (int) constant_int( c ) ) > 0 );
        html_output(buf, true);
        free(buf);
        break;
      }
      case is_constant_float: {
        string buf;
        pips_assert("Asprintf !",
            asprintf( &buf, "float : %f", (float) constant_float( c ) ) > 0 );
        html_output(buf, true);
        free(buf);
        break;
      }
      case is_constant_logical: {
        string buf;
        pips_assert("Asprintf !",
            asprintf( &buf, "Logical : %d", (int) constant_logical( c ) ) > 0 );
        html_output(buf, true);
        free(buf);
        break;
      }
      case is_constant_litteral:
        html_output("litteral", false);
        break;
      case is_constant_call:
        html_print_entity_name(constant_call(c));
        break;
      case is_constant_unknown:
        begin_block("unknown", false);
        break;
      default:
        html_output("error", false);
        break;
    }
  }
  end_block("constant", false);
}

static void html_print_value(value v) {
  begin_block("value", false);
  if(!v || v == value_undefined) {
    html_output("undefined", false);
  } else {
    switch(value_tag( v )) {
      case is_value_code:
        html_print_code(value_code(v));
        break;
      case is_value_symbolic:
        html_output("symbolic", false);
        break;
      case is_value_constant:
        html_print_constant(value_constant(v));
        break;
      case is_value_intrinsic:
        html_output("intrinsic", false);
        break;
      case is_value_unknown:
        html_output("unknown", false);
        break;
      case is_value_expression:
        begin_block("expression", false);
        html_print_expression(value_expression( v ), false);
        end_block("expression", false);
        break;
      default:
        html_output("error", false);
        break;
    }
  }
  end_block("value", false);
}

void html_print_entity_full(entity e) {
  begin_block("entity", true);
  html_output(entity_name( e ), true);
  html_print_type(entity_type( e ));
  html_print_storage(entity_storage( e ));
  html_print_value(entity_initial( e ));

  end_block("entity", true);
}

static void html_print_call(call c) {
  bool cr = false;
  if(call_arguments( c )) {
    cr = true;
  }
  begin_block("call", cr);

  begin_block("function", cr);
  html_print_entity_name(call_function(c));
  end_block("function", cr);

  if(call_arguments( c )) {
    begin_block("arguments", cr);
    FOREACH(expression, e, call_arguments( c ) ) {
      html_print_expression(e, cr);
    }
    end_block("arguments", cr);
  }
  end_block("call", cr);
}

static void html_print_unstructured(_UNUSED_ unstructured u) {
  begin_block("unstructured", false);
  html_output("Not implemented", false);
  end_block("unstructured", false);
}

static void html_print_reference(reference r) {
  bool cr = false;
  if(reference_indices( r )) {
    cr = true;
  }

  begin_block("reference", cr);
  begin_block("variable", cr);
  html_print_entity_name(reference_variable( r ));
  end_block("variable", cr);

  if(reference_indices( r )) {
    begin_block("indices", cr);
    FOREACH(expression, e, reference_indices( r ) ) {
      html_print_expression(e, false);
    }
    end_block("indices", cr);
  }

  end_block("reference", cr);
}

static void html_print_subscript(subscript s) {
  begin_block("subscript", false);
  begin_block("array", false);
  html_print_expression(subscript_array( s ), false);
  end_block("array", false);
  begin_block("indices", false);
  FOREACH(expression, e, subscript_indices( s ) ) {
    html_print_expression(e, false);
  }
  end_block("indices", false);
  end_block("subscript", false);
}

static void html_print_expression(expression e, bool cr) {
  begin_block("expression", cr);
  begin_block("syntax", false);

  syntax s = expression_syntax(e);
  switch(syntax_tag(s)) {
    case is_syntax_call:
      html_print_call(syntax_call( s ));
      break;
    case is_syntax_range:
      html_print_range(syntax_range( s ));
      break;
    case is_syntax_reference:
      html_print_reference(syntax_reference( s ));
      break;
    case is_syntax_subscript:
      html_print_subscript(syntax_subscript( s ));
      break;
    case is_syntax_cast:
      html_output("cast unimplemented", false);
      break;
    case is_syntax_sizeofexpression:
      html_output("sizeofexpression unimplemented", false);
      break;
    case is_syntax_application:
      html_output("sizeofexpression unimplemented", false);
      break;
    case is_syntax_va_arg:
      html_output("va_arg unimplemented", false);
      break;
    default:
      pips_internal_error("unexpected syntax tag");
  }

  end_block("syntax", false);
  end_block("expression", cr);
}

static void html_print_range(range r) {
  begin_block("range", true);
  begin_block("lower", false);
  html_print_expression(range_lower( r ), false);
  end_block("lower", false);
  begin_block("upper", true);
  html_print_expression(range_upper( r ), false);
  end_block("upper", true);
  begin_block("increment", true);
  html_print_expression(range_increment( r ), false);
  end_block("increment", true);
  end_block("range", true);
}

static void html_print_loop(loop l) {
  begin_block("loop", true);
  /* partial implementation ??? */

  begin_block("index", false);
  html_print_entity_name(loop_index( l ));
  end_block("index", false);

  html_print_range(loop_range( l ));

  begin_block("body", false);
  html_print_statement(loop_body( l ));
  end_block("body", false);

  end_block("loop", true);
}

static void html_print_whileloop(whileloop w) {
  /* partial implementation...  ?? */

  begin_block("whileloop", true);

  begin_block("condition", false);
  html_print_expression(whileloop_condition( w ), false);
  end_block("condition", false);

  begin_block("statement", false);
  html_print_statement(whileloop_body( w ));
  end_block("statement", false);

  begin_block("evaluation", false);
  evaluation eval = whileloop_evaluation(w);
  /*do while and while do loops */
  if(evaluation_before_p(eval))
    html_output("while() {}" NL, false);
  else
    html_output("do {} while(); " NL, false);
  end_block("evaluation", false);

  begin_block("body", false);
  html_print_statement(whileloop_body( w ));
  end_block("body", false);

  end_block("whileloop", true);
}

static void html_print_forloop(forloop f) {
  /* partial implementation... */

  begin_block("forloop", true);

  begin_block("initialization", true);
  html_print_expression(forloop_initialization( f ), false);
  end_block("initialization", true);

  begin_block("condition", true);
  html_print_expression(forloop_condition( f ), false);
  end_block("condition", true);

  begin_block("increment", true);
  html_print_expression(forloop_increment( f ), false);
  end_block("increment", true);

  begin_block("body", false);
  html_print_statement(forloop_body( f ));
  end_block("body", false);

  end_block("forloop", true);
}

static void html_print_sequence(sequence seq) {
  begin_block("sequence", true);
  FOREACH( statement, s, sequence_statements( seq ) ) {
    html_print_statement(s);
  }
  end_block("sequence", true);
}

static void html_print_test(test t) {
  begin_block("test", true);

  begin_block("cond", true);
  html_print_expression(test_condition( t ), false);
  end_block("cond", true);

  begin_block("strue", false);
  html_print_statement(test_true( t ));
  end_block("strue", false);

  if(!empty_statement_p(test_false( t ))) {
    begin_block("sfalse", false);
    html_print_statement(test_false(t));
    end_block("sfalse", false);
  }

  end_block("test", true);
}

static void html_print_statement(statement s) {
  begin_block("statement", true);

  if(statement_label(s) != entity_undefined) {
    begin_block("label", false);
    html_print_entity_name(statement_label(s));
    end_block("label", false);
  }

  list l = statement_declarations(s);
  if(!ENDP(l)) {
    begin_block("declarations", true);
    FOREACH( entity, e, l ) {
      html_print_entity_name(e);
    }
    end_block("declarations", true);
  }

  begin_block("instruction", true);
  instruction i = statement_instruction(s);
  switch(instruction_tag(i)) {
    case is_instruction_test:
      html_print_test(instruction_test( i ));
      break;
    case is_instruction_sequence:
      html_print_sequence(instruction_sequence( i ));
      break;
    case is_instruction_loop:
      html_print_loop(instruction_loop( i ));
      break;
    case is_instruction_whileloop:
      html_print_whileloop(instruction_whileloop( i ));
      break;
    case is_instruction_forloop:
      html_print_forloop(instruction_forloop( i ));
      break;
    case is_instruction_call:
      html_print_call(instruction_call( i ));
      break;
    case is_instruction_unstructured:
      html_print_unstructured(instruction_unstructured( i ));
      break;
    case is_instruction_expression:
      html_print_expression(instruction_expression( i ), false);
      break;
    case is_instruction_goto:
      /*      statement g = instruction_goto(i);
       entity el = statement_label(g);
       string l = entity_local_name(el) + sizeof(LABEL_PREFIX) -1;
       printf("%s", strdup( concatenate( "goto ", l, SEMICOLON, NULL ) ) );*/
      break;
      /* add switch, forloop break, continue, return instructions here*/
    default:
      html_output(" Instruction not implemented" NL, false);
      break;
  }
  end_block("instruction", true);

  end_block("statement", true);
}


void html_print_symbol_table(void)
{
  /* Print symbol table */
  html_print(NL "<li><ul class=\"symbolTable\">" NL);
  begin_block("Symbol table", true);
  list entities = gen_filter_tabulated(gen_true, entity_domain);
  FOREACH(entity, e, entities ) {
    html_print_entity_full(e);
  }
  html_print("<li class=\"endSymbolTable\">&nbsp;</li>" NL "</ul></li>" NL);
  end_block("Symbol table", true);
}

bool html_prettyprint(const string mod_name)
{

  statement module_statement = (statement)db_get_memory_resource(DBR_CODE,
                                                                 mod_name,
                                                                 true);

  set_current_module_statement(module_statement);

  /* Set the current module entity required to have many things
     working in PIPS: */
  set_current_module_entity(module_name_to_entity(mod_name));


  /* The debug is now controled by this environment variable name: */
  debug_on("HTML_PRETTYPRINT_DEBUG_LEVEL");
  pips_assert("Statement should be OK at entry...",
              statement_consistent_p(module_statement));

  // Prepare the output file
  string html_file_name = db_build_file_resource_name( "RI", mod_name, ".ri.html" );
  string output_file = strdup( concatenate( db_get_current_workspace_directory( ),
                                        "/",
                                        html_file_name,
                                        NULL ) );
  pips_debug(2,"Output in %s",output_file);
  FILE *fp = safe_fopen( output_file, "w" );
  html_set_output(fp);

  /* Print current module */
  html_print(NL "<li><ul class=\"module\">" NL);
  begin_block(mod_name, true);
  html_print_statement(module_statement);
  end_block(mod_name, true);
  html_print("<li class=\"endmodule\">&nbsp;</li>" NL "</ul></li>" NL);


  if(get_bool_property("HTML_PRETTYPRINT_SYMBOL_TABLE")) {
    html_print_symbol_table();
  }

  // Reset output file
  html_set_output(0);
  safe_fclose( fp, output_file );


  DB_PUT_FILE_RESOURCE( DBR_HTML_IR_FILE, strdup( mod_name ), html_file_name );

  reset_current_module_statement();
  reset_current_module_entity();

  return true;
}

bool html_prettyprint_symbol_table(const string module)
{
  pips_debug(1, "working on %s", module);

  // Prepare the output file
  string html_file_name =
    db_build_file_resource_name( "Symbols", "", ".symbols.html" );
  string output_file =
    strdup( concatenate( db_get_current_workspace_directory( ),
                         "/", html_file_name, NULL ) );
  FILE *fp = safe_fopen( output_file, "w" );
  html_set_output(fp);

  // Reset output file
  html_set_output(0);
  safe_fclose( fp, output_file );

  DB_PUT_FILE_RESOURCE( DBR_HTML_IR_FILE, "", html_file_name );

  return true;
}
