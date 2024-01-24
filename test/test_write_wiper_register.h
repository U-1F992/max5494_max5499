#include "max5494_max5499.h"
#include "mock_spi.h"

int test_write_wiper_register(void)
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
            fprintf(stderr, "[test_write_wiper_register:%d] unexpected error on init: %d\n", i, ret);
            return 1;
        }

        ret = max5494_max5499_write_wiper_register(&rdac, cases[i].ra, cases[i].d);
        if (ret != MAX5494_MAX5499_OK)
        {
            fprintf(stderr, "[test_write_wiper_register:%d] unexpected error on write_wiper_register: %d\n", i, ret);
            return 1;
        }

        if (spi.length != 3)
        {
            fprintf(stderr, "[test_write_wiper_register:%d] length expected: 3, actual: %d\n", i, spi.length);
            return 1;
        }
        for (size_t j = 0; j < 3; j++)
        {
            if (spi.written[j] != cases[i].expected[j])
            {
                fprintf(stderr, "[test_write_wiper_register:%d] data expected: %#x %#x %#x, actual: %#x %#x %#x\n",
                        i, cases[i].expected[0], cases[i].expected[1], cases[i].expected[2], spi.written[0], spi.written[1], spi.written[2]);
                return 1;
            }
        }
    }

    return 0;
}

int test_write_wiper_register_propagates_error(void)
{
    typedef struct test_case_t
    {
        max5494_max5499_errno_t (*spi_write)(max5494_max5499_spi_interface_t *, uint8_t *, size_t);

        max5494_max5499_errno_t expected;
    } test_case_t;

    test_case_t cases[] = {
        {.spi_write = mock_spi_write_einval, .expected = MAX5494_MAX5499_EINVAL},
        {.spi_write = mock_spi_write_eio, .expected = MAX5494_MAX5499_EIO},
    };
    size_t length = sizeof(cases) / sizeof(test_case_t);

    for (size_t i = 0; i < length; i++)
    {
        max5494_max5499_t rdac;
        mock_spi_t spi;
        spi.parent.write = cases[i].spi_write;

        max5494_max5499_errno_t ret = max5494_max5499_init(&rdac, (max5494_max5499_spi_interface_t *)&spi);
        if (ret != MAX5494_MAX5499_OK)
        {
            fprintf(stderr, "[test_write_wiper_register_propagates_error:%d] unexpected error on init: %d\n", i, ret);
            return 1;
        }

        ret = max5494_max5499_write_wiper_register(&rdac, MAX5494_MAX5499_RA0, 0);
        if (ret != cases[i].expected)
        {
            fprintf(stderr, "[test_write_wiper_register_propagates_error:%d] expected: %d, actual: %d\n", i, cases[i].expected, ret);
            return 1;
        }
    }

    return 0;
}