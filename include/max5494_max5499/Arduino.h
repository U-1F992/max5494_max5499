#ifdef ARDUINO

#ifndef MAX5494_MAX5499_ARDUINO_H_
#define MAX5494_MAX5499_ARDUINO_H_

#include "../max5494_max5499.h"

#include <Arduino.h>
#include <SPI.h>

#include <assert.h>

class MAX5494_MAX5499
{
public:
    MAX5494_MAX5499(HardwareSPI *spi, pin_size_t cs)
    {
        writer_.parent.write = [](max5494_max5499_spi_writer_t *parent, uint8_t data[], size_t size)
        {
            Writer_ *writer = (Writer_ *)parent;
            if (writer == NULL)
            {
                return MAX5494_MAX5499_EINVAL;
            }

            digitalWrite(writer->cs_, LOW);
            writer->spi_->transfer(data, size);
            digitalWrite(writer->cs_, HIGH);

            return MAX5494_MAX5499_OK;
        };
        writer_.spi_ = spi;
        writer_.cs_ = cs;

        assert(max5494_max5499_init(&max5494_max5499_, (max5494_max5499_spi_writer_t *)&writer_) == MAX5494_MAX5499_OK);
    }

    max5494_max5499_error_t writeWiperRegister1(uint16_t d) { return max5494_max5499_write_wiper_register_1(&max5494_max5499_, d); }
    max5494_max5499_error_t writeWiperRegister2(uint16_t d) { return max5494_max5499_write_wiper_register_2(&max5494_max5499_, d); }
    max5494_max5499_error_t writeNVRegister1(uint16_t d) { return max5494_max5499_write_nv_register_1(&max5494_max5499_, d); }
    max5494_max5499_error_t writeNVRegister2(uint16_t d) { return max5494_max5499_write_nv_register_2(&max5494_max5499_, d); }
    max5494_max5499_error_t copyWiperRegister1ToNVRegister1() { return max5494_max5499_copy_wiper_register_1_to_nv_register_1(&max5494_max5499_); }
    max5494_max5499_error_t copyWiperRegister2ToNVRegister2() { return max5494_max5499_copy_wiper_register_2_to_nv_register_2(&max5494_max5499_); }
    max5494_max5499_error_t copyWiperRegistersToNVRegistersSimultaneously() { return max5494_max5499_copy_wiper_registers_to_nv_registers_simultaneously(&max5494_max5499_); }
    max5494_max5499_error_t copyNVRegister1ToWiperRegister1() { return max5494_max5499_copy_nv_register_1_to_wiper_register_1(&max5494_max5499_); }
    max5494_max5499_error_t copyNVRegister2ToWiperRegister2() { return max5494_max5499_copy_nv_register_2_to_wiper_register_2(&max5494_max5499_); }
    max5494_max5499_error_t copyNVRegistersToWiperRegistersSimultaneously() { return max5494_max5499_copy_nv_registers_to_wiper_registers_simultaneously(&max5494_max5499_); }

private:
    max5494_max5499_t max5494_max5499_;

    struct Writer_
    {
        max5494_max5499_spi_writer_t parent;
        HardwareSPI *spi_;
        pin_size_t cs_;
    };

    Writer_ writer_;
};

#endif // MAX5494_MAX5499_ARDUINO_H_

#endif // ARDUINO