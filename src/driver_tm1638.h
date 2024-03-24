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
 * @file      driver_tm1638.h
 * @brief     driver tm1638 header file
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

#ifndef DRIVER_TM1638_H
#define DRIVER_TM1638_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup tm1638_driver tm1638 driver function
 * @brief    tm1638 driver modules
 * @{
 */

/**
 * @addtogroup tm1638_basic_driver
 * @{
 */

/**
 * @brief tm1638 address mode enumeration definition
 */
typedef enum
{
    TM1638_ADDRESS_MODE_INC = 0x00,        /**< auto increment 1 mode */
    TM1638_ADDRESS_MODE_FIX = 0x01,        /**< fixed address mode */
} tm1638_address_mode_t;

/**
 * @brief tm1638 bool enumeration definition
 */
typedef enum
{
    TM1638_BOOL_FALSE = 0x00,        /**< false */
    TM1638_BOOL_TRUE  = 0x01,        /**< true */
} tm1638_bool_t;

/**
 * @brief tm1638 pulse width enumeration definition
 */
typedef enum
{
    TM1638_PULSE_WIDTH_1_DIV_16  = 0x00,        /**< 1/16 */
    TM1638_PULSE_WIDTH_2_DIV_16  = 0x01,        /**< 2/16 */
    TM1638_PULSE_WIDTH_4_DIV_16  = 0x02,        /**< 4/16 */
    TM1638_PULSE_WIDTH_10_DIV_16 = 0x03,        /**< 10/16 */
    TM1638_PULSE_WIDTH_11_DIV_16 = 0x04,        /**< 11/16 */
    TM1638_PULSE_WIDTH_12_DIV_16 = 0x05,        /**< 12/16 */
    TM1638_PULSE_WIDTH_13_DIV_16 = 0x06,        /**< 13/16 */
    TM1638_PULSE_WIDTH_14_DIV_16 = 0x07,        /**< 14/16 */
} tm1638_pulse_width_t;

/**
 * @brief tm1638 number enumeration definition
 */
typedef enum
{
    TM1638_NUMBER_0 = 0x003F,        /**< 0 */
    TM1638_NUMBER_1 = 0x0006,        /**< 1 */
    TM1638_NUMBER_2 = 0x005B,        /**< 2 */
    TM1638_NUMBER_3 = 0x004F,        /**< 3 */
    TM1638_NUMBER_4 = 0x0066,        /**< 4 */
    TM1638_NUMBER_5 = 0x006D,        /**< 5 */
    TM1638_NUMBER_6 = 0x007D,        /**< 6 */
    TM1638_NUMBER_7 = 0x0007,        /**< 7 */
    TM1638_NUMBER_8 = 0x007F,        /**< 8 */
    TM1638_NUMBER_9 = 0x006F,        /**< 9 */
} tm1638_number_t;

/**
 * @brief tm1638 handle structure definition
 */
typedef struct tm1638_handle_s
{
    uint8_t (*spi_init)(void);                                            /**< point to a dio_init function address */
    uint8_t (*spi_deinit)(void);                                          /**< point to a dio_deinit function address */
    uint8_t (*spi_write)(uint8_t addr, uint8_t *buf, uint16_t len);       /**< point to a dio_write function address */
    uint8_t (*spi_read)(uint8_t addr, uint8_t *buf, uint16_t len);        /**< point to a dio_read function address */
    void (*delay_ms)(uint32_t ms);                                        /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                      /**< point to a debug_print function address */
    uint8_t inited;                                                       /**< inited flag */
    uint8_t display_conf;                                                 /**< display configure */
    uint8_t data_conf;                                                    /**< data configure */
} tm1638_handle_t;

/**
 * @brief tm1638 information structure definition
 */
typedef struct tm1638_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} tm1638_info_t;

/**
 * @}
 */

/**
 * @defgroup tm1638_link_driver tm1638 link driver function
 * @brief    tm1638 link driver modules
 * @ingroup  tm1638_driver
 * @{
 */

/**
 * @brief     initialize tm1638_handle_t structure
 * @param[in] HANDLE points to a tm1638 handle structure
 * @param[in] STRUCTURE is tm1638_handle_t
 * @note      none
 */
#define DRIVER_TM1638_LINK_INIT(HANDLE, STRUCTURE)                  memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link spi_init function
 * @param[in] HANDLE points to a tm1638 handle structure
 * @param[in] FUC points to a spi_init function address
 * @note      none
 */
#define DRIVER_TM1638_LINK_SPI_INIT(HANDLE, FUC)                   (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE points to a tm1638 handle structure
 * @param[in] FUC points to a spi_deinit function address
 * @note      none
 */
