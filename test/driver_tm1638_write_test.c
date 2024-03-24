/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_tm1638_write_test.c
 * @brief     driver tm1638 write test source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-03-31
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/03/31  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */
 
#include "driver_tm1638_write_test.h"
#include <stdlib.h>

static tm1638_handle_t gs_handle;        /**< tm1638 handle */

/**
 * @brief  write test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t tm1638_write_test(void)
{
    uint8_t res;
    uint16_t number[] = {TM1638_NUMBER_0, TM1638_NUMBER_1, TM1638_NUMBER_2,
                         TM1638_NUMBER_3, TM1638_NUMBER_4, TM1638_NUMBER_5,
                         TM1638_NUMBER_6, TM1638_NUMBER_7, TM1638_NUMBER_8, TM1638_NUMBER_9};
    tm1638_info_t info;

    /* link interface function */
    DRIVER_TM1638_LINK_INIT(&gs_handle, tm1638_handle_t); 
    DRIVER_TM1638_LINK_SPI_INIT(&gs_handle, tm1638_interface_spi_init);
    DRIVER_TM1638_LINK_SPI_DEINIT(&gs_handle, tm1638_interface_spi_deinit);
    DRIVER_TM1638_LINK_SPI_WRITE(&gs_handle, tm1638_interface_spi_write);
    DRIVER_TM1638_LINK_SPI_READ(&gs_handle, tm1638_interface_spi_read);
    DRIVER_TM1638_LINK_DELAY_MS(&gs_handle, tm1638_interface_delay_ms);
    DRIVER_TM1638_LINK_DEBUG_PRINT(&gs_handle, tm1638_interface_debug_print);
    
    /* get information */
    res = tm1638_info(&info);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        tm1638_interface_debug_print("tm1638: chip is %s.\n", info.chip_name);
        tm1638_interface_debug_print("tm1638: manufacturer is %s.\n", info.manufacturer_name);
        tm1638_interface_debug_print("tm1638: interface is %s.\n", info.interface);
        tm1638_interface_debug_print("tm1638: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tm1638_interface_debug_print("tm1638: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tm1638_interface_debug_print("tm1638: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tm1638_interface_debug_print("tm1638: max current is %0.2fmA.\n", info.max_current_ma);
        tm1638_interface_debug_print("tm1638: max temperature is %0.1fC.\n", info.temperature_max);
        tm1638_interface_debug_print("tm1638: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start write test */
    tm1638_interface_debug_print("tm1638: start write test.\n");
    
    /* tm1638 init */
    res = tm1638_init(&gs_handle);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: init failed.\n");
        
        return 1;
    }
    
    /* address auto increment mode */
    tm1638_interface_debug_print("tm1638: address auto increment mode.\n");
    
    /* set pulse width 14/16 */
    res = tm1638_set_pulse_width(&gs_handle, TM1638_PULSE_WIDTH_14_DIV_16);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: set pulse width failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set address auto inc mode */
    res = tm1638_set_address_mode(&gs_handle, TM1638_ADDRESS_MODE_INC);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: set address mode failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable test mode */
    res = tm1638_set_test_mode(&gs_handle, TM1638_BOOL_FALSE);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: set test mode failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear segment */
    res = tm1638_clear_segment(&gs_handle);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: clear segment failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable display */
    res = tm1638_set_display(&gs_handle, TM1638_BOOL_TRUE);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: set display failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    
    /* write segment */
    res = tm1638_write_segment(&gs_handle, 0x00, &number[0], 8);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: write segment failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 5000ms */
    tm1638_interface_delay_ms(5000);
    
    /* address fix mode */
    tm1638_interface_debug_print("tm1638: address fix mode.\n");
    
    /* set address fix mode */
    res = tm1638_set_address_mode(&gs_handle, TM1638_ADDRESS_MODE_FIX);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: set address mode failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    
    /* write segment */
    res = tm1638_write_segment(&gs_handle, 0x00, &number[1], 8);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: write segment failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 5000ms */
    tm1638_interface_delay_ms(5000);
    
    /* set pulse width */
    tm1638_interface_debug_print("tm1638: set pulse width 12.\n");
    
    /* set pulse width 12/16 */
    res = tm1638_set_pulse_width(&gs_handle, TM1638_PULSE_WIDTH_12_DIV_16);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: set pulse width failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 3000ms */
    tm1638_interface_delay_ms(3000);
    
    /* set pulse width */
    tm1638_interface_debug_print("tm1638: set pulse width 10.\n");
    
    /* set pulse width 12/16 */
    res = tm1638_set_pulse_width(&gs_handle, TM1638_PULSE_WIDTH_10_DIV_16);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: set pulse width failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 3000ms */
    tm1638_interface_delay_ms(3000);
    
    /* set pulse width */
    tm1638_interface_debug_print("tm1638: set pulse width 2.\n");
    
    /* set pulse width 2/16 */
    res = tm1638_set_pulse_width(&gs_handle, TM1638_PULSE_WIDTH_2_DIV_16);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: set pulse width failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 3000ms */
    tm1638_interface_delay_ms(3000);
    
    /* display off */
    tm1638_interface_debug_print("tm1638: display off.\n");
    
    /* disable display */
    res = tm1638_set_display(&gs_handle, TM1638_BOOL_FALSE);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: set display failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    /* delay 3000ms */
    tm1638_interface_delay_ms(3000);
    
    /* display on */
    tm1638_interface_debug_print("tm1638: display on.\n");
    
    /* set pulse width 14/16 */
    res = tm1638_set_pulse_width(&gs_handle, TM1638_PULSE_WIDTH_14_DIV_16);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: set pulse width failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable display */
    res = tm1638_set_display(&gs_handle, TM1638_BOOL_TRUE);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: set display failed.\n");
        (void)tm1638_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 3000ms */
    tm1638_interface_delay_ms(3000);
    
    /* finish write test */
    tm1638_interface_debug_print("tm1638: finish write test.\n");
    (void)tm1638_deinit(&gs_handle);
    
    return 0;
}
