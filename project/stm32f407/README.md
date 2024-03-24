### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

SPI Pin: SCK/MOMI/CS  PA5/PA7/PA4.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. TM1638

#### 3.1 Command Instruction

1. Show tm1638 chip and driver information.

    ```shell
    tm1638 (-i | --information)  
    ```

2. Show tm1638 help.

    ```shell
    tm1638 (-h | --help)        
    ```

3. Show tm1638 pin connections of the current board.

    ```shell
    tm1638 (-p | --port)        
    ```

4. Run tm1638 write test.

    ```shell
    tm1638 (-t write  | --test=write )      
    ```

5. Run tm1638 read test, num means test times.

    ```shell
    tm1638 (-t read | --test=read) [--times=<num>]    
    ```

8. Run tm1638 read function.

    ```shell
    tm1638 (-e read | --example=read)    
    ```

8. Run tm1638 write function,  address is the start address and the range is 0 - 7.

    ```shell
    tm1638 (-e write | --example=write) [--addr=<address>] [--num=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9>]   
    ```
    
9. Run tm1638 init function.

    ```shell
    tm1638 (-e init | --example=init)

9. Run tm1638 deinit function.

    ```shell
    tm1638 (-e deinit | --example=deinit)

9. Run tm1638 on function.

    ```shell
    tm1638 (-e on | --example=on)

9. Run tm1638 off function.

    ```shell
    tm1638 (-e off | --example=off)

#### 3.2 Command Example

```shell
tm1638 -i

tm1638: chip is Titan Micro Electronics TM1638.
tm1638: manufacturer is Titan Micro Electronics.
tm1638: interface is SPI.
tm1638: driver version is 1.0.
tm1638: min supply voltage is 3.0V.
tm1638: max supply voltage is 6.0V.
tm1638: max current is 200.00mA.
tm1638: max temperature is 125.0C.
tm1638: min temperature is -40.0C.
```

```shell
tm1638 -p

tm1638: SPI interface SCK connected to GPIOA PIN5.
tm1638: SPI interface MOMI connected to GPIOA PIN7.
tm1638: SPI interface CS connected to GPIOA PIN4.
```

```shell
tm1638 -t write

tm1638: chip is Titan Micro Electronics TM1638.
tm1638: manufacturer is Titan Micro Electronics.
tm1638: interface is GPIO.
tm1638: driver version is 1.0.
tm1638: min supply voltage is 3.0V.
tm1638: max supply voltage is 6.0V.
tm1638: max current is 200.00mA.
tm1638: max temperature is 125.0C.
tm1638: min temperature is -40.0C.
tm1638: start write test.
tm1638: address auto increment mode.
tm1638: address fix mode.
tm1638: set pulse width 12.
tm1638: set pulse width 10.
tm1638: set pulse width 2.
tm1638: display off.
tm1638: display on.
tm1638: finish write test.
```

```shell
tm1638 -t read --times=3

tm1638: chip is Titan Micro Electronics TM1638.
tm1638: manufacturer is Titan Micro Electronics.
tm1638: interface is GPIO.
tm1638: driver version is 1.0.
tm1638: min supply voltage is 3.0V.
tm1638: max supply voltage is 6.0V.
tm1638: max current is 200.00mA.
tm1638: max temperature is 125.0C.
tm1638: min temperature is -40.0C.
tm1638: start read test.
tm1638: segk[0]: 0x01.
tm1638: segk[1]: 0x00.
tm1638: segk[2]: 0x00.
tm1638: segk[3]: 0x00.
tm1638: segk[0]: 0x00.
tm1638: segk[1]: 0x01.
tm1638: segk[2]: 0x00.
tm1638: segk[3]: 0x00.
tm1638: segk[0]: 0x00.
tm1638: segk[1]: 0x00.
tm1638: segk[2]: 0x01.
tm1638: segk[3]: 0x00.
tm1638: finish read test.
```

```shell
tm1638 -e init

tm1638: init.
```

```shell
tm1638 -e read

tm1638: segk[0]: 0x01.
tm1638: segk[1]: 0x00.
tm1638: segk[2]: 0x00.
tm1638: segk[3]: 0x00.
```

```shell
tm1638 -e write --addr=0 --num=0

tm1638: write address 0 number 0.
```
```shell
tm1638 -e on

tm1638: display on.
```
```
tm1638 -e off

tm1638: display off.
```
```shell
tm1638 -e deinit

tm1638: deinit.
```
```shell
tm1638 -h

Usage:
  tm1638 (-i | --information)
  tm1638 (-h | --help)
  tm1638 (-p | --port)
  tm1638 (-t write | --test=write)
  tm1638 (-t read | --test=read) [--times=<num>]
  tm1638 (-e init | --example=init)
  tm1638 (-e deinit | --example=deinit)
  tm1638 (-e on | --example=on)
  tm1638 (-e off | --example=off)
  tm1638 (-e write | --example=write) [--addr=<address>]
         [--num=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9>]
  tm1638 (-e read | --example=read)

Options:
      --addr=<address>                   Set the start address and the range is 0-7.([default: 0])
  -e <init | deinit | write | read | on | off>, --example=<init | deinit | write | read | on | off>
                                         Run the driver example.
  -h, --help                             Show the help.
  -i, --information                      Show the chip information.
  -p, --port                             Display the pin connections of the current board.
      --num=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9>([default: 0])
                                         Set display number.
  -t <read | write>, --test=<read | write>.
                                         Run the driver test.
      --times=<num>                      Set the running times.([default: 3])
```
