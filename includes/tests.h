/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:28:29 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/21 18:55:37 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "push_swap.h"
# include <assert.h>
# include <stdio.h>
# include <string.h>

// Test framework macros
#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s\n", message); \
            return 0; \
        } \
        printf("PASS: %s\n", message); \
    } while(0)

#define RUN_TEST(test_func) \
    do { \
        printf("Running %s...\n", #test_func); \
        if (test_func()) { \
            printf("✓ %s passed\n\n", #test_func); \
            tests_passed++; \
        } else { \
            printf("✗ %s failed\n\n", #test_func); \
            tests_failed++; \
        } \
        total_tests++; \
    } while(0)

// Stack operation tests
int test_stack_init(void);
int test_push_pop_operations(void);
int test_swap_operations(void);
int test_push_operations(void);
int test_rotate_operations(void);
int test_reverse_rotate_operations(void);

// Input validation tests
int test_input_validation(void);
int test_duplicate_detection(void);
int test_integer_limits(void);

// Sorting algorithm tests
int test_is_sorted_function(void);
int test_sort_two_elements(void);
int test_sort_three_elements(void);
int test_sort_small_arrays(void);

// Integration tests for checker
int test_instruction_parsing(void);
int test_operation_sequence(void);
int test_final_state_validation(void);

// Performance tests
int test_100_elements_performance(void);
int test_performance_multiple_runs(void);

// 500 elements specific tests
void test_500_elements_performance(void);
void test_500_worst_case(void);
int *generate_random_500(void);
void reset_operation_count(void);
int get_operation_count(void);
void clear_stack(t_stack **stack);
int stack_size(t_stack *stack);

// Helper functions
t_stack *create_test_stack(int size);
void free_test_stack(t_stack *stack);
void setup_stack_with_values(t_stack *stack, int *values, int count);
int arrays_equal(int *arr1, int *arr2, int size);
void print_test_summary(void);

// Silent operation functions for testing (no output)
void swap_a_silent(t_stack *stack_a);
void swap_b_silent(t_stack *stack_b);
int push_atob_silent(t_stack *src, t_stack *dst);
int push_btoa_silent(t_stack *src, t_stack *dst);
void rotate_a_silent(t_stack *stack_a);
void rotate_b_silent(t_stack *stack_b);
void reverse_rotate_a_silent(t_stack *stack_a);
void reverse_rotate_b_silent(t_stack *stack_b);

// Global test counters
extern int tests_passed;
extern int tests_failed;
extern int total_tests;

// Legacy display tests (keep for compatibility)
void test_display_stack_when_stack_is_empty(t_stack *s);
void test_display_stack_when_stack_has_one_element(t_stack *s);
void test_display_stack_when_stack_has_two_elements(t_stack *s);
void test_display_stack_when_stack_has_three_elements(t_stack *s);
void test_display_stack_when_stack_has_four_elements(t_stack *s);

#endif