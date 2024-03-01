#ifndef MAX5494_MAX5499_INTERNAL_H_
#define MAX5494_MAX5499_INTERNAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <max5494_max5499.h>

#include <assert.h>

    typedef enum MAX5494_MAX5499Command
    {
        MAX5494_MAX5499_WRITE_WIPER_REGISTER = 0,
        MAX5494_MAX5499_WRITE_NV_REGISTER = 1,
        MAX5494_MAX5499_COPY_WIPER_REGISTER_TO_NV_REGISTER = 2,
        MAX5494_MAX5499_COPY_NV_REGISTER_TO_WIPER_REGISTER = 3
    } MAX5494_MAX5499Command;

    typedef enum MAX5494_MAX5499Register
    {
        MAX5494_MAX5499_RA0 = 1,
        MAX5494_MAX5499_RA1 = 2
    } MAX5494_MAX5499Register;

    static inline MAX5494_MAX5499ErrNo max5494_max5499_internal_write(MAX5494_MAX5499 *max5494_max5499, MAX5494_MAX5499Command c, MAX5494_MAX5499Register ra)
    {
        if (max5494_max5499 == NULL ||
            (c != MAX5494_MAX5499_COPY_WIPER_REGISTER_TO_NV_REGISTER && c != MAX5494_MAX5499_COPY_NV_REGISTER_TO_WIPER_REGISTER) ||
            (ra != MAX5494_MAX5499_RA0 && ra != MAX5494_MAX5499_RA1 && ra != (MAX5494_MAX5499_RA0 | MAX5494_MAX5499_RA1)))
        {
            return MAX5494_MAX5499_EINVAL;
        }
        assert(max5494_max5499->writer != NULL);

        uint8_t buf = (uint8_t)((c << 4) | ra);
        MAX5494_MAX5499ErrNo ret = max5494_max5499->writer->write(max5494_max5499->writer, &buf, 1);
        if (ret != MAX5494_MAX5499_OK)
        {
            return MAX5494_MAX5499_EIO;
        }

        return MAX5494_MAX5499_OK;
    }

    static inline MAX5494_MAX5499ErrNo max5494_max5499_internal_write_d(MAX5494_MAX5499 *max5494_max5499, MAX5494_MAX5499Command c, MAX5494_MAX5499Register ra, uint16_t d)
    {
        if (max5494_max5499 == NULL ||
            (c != MAX5494_MAX5499_WRITE_WIPER_REGISTER && c != MAX5494_MAX5499_WRITE_NV_REGISTER) ||
            (ra != MAX5494_MAX5499_RA0 && ra != MAX5494_MAX5499_RA1) ||
            MAX5494_MAX5499_D_MAX < d)
        {
            return MAX5494_MAX5499_EINVAL;
        }
        assert(max5494_max5499->writer != NULL);

        uint8_t buf[] = {(uint8_t)((c << 4) | ra),
                         (uint8_t)(d >> 2),
                         (uint8_t)((d & /* 0b00000011 */ 0x03) << 6)};
        MAX5494_MAX5499ErrNo ret = max5494_max5499->writer->write(max5494_max5499->writer, buf, 3);
        if (ret != MAX5494_MAX5499_OK)
        {
            return MAX5494_MAX5499_EIO;
        }

        return MAX5494_MAX5499_OK;
    }

#ifdef __cplusplus
}
#endif

#endif