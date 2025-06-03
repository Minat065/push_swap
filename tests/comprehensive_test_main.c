/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comprehensive_test_main.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:30:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 20:30:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tests.h"

int main(void)
{
	printf("🧪 Starting Comprehensive Push_swap Test Suite\n");
	printf("===============================================\n\n");

	// Stack operation tests
	printf("📚 STACK OPERATIONS TESTS\n");
	printf("--------------------------\n");
	RUN_TEST(test_stack_init);
	RUN_TEST(test_push_pop_operations);
	RUN_TEST(test_swap_operations);
	RUN_TEST(test_push_operations);
	RUN_TEST(test_rotate_operations);
	RUN_TEST(test_reverse_rotate_operations);

	// Input validation tests
	printf("\n🔍 INPUT VALIDATION TESTS\n");
	printf("-------------------------\n");
	RUN_TEST(test_input_validation);
	RUN_TEST(test_duplicate_detection);
	RUN_TEST(test_integer_limits);

	// Sorting algorithm tests
	printf("\n🔄 SORTING ALGORITHM TESTS\n");
	printf("--------------------------\n");
	RUN_TEST(test_is_sorted_function);
	RUN_TEST(test_sort_two_elements);
	RUN_TEST(test_sort_three_elements);
	RUN_TEST(test_sort_small_arrays);

	// Print final summary
	print_test_summary();

	if (tests_failed == 0)
	{
		printf("\n🎉 All tests passed! Ready for checker implementation.\n");
		return (0);
	}
	else
	{
		printf("\n❌ Some tests failed. Fix issues before proceeding.\n");
		return (1);
	}
}