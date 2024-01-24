#include "max5494_max5499.h"

#include <stdio.h>

#include "test_init.h"
#include "test_write_wiper_register.h"
#include "test_write_nv_register.h"
#include "test_copy_wiper_register_to_nv_register.h"
#include "test_copy_nv_register_to_wiper_register.h"

int main(void)
{
    int (*tests[])(void) = {
        test_init,
        test_write_wiper_register,
        test_write_wiper_register_propagates_error,
        test_write_nv_register,
        test_write_nv_register_propagates_error,
        test_copy_wiper_register_to_nv_register,
        test_copy_wiper_register_to_nv_register_propagates_error,
        test_copy_wiper_registers_to_nv_registers_simultaneously,
        test_copy_wiper_registers_to_nv_registers_simultaneously_propagates_error,
        test_copy_nv_register_to_wiper_register,
        test_copy_nv_register_to_wiper_register_propagates_error,
        test_copy_nv_registers_to_wiper_registers_simultaneously,
        test_copy_nv_registers_to_wiper_registers_simultaneously_propagates_error};
    size_t length = sizeof(tests) / sizeof(int (*)(void));

    for (size_t i = 0; i < length; i++)
    {
        int ret = tests[i]();
        if (ret != 0)
        {
            return 1;
        }
    }

    printf("OK\n");
    return 0;
}