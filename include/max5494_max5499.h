#ifndef MAX5494_MAX5499_H_
#define MAX5494_MAX5499_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>

    typedef int MAX5494_MAX5499ErrNo;

#define MAX5494_MAX5499_OK /*    */ ((MAX5494_MAX5499ErrNo)0)
#define MAX5494_MAX5499_EIO /*   */ ((MAX5494_MAX5499ErrNo)5)
#define MAX5494_MAX5499_EINVAL /**/ ((MAX5494_MAX5499ErrNo)22)

    typedef struct MAX5494_MAX5499SPIWriter
    {
        MAX5494_MAX5499ErrNo (*write)(struct MAX5494_MAX5499SPIWriter *writer, uint8_t data[], size_t size);
    } MAX5494_MAX5499SPIWriter;

    typedef struct MAX5494_MAX5499
    {
        MAX5494_MAX5499SPIWriter *writer;
    } MAX5494_MAX5499;

#define MAX5494_MAX5499_D_MAX ((uint16_t) /* 0b11'11111111 */ 0x3FF)

    MAX5494_MAX5499ErrNo max5494_max5499_init(MAX5494_MAX5499 *max5494_max5499, MAX5494_MAX5499SPIWriter *writer);
    MAX5494_MAX5499ErrNo max5494_max5499_write_wiper_register_1(MAX5494_MAX5499 *max5494_max5499, uint16_t d);
    MAX5494_MAX5499ErrNo max5494_max5499_write_wiper_register_2(MAX5494_MAX5499 *max5494_max5499, uint16_t d);
    MAX5494_MAX5499ErrNo max5494_max5499_write_nv_register_1(MAX5494_MAX5499 *max5494_max5499, uint16_t d);
    MAX5494_MAX5499ErrNo max5494_max5499_write_nv_register_2(MAX5494_MAX5499 *max5494_max5499, uint16_t d);
    MAX5494_MAX5499ErrNo max5494_max5499_copy_wiper_register_1_to_nv_register_1(MAX5494_MAX5499 *max5494_max5499);
    MAX5494_MAX5499ErrNo max5494_max5499_copy_wiper_register_2_to_nv_register_2(MAX5494_MAX5499 *max5494_max5499);
    MAX5494_MAX5499ErrNo max5494_max5499_copy_wiper_registers_to_nv_registers_simultaneously(MAX5494_MAX5499 *max5494_max5499);
    MAX5494_MAX5499ErrNo max5494_max5499_copy_nv_register_1_to_wiper_register_1(MAX5494_MAX5499 *max5494_max5499);
    MAX5494_MAX5499ErrNo max5494_max5499_copy_nv_register_2_to_wiper_register_2(MAX5494_MAX5499 *max5494_max5499);
    MAX5494_MAX5499ErrNo max5494_max5499_copy_nv_registers_to_wiper_registers_simultaneously(MAX5494_MAX5499 *max5494_max5499);

#ifdef __cplusplus
}
#endif

#endif