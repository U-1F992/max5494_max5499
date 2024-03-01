#ifndef TEST_H_
#define TEST_H_

#include <max5494_max5499.h>

#include <assert.h>
#include <stdbool.h>

#define TEST_FOR(cases) \
    TestCase case_;     \
    for (size_t i = 0; case_ = (cases)[i], i < sizeof((cases)) / sizeof(TestCase); i++)

#define TEST_MAX5494_MAX5499_ERROR(e) ((e) == MAX5494_MAX5499_OK       ? "MAX5494_MAX5499_OK"     \
                                       : (e) == MAX5494_MAX5499_EIO    ? "MAX5494_MAX5499_EIO"    \
                                       : (e) == MAX5494_MAX5499_EINVAL ? "MAX5494_MAX5499_EINVAL" \
                                                                       : "")

#define TEST_ASSERT_EQUAL_MAX5494_MAX5499_ERROR_RET(expected_ret, actual_ret)                             \
    if ((expected_ret) != (actual_ret))                                                                   \
    {                                                                                                     \
        fprintf(stderr, "index: %d, expected_ret: %s, actual_ret: %s\n",                                  \
                i, TEST_MAX5494_MAX5499_ERROR((expected_ret)), TEST_MAX5494_MAX5499_ERROR((actual_ret))); \
        cnt++;                                                                                            \
        continue;                                                                                         \
    }

#define TEST_SPI_SIZE ((size_t)8)

typedef struct TestSPIWriter
{
    MAX5494_MAX5499SPIWriter parent;
    uint8_t last_data[TEST_SPI_SIZE];
    size_t last_size;
} TestSPIWriter;

MAX5494_MAX5499ErrNo test_spi_writer_write(MAX5494_MAX5499SPIWriter *parent, uint8_t data[], size_t size)
{
    assert(parent != NULL);
    assert(size < TEST_SPI_SIZE);
    TestSPIWriter *writer = (TestSPIWriter *)parent;
    for (size_t i = 0; i < size; i++)
    {
        writer->last_data[i] = data[i];
    }
    writer->last_size = size;
    return MAX5494_MAX5499_OK;
}

#define test_spi_writer_init(writer) ((writer)->parent.write = test_spi_writer_write, \
                                      (writer)->last_size = 0,                        \
                                      (void)0)

bool test_spi_data_equals(uint8_t arr0[], uint8_t arr1[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr0[i] != arr1[i])
        {
            return false;
        }
    }
    return true;
}

#define TEST_ASSERT_EQUAL_SPI_WRITTEN(expected_data, expected_size, actual_data, actual_size) \
    if ((expected_size) != (actual_size))                                                     \
    {                                                                                         \
        fprintf(stderr, "index: %d, expected_size: %d, actual_size: %d\n",                    \
                i, (expected_size), (actual_size));                                           \
        cnt++;                                                                                \
        continue;                                                                             \
    }                                                                                         \
    if (!test_spi_data_equals((expected_data), (actual_data), (actual_size)))                 \
    {                                                                                         \
        fprintf(stderr, "index: %d,\n", i);                                                   \
        for (size_t j = 0; j < (actual_size); j++)                                            \
        {                                                                                     \
            if ((expected_data)[j] != (actual_data)[j])                                       \
            {                                                                                 \
                fprintf(stderr, "  expected_data[%d]: %d, actual_data[%d]: %d\n",             \
                        j, (expected_data)[j], j, (actual_data)[j]);                          \
            }                                                                                 \
        }                                                                                     \
        cnt++;                                                                                \
        continue;                                                                             \
    }

#endif // TEST_H_