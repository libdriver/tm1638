[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TM1638

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tm1638/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TM1638是一种带键盘扫描接口的LED（发光二极管显示器）驱动控制专用IC,内部集成有MCU数字接口、 数据锁存器、LED驱动、键盘扫描等电路。本产品质量可靠、稳定性好、抗干扰能力强。主要适用于家电设备(智能热水器、微波炉、洗衣机、空调、电磁炉)、机顶盒、电子称、智能电表等数码管或LED显示设备。

LibDriver TM1638是LibDriver推出的TM1638的全功能驱动，该驱动提供数码管显示、键盘扫描等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver TM1638的源文件。

/interface目录包含了LibDriver TM1638与平台无关的SPI总线模板。

/test目录包含了LibDriver TM1638驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver TM1638编程范例。

/doc目录包含了LibDriver TM1638离线文档。

/datasheet目录包含了TM1638数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的SPI总线模板，完成指定平台的SPI总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_tm1638_basic.h"

uint8_t res;
uint8_t segk[4];
uint16_t number[] = {TM1638_NUMBER_0, TM1638_NUMBER_1, TM1638_NUMBER_2,
                     TM1638_NUMBER_3, TM1638_NUMBER_4, TM1638_NUMBER_5,
                     TM1638_NUMBER_6, TM1638_NUMBER_7, TM1638_NUMBER_8, TM1638_NUMBER_9};

/* init */
res = tm1638_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* write */
res = tm1638_basic_write(0x00, number, 8);
if (res != 0)
{
    (void)tm1638_basic_deinit();
    
    return 1;
}

...
    
/* read */
res = tm1638_basic_read(segk);
if (res != 0)
{
    (void)tm1638_basic_deinit();
    
    return 1;
}

/* output */
tm1638_interface_debug_print("tm1638: segk[0]: 0x%02X.\n", segk[0]);
tm1638_interface_debug_print("tm1638: segk[1]: 0x%02X.\n", segk[1]);
tm1638_interface_debug_print("tm1638: segk[2]: 0x%02X.\n", segk[2]);
tm1638_interface_debug_print("tm1638: segk[3]: 0x%02X.\n", segk[3]);

...
    
/* on */
res = tm1638_basic_display_on();
if (res != 0)
{
    (void)tm1638_basic_deinit();
    
    return 1;
}

...
    
/* off */
res = tm1638_basic_display_off();
if (res != 0)
{
    (void)tm1638_basic_deinit();
    
    return 1;
}

...
    
/* deinit */
res = tm1638_basic_deinit();
if (res != 0)
{
    return 1;
}

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/tm1638/index.html](https://www.libdriver.com/docs/tm1638/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。