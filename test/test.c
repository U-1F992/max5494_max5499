#include <max5494_max5499.h>
#include "test.h"

#include <stdio.h>

static int test_init(void)
{
    printf("* test_init\n");
    int cnt = 0;

    typedef struct test_case_t
    {
        max5494_max5499_t *max5494_max5499;
        max5494_max5499_spi_writer_t *writer;

        max5494_max5499_error_t expected_ret;
        max5494_max5499_spi_writer_t *expected_writer;
    } test_case_t;

    max5494_max5499_t max5494_max5499[4];
    max5494_max5499_spi_writer_t writer[4];

    test_case_t cases[] = {{.max5494_max5499 = NULL, /*          */ .writer = NULL, /* */ .expected_ret = MAX5494_MAX5499_EINVAL},
                           {.max5494_max5499 = &max5494_max5499[1], .writer = NULL, /* */ .expected_ret = MAX5494_MAX5499_EINVAL},
                           {.max5494_max5499 = NULL, /*          */ .writer = &writer[2], .expected_ret = MAX5494_MAX5499_EINVAL},
                           {.max5494_max5499 = &max5494_max5499[3], .writer = &writer[3], .expected_ret = MAX5494_MAX5499_OK, .expected_writer = &writer[3]}};

    TEST_FOR(cases)
    {
        max5494_max5499_error_t actual_ret = max5494_max5499_init(case_.max5494_max5499, case_.writer);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != MAX5494_MAX5499_OK)
        {
            continue;
        }

        max5494_max5499_spi_writer_t *actual_writer = case_.max5494_max5499->writer_;
        if (case_.expected_writer != actual_writer)
        {
            fprintf(stderr, "index: %d, expected_writer: %#x, actual_writer: %#x\n",
                    i, case_.expected_writer, actual_writer);
            cnt++;
            continue;
        }
    }

    return cnt;
}

