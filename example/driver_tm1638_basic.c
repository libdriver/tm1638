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
 * @file      driver_tm1638_basic.c
 * @brief     driver tm1638 basic source file
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

#include "driver_tm1638_basic.h"

static tm1638_handle_t gs_handle;        /**< tm1638 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t tm1638_basic_init(void)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_TM1638_LINK_INIT(&gs_handle, tm1638_handle_t); 
    DRIVER_TM1638_LINK_SPI_INIT(&gs_handle, tm1638_interface_spi_init);
    DRIVER_TM1638_LINK_SPI_DEINIT(&gs_handle, tm1638_interface_spi_deinit);
    DRIVER_TM1638_LINK_SPI_WRITE(&gs_handle, tm1638_interface_spi_write);
    DRIVER_TM1638_LINK_SPI_READ(&gs_handle, tm1638_interface_spi_read);
    DRIVER_TM1638_LINK_DELAY_MS(&gs_handle, tm1638_interface_delay_ms);
    DRIVER_TM1638_LINK_DEBUG_PRINT(&gs_handle, tm1638_interface_debug_print);
    
    /* tm1638 init */
    res = tm1638_init(&gs_handle);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: init failed.\n");
        
        return 1;
    }
    
    /* set default address mode */
    res = tm1638_set_address_mode(&gs_handle, TM1638_BASIC_DEFAULT_ADDRESS_MODE);
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
    
    /* set default pulse width */
    res = tm1638_set_pulse_width(&gs_handle, TM1638_BASIC_DEFAULT_PULSE_WIDTH);
    if (res != 0)
    {
        tm1638_interface_debug_print("tm1638: set pulse width failed.\n");
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
    
    return 0;
}

/**
 * @brief     basic example write
 * @param[in] addr is the start address
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t tm1638_basic_write(uint8_t addr, uint16_t *data, uint8_t len)
{
    uint8_t res;
    
    /* write segment */
    res = tm1638_write_segment(&gs_handle, addr, data, len);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example clear
 * @return status code
 *         - 0 success
 *         - 1 clear failed
 * @note   none
 */
uint8_t tm1638_basic_clear(void)
{
    uint8_t res;
    
    /* clear segment */
    res = tm1638_clear_segment(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example display on
 * @return status code
 *         - 0 success
 *         - 1 display on failed
 * @note   none
 */
uint8_t tm1638_basic_display_on(void)
{
    uint8_t res;
    
    /* display on */
    res = tm1638_set_display(&gs_handle, TM1638_BOOL_TRUE);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example display off
 * @return status code
 *         - 0 success
 *         - 1 display off failed
 * @note   none
 */
uint8_t tm1638_basic_display_off(void)
{
    uint8_t res;
    
    /* display off */
    res = tm1638_set_display(&gs_handle, TM1638_BOOL_FALSE);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *segk points to a segk buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t tm1638_basic_read(uint8_t segk[4])
{
    uint8_t res;
    
    /* read segment */
    res = tm1638_read_segment(&gs_handle, segk);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t tm1638_basic_deinit(void)
{
    uint8_t res;
    
    /* deinit tm1638 */
    res = tm1638_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}