#define DRIVER_TM1638_LINK_SPI_DEINIT(HANDLE, FUC)                 (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_write function
 * @param[in] HANDLE points to a tm1638 handle structure
 * @param[in] FUC points to a spi_write function address
 * @note      none
 */
#define DRIVER_TM1638_LINK_SPI_WRITE(HANDLE, FUC)                  (HANDLE)->spi_write = FUC

/**
 * @brief     link spi_read function
 * @param[in] HANDLE points to a tm1638 handle structure
 * @param[in] FUC points to a spi_read function address
 * @note      none
 */
#define DRIVER_TM1638_LINK_SPI_READ(HANDLE, FUC)                   (HANDLE)->spi_read = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a tm1638 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_TM1638_LINK_DELAY_MS(HANDLE, FUC)                   (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a tm1638 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_TM1638_LINK_DEBUG_PRINT(HANDLE, FUC)                (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup tm1638_basic_driver tm1638 basic driver function
 * @brief    tm1638 basic driver modules
 * @ingroup  tm1638_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a tm1638 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tm1638_info(tm1638_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a tm1638 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t tm1638_init(tm1638_handle_t *handle);

/**
 * @brief     clear segment
 * @param[in] *handle points to a tm1638 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 clear segment failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1638_clear_segment(tm1638_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a tm1638 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t tm1638_deinit(tm1638_handle_t *handle);

/**
 * @brief     write segment
 * @param[in] *handle points to a tm1638 handle structure
 * @param[in] addr is the start address
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write segment failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 addr + len > 8
 * @note      none
 */
uint8_t tm1638_write_segment(tm1638_handle_t *handle, uint8_t addr, uint16_t *data, uint8_t len);

/**
 * @brief      read segment
 * @param[in]  *handle points to a tm1638 handle structure
 * @param[out] *segk points to a segk buffer
 * @return     status code
 *             - 0 success
 *             - 1 read segment failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tm1638_read_segment(tm1638_handle_t *handle, uint8_t segk[4]);

/**
 * @brief     set pulse width
 * @param[in] *handle points to a tm1638 handle structure
 * @param[in] width is the pulse width
 * @return    status code
 *            - 0 success
 *            - 1 set pulse width failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1638_set_pulse_width(tm1638_handle_t *handle, tm1638_pulse_width_t width);

/**
 * @brief      get pulse width
 * @param[in]  *handle points to a tm1638 handle structure
 * @param[out] *width points to a pulse width buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tm1638_get_pulse_width(tm1638_handle_t *handle, tm1638_pulse_width_t *width);

/**
 * @brief     enable or disable display
 * @param[in] *handle points to a tm1638 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set display failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1638_set_display(tm1638_handle_t *handle, tm1638_bool_t enable);

/**
 * @brief      get display status
 * @param[in]  *handle points to a tm1638 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tm1638_get_display(tm1638_handle_t *handle, tm1638_bool_t *enable);

/**
 * @brief     set address mode
 * @param[in] *handle points to a tm1638 handle structure
 * @param[in] mode is the address mode
 * @return    status code
 *            - 0 success
 *            - 1 set address mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1638_set_address_mode(tm1638_handle_t *handle, tm1638_address_mode_t mode);

/**
 * @brief      get address mode
 * @param[in]  *handle points to a tm1638 handle structure
 * @param[out] *mode points to an address mode buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tm1638_get_address_mode(tm1638_handle_t *handle, tm1638_address_mode_t *mode);

/**
 * @brief     enable or disable test mode
 * @param[in] *handle points to a tm1638 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set test mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1638_set_test_mode(tm1638_handle_t *handle, tm1638_bool_t enable);

/**
 * @brief      get test mode status
 * @param[in]  *handle points to a tm1638 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tm1638_get_test_mode(tm1638_handle_t *handle, tm1638_bool_t *enable);

/**
 * @}
 */

/**
 * @defgroup tm1638_extern_driver tm1638 extern driver function
 * @brief    tm1638 extern driver modules
 * @ingroup  tm1638_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to a tm1638 handle structure
 * @param[in] cmd is the send command
 * @param[in] *data points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1638_set_reg(tm1638_handle_t *handle, uint8_t cmd, uint8_t *data, uint8_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to a tm1638 handle structure
 * @param[in]  cmd is the send command
 * @param[out] *data points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tm1638_get_reg(tm1638_handle_t *handle, uint8_t cmd, uint8_t *data, uint8_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
