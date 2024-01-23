#include "max5494_max5499.h"

extern inline max5494_max5499_errno_t max5494_max5499_init(max5494_max5499_t *rdac, max5494_max5499_spi_interface_t *spi);

static max5494_max5499_errno_t _write_d(max5494_max5499_t *rdac, max5494_max5499_command_t c, max5494_max5499_register_t ra, uint16_t d)
{
    if (MAX5494_MAX5499_D_MAX < d)
    {
        return MAX5494_MAX5499_EINVAL;
    }

    uint8_t _d[] = {(uint8_t)((c << 4) | ra),
                    (uint8_t)(d >> 2),
                    (uint8_t)(((d & 0b11U) << 6))};
    return rdac->spi->write(rdac->spi, _d, 3);
}

static max5494_max5499_errno_t _write(max5494_max5499_t *rdac, max5494_max5499_command_t c, max5494_max5499_register_t ra)
{
    uint8_t _d[] = {(uint8_t)((c << 4) | ra)};
    return rdac->spi->write(rdac->spi, _d, 1);
}

max5494_max5499_errno_t max5494_max5499_write_wiper_register(max5494_max5499_t *rdac, max5494_max5499_register_t ra, uint16_t d)
{
    return _write_d(rdac, MAX5494_MAX5499_WRITE_WIPER_REGISTER, ra, d);
}

max5494_max5499_errno_t max5494_max5499_write_nv_register(max5494_max5499_t *rdac, max5494_max5499_register_t ra, uint16_t d)
{
    return _write_d(rdac, MAX5494_MAX5499_WRITE_NV_REGISTER, ra, d);
}

max5494_max5499_errno_t max5494_max5499_copy_wiper_register_to_nv_register(max5494_max5499_t *rdac, max5494_max5499_register_t ra)
{
    return _write(rdac, MAX5494_MAX5499_COPY_WIPER_REGISTER_TO_NV_REGISTER, ra);
}

extern inline max5494_max5499_errno_t max5494_max5499_copy_wiper_registers_to_nv_registers_simultaneously(max5494_max5499_t *rdac);

max5494_max5499_errno_t max5494_max5499_copy_nv_register_to_wiper_register(max5494_max5499_t *rdac, max5494_max5499_register_t ra)
{
    return _write(rdac, MAX5494_MAX5499_COPY_NV_REGISTER_TO_WIPER_REGISTER, ra);
}

extern inline max5494_max5499_errno_t max5494_max5499_copy_nv_registers_to_wiper_registers_simultaneously(max5494_max5499_t *rdac);