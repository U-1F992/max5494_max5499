#include "max5494_max5499.h"

int test_init(void)
{
    max5494_max5499_t rdac;
    max5494_max5499_spi_interface_t spi;

    typedef struct test_case_t
    {
        max5494_max5499_t *rdac;
        max5494_max5499_spi_interface_t *spi;

        max5494_max5499_errno_t expected;
    } test_case_t;

    test_case_t cases[] = {
        {.rdac = &rdac, .spi = &spi, .expected = MAX5494_MAX5499_OK},
        {.rdac = &rdac, .spi = NULL, .expected = MAX5494_MAX5499_EINVAL},
        {.rdac = NULL, .spi = &spi, .expected = MAX5494_MAX5499_EINVAL},
        {.rdac = NULL, .spi = NULL, .expected = MAX5494_MAX5499_EINVAL},
    };
    size_t length = sizeof(cases) / sizeof(test_case_t);

    for (size_t i = 0; i < length; i++)
    {
        max5494_max5499_errno_t ret = max5494_max5499_init(cases[i].rdac, cases[i].spi);
        if (ret != cases[i].expected)
        {
            fprintf(stderr, "[test_init:%d] expected: %d, actual: %d\n", i, cases[i].expected, ret);
            return 1;
        }
    }

    return 0;
}