#include "max5494_max5499.h"

#include <stdio.h>
#include <stdlib.h>

static int test_init(void)
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
            fprintf(stderr, "[test_init:%d] expected: %d, actual: %d", i, cases[i].expected, ret);
            return 1;
        }
    }

    return 0;
}

typedef struct mock_spi_t
{
    max5494_max5499_spi_interface_t parent;
    uint8_t *written;
    size_t length;
} mock_spi_t;

static max5494_max5499_errno_t mock_spi_write(max5494_max5499_spi_interface_t *parent, uint8_t *data, size_t length)
{
    mock_spi_t *self = (mock_spi_t *)parent;

    self->written = (uint8_t *)malloc(sizeof(uint8_t) * length);
    for (size_t i = 0; i < length; i++)
    {
        self->written[i] = data[i];
    }
    self->length = length;

    return MAX5494_MAX5499_OK;
}

static int test_write_wiper_register(void)
{
    typedef struct test_case_t
    {
        max5494_max5499_register_t ra;
        uint16_t d;

        uint8_t *expected;
    } test_case_t;

    uint8_t expected_0[] = {
        0b00000001U, 0b00000000U, 0b00000000U};
    uint8_t expected_1[] = {
        0b00000010U, 0b00000000U, 0b00000000U};
    uint8_t expected_2[] = {
        0b00000001U, 0b10101010U, 0b11000000U};

    test_case_t cases[] = {
        {.ra = MAX5494_MAX5499_RA0, .d = 0U, .expected = expected_0},
        {.ra = MAX5494_MAX5499_RA1, .d = 0U, .expected = expected_1},
        {.ra = MAX5494_MAX5499_RA0, .d = 0b1010101011U, .expected = expected_2},
    };
    size_t length = sizeof(cases) / sizeof(test_case_t);

    for (size_t i = 0; i < length; i++)
    {
        max5494_max5499_t rdac;
        mock_spi_t spi;
        spi.parent.write = mock_spi_write;

        max5494_max5499_errno_t ret = max5494_max5499_init(&rdac, (max5494_max5499_spi_interface_t *)&spi);
        if (ret != MAX5494_MAX5499_OK)
        {
            fprintf(stderr, "[test_write_wiper_register:%d] unexpected error on init: %d", i, ret);
            return 1;
        }

        ret = max5494_max5499_write_wiper_register(&rdac, cases[i].ra, cases[i].d);
        if (ret != MAX5494_MAX5499_OK)
        {
            fprintf(stderr, "[test_write_wiper_register:%d] unexpected error on write_wiper_register: %d", i, ret);
            return 1;
        }

        if (spi.length != 3)
        {
            fprintf(stderr, "[test_write_wiper_register:%d] length expected: 3, actual: %d", i, spi.length);
            free(spi.written);
            return 1;
        }
        for (size_t j = 0; j < 3; j++)
        {
            if (spi.written[j] != cases[i].expected[j])
            {
                fprintf(stderr, "[test_write_wiper_register:%d] data expected: %#x %#x %#x, actual: %#x %#x %#x",
                        i, cases[i].expected[0], cases[i].expected[1], cases[i].expected[2], spi.written[0], spi.written[1], spi.written[2]);
                free(spi.written);
                return 1;
            }
        }

        free(spi.written);
    }

    return 0;
}

static int test_write_nv_register(void)
{
    typedef struct test_case_t
    {
        max5494_max5499_register_t ra;
        uint16_t d;

        uint8_t *expected;
    } test_case_t;

    uint8_t expected_0[] = {
        0b00010001U, 0b00000000U, 0b00000000U};
    uint8_t expected_1[] = {
        0b00010010U, 0b00000000U, 0b00000000U};
    uint8_t expected_2[] = {
        0b00010001U, 0b10101010U, 0b11000000U};

    test_case_t cases[] = {
        {.ra = MAX5494_MAX5499_RA0, .d = 0U, .expected = expected_0},
        {.ra = MAX5494_MAX5499_RA1, .d = 0U, .expected = expected_1},
        {.ra = MAX5494_MAX5499_RA0, .d = 0b1010101011U, .expected = expected_2},
    };
    size_t length = sizeof(cases) / sizeof(test_case_t);

    for (size_t i = 0; i < length; i++)
    {
        max5494_max5499_t rdac;
        mock_spi_t spi;
        spi.parent.write = mock_spi_write;

        max5494_max5499_errno_t ret = max5494_max5499_init(&rdac, (max5494_max5499_spi_interface_t *)&spi);
        if (ret != MAX5494_MAX5499_OK)
        {
            fprintf(stderr, "[test_write_nv_register:%d] unexpected error on init: %d", i, ret);
            return 1;
        }

        ret = max5494_max5499_write_nv_register(&rdac, cases[i].ra, cases[i].d);
        if (ret != MAX5494_MAX5499_OK)
        {
            fprintf(stderr, "[test_write_nv_register:%d] unexpected error on write_wiper_register: %d", i, ret);
            return 1;
        }

        if (spi.length != 3)
        {
            fprintf(stderr, "[test_write_nv_register:%d] length expected: 3, actual: %d", i, spi.length);
            free(spi.written);
            return 1;
        }
        for (size_t j = 0; j < 3; j++)
        {
            if (spi.written[j] != cases[i].expected[j])
            {
                fprintf(stderr, "[test_write_nv_register:%d] data expected: %#x %#x %#x, actual: %#x %#x %#x",
                        i, cases[i].expected[0], cases[i].expected[1], cases[i].expected[2], spi.written[0], spi.written[1], spi.written[2]);
                free(spi.written);
                return 1;
            }
        }

        free(spi.written);
    }

    return 0;
}

int main(void)
{
    int (*tests[])(void) = {
        test_init,
        test_write_wiper_register,
        test_write_nv_register};
    size_t length = sizeof(tests) / sizeof(int (*)(void));

    for (size_t i = 0; i < length; i++)
    {
        int ret = tests[i]();
        if (ret != 0)
        {
            return ret;
        }
    }

    printf("OK");
    return 0;
}