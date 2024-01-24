#ifndef MOCK_SPI_H_
#define MOCK_SPI_H_

#include "max5494_max5499.h"

typedef struct mock_spi_t
{
    max5494_max5499_spi_interface_t parent;
    uint8_t written[256];
    size_t length;
} mock_spi_t;

max5494_max5499_errno_t mock_spi_write(max5494_max5499_spi_interface_t *parent, uint8_t *data, size_t length)
{
    mock_spi_t *self = (mock_spi_t *)parent;

    for (size_t i = 0; i < length; i++)
    {
        self->written[i] = data[i];
    }
    self->length = length;

    return MAX5494_MAX5499_OK;
}

max5494_max5499_errno_t mock_spi_write_einval(max5494_max5499_spi_interface_t *parent, uint8_t *data, size_t length)
{
    return MAX5494_MAX5499_EINVAL;
}

max5494_max5499_errno_t mock_spi_write_eio(max5494_max5499_spi_interface_t *parent, uint8_t *data, size_t length)
{
    return MAX5494_MAX5499_EIO;
}

#endif