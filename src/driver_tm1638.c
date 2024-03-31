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
 * @file      driver_tm1638.c
 * @brief     driver tm1638 source file
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

#include "driver_tm1638.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Titan Micro Electronics TM1638"        /**< chip name */
#define MANUFACTURER_NAME         "Titan Micro Electronics"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        3.0f                                    /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        6.0f                                    /**< chip max supply voltage */
#define MAX_CURRENT               200.0f                                  /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                                  /**< chip min operating temperature */
#define TEMPERATURE_MAX           125.0f                                  /**< chip max operating temperature */
#define DRIVER_VERSION            1000                                    /**< driver version */

/**
 * @brief chip command definition
 */
#define TM1638_COMMAND_DATA           (1 << 6)        /**< data command setting */
#define TM1638_COMMAND_DISPLAY        (2 << 6)        /**< display and control command setting */
#define TM1638_COMMAND_ADDRESS        (3 << 6)        /**< address command setting */

/**
 * @brief     high low shift
 * @param[in] data is the input data
 * @return    output data
 * @note      none
 */
static uint8_t a_high_low_shift(uint8_t data)  
{
    uint8_t output;
    
    output = (data << 4) | (data >> 4);                              /* part 1 */
    output = ((output << 2) & 0xCC) | ((output >> 2) & 0x33);        /* part 2 */
    output = ((output << 1) & 0xAA) | ((output >> 1) & 0x55);        /* part 3 */
    
    return output;                                                   /* return output */
}

/**
 * @brief     spi write
 * @param[in] *handle points to a tm1638 handle structure
 * @param[in] cmd is the set command
 * @param[in] *buf points to a data buffer 
 * @param[in] len is the buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_tm1638_write(tm1638_handle_t *handle, uint8_t cmd, uint8_t *buf, uint16_t len)
{
    uint8_t inner_buffer[32];
    uint16_t i;
    
    if (len > 32)                                                            /* check len */
    {
        return 1;                                                            /* return error */
    }
    for (i = 0; i < len; i++)                                                /* loop all */
    {
        inner_buffer[i] = a_high_low_shift(buf[i]);                          /* shift */
    }
    if (handle->spi_write(a_high_low_shift(cmd), inner_buffer, len) != 0)    /* write data */
    {
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

/**
 * @brief      spi read
 * @param[in]  *handle points to a tm1638 handle structure
 * @param[in]  cmd is the set command
 * @param[out] *buf points to a data buffer 
 * @param[in]  len is the buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_tm1638_read(tm1638_handle_t *handle, uint8_t cmd, uint8_t *buf, uint16_t len)
{
    uint16_t i;
    
    if (handle->spi_read(a_high_low_shift(cmd), buf, len) != 0)        /* read data */
    {
        return 1;                                                      /* return error */
    }
    for (i = 0; i < len; i++)                                          /* loop all */
    {
        buf[i] = a_high_low_shift(buf[i]);                             /* shift */
    }
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t tm1638_init(tm1638_handle_t *handle)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->debug_print == NULL)                                 /* check debug_print */
    {
        return 3;                                                    /* return error */
    }
    if (handle->spi_init == NULL)                                    /* check spi_init */
    {
        handle->debug_print("tm1638: spi_init is null.\n");          /* spi_init is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->spi_deinit == NULL)                                  /* check spi_deinit */
    {
        handle->debug_print("tm1638: spi_deinit is null.\n");        /* spi_deinit is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->spi_write == NULL)                                   /* check spi_write */
    {
        handle->debug_print("tm1638: spi_write is null.\n");         /* spi_write is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->spi_read == NULL)                                    /* check spi_read */
    {
        handle->debug_print("tm1638: spi_read is null.\n");          /* spi_read is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->delay_ms == NULL)                                    /* check delay_ms */
    {
        handle->debug_print("tm1638: delay_ms is null.\n");          /* delay_ms is null */
        
        return 3;                                                    /* return error */
    }
    
    if (handle->spi_init() != 0)                                     /* spi init */
    {
        handle->debug_print("tm1638: spi init failed.\n");           /* spi init failed */
        
        return 1;                                                    /* return error */
    }
    handle->data_conf = 0x00;                                        /* init 0 */
    handle->display_conf = 0x00;                                     /* init 0  */
    handle->inited = 1;                                              /* flag inited */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t tm1638_deinit(tm1638_handle_t *handle)
{
    uint8_t res;
    uint8_t cmd;
    
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }
    
    handle->display_conf &= ~(1 << 3);                          /* clear settings */
    cmd = TM1638_COMMAND_DISPLAY | handle->display_conf;        /* set the command */
    res = a_tm1638_write(handle, cmd, NULL, 0);                 /* write */
    if (res != 0)                                               /* check error */
    {
        handle->debug_print("tm1638: write failed.\n");         /* write failed */
        
        return 4;                                               /* return error */
    }
    
    res = handle->spi_deinit();                                 /* close spi */
    if (res != 0)                                               /* check the result */
    {
        handle->debug_print("tm1638: spi deinit failed.\n");    /* spi deinit failed */
        
        return 1;                                               /* return error */
    }
    handle->inited = 0;                                         /* flag close */
    
    return 0;                                                   /* success return 0 */
}

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
uint8_t tm1638_set_pulse_width(tm1638_handle_t *handle, tm1638_pulse_width_t width)
{
    uint8_t res;
    uint8_t cmd;
    
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }
    
    handle->display_conf &= ~(7 << 0);                          /* clear settings */
    handle->display_conf |= width;                              /* set display conf */
    cmd = TM1638_COMMAND_DISPLAY | handle->display_conf;        /* set the command */
    res = a_tm1638_write(handle, cmd, NULL, 0);                 /* write */
    if (res != 0)                                               /* check error */
    {
        handle->debug_print("tm1638: write failed.\n");         /* write failed */
        
        return 1;                                               /* return error */
    }
    
    return 0;                                                   /* success return 0 */
}

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
uint8_t tm1638_get_pulse_width(tm1638_handle_t *handle, tm1638_pulse_width_t *width)
{
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    *width = (tm1638_pulse_width_t)(handle->display_conf & 0x7);        /* get width */
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t tm1638_set_display(tm1638_handle_t *handle, tm1638_bool_t enable)
{
    uint8_t res;
    uint8_t cmd;
    
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }
    
    handle->display_conf &= ~(1 << 3);                          /* clear settings */
    handle->display_conf |= enable << 3;                        /* set display conf */
    cmd = TM1638_COMMAND_DISPLAY | handle->display_conf;        /* set the command */
    res = a_tm1638_write(handle, cmd, NULL, 0);                 /* write */
    if (res != 0)                                               /* check error */
    {
        handle->debug_print("tm1638: write failed.\n");         /* write failed */
        
        return 1;                                               /* return error */
    }
    
    return 0;                                                   /* success return 0 */
}

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
uint8_t tm1638_get_display(tm1638_handle_t *handle, tm1638_bool_t *enable)
{
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    *enable = (tm1638_bool_t)((handle->display_conf >> 3) & 0x01);      /* get bool */
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t tm1638_set_address_mode(tm1638_handle_t *handle, tm1638_address_mode_t mode)
{
    uint8_t res;
    uint8_t cmd;
    
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }
    
    handle->data_conf &= ~(1 << 2);                             /* clear settings */
    handle->data_conf |= mode << 2;                             /* set address mode */
    cmd = TM1638_COMMAND_DATA | handle->data_conf;              /* set the command */
    res = a_tm1638_write(handle, cmd, NULL, 0);                 /* write */
    if (res != 0)                                               /* check error */
    {
        handle->debug_print("tm1638: write failed.\n");         /* write failed */
        
        return 1;                                               /* return error */
    }
    
    return 0;                                                   /* success return 0 */
}

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
uint8_t tm1638_get_address_mode(tm1638_handle_t *handle, tm1638_address_mode_t *mode)
{
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    *mode = (tm1638_address_mode_t)((handle->data_conf >> 2) & 0x01);        /* get address mode */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t tm1638_set_test_mode(tm1638_handle_t *handle, tm1638_bool_t enable)
{
    uint8_t res;
    uint8_t cmd;
    
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }
    
    handle->data_conf &= ~(1 << 3);                             /* clear settings */
    handle->data_conf |= enable << 3;                           /* set test mode */
    cmd = TM1638_COMMAND_DATA | handle->data_conf;              /* set the command */
    res = a_tm1638_write(handle, cmd, NULL, 0);                 /* write */
    if (res != 0)                                               /* check error */
    {
        handle->debug_print("tm1638: write failed.\n");         /* write failed */
        
        return 1;                                               /* return error */
    }
    
    return 0;                                                   /* success return 0 */
}

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
uint8_t tm1638_get_test_mode(tm1638_handle_t *handle, tm1638_bool_t *enable)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    *enable = (tm1638_bool_t)((handle->data_conf >> 3) & 0x01);        /* get test mode */
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t tm1638_clear_segment(tm1638_handle_t *handle)
{
    uint8_t res;
    uint8_t i;
    uint8_t cmd;
    uint16_t data[8] = {0};
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    cmd = TM1638_COMMAND_DATA | handle->data_conf;                      /* set the command */
    res = a_tm1638_write(handle, cmd, NULL, 0);                         /* write */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("tm1638: write failed.\n");                 /* write failed */
        
        return 1;                                                       /* return error */
    }

    if ((handle->data_conf & (1 << 2)) != 0)                            /* fixed address mode */
    {
        for (i = 0; i < 8; i++)                                         /* loop all */
        {
            uint8_t temp;
            
            cmd = TM1638_COMMAND_ADDRESS | (i * 2);                     /* set the command */
            temp = (data[i] >> 0) & 0xFF;                               /* set lsb */
            res = a_tm1638_write(handle, cmd, &temp, 1);                /* write */
            if (res != 0)                                               /* check error */
            {
                handle->debug_print("tm1638: write failed.\n");         /* write failed */
                
                return 1;                                               /* return error */
            }
            
            cmd = TM1638_COMMAND_ADDRESS | (i * 2 + 1);                 /* set the command */
            temp = (data[i] >> 8) & 0xFF;                               /* set msb */
            res = a_tm1638_write(handle, cmd, &temp, 1);                /* write */
            if (res != 0)                                               /* check error */
            {
                handle->debug_print("tm1638: write failed.\n");         /* write failed */
                
                return 1;                                               /* return error */
            }
        }
    }
    else                                                                /* auto increment 1 mode */
    {
        uint8_t temp[16];
        
        for (i = 0; i < 8; i++)                                         /* loop all */
        {
           temp[i * 2 + 0] = data[i] & 0xFF;                            /* set lsb */
           temp[i * 2 + 1] = (data[i] >> 8) & 0xFF;                     /* set msb */
        }
        cmd = TM1638_COMMAND_ADDRESS;                                   /* set the command */
        res = a_tm1638_write(handle, cmd, temp, 8 * 2);                 /* write */
        if (res != 0)                                                   /* check error */
        {
            handle->debug_print("tm1638: write failed.\n");             /* write failed */
            
            return 1;                                                   /* return error */
        }
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t tm1638_write_segment(tm1638_handle_t *handle, uint8_t addr, uint16_t *data, uint8_t len)
{
    uint8_t res;
    uint8_t i;
    uint8_t cmd;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    if (addr + len > 8)                                                 /* check range */
    {
        handle->debug_print("tm1638: addr + len > 8.\n");               /* addr + len > 8 */
        
        return 4;                                                       /* return error */
    }
    
    cmd = TM1638_COMMAND_DATA | handle->data_conf;                      /* set the command */
    res = a_tm1638_write(handle, cmd, NULL, 0);                         /* write */
    if (res != 0)                                                       /* check error */
    {
        handle->debug_print("tm1638: write failed.\n");                 /* write failed */
        
        return 1;                                                       /* return error */
    }

    if ((handle->data_conf & (1 << 2)) != 0)                            /* fixed address mode */
    {
        for (i = 0; i < len; i++)                                       /* loop all */
        {
            uint8_t temp;
            
            cmd = TM1638_COMMAND_ADDRESS | (addr * 2 + i * 2);          /* set the command */
            temp = (data[i] >> 0) & 0xFF;                               /* set lsb */
            res = a_tm1638_write(handle, cmd, &temp, 1);                /* write */
            if (res != 0)                                               /* check error */
            {
                handle->debug_print("tm1638: write failed.\n");         /* write failed */
                
                return 1;                                               /* return error */
            }
            
            cmd = TM1638_COMMAND_ADDRESS | (addr * 2 + i * 2 + 1);      /* set the command */
            temp = (data[i] >> 8) & 0xFF;                               /* set msb */
            res = a_tm1638_write(handle, cmd, &temp, 1);                /* write */
            if (res != 0)                                               /* check error */
            {
                handle->debug_print("tm1638: write failed.\n");         /* write failed */
                
                return 1;                                               /* return error */
            }
        }
    }
    else                                                                /* auto increment 1 mode */
    {
        uint8_t temp[16];
        
        for (i = 0; i < len; i++)                                       /* loop all */
        {
           temp[i * 2 + 0] = data[i] & 0xFF;                            /* set lsb */
           temp[i * 2 + 1] = (data[i] >> 8) & 0xFF;                     /* set msb */
        }
        cmd = TM1638_COMMAND_ADDRESS | addr * 2;                        /* set the command */
        res = a_tm1638_write(handle, cmd, temp, len * 2);               /* write */
        if (res != 0)                                                   /* check error */
        {
            handle->debug_print("tm1638: write failed.\n");             /* write failed */
            
            return 1;                                                   /* return error */
        }
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t tm1638_read_segment(tm1638_handle_t *handle, uint8_t segk[4])
{
    uint8_t res;
    uint8_t cmd;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    cmd = TM1638_COMMAND_DATA | handle->data_conf | (1 << 1);        /* set the command */
    res = a_tm1638_read(handle, cmd, segk, 4);                       /* read */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("tm1638: write failed.\n");              /* write failed */
        
        return 1;                                                    /* return error */
    }

    return 0;                                                        /* success return 0 */
}

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
uint8_t tm1638_set_reg(tm1638_handle_t *handle, uint8_t cmd, uint8_t *data, uint8_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    res = a_tm1638_write(handle, cmd, data, len);                   /* write */
    if (res != 0)                                                   /* check error */
    {
        handle->debug_print("tm1638: write failed.\n");             /* write failed */
        
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t tm1638_get_reg(tm1638_handle_t *handle, uint8_t cmd, uint8_t *data, uint8_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = a_tm1638_read(handle, cmd, data, len);                   /* read */
    if (res != 0)                                                  /* check error */
    {
        handle->debug_print("tm1638: read failed.\n");             /* read failed */
        
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to a tm1638 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tm1638_info(tm1638_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(tm1638_info_t));                         /* initialize tm1638 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "SPI", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
