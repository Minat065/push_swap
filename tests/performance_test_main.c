/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   performance_test_main.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:30:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 21:30:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tests.h"

int main(void)
{
	printf("🚀 Push_swap Performance Test Suite\n");
	printf("====================================\n\n");

	// Performance tests
	printf("⚡ PERFORMANCE TESTS\n");
	printf("--------------------\n");
	RUN_TEST(test_100_elements_performance);
	RUN_TEST(test_500_elements_performance);
	RUN_TEST(test_performance_multiple_runs);

	// Print final summary
	print_test_summary();

	if (tests_failed == 0)
	{
		printf("\n🎯 Performance targets met!\n");
		return (0);
	}
	else
	{
		printf("\n⚠️  Performance optimization needed.\n");
		return (1);
	}
}