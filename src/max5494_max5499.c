#include <max5494_max5499.h>
#include "internal.h"

MAX5494_MAX5499ErrNo max5494_max5499_init(MAX5494_MAX5499 *max5494_max5499, MAX5494_MAX5499SPIWriter *writer)
{
    if (max5494_max5499 == NULL ||
        writer == NULL)
    {
        return MAX5494_MAX5499_EINVAL;
    }

    max5494_max5499->writer = writer;

    return MAX5494_MAX5499_OK;
}

MAX5494_MAX5499ErrNo max5494_max5499_write_wiper_register_1(MAX5494_MAX5499 *max5494_max5499, uint16_t d)
{
    return max5494_max5499_internal_write_d((max5494_max5499), MAX5494_MAX5499_WRITE_WIPER_REGISTER, MAX5494_MAX5499_RA0, (d));
}

MAX5494_MAX5499ErrNo max5494_max5499_write_wiper_register_2(MAX5494_MAX5499 *max5494_max5499, uint16_t d)
{
    return max5494_max5499_internal_write_d((max5494_max5499), MAX5494_MAX5499_WRITE_WIPER_REGISTER, MAX5494_MAX5499_RA1, (d));
}

MAX5494_MAX5499ErrNo max5494_max5499_write_nv_register_1(MAX5494_MAX5499 *max5494_max5499, uint16_t d)
{
    return max5494_max5499_internal_write_d((max5494_max5499), MAX5494_MAX5499_WRITE_NV_REGISTER, MAX5494_MAX5499_RA0, (d));
}

MAX5494_MAX5499ErrNo max5494_max5499_write_nv_register_2(MAX5494_MAX5499 *max5494_max5499, uint16_t d)
{
    return max5494_max5499_internal_write_d((max5494_max5499), MAX5494_MAX5499_WRITE_NV_REGISTER, MAX5494_MAX5499_RA1, (d));
}

MAX5494_MAX5499ErrNo max5494_max5499_copy_wiper_register_1_to_nv_register_1(MAX5494_MAX5499 *max5494_max5499)
{
    return max5494_max5499_internal_write((max5494_max5499), MAX5494_MAX5499_COPY_WIPER_REGISTER_TO_NV_REGISTER, MAX5494_MAX5499_RA0);
}

MAX5494_MAX5499ErrNo max5494_max5499_copy_wiper_register_2_to_nv_register_2(MAX5494_MAX5499 *max5494_max5499)
{
    return max5494_max5499_internal_write((max5494_max5499), MAX5494_MAX5499_COPY_WIPER_REGISTER_TO_NV_REGISTER, MAX5494_MAX5499_RA1);
}

MAX5494_MAX5499ErrNo max5494_max5499_copy_wiper_registers_to_nv_registers_simultaneously(MAX5494_MAX5499 *max5494_max5499)
{
    return max5494_max5499_internal_write((max5494_max5499), MAX5494_MAX5499_COPY_WIPER_REGISTER_TO_NV_REGISTER, MAX5494_MAX5499_RA0 | MAX5494_MAX5499_RA1);
}

MAX5494_MAX5499ErrNo max5494_max5499_copy_nv_register_1_to_wiper_register_1(MAX5494_MAX5499 *max5494_max5499)
{
    return max5494_max5499_internal_write((max5494_max5499), MAX5494_MAX5499_COPY_NV_REGISTER_TO_WIPER_REGISTER, MAX5494_MAX5499_RA0);
}

MAX5494_MAX5499ErrNo max5494_max5499_copy_nv_register_2_to_wiper_register_2(MAX5494_MAX5499 *max5494_max5499)
{
    return max5494_max5499_internal_write((max5494_max5499), MAX5494_MAX5499_COPY_NV_REGISTER_TO_WIPER_REGISTER, MAX5494_MAX5499_RA1);
}

MAX5494_MAX5499ErrNo max5494_max5499_copy_nv_registers_to_wiper_registers_simultaneously(MAX5494_MAX5499 *max5494_max5499)
{
    return max5494_max5499_internal_write((max5494_max5499), MAX5494_MAX5499_COPY_NV_REGISTER_TO_WIPER_REGISTER, MAX5494_MAX5499_RA0 | MAX5494_MAX5499_RA1);
}