/* Warning! Do not modify this file that is automatically generated! */
/* Modify src/Libs/effects-convex/effects-convex-local.h instead, to add your own modifications. */

/* header file built by cproto */

#ifndef  effects_convex_header_included
#define  effects_convex_header_included
/*

  $Id: effects-convex-local.h 23065 2016-03-02 09:05:50Z coelho $

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

/* simulation of the type region */

#define region effect
#define REGION EFFECT  /* for casts */
#define region_CAST REGION_CAST
#define REGION_CAST(x) REGION(x)
#define REGION_ EFFECT_  /* for some left casts */
#define REGION_TYPE EFFECT_TYPE
#define REGION_NEWGEN_DOMAIN EFFECT_NEWGEN_DOMAIN
#define gen_REGION_cons gen_effect_cons
#define gen_region_cons gen_effect_cons

#define region_undefined effect_undefined
#define region_undefined_p(reg)  effect_undefined_p((reg))
#define make_region(reference,action,approximation,system) \
  make_effect(make_cell(is_cell_reference, (reference)),   \
		(action), (approximation),	\
		make_descriptor(is_descriptor_convex,system))
/* To be avoided. Use region_any_reference() instead.
   I definitely remove this one : it is too dangerous. BC.
   FC: it should not compile, rather than compile and fail???
*/
/*
  // v1
  #define region_reference(reg)                             \
    preference_reference(cell_preference(effect_cell(reg)))
  // v2
  #define region_reference(reg)                                   \
    pips_internal_error("region_reference is not defined anymore \n")
  // v3: nothing, should break compilation or link
*/
#define region_any_reference(reg) \
  (cell_preference_p(effect_cell(reg)) ? preference_reference(cell_preference(effect_cell(reg))) : cell_reference(effect_cell(reg)))
#define region_action(reg) effect_action(reg)
#define region_approximation(reg) effect_approximation(reg)
#define region_context(reg) effect_context(reg)
#define region_cell(reg) effect_cell(reg)

#define region_entity(reg) reference_variable(region_any_reference(reg))
#define region_action_tag(reg) action_tag(effect_action(reg))
#define region_approximation_tag(reg) \
    approximation_tag(effect_approximation(reg))
#define region_system_(reg) \
    descriptor_convex_(effect_descriptor(reg))
#define region_system(reg) \
    descriptor_convex(effect_descriptor(reg))

/* useful region macros */

#define region_read_p(reg) (action_tag(effect_action(reg))==is_action_read)
#define region_write_p(reg) (action_tag(effect_action(reg))==is_action_write)
#define region_may_p(reg) \
        (approximation_tag(effect_approximation(reg)) == is_approximation_may)
#define region_must_p(reg) \
        (approximation_tag(effect_approximation(reg)) == is_approximation_must)
#define region_exact_p(reg) \
        (approximation_tag(effect_approximation(reg)) == is_approximation_exact)
#define region_empty_p(reg) sc_empty_p(region_system(reg))
#define region_rn_p(reg) sc_rn_p(region_system(reg))
#define region_scalar_p(reg) (anywhere_effect_p(reg) || entity_scalar_p(region_entity(reg)))
#define effect_region_p(e) (descriptor_convex_p(effect_descriptor(e)))

/* consistency checking */
#define debug_regions_consistency(l_reg)\
ifdebug(1){regions_consistent_p(l_reg);}
#define debug_region_consistency(reg)\
ifdebug(1){region_consistent_p(reg);}

/* convenient debug messages */
#define debug_print_region(level, message, region) \
  ifdebug(level) { pips_debug(level, "%s\n", message); print_region(region);}

/* other things */



#define R_RW 0
#define R_IN 1
#define R_OUT 2

#define SEQUENTIAL_REGION_SUFFIX ".reg"
#define SEQUENTIAL_PROPER_REGION_SUFFIX ".preg"
#define USER_REGION_SUFFIX ".ureg"
#define SEQUENTIAL_IN_REGION_SUFFIX ".inreg"
#define USER_IN_REGION_SUFFIX ".uinreg"
#define SEQUENTIAL_OUT_REGION_SUFFIX ".outreg"
#define USER_OUT_REGION_SUFFIX ".uoutreg"

#define NB_MAX_ARRAY_DIM 12
/* interface.c */
extern bool summary_pointer_regions(const string /*module_name*/);
extern bool summary_regions(const string /*module_name*/);
extern bool may_pointer_regions(const string /*module_name*/);
extern bool may_regions(const string /*module_name*/);
extern bool must_pointer_regions(const string /*module_name*/);
extern bool must_pointer_regions_with_points_to(const string /*module_name*/);
extern bool must_regions(const string /*module_name*/);
extern bool must_regions_with_points_to(const string /*module_name*/);
extern bool must_regions_with_pointer_values(const string /*module_name*/);
extern bool in_summary_regions(const string /*module_name*/);
extern bool in_regions(const string /*module_name*/);
extern bool out_summary_regions(const string /*module_name*/);
extern bool out_regions(const string /*module_name*/);
extern bool print_code_proper_pointer_regions(const string /*module_name*/);
extern bool print_code_pointer_regions(const string /*module_name*/);
extern bool print_code_inv_pointer_regions(const string /*module_name*/);
extern bool print_code_proper_regions(const string /*module_name*/);
extern bool print_source_proper_regions(const string /*module_name*/);
extern bool print_code_regions(const string /*module_name*/);
extern bool print_source_regions(const string /*module_name*/);
extern bool print_code_inv_regions(const string /*module_name*/);
extern bool print_source_inv_regions(const string /*module_name*/);
extern bool print_code_in_regions(const string /*module_name*/);
extern bool print_source_in_regions(const string /*module_name*/);
extern bool print_code_out_regions(const string /*module_name*/);
extern bool print_source_out_regions(const string /*module_name*/);
extern bool print_code_as_a_graph_regions(const string /*mod_name*/);
extern bool print_code_as_a_graph_in_regions(const string /*mod_name*/);
extern bool print_code_as_a_graph_out_regions(const string /*mod_name*/);
extern list regions_of_expression(expression /*e*/, transformer /*context*/);
extern list proper_regions_of_expression(expression /*e*/, transformer /*context*/);
extern list proper_regions_of_expressions(list /*l_exp*/, transformer /*context*/);
extern bool print_call_graph_with_regions(const string /*module_name*/);
extern bool print_call_graph_with_in_regions(const string /*module_name*/);
extern bool print_call_graph_with_out_regions(const string /*module_name*/);
extern bool print_icfg_with_regions(const string /*module_name*/);
extern bool print_icfg_with_in_regions(const string /*module_name*/);
extern bool print_icfg_with_out_regions(const string /*module_name*/);
extern bool print_icfg_with_loops_regions(const string /*module_name*/);
extern bool print_icfg_with_loops_in_regions(const string /*module_name*/);
extern bool print_icfg_with_loops_out_regions(const string /*module_name*/);
extern bool print_icfg_with_control_regions(const string /*module_name*/);
extern bool print_icfg_with_control_in_regions(const string /*module_name*/);
extern bool print_icfg_with_control_out_regions(const string /*module_name*/);
/* translation.c */
extern void region_translation_statistics_init(bool /*stat_p*/);
extern void region_translation_statistics_close(const char */*mod_name*/, const char */*prefix*/);
extern void region_translation_init(entity /*ent_1*/, reference /*rf_1*/, entity /*ent_2*/, reference /*rf_2*/, Value /*offset_1_m_2*/);
extern void append_declaration_sc_if_exact_without_constraints(effect /*r*/);
extern effect region_translation(effect /*reg_1*/, entity /*func_1*/, reference /*rf_1*/, entity /*ent_2*/, entity /*func_2*/, reference /*rf_2*/, Value /*offset_1_m_2*/, bool /*backward_p*/);
extern void set_region_interprocedural_translation(void);
extern void reset_region_interprocedural_translation(void);
extern void set_interprocedural_translation_context_sc(entity /*callee*/, list /*real_args*/);
extern void set_translation_context_sc(Psysteme /*sc*/);
extern Psysteme get_translation_context_sc(void);
extern void reset_translation_context_sc(void);
extern void set_forward_arguments_to_eliminate(void);
extern void set_backward_arguments_to_eliminate(entity /*func*/);
extern void set_arguments_to_eliminate(list /*l_args*/);
extern void reset_arguments_to_eliminate(void);
extern list get_arguments_to_eliminate(void);
extern void convex_region_descriptor_translation(effect /*eff*/);
extern void convex_cell_reference_with_address_of_cell_reference_translation(reference /*input_ref*/, descriptor /*input_desc*/, reference /*address_of_ref*/, descriptor /*address_of_desc*/, int /*nb_common_indices*/, reference */*output_ref*/, descriptor */*output_desc*/, bool */*exact_p*/);
extern void convex_cell_reference_with_value_of_cell_reference_translation(reference /*input_ref*/, descriptor /*input_desc*/, reference /*value_of_ref*/, descriptor /*value_of_desc*/, int /*nb_common_indices*/, reference */*output_ref*/, descriptor */*output_desc*/, bool */*exact_p*/);
extern void convex_cell_with_address_of_cell_translation(cell /*input_cell*/, descriptor /*input_desc*/, cell /*address_of_cell*/, descriptor /*address_of_desc*/, int /*nb_common_indices*/, cell */*output_cell*/, descriptor */*output_desc*/, bool */*exact_p*/);
extern void convex_cell_with_value_of_cell_translation(cell /*input_cell*/, descriptor /*input_desc*/, cell /*value_of_cell*/, descriptor /*value_of_desc*/, int /*nb_common_indices*/, cell */*output_cell*/, descriptor */*output_desc*/, bool */*exact_p*/);
/* methods.c */
extern void set_methods_for_convex_effects(void);
extern void set_methods_for_convex_rw_effects(void);
extern void set_methods_for_convex_rw_pointer_effects(void);
extern void set_methods_for_convex_in_out_effects(void);
extern bool in_out_methods_p(void);
extern void init_convex_rw_prettyprint(const char */*module_name*/);
extern void init_convex_rw_regions(const char */*module_name*/);
extern void init_convex_inout_prettyprint(const char */*module_name*/);
extern void init_convex_in_out_regions(const char */*module_name*/);
extern void reset_convex_rw_regions(const char */*module_name*/);
extern void reset_convex_in_out_regions(const char */*module_name*/);
extern void init_convex_summary_rw_regions(const char */*module_name*/);
extern void reset_convex_summary_rw_regions(const char */*module_name*/);
extern void init_convex_summary_in_out_regions(const char */*module_name*/);
extern void reset_convex_prettyprint(const char */*module_name*/);
extern void reset_convex_summary_in_out_regions(const char */*module_name*/);
/* compose.c */
extern list convex_regions_transformer_compose(list /*l_reg*/, transformer /*trans*/);
extern list convex_regions_inverse_transformer_compose(list /*l_reg*/, transformer /*trans*/);
extern list convex_regions_precondition_compose(list /*l_reg*/, transformer /*context*/, bool /*on_scalar_p*/);
/* unary_operators.c */
extern effect reference_to_convex_region(reference /*ref*/, action /*act*/, bool /*use_preference_p*/);
extern list convex_regions_descriptor_variable_rename(list /*l_reg*/, entity /*old_ent*/, entity /*new_ent*/);
extern descriptor loop_convex_descriptor_make(loop /*l*/);
extern list convex_regions_loop_normalize(list /*l_reg*/, entity /*index*/, range /*r*/, entity */*new_index*/, descriptor /*d*/, bool /*descriptor_normalize_p*/);
extern list convex_regions_union_over_range(list /*l_reg*/, entity /*index*/, range /*r*/, descriptor /*d*/);
extern descriptor vector_to_convex_descriptor(Pvecteur /*v*/);
extern void convex_effects_descriptor_normalize(list /*l_eff*/);
/* sc_enumerate.c */
extern Ppolynome sc_enumerate(Psysteme /*ordered_sc*/, Pbase /*ordered_base*/, const char */*variable_names*/[]);
/* utils.c */
extern entity make_beta_entity(int /*n*/);
extern list beta_entities_list(int /*beta_min*/, int /*beta_max*/);
extern bool add_precondition_to_scalar_convex_regions;
extern void regions_init(void);
extern void regions_end(void);
extern effect region_dup(effect /*reg*/);
extern list regions_dup(list /*l_reg*/);
extern void regions_free(list /*l_reg*/);
extern void region_free(effect /*reg*/);
extern list region_add_to_regions(effect /*reg*/, list /*l_reg*/);
extern list regions_add_region(list /*l_reg*/, effect /*reg*/);
extern list regions_add_context(list /*l_reg*/, transformer /*context*/);
extern Psysteme region_sc_normalize(Psysteme /*sc_reg*/, int /*level*/);
extern Psysteme cell_system_sc_append_and_normalize(Psysteme /*sc1*/, Psysteme /*sc2*/, int /*level*/);
extern void region_sc_append_and_normalize(effect /*reg*/, Psysteme /*sc*/, int /*level*/);
extern list regions_sc_append_and_normalize(list /*l_reg*/, Psysteme /*sc*/, bool /*arrays_only*/, bool /*scalars_only*/, int /*level*/);
extern list array_regions_sc_append_and_normalize(list /*l_reg*/, Psysteme /*sc*/, int /*level*/);
extern void region_sc_append(effect /*reg*/, Psysteme /*sc*/, bool /*nredund_p*/);
extern list regions_sc_append(list /*l_reg*/, Psysteme /*sc*/, bool /*arrays_only*/, bool /*scalars_only*/, bool /*nredund_p*/);
extern list all_regions_sc_append(list /*l_reg*/, Psysteme /*sc*/, bool /*nredund_p*/);
extern list scalar_regions_sc_append(list /*l_reg*/, Psysteme /*sc*/, bool /*nredund_p*/);
extern list array_regions_sc_append(list /*l_reg*/, Psysteme /*sc*/, bool /*nredund_p*/);
extern list regions_remove_variables_regions(list /*l_reg*/, list /*l_var*/);
extern void array_regions_variable_rename(list /*l_reg*/, entity /*old_entity*/, entity /*new_entity*/);
extern void all_regions_variable_rename(list /*l_reg*/, entity /*old_entity*/, entity /*new_entity*/);
extern void region_value_substitute(effect /*reg*/, entity /*e1*/, entity /*e2*/);
extern list region_entities_cfc_variables(effect /*reg*/, list /*l_ent*/);
extern list sc_entities_cfc_variables(Psysteme /*sc*/, list /*l_ent*/);
extern list region_to_list(effect /*reg*/);
extern list region_to_may_region_list(effect /*reg*/);
extern list regions_to_nil_list(effect /*reg1*/, effect /*reg2*/);
extern list region_to_nil_list(effect /*reg*/);
extern list regions_to_write_regions(list /*l_reg*/);
extern list regions_read_regions(list /*l_reg*/);
extern list regions_write_regions(list /*l_reg*/);
extern reference make_pointed_regions_reference(entity /*ent*/, bool /*indexed_p*/);
extern reference make_regions_reference(entity /*ent*/);
extern effect make_reference_region(reference /*ref*/, action /*tac*/);
extern reference make_regions_psi_reference(entity /*ent*/);
extern effect reference_whole_region(reference /*ref*/, action /*tac*/);
extern effect entity_whole_region(entity /*e*/, action /*tac*/);
extern list region_to_store_independent_region_list(effect /*reg*/, bool /*force_may_p*/);
extern void convex_region_add_expression_dimension(effect /*reg*/, expression /*exp*/);
extern void convex_region_change_ith_dimension_expression(effect /*reg*/, expression /*exp*/, int /*i*/);
extern void convex_region_descriptor_remove_ith_dimension(effect /*reg*/, int /*i*/);
extern effect convex_effect_field_to_rank_conversion(effect /*input_effect*/);
extern effect region_append(effect /*eff1*/, effect /*eff2*/);
extern entity make_phi_entity(int /*n*/);
extern list phi_entities_list(int /*phi_min*/, int /*phi_max*/);
extern expression make_phi_expression(int /*n*/);
extern bool sc_add_phi_equation(Psysteme */*psc*/, expression /*expr*/, int /*dim*/, bool /*is_eg*/, bool /*is_phi_first*/);
extern void phi_first_sort_base(Pbase */*ppbase*/);
extern int base_nb_phi(Pbase /*b*/);
extern entity make_psi_entity(int /*n*/);
extern list psi_entities_list(int /*psi_min*/, int /*psi_max*/);
extern expression make_psi_expression(int /*n*/);
extern int base_nb_psi(Pbase /*b*/);
extern entity make_rho_entity(int /*n*/);
extern list rho_entities_list(int /*rho_min*/, int /*rho_max*/);
extern bool rho_reference_p(reference /*ref*/);
extern bool rho_region_p(effect /*reg*/);
extern expression make_rho_expression(int /*n*/);
extern int base_nb_rho(Pbase /*b*/);
extern list cell_reference_phi_cfc_variables(reference /*ref*/, Psysteme /*sc*/);
extern list region_phi_cfc_variables(effect /*reg*/);
extern void psi_to_phi_region(effect /*reg*/);
extern void phi_to_psi_region(effect /*reg*/);
extern bool psi_reference_p(reference /*ref*/);
extern bool psi_region_p(effect /*reg*/);
extern bool exact_regions_p(void);
extern bool must_regions_p(void);
extern bool array_bounds_p(void);
extern bool disjunct_regions_p(void);
extern bool op_statistics_p(void);
extern void reset_op_statistics(void);
extern void get_regions_properties(void);
extern void get_in_out_regions_properties(void);
extern void region_sc_sort(Psysteme /*sc*/, Pbase /*sorted_base*/);
extern Pcontrainte region_constraints_sort(Pcontrainte /*c*/, Pbase /*sorted_base*/, bool /*equality_p*/);
extern Pbase region_sorted_base_dup(effect /*reg*/);
extern Psysteme entity_declaration_sc(entity /*e*/);
extern list variables_to_int_variables(list /*l_var*/);
extern list variables_to_old_variables(list /*l_var*/);
extern Psysteme sc_list_variables_rename(Psysteme /*sc*/, list /*l_var*/, list /*l_var_new*/);
extern list function_formal_parameters(entity /*func*/);
extern char *func_entity_name(entity /*e*/);
extern bool same_common_variables_p(entity /*e1*/, entity /*e2*/);
extern Psysteme sc_loop_proper_precondition(loop /*l*/);
extern bool empty_convex_context_p(transformer /*context*/);
extern string region_to_string(effect /*reg*/);
extern bool rectangular_region_p(effect /*r*/);
extern bool rectangular_must_region_p(entity /*var*/, statement /*s*/);
extern effect region_rectangular_hull(effect /*reg*/, bool /*nofield*/);
extern expression region_reference_to_expression(reference /*r*/);
extern Ppolynome region_enumerate(effect /*reg*/);
/* debug.c */
extern bool region_consistent_p(effect /*reg*/);
extern bool regions_consistent_p(list /*l_reg*/);
/* interprocedural.c */
extern void convex_regions_translation_init(entity /*callee*/, list /*real_args*/, bool /*backward_p*/);
extern void convex_regions_translation_end(void);
extern void reset_out_summary_regions_list(void);
extern void update_out_summary_regions_list(list /*l_out*/);
extern list get_out_summary_regions_list(void);
extern list out_regions_from_caller_to_callee(entity /*caller*/, entity /*callee*/);
extern void out_regions_from_call_site_to_callee(call /*c*/);
extern list in_regions_of_external(entity /*func*/, list /*real_args*/, transformer /*context*/);
extern list regions_of_external(entity /*func*/, list /*real_args*/, transformer /*context*/, bool /*proper*/);
extern list convex_regions_backward_translation(entity /*func*/, list /*real_args*/, list /*l_reg*/, transformer /*context*/);
extern list convex_regions_forward_translation(entity /*callee*/, list /*real_args*/, list /*l_reg*/, transformer /*context*/);
extern list regions_backward_translation(entity /*func*/, list /*real_args*/, list /*func_regions*/, transformer /*context*/, bool /*proper*/);
extern list c_convex_effects_on_formal_parameter_backward_translation(list /*l_sum_eff*/, expression /*real_arg*/, transformer /*context*/);
extern list regions_forward_translation(entity /*func*/, list /*real_args*/, list /*l_reg*/, transformer /*context*/);
extern list c_convex_effects_on_actual_parameter_forward_translation(entity /*callee*/, expression /*real_exp*/, entity /*formal_ent*/, list /*l_reg*/, transformer /*context*/);
/* prettyprint.c */
extern string region_sc_to_string(string /*s*/, Psysteme /*ps*/);
extern text text_region(effect /*reg*/);
extern void print_region_sc(effect /*r*/);
extern text text_inout_array_regions(list /*l*/);
extern text text_rw_array_regions(list /*l*/);
extern text text_copyinout_array_regions(list /*l*/);
extern text text_private_array_regions(list /*l*/);
extern text get_text_regions(const string /*module_name*/);
extern text get_text_in_regions(const string /*module_name*/);
extern text get_text_out_regions(const string /*module_name*/);
extern void print_rw_regions(list /*l*/);
extern void print_inout_regions(list /*l*/);
extern void print_copyinout_regions(list /*l*/);
extern void print_private_regions(list /*l*/);
extern void print_regions(list /*l*/);
extern void print_region(effect /*r*/);
extern void print_regions_op_statistics(char */*mod_name*/, int /*regions_type*/);
/* binary_operators.c */
extern void reset_binary_op_statistics(void);
extern void print_umust_statistics(char */*mod_name*/, char */*prefix*/);
extern void print_umay_statistics(char */*mod_name*/, char */*prefix*/);
extern void print_dsup_statistics(char */*mod_name*/, char */*prefix*/);
extern void print_dinf_statistics(char */*mod_name*/, char */*prefix*/);
extern list RegionsMayUnion(list /*l1*/, list /*l2*/, bool (* /*union_combinable_p*/)(effect, effect));
extern list RegionsMustUnion(list /*l1*/, list /*l2*/, bool (* /*union_combinable_p*/)(effect, effect));
extern list RegionsIntersection(list /*l1*/, list /*l2*/, bool (* /*intersection_combinable_p*/)(effect, effect));
extern list RegionsEntitiesIntersection(list /*l1*/, list /*l2*/, bool (* /*intersection_combinable_p*/)(effect, effect));
extern list RegionsSupDifference(list /*l1*/, list /*l2*/, bool (* /*difference_combinable_p*/)(effect, effect));
extern list RegionsInfDifference(list /*l1*/, list /*l2*/, bool (* /*difference_combinable_p*/)(effect, effect));
extern list RegionsEntitiesInfDifference(list /*l1*/, list /*l2*/, bool (* /*difference_combinable_p*/)(effect, effect));
extern list region_must_union(effect /*r1*/, effect /*r2*/);
extern list region_may_union(effect /*r1*/, effect /*r2*/);
extern list region_union(effect /*r1*/, effect /*r2*/, bool /*must_p*/);
extern effect regions_must_convex_hull(effect /*r1*/, effect /*r2*/);
extern bool convex_cells_inclusion_p(cell /*c1*/, descriptor /*d1*/, cell /*c2*/, descriptor /*d2*/, bool */*exact_p*/);
extern list region_intersection(effect /*reg1*/, effect /*reg2*/);
extern bool convex_cells_intersection_p(cell /*c1*/, descriptor /*d1*/, cell /*c2*/, descriptor /*d2*/, bool */*exact_p*/);
extern list region_entities_intersection(effect /*r1*/, effect /*r2*/);
extern list region_sup_difference(effect /*reg1*/, effect /*reg2*/);
extern list region_inf_difference(effect /*reg1*/, effect /*reg2*/);
/* old_projection.c */
extern void reset_proj_op_statistics(void);
extern void print_proj_op_statistics(char */*mod_name*/, char */*prefix*/);
extern entity loop_regions_normalize(list /*l_reg*/, entity /*index*/, range /*l_range*/, bool */*normalized_regions_p*/, bool /*sc_loop_p*/, Psysteme */*psc_loop*/);
extern void project_regions_along_loop_index(list /*l_reg*/, entity /*index*/, range /*l_range*/);
extern void project_regions_along_variables(list /*l_reg*/, list /*l_var*/);
extern void project_regions_along_parameters(list /*l_reg*/, list /*l_param*/);
extern void project_regions_with_transformer(list /*l_reg*/, transformer /*trans*/, list /*l_var_not_proj*/);
extern void project_regions_with_transformer_inverse(list /*l_reg*/, transformer /*trans*/, list /*l_var_not_proj*/);
extern void regions_transformer_apply(list /*l_reg*/, transformer /*trans*/, list /*l_var_not_proj*/, bool /*backward_p*/);
extern void regions_remove_phi_variables(list /*l_reg*/);
extern list regions_dynamic_elim(list /*l_reg*/);
extern void region_remove_phi_variables(effect /*reg*/);
extern Psysteme cell_reference_system_remove_psi_variables(reference /*ref*/, Psysteme /*sc*/, bool */*exact_p*/);
extern void region_remove_psi_variables(effect /*reg*/);
extern Psysteme cell_reference_system_remove_rho_variables(reference /*ref*/, Psysteme /*sc*/, bool */*exact_p*/);
extern void region_remove_rho_variables(effect /*reg*/);
extern void region_remove_beta_variables(effect /*reg*/);
extern void region_non_exact_projection_along_parameters(effect /*reg*/, list /*l_param*/);
extern void region_exact_projection_along_parameters(effect /*reg*/, list /*l_param*/);
extern void region_non_exact_projection_along_variables(effect /*reg*/, list /*l_var*/);
extern void region_exact_projection_along_variables(effect /*reg*/, list /*l_var*/);
extern Psysteme cell_reference_sc_exact_projection_along_variable(reference /*ref*/, Psysteme /*sc*/, entity /*var*/, bool */*exact_p*/);
extern void region_exact_projection_along_variable(effect /*reg*/, entity /*var*/);
extern bool region_projection_along_index_safe_p(entity /*index*/, range /*l_range*/);
extern void region_dynamic_var_elim(effect /*reg*/);
extern Psysteme sc_projection_ofl_along_list_of_variables(Psysteme /*ps*/, list /*l_var*/);
extern void region_sc_projection_along_variables_ofl_ctrl(Psysteme */*psc*/, Pvecteur /*pv*/, int /*ofl_ctrl*/);
/* eval.c */
extern bool convex_cell_reference_preceding_p(reference /*r1*/, descriptor /*d1*/, reference /*r2*/, descriptor /*d2*/, transformer /*current_precondition*/, bool /*strict_p*/, bool */*exact_p*/);
extern bool convex_cell_preceding_p(cell /*c1*/, descriptor /*d1*/, cell /*c2*/, descriptor /*d2*/, transformer /*current_precondition*/, bool /*strict_p*/, bool */*exact_p*/);
extern void simple_reference_to_convex_reference_conversion(reference /*ref*/, reference */*output_ref*/, descriptor */*output_desc*/);
extern void simple_cell_to_convex_cell_conversion(cell /*input_cell*/, cell */*output_cell*/, descriptor */*output_desc*/);
extern list eval_convex_cell_with_points_to(cell /*c*/, descriptor /*d*/, list /*ptl*/, bool */*exact_p*/, transformer /*current_precondition*/);
extern list convex_effect_to_constant_path_effects_with_points_to(effect /*eff*/);
extern list convex_effect_find_aliased_paths_with_pointer_values(effect /*eff*/, statement /*s*/);
extern list convex_effect_to_constant_path_effects_with_pointer_values(effect /*eff*/);
#endif /*  effects_convex_header_included */
