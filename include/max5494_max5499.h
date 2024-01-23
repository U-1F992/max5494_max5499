#ifndef MAX5494_MAX5499_H_
#define MAX5494_MAX5499_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>

typedef enum max5494_max5499_errno_t
{
    MAX5494_MAX5499_OK,
    MAX5494_MAX5499_EIO = 5,
    MAX5494_MAX5499_EINVAL = 22,
} max5494_max5499_errno_t;

typedef struct max5494_max5499_spi_interface_t
{
    max5494_max5499_errno_t (*write)(struct max5494_max5499_spi_interface_t *self, uint8_t data[], size_t length);
} max5494_max5499_spi_interface_t;

#define MAX5494_MAX5499_D_MAX 0b1111111111U

typedef struct max5494_max5499_t
{
    max5494_max5499_spi_interface_t *spi;
} max5494_max5499_t;

typedef enum max5494_max5499_register_t
{
    MAX5494_MAX5499_RA0 = 0b01U,
    MAX5494_MAX5499_RA1 = 0b10U
} max5494_max5499_register_t;

typedef enum max5494_max5499_command_t
{
    MAX5494_MAX5499_WRITE_WIPER_REGISTER = 0b00U,
    MAX5494_MAX5499_WRITE_NV_REGISTER = 0b01U,
    MAX5494_MAX5499_COPY_WIPER_REGISTER_TO_NV_REGISTER = 0b10U,
    MAX5494_MAX5499_COPY_NV_REGISTER_TO_WIPER_REGISTER = 0b11U
} max5494_max5499_command_t;

inline max5494_max5499_errno_t max5494_max5499_init(max5494_max5499_t *rdac, max5494_max5499_spi_interface_t *spi)
{
    if (rdac == NULL || spi == NULL)
    {
        return MAX5494_MAX5499_EINVAL;
    }

    rdac->spi = spi;

    return MAX5494_MAX5499_OK;
}

max5494_max5499_errno_t max5494_max5499_write_wiper_register(max5494_max5499_t *rdac, max5494_max5499_register_t ra, uint16_t d);
max5494_max5499_errno_t max5494_max5499_write_nv_register(max5494_max5499_t *rdac, max5494_max5499_register_t ra, uint16_t d);
max5494_max5499_errno_t max5494_max5499_copy_wiper_register_to_nv_register(max5494_max5499_t *rdac, max5494_max5499_register_t ra);

inline max5494_max5499_errno_t max5494_max5499_copy_wiper_registers_to_nv_registers_simultaneously(max5494_max5499_t *rdac)
{
    return max5494_max5499_copy_wiper_register_to_nv_register(rdac, (max5494_max5499_register_t)(MAX5494_MAX5499_RA0 | MAX5494_MAX5499_RA1));
}

max5494_max5499_errno_t max5494_max5499_copy_nv_register_to_wiper_register(max5494_max5499_t *rdac, max5494_max5499_register_t ra);

inline max5494_max5499_errno_t max5494_max5499_copy_nv_registers_to_wiper_registers_simultaneously(max5494_max5499_t *rdac)
{
    return max5494_max5499_copy_nv_register_to_wiper_register(rdac, (max5494_max5499_register_t)(MAX5494_MAX5499_RA0 | MAX5494_MAX5499_RA1));
}

#ifdef __cplusplus
}
#endif

#endif