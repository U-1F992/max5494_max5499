#ifndef MAX5494_MAX5499_H_
#define MAX5494_MAX5499_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>

    typedef enum max5494_max5499_error_t
    {
        MAX5494_MAX5499_OK = 0,
        MAX5494_MAX5499_EIO = 5,
        MAX5494_MAX5499_EINVAL = 22,
    } max5494_max5499_error_t;

    typedef struct max5494_max5499_spi_writer_t
    {
        max5494_max5499_error_t (*write)(struct max5494_max5499_spi_writer_t *writer, uint8_t data[], size_t size);
    } max5494_max5499_spi_writer_t;

    typedef struct max5494_max5499_t
    {
        max5494_max5499_spi_writer_t *writer_;
        uint8_t buffer_[3];
    } max5494_max5499_t;

    typedef enum max5494_max5499_command_t
    {
        MAX5494_MAX5499_WRITE_WIPER_REGISTER = 0,
        MAX5494_MAX5499_WRITE_NV_REGISTER = 1,
        MAX5494_MAX5499_COPY_WIPER_REGISTER_TO_NV_REGISTER = 2,
        MAX5494_MAX5499_COPY_NV_REGISTER_TO_WIPER_REGISTER = 3
    } max5494_max5499_command_t;

    typedef enum max5494_max5499_register_t
    {
        MAX5494_MAX5499_RA0 = 1,
        MAX5494_MAX5499_RA1 = 2
    } max5494_max5499_register_t;

#define MAX5494_MAX5499_D_MAX ((uint16_t) /* 0b11'11111111 */ 0x3FF)

#define max5494_max5499_internal_write(max5494_max5499, c, ra) (((max5494_max5499) != NULL &&                                                                                                \
                                                                 ((c) == MAX5494_MAX5499_COPY_WIPER_REGISTER_TO_NV_REGISTER || (c) == MAX5494_MAX5499_COPY_NV_REGISTER_TO_WIPER_REGISTER) && \
                                                                 ((ra) == MAX5494_MAX5499_RA0 || (ra) == MAX5494_MAX5499_RA1 || (ra) == MAX5494_MAX5499_RA0 | MAX5494_MAX5499_RA1))          \
                                                                    ? ((max5494_max5499)->buffer_[0] = (uint8_t)(((c) << 4) | (ra)),                                                         \
                                                                       (max5494_max5499)->writer_->write((max5494_max5499)->writer_, (max5494_max5499)->buffer_, 1))                         \
                                                                    : MAX5494_MAX5499_EINVAL)

#define max5494_max5499_internal_write_d(max5494_max5499, c, ra, d) (((max5494_max5499) != NULL &&                                                                        \
                                                                      ((c) == MAX5494_MAX5499_WRITE_WIPER_REGISTER || (c) == MAX5494_MAX5499_WRITE_NV_REGISTER) &&        \
                                                                      ((ra) == MAX5494_MAX5499_RA0 || (ra) == MAX5494_MAX5499_RA1) &&                                     \
                                                                      (d) <= MAX5494_MAX5499_D_MAX)                                                                       \
                                                                         ? ((max5494_max5499)->buffer_[0] = (uint8_t)(((c) << 4) | (ra)),                                 \
                                                                            (max5494_max5499)->buffer_[1] = (uint8_t)((d) >> 2),                                          \
                                                                            (max5494_max5499)->buffer_[2] = (uint8_t)(((d) & /* 0b00000011 */ 0x03) << 6),                \
                                                                            (max5494_max5499)->writer_->write((max5494_max5499)->writer_, (max5494_max5499)->buffer_, 3)) \
                                                                         : MAX5494_MAX5499_EINVAL)

#define max5494_max5499_init(max5494_max5499, writer) (((max5494_max5499) != NULL &&                 \
                                                        (writer) != NULL)                            \
                                                           ? ((max5494_max5499)->writer_ = (writer), \
                                                              MAX5494_MAX5499_OK)                    \
                                                           : MAX5494_MAX5499_EINVAL)
#define max5494_max5499_write_wiper_register_1(max5494_max5499, d) (max5494_max5499_internal_write_d((max5494_max5499), MAX5494_MAX5499_WRITE_WIPER_REGISTER, MAX5494_MAX5499_RA0, (d)))
#define max5494_max5499_write_wiper_register_2(max5494_max5499, d) (max5494_max5499_internal_write_d((max5494_max5499), MAX5494_MAX5499_WRITE_WIPER_REGISTER, MAX5494_MAX5499_RA1, (d)))
#define max5494_max5499_write_nv_register_1(max5494_max5499, d) (max5494_max5499_internal_write_d((max5494_max5499), MAX5494_MAX5499_WRITE_NV_REGISTER, MAX5494_MAX5499_RA0, (d)))
#define max5494_max5499_write_nv_register_2(max5494_max5499, d) (max5494_max5499_internal_write_d((max5494_max5499), MAX5494_MAX5499_WRITE_NV_REGISTER, MAX5494_MAX5499_RA1, (d)))
#define max5494_max5499_copy_wiper_register_1_to_nv_register_1(max5494_max5499) (max5494_max5499_internal_write((max5494_max5499), MAX5494_MAX5499_COPY_WIPER_REGISTER_TO_NV_REGISTER, MAX5494_MAX5499_RA0))
#define max5494_max5499_copy_wiper_register_2_to_nv_register_2(max5494_max5499) (max5494_max5499_internal_write((max5494_max5499), MAX5494_MAX5499_COPY_WIPER_REGISTER_TO_NV_REGISTER, MAX5494_MAX5499_RA1))
#define max5494_max5499_copy_wiper_registers_to_nv_registers_simultaneously(max5494_max5499) (max5494_max5499_internal_write((max5494_max5499), MAX5494_MAX5499_COPY_WIPER_REGISTER_TO_NV_REGISTER, MAX5494_MAX5499_RA0 | MAX5494_MAX5499_RA1))
#define max5494_max5499_copy_nv_register_1_to_wiper_register_1(max5494_max5499) (max5494_max5499_internal_write((max5494_max5499), MAX5494_MAX5499_COPY_NV_REGISTER_TO_WIPER_REGISTER, MAX5494_MAX5499_RA0))
#define max5494_max5499_copy_nv_register_2_to_wiper_register_2(max5494_max5499) (max5494_max5499_internal_write((max5494_max5499), MAX5494_MAX5499_COPY_NV_REGISTER_TO_WIPER_REGISTER, MAX5494_MAX5499_RA1))
#define max5494_max5499_copy_nv_registers_to_wiper_registers_simultaneously(max5494_max5499) (max5494_max5499_internal_write((max5494_max5499), MAX5494_MAX5499_COPY_NV_REGISTER_TO_WIPER_REGISTER, MAX5494_MAX5499_RA0 | MAX5494_MAX5499_RA1))

#ifdef __cplusplus
}
#endif

#endif