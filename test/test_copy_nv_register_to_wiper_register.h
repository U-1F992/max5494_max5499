#include "max5494_max5499.h"
#include "mock_spi.h"

int test_copy_nv_register_to_wiper_register(void)
{
    typedef struct test_case_t
    {
        max5494_max5499_register_t ra;

        uint8_t expected;
    } test_case_t;

    test_case_t cases[] = {
        {.ra = MAX5494_MAX5499_RA0, .expected = 0b00110001U},
        {.ra = MAX5494_MAX5499_RA1, .expected = 0b00110010U},
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
            fprintf(stderr, "[test_copy_nv_register_to_wiper_register:%d] unexpected error on init: %d\n", i, ret);
            return 1;
        }

        ret = max5494_max5499_copy_nv_register_to_wiper_register(&rdac, cases[i].ra);
        if (ret != MAX5494_MAX5499_OK)
        {
            fprintf(stderr, "[test_copy_nv_register_to_wiper_register:%d] unexpected error on copy_nv_register_to_wiper_register: %d\n", i, ret);
            return 1;
        }

        if (spi.length != 1)
        {
            fprintf(stderr, "[test_copy_nv_register_to_wiper_register:%d] length expected: 1, actual: %d\n", i, spi.length);
            return 1;
        }
        if (spi.written[0] != cases[i].expected)
        {
            fprintf(stderr, "[test_copy_nv_register_to_wiper_register:%d] data expected: %#x, actual: %#x\n", i, cases[i].expected, spi.written[0]);
            return 1;
        }
    }

    return 0;
}

int test_copy_nv_register_to_wiper_register_propagates_error(void)
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
            fprintf(stderr, "[test_copy_nv_register_to_wiper_register_propagates_error:%d] unexpected error on init: %d\n", i, ret);
            return 1;
        }

        ret = max5494_max5499_copy_nv_register_to_wiper_register(&rdac, MAX5494_MAX5499_RA0);
        if (ret != cases[i].expected)
        {
            fprintf(stderr, "[test_copy_nv_register_to_wiper_register_propagates_error:%d] expected: %d, actual: %d\n", i, cases[i].expected, ret);
            return 1;
        }
    }

    return 0;
}

int test_copy_nv_registers_to_wiper_registers_simultaneously(void)
{
    uint16_t expected = 0b00110011U;

    max5494_max5499_t rdac;
    mock_spi_t spi;
    spi.parent.write = mock_spi_write;

    max5494_max5499_errno_t ret = max5494_max5499_init(&rdac, (max5494_max5499_spi_interface_t *)&spi);
    if (ret != MAX5494_MAX5499_OK)
    {
        fprintf(stderr, "[test_copy_nv_registers_to_wiper_registers_simultaneously] unexpected error on init: %d\n", ret);
        return 1;
    }

    ret = max5494_max5499_copy_nv_registers_to_wiper_registers_simultaneously(&rdac);
    if (ret != MAX5494_MAX5499_OK)
    {
        fprintf(stderr, "[test_copy_nv_registers_to_wiper_registers_simultaneously] unexpected error on copy_nv_registers_to_wiper_registers_simultaneously: %d\n", ret);
        return 1;
    }

    if (spi.length != 1)
    {
        fprintf(stderr, "[test_copy_nv_registers_to_wiper_registers_simultaneously] length expected: 1, actual: %d\n", spi.length);
        return 1;
    }
    if (spi.written[0] != expected)
    {
        fprintf(stderr, "[test_copy_nv_registers_to_wiper_registers_simultaneously] data expected: %#x, actual: %#x\n", expected, spi.written[0]);
        return 1;
    }

    return 0;
}

int test_copy_nv_registers_to_wiper_registers_simultaneously_propagates_error(void)
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
            fprintf(stderr, "[test_copy_nv_registers_to_wiper_registers_simultaneously_propagates_error:%d] unexpected error on init: %d\n", i, ret);
            return 1;
        }

        ret = max5494_max5499_copy_nv_registers_to_wiper_registers_simultaneously(&rdac);
        if (ret != cases[i].expected)
        {
            fprintf(stderr, "[test_copy_nv_registers_to_wiper_registers_simultaneously_propagates_error:%d] expected: %d, actual: %d\n", i, cases[i].expected, ret);
            return 1;
        }
    }

    return 0;
}