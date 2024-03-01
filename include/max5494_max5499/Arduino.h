#ifdef ARDUINO

#ifndef MAX5494_MAX5499_ARDUINO_H_
#define MAX5494_MAX5499_ARDUINO_H_

#include "../max5494_max5499.h"

#include <Arduino.h>
#include <SPI.h>

#include <assert.h>

class MAX5494_MAX5499Wrapper
{
public:
    MAX5494_MAX5499Wrapper(HardwareSPI *spi, pin_size_t cs)
    {
        writer_.parent.write = [](MAX5494_MAX5499SPIWriter *parent, uint8_t data[], size_t size)
        {
            Writer_ *writer = (Writer_ *)parent;
            if (writer == NULL)
            {
                return MAX5494_MAX5499_EINVAL;
            }

            writer->spi_->beginTransaction(writer->setting_);
            digitalWrite(writer->cs_, LOW);
            writer->spi_->transfer(data, size);
            digitalWrite(writer->cs_, HIGH);
            writer->spi_->endTransaction();

            return MAX5494_MAX5499_OK;
        };
        writer_.spi_ = spi;
        writer_.cs_ = cs;
        writer_.setting_ = SPISettings(7'000'000, MSBFIRST, SPI_MODE0);

        assert(max5494_max5499_init(&max5494_max5499_, (MAX5494_MAX5499SPIWriter *)&writer_) == MAX5494_MAX5499_OK);
    }

    MAX5494_MAX5499ErrNo writeWiperRegister1(uint16_t d) { return max5494_max5499_write_wiper_register_1(&max5494_max5499_, d); }
    MAX5494_MAX5499ErrNo writeWiperRegister2(uint16_t d) { return max5494_max5499_write_wiper_register_2(&max5494_max5499_, d); }
    MAX5494_MAX5499ErrNo writeNVRegister1(uint16_t d) { return max5494_max5499_write_nv_register_1(&max5494_max5499_, d); }
    MAX5494_MAX5499ErrNo writeNVRegister2(uint16_t d) { return max5494_max5499_write_nv_register_2(&max5494_max5499_, d); }
    MAX5494_MAX5499ErrNo copyWiperRegister1ToNVRegister1() { return max5494_max5499_copy_wiper_register_1_to_nv_register_1(&max5494_max5499_); }
    MAX5494_MAX5499ErrNo copyWiperRegister2ToNVRegister2() { return max5494_max5499_copy_wiper_register_2_to_nv_register_2(&max5494_max5499_); }
    MAX5494_MAX5499ErrNo copyWiperRegistersToNVRegistersSimultaneously() { return max5494_max5499_copy_wiper_registers_to_nv_registers_simultaneously(&max5494_max5499_); }
    MAX5494_MAX5499ErrNo copyNVRegister1ToWiperRegister1() { return max5494_max5499_copy_nv_register_1_to_wiper_register_1(&max5494_max5499_); }
    MAX5494_MAX5499ErrNo copyNVRegister2ToWiperRegister2() { return max5494_max5499_copy_nv_register_2_to_wiper_register_2(&max5494_max5499_); }
    MAX5494_MAX5499ErrNo copyNVRegistersToWiperRegistersSimultaneously() { return max5494_max5499_copy_nv_registers_to_wiper_registers_simultaneously(&max5494_max5499_); }

private:
    MAX5494_MAX5499 max5494_max5499_;
    struct Writer_
    {
        MAX5494_MAX5499SPIWriter parent;
        HardwareSPI *spi_;
        pin_size_t cs_;
        SPISettings setting_;
    } writer_;
};

#endif // MAX5494_MAX5499_ARDUINO_H_

#endif // ARDUINO