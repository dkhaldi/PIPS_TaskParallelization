pointer01, 03, 05 and 07 are interprocedural cases, with about the same C codes
pointer 02, 04 and 06 are procedural, with about the same C codes

pointer 01 and 02 use CONSTANT_PATH_EFFECTS=FALSE, ALIASING_ACROSS_TYPE=FALSE
pointer 03 and 04 use CONSTANT_PATH_EFFECTS=TRUE, ALIASING_ACROSS_TYPE=FALSE
pointer 05 and 06 use TRANSFORMERS_INTER_FULL_WITH_POINTS_TO, i.e. points-to information, ALIASING_ACROSS_TYPE=FALSE

pointer07 uses CONSTANT_PATH_EFFECTS=FALSE, ALIASING_ACROSS_TYPE=TRUE
          (very similar to pointer01)
pointer08 copy of pointer01.c, CONSTANT_PATH_EFFECTS=TRUE,
	  ALIASING_ACROSS_TYPES=TRUE, EFFECTS_IGNORE_DEREFERENCING=TRUE,
	  The results are weird looking since the update of b thru a pointer
	   dereferencement is ignored

pointer09 modified version of pointer01.c to check the impact of
	  CONSTANT_PATH_EFFECTS=FALSE when pointers are updated.
	  Correctness requires EFFECTS_POINTER_MODIFICATION_CHECKING=TRUE

pointer10 a variant of pointer08 to show the wrong results obtained with 
          EFFECTS_IGNORE_DEREFERENCING=TRUE

# The struct files were added by Fabien Coelho, Corinne Ancourt and
# Francois Irigoin to check struct and struct field assignments,
# struct as formal parameters, and struct returned by a function

struct00: requires pointer and struct and interprocedural analysis

struct01: requires struct analysis with global variables (no pointers,
          almost no interprocedural analysis); integer fields

struct02: requires struct plus interprocedural analysis limited to
          global variables (no pointers)

struct03: same as struct02, but with a "static" global variable

struct04: uses IOs, pointers to files, reading of struct files, model
	  of IO functions; the file pointer breaks the analysis

struct05: subset of struct02 to check a summary transformer

struct06: modified version of struct04 using "stdin" instead of "file"
          to avoid clogging the analysis with an anywhere effect

struct07: simplified version of struct06 to check the analysis of fscanf()

struct08: copy of struct04 analyzed with property
          ALIASING_ACROSS_TYPES set to false; the effect computation seems wrong

struct09: excerpt from struct08 to debug effect computation
          ALIASING_ACROSS_TYPE is not implemented  

struct10: struct assignment

struct11: check side effects in struct assignment

struct12: passage d'un champ de structure en argument reel/effectif

struct13: nested struct

struct14: copy of Corinne's version of read_config_file()

struct15: same as struct14, but uses "stdin" instead of pointer "file"

struct16: same as struct14, but point-to information is used to
          disambiguate pointer "file"

struct17: nested struct

struct18: array of struct with constant subscript expressions

struct19: array field in struct, in fact in an array of structs

struct20: array declaration using struct fields (bug due to separate compilation)

struct21: same as struct20, but with two different source files

struct22: array of struct + struct assignment of array elements with
          constant subscripts

struct23: same as struct22, but with varying subscripts

struct24: call returning a struct

struct25: struct as formal parameter (similar to struct24)

struct26:  bug submitted by Corinne

struct27:  excerpt from struct26 (1st bug: do not analyze not analyzable fields)

struct30:  excerpt from struct26 (2nd bug: do not anlyze assignment to array elements)

struct31: simplified version of struct11.c; assignment of an
	  unanalyzabe rhs to a struct; no side effects in rhs