static int test_write_wiper_register_1(void)
{
    printf("* test_write_wiper_register_1\n");
    int cnt = 0;

    typedef struct test_case_t
    {
        uint16_t d;

        max5494_max5499_error_t expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } test_case_t;

    test_case_t cases[] = {{.d = 0, /*                    */ .expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00000001'00000000'00______ */ (uint8_t[]){0x01, 0x00, 0x00}, .expected_size = 3},
                           {.d = 1, /*                    */ .expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00000001'00000000'01______ */ (uint8_t[]){0x01, 0x00, 0x40}, .expected_size = 3},
                           {.d = /* 0b011'11111111 */ 0x3FF, .expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00000001'11111111'11______ */ (uint8_t[]){0x01, 0xFF, 0xC0}, .expected_size = 3},
                           {.d = /* 0b100'00000000 */ 0x400, .expected_ret = MAX5494_MAX5499_EINVAL}};
    size_t size = sizeof(cases) / sizeof(test_case_t);

    TEST_FOR(cases)
    {
        max5494_max5499_t *max5494_max5499_null = NULL;
        max5494_max5499_error_t actual_ret = max5494_max5499_write_wiper_register_1(max5494_max5499_null, case_.d);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_PRE_RET(MAX5494_MAX5499_EINVAL, actual_ret);

        max5494_max5499_t max5494_max5499;
        test_spi_writer_t writer;
        test_spi_writer_init(&writer);
        assert(max5494_max5499_init(&max5494_max5499, (max5494_max5499_spi_writer_t *)&writer) == MAX5494_MAX5499_OK);

        actual_ret = max5494_max5499_write_wiper_register_1(&max5494_max5499, case_.d);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != MAX5494_MAX5499_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

static int test_write_wiper_register_2(void)
{
    printf("* test_write_wiper_register_2\n");
    int cnt = 0;

    typedef struct test_case_t
    {
        uint16_t d;

        max5494_max5499_error_t expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } test_case_t;

    test_case_t cases[] = {{.d = 0, /*                    */ .expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00000010'00000000'00______ */ (uint8_t[]){0x02, 0x00, 0x00}, .expected_size = 3},
                           {.d = 1, /*                    */ .expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00000010'00000000'01______ */ (uint8_t[]){0x02, 0x00, 0x40}, .expected_size = 3},
                           {.d = /* 0b011'11111111 */ 0x3FF, .expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00000010'11111111'11______ */ (uint8_t[]){0x02, 0xFF, 0xC0}, .expected_size = 3},
                           {.d = /* 0b100'00000000 */ 0x400, .expected_ret = MAX5494_MAX5499_EINVAL}};
    size_t size = sizeof(cases) / sizeof(test_case_t);

    TEST_FOR(cases)
    {
        max5494_max5499_t *max5494_max5499_null = NULL;
        max5494_max5499_error_t actual_ret = max5494_max5499_write_wiper_register_2(max5494_max5499_null, case_.d);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_PRE_RET(MAX5494_MAX5499_EINVAL, actual_ret);

        max5494_max5499_t max5494_max5499;
        test_spi_writer_t writer;
        test_spi_writer_init(&writer);
        assert(max5494_max5499_init(&max5494_max5499, (max5494_max5499_spi_writer_t *)&writer) == MAX5494_MAX5499_OK);

        actual_ret = max5494_max5499_write_wiper_register_2(&max5494_max5499, case_.d);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != MAX5494_MAX5499_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

static int test_write_nv_register_1(void)
{
    printf("* test_write_nv_register_1\n");
    int cnt = 0;

    typedef struct test_case_t
    {
        uint16_t d;

        max5494_max5499_error_t expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } test_case_t;

    test_case_t cases[] = {{.d = 0, /*                    */ .expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00010001'00000000'00______ */ (uint8_t[]){0x11, 0x00, 0x00}, .expected_size = 3},
                           {.d = 1, /*                    */ .expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00010001'00000000'01______ */ (uint8_t[]){0x11, 0x00, 0x40}, .expected_size = 3},
                           {.d = /* 0b011'11111111 */ 0x3FF, .expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00010001'11111111'11______ */ (uint8_t[]){0x11, 0xFF, 0xC0}, .expected_size = 3},
                           {.d = /* 0b100'00000000 */ 0x400, .expected_ret = MAX5494_MAX5499_EINVAL}};
    size_t size = sizeof(cases) / sizeof(test_case_t);

    TEST_FOR(cases)
    {
        max5494_max5499_t *max5494_max5499_null = NULL;
        max5494_max5499_error_t actual_ret = max5494_max5499_write_nv_register_1(max5494_max5499_null, case_.d);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_PRE_RET(MAX5494_MAX5499_EINVAL, actual_ret);

        max5494_max5499_t max5494_max5499;
        test_spi_writer_t writer;
        test_spi_writer_init(&writer);
        assert(max5494_max5499_init(&max5494_max5499, (max5494_max5499_spi_writer_t *)&writer) == MAX5494_MAX5499_OK);

        actual_ret = max5494_max5499_write_nv_register_1(&max5494_max5499, case_.d);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != MAX5494_MAX5499_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

static int test_write_nv_register_2(void)
{
    printf("* test_write_nv_register_2\n");
    int cnt = 0;

    typedef struct test_case_t
    {
        uint16_t d;

        max5494_max5499_error_t expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } test_case_t;

    test_case_t cases[] = {{.d = 0, /*                    */ .expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00010010'00000000'00______ */ (uint8_t[]){0x12, 0x00, 0x00}, .expected_size = 3},
                           {.d = 1, /*                    */ .expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00010010'00000000'01______ */ (uint8_t[]){0x12, 0x00, 0x40}, .expected_size = 3},
                           {.d = /* 0b011'11111111 */ 0x3FF, .expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00010010'11111111'11______ */ (uint8_t[]){0x12, 0xFF, 0xC0}, .expected_size = 3},
                           {.d = /* 0b100'00000000 */ 0x400, .expected_ret = MAX5494_MAX5499_EINVAL}};
    size_t size = sizeof(cases) / sizeof(test_case_t);

    TEST_FOR(cases)
    {
        max5494_max5499_t *max5494_max5499_null = NULL;
        max5494_max5499_error_t actual_ret = max5494_max5499_write_nv_register_2(max5494_max5499_null, case_.d);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_PRE_RET(MAX5494_MAX5499_EINVAL, actual_ret);

        max5494_max5499_t max5494_max5499;
        test_spi_writer_t writer;
        test_spi_writer_init(&writer);
        assert(max5494_max5499_init(&max5494_max5499, (max5494_max5499_spi_writer_t *)&writer) == MAX5494_MAX5499_OK);

        actual_ret = max5494_max5499_write_nv_register_2(&max5494_max5499, case_.d);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != MAX5494_MAX5499_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

static int test_copy_wiper_register_1_to_nv_register_1(void)
{
    printf("* test_copy_wiper_register_1_to_nv_register_1\n");
    int cnt = 0;

    typedef struct test_case_t
    {
        max5494_max5499_error_t expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } test_case_t;

    test_case_t cases[] = {{.expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00100001 */ (uint8_t[]){0x21}, .expected_size = 1}};
    size_t size = sizeof(cases) / sizeof(test_case_t);

    TEST_FOR(cases)
    {
        max5494_max5499_t *max5494_max5499_null = NULL;
        max5494_max5499_error_t actual_ret = max5494_max5499_copy_wiper_register_1_to_nv_register_1(max5494_max5499_null);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_PRE_RET(MAX5494_MAX5499_EINVAL, actual_ret);

        max5494_max5499_t max5494_max5499;
        test_spi_writer_t writer;
        test_spi_writer_init(&writer);
        assert(max5494_max5499_init(&max5494_max5499, (max5494_max5499_spi_writer_t *)&writer) == MAX5494_MAX5499_OK);

        actual_ret = max5494_max5499_copy_wiper_register_1_to_nv_register_1(&max5494_max5499);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != MAX5494_MAX5499_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

static int test_copy_wiper_register_2_to_nv_register_2(void)
{
    printf("* test_copy_wiper_register_2_to_nv_register_2\n");
    int cnt = 0;

    typedef struct test_case_t
    {
        max5494_max5499_error_t expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } test_case_t;

    test_case_t cases[] = {{.expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00100010 */ (uint8_t[]){0x22}, .expected_size = 1}};

    TEST_FOR(cases)
    {
        max5494_max5499_t *max5494_max5499_null = NULL;
        max5494_max5499_error_t actual_ret = max5494_max5499_copy_wiper_register_2_to_nv_register_2(max5494_max5499_null);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_PRE_RET(MAX5494_MAX5499_EINVAL, actual_ret);

        max5494_max5499_t max5494_max5499;
        test_spi_writer_t writer;
        test_spi_writer_init(&writer);
        assert(max5494_max5499_init(&max5494_max5499, (max5494_max5499_spi_writer_t *)&writer) == MAX5494_MAX5499_OK);

        actual_ret = max5494_max5499_copy_wiper_register_2_to_nv_register_2(&max5494_max5499);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != MAX5494_MAX5499_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

static int test_copy_wiper_registers_to_nv_registers_simultaneously(void)
{
    printf("* test_copy_wiper_registers_to_nv_registers_simultaneously\n");
    int cnt = 0;

    typedef struct test_case_t
    {
        max5494_max5499_error_t expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } test_case_t;

    test_case_t cases[] = {{.expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00100011 */ (uint8_t[]){0x23}, .expected_size = 1}};
    size_t size = sizeof(cases) / sizeof(test_case_t);

    TEST_FOR(cases)
    {
        max5494_max5499_t *max5494_max5499_null = NULL;
        max5494_max5499_error_t actual_ret = max5494_max5499_copy_wiper_registers_to_nv_registers_simultaneously(max5494_max5499_null);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_PRE_RET(MAX5494_MAX5499_EINVAL, actual_ret);

        max5494_max5499_t max5494_max5499;
        test_spi_writer_t writer;
        test_spi_writer_init(&writer);
        assert(max5494_max5499_init(&max5494_max5499, (max5494_max5499_spi_writer_t *)&writer) == MAX5494_MAX5499_OK);

        actual_ret = max5494_max5499_copy_wiper_registers_to_nv_registers_simultaneously(&max5494_max5499);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != MAX5494_MAX5499_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

static int test_copy_nv_register_1_to_wiper_register_1(void)
{
    printf("* test_copy_nv_register_1_to_wiper_register_1\n");
    int cnt = 0;

    typedef struct test_case_t
    {
        max5494_max5499_error_t expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } test_case_t;

    test_case_t cases[] = {{.expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00110001 */ (uint8_t[]){0x31}, .expected_size = 1}};

    TEST_FOR(cases)
    {
        max5494_max5499_t *max5494_max5499_null = NULL;
        max5494_max5499_error_t actual_ret = max5494_max5499_copy_nv_register_1_to_wiper_register_1(max5494_max5499_null);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_PRE_RET(MAX5494_MAX5499_EINVAL, actual_ret);

        max5494_max5499_t max5494_max5499;
        test_spi_writer_t writer;
        test_spi_writer_init(&writer);
        assert(max5494_max5499_init(&max5494_max5499, (max5494_max5499_spi_writer_t *)&writer) == MAX5494_MAX5499_OK);

        actual_ret = max5494_max5499_copy_nv_register_1_to_wiper_register_1(&max5494_max5499);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != MAX5494_MAX5499_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

static int test_copy_nv_register_2_to_wiper_register_2(void)
{
    printf("* test_copy_nv_register_2_to_wiper_register_2\n");
    int cnt = 0;

    typedef struct test_case_t
    {
        max5494_max5499_error_t expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } test_case_t;

    test_case_t cases[] = {{.expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00110010 */ (uint8_t[]){0x32}, .expected_size = 1}};

    TEST_FOR(cases)
    {
        max5494_max5499_t *max5494_max5499_null = NULL;
        max5494_max5499_error_t actual_ret = max5494_max5499_copy_nv_register_2_to_wiper_register_2(max5494_max5499_null);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_PRE_RET(MAX5494_MAX5499_EINVAL, actual_ret);

        max5494_max5499_t max5494_max5499;
        test_spi_writer_t writer;
        test_spi_writer_init(&writer);
        assert(max5494_max5499_init(&max5494_max5499, (max5494_max5499_spi_writer_t *)&writer) == MAX5494_MAX5499_OK);

        actual_ret = max5494_max5499_copy_nv_register_2_to_wiper_register_2(&max5494_max5499);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != MAX5494_MAX5499_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

static int test_copy_nv_registers_to_wiper_registers_simultaneously(void)
{
    printf("* test_copy_nv_registers_to_wiper_registers_simultaneously\n");
    int cnt = 0;

    typedef struct test_case_t
    {
        max5494_max5499_error_t expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } test_case_t;

    test_case_t cases[] = {{.expected_ret = MAX5494_MAX5499_OK, .expected_data = /* 0b00110011 */ (uint8_t[]){0x33}, .expected_size = 1}};

    TEST_FOR(cases)
    {
        max5494_max5499_t *max5494_max5499_null = NULL;
        max5494_max5499_error_t actual_ret = max5494_max5499_copy_nv_registers_to_wiper_registers_simultaneously(max5494_max5499_null);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_PRE_RET(MAX5494_MAX5499_EINVAL, actual_ret);

        max5494_max5499_t max5494_max5499;
        test_spi_writer_t writer;
        test_spi_writer_init(&writer);
        assert(max5494_max5499_init(&max5494_max5499, (max5494_max5499_spi_writer_t *)&writer) == MAX5494_MAX5499_OK);

        actual_ret = max5494_max5499_copy_nv_registers_to_wiper_registers_simultaneously(&max5494_max5499);
        TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != MAX5494_MAX5499_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

int main(void)
{
    int cnt = 0;

    cnt += test_init();
    cnt += test_write_wiper_register_1();
    cnt += test_write_wiper_register_2();
    cnt += test_write_nv_register_1();
    cnt += test_write_nv_register_2();
    cnt += test_copy_wiper_register_1_to_nv_register_1();
    cnt += test_copy_wiper_register_2_to_nv_register_2();
    cnt += test_copy_wiper_registers_to_nv_registers_simultaneously();
    cnt += test_copy_nv_register_1_to_wiper_register_1();
    cnt += test_copy_nv_register_2_to_wiper_register_2();
    cnt += test_copy_nv_registers_to_wiper_registers_simultaneously();

    if (cnt == 0)
    {
        printf("OK\n");
        return 0;
    }
    else
    {
        fprintf(stderr, "%d errors found.\n", cnt);
        return 1;
    }
}