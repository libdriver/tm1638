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
 * @file      main.c
 * @brief     main source file
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
#include "driver_tm1638_read_test.h"
#include "driver_tm1638_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];             /**< uart buffer */
volatile uint16_t g_len;        /**< uart buffer length */

/**
 * @brief     tm1638 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t tm1638(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    char short_options[] = "hipe:t:";
    struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"num", required_argument, NULL, 2},
        {"times", required_argument, NULL, 3},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint8_t addr = 0;
    uint8_t num = 0;
    uint32_t times = 3;
    uint16_t number[] = {TM1638_NUMBER_0, TM1638_NUMBER_1, TM1638_NUMBER_2,
                         TM1638_NUMBER_3, TM1638_NUMBER_4, TM1638_NUMBER_5,
                         TM1638_NUMBER_6, TM1638_NUMBER_7, TM1638_NUMBER_8, TM1638_NUMBER_9};

    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }

    /* init 0 */
    optind = 0;

    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);

        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");

                break;
            }

            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");

                break;
            }

            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");

                break;
            }

            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);

                break;
            }

            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);

                break;
            }

            /* addr */
            case 1 :
            {
                /* set the address */
                addr = atol(optarg);
                if (addr > 7)
                {
                    return 1;
                }

                break;
            }

            /* num */
            case 2 :
            {
                /* set the number */
                num = atol(optarg);
                if (num > 9)
                {
                    return 1;
                }

                break;
            }
            
            /* running times */
            case 3 :
            {
                /* set the times */
                times = atol(optarg);

                break;
            }

            /* the end */
            case -1 :
            {
                break;
            }

            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_write", type) == 0)
    {
        /* run the write test */
        if (tm1638_write_test() != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run the read test */
        if (tm1638_read_test(times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_init", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = tm1638_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        tm1638_interface_debug_print("tm1638: init.\n");
        
        return 0;
    }
    else if (strcmp("e_deinit", type) == 0)
    {
        uint8_t res;
        
        /* deinit */
        res = tm1638_basic_deinit();
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        tm1638_interface_debug_print("tm1638: deinit.\n");
        
        return 0;
    }
    else if (strcmp("e_write", type) == 0)
    {
        uint8_t res;
        
        /* write */
        res = tm1638_basic_write(addr, &number[num], 1);
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        tm1638_interface_debug_print("tm1638: write address %d number %d.\n", addr, num);
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint8_t segk[4];
        
        /* read */
        res = tm1638_basic_read(segk);
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        tm1638_interface_debug_print("tm1638: segk[0]: 0x%02X.\n", segk[0]);
        tm1638_interface_debug_print("tm1638: segk[1]: 0x%02X.\n", segk[1]);
        tm1638_interface_debug_print("tm1638: segk[2]: 0x%02X.\n", segk[2]);
        tm1638_interface_debug_print("tm1638: segk[3]: 0x%02X.\n", segk[3]);
        
        return 0;
    }
    else if (strcmp("e_on", type) == 0)
    {
        uint8_t res;
        
        /* on */
        res = tm1638_basic_display_on();
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        tm1638_interface_debug_print("tm1638: display on.\n");
        
        return 0;
    }
    else if (strcmp("e_off", type) == 0)
    {
        uint8_t res;
        
        /* off */
        res = tm1638_basic_display_off();
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        tm1638_interface_debug_print("tm1638: display off.\n");
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        tm1638_interface_debug_print("Usage:\n");
        tm1638_interface_debug_print("  tm1638 (-i | --information)\n");
        tm1638_interface_debug_print("  tm1638 (-h | --help)\n");
        tm1638_interface_debug_print("  tm1638 (-p | --port)\n");
        tm1638_interface_debug_print("  tm1638 (-t write | --test=write)\n");
        tm1638_interface_debug_print("  tm1638 (-t read | --test=read) [--times=<num>]\n");
        tm1638_interface_debug_print("  tm1638 (-e init | --example=init)\n");
        tm1638_interface_debug_print("  tm1638 (-e deinit | --example=deinit)\n");
        tm1638_interface_debug_print("  tm1638 (-e on | --example=on)\n");
        tm1638_interface_debug_print("  tm1638 (-e off | --example=off)\n");
        tm1638_interface_debug_print("  tm1638 (-e write | --example=write) [--addr=<address>]\n");
        tm1638_interface_debug_print("         [--num=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9>]\n");
        tm1638_interface_debug_print("  tm1638 (-e read | --example=read)\n");
        tm1638_interface_debug_print("\n");
        tm1638_interface_debug_print("Options:\n");
        tm1638_interface_debug_print("      --addr=<address>                   Set the start address and the range is 0-7.([default: 0])\n");
        tm1638_interface_debug_print("  -e <init | deinit | write | read | on | off>, --example=<init | deinit | write | read | on | off>\n");
        tm1638_interface_debug_print("                                         Run the driver example.\n");
        tm1638_interface_debug_print("  -h, --help                             Show the help.\n");
        tm1638_interface_debug_print("  -i, --information                      Show the chip information.\n");
        tm1638_interface_debug_print("  -p, --port                             Display the pin connections of the current board.\n");
        tm1638_interface_debug_print("      --num=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9>([default: 0])\n");
        tm1638_interface_debug_print("                                         Set display number.\n");
        tm1638_interface_debug_print("  -t <read | write>, --test=<read | write>.\n");
        tm1638_interface_debug_print("                                         Run the driver test.\n");
        tm1638_interface_debug_print("      --times=<num>                      Set the running times.([default: 3])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        tm1638_info_t info;

        /* print tm1638 info */
        tm1638_info(&info);
        tm1638_interface_debug_print("tm1638: chip is %s.\n", info.chip_name);
        tm1638_interface_debug_print("tm1638: manufacturer is %s.\n", info.manufacturer_name);
        tm1638_interface_debug_print("tm1638: interface is %s.\n", info.interface);
        tm1638_interface_debug_print("tm1638: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tm1638_interface_debug_print("tm1638: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tm1638_interface_debug_print("tm1638: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tm1638_interface_debug_print("tm1638: max current is %0.2fmA.\n", info.max_current_ma);
        tm1638_interface_debug_print("tm1638: max temperature is %0.1fC.\n", info.temperature_max);
        tm1638_interface_debug_print("tm1638: min temperature is %0.1fC.\n", info.temperature_min);

        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        tm1638_interface_debug_print("tm1638: SPI interface SCK connected to GPIOA PIN5.\n");
        tm1638_interface_debug_print("tm1638: SPI interface MOMI connected to GPIOA PIN7.\n");
        tm1638_interface_debug_print("tm1638: SPI interface CS connected to GPIOA PIN4.\n");

        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;

    /* stm32f407 clock init and hal init */
    clock_init();

    /* delay init */
    delay_init();

    /* uart init */
    uart_init(115200);

    /* shell init && register tm1638 function */
    shell_init();
    shell_register("tm1638", tm1638);
    uart_print("tm1638: welcome to libdriver tm1638.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("tm1638: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("tm1638: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("tm1638: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("tm1638: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("tm1638: param is invalid.\n");
            }
            else
            {
                uart_print("tm1638: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
