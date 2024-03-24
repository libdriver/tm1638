### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

SPI Pin: SCLK/MOMI/CS GPIO11/GPIO10/GPIO8.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(tm1638 REQUIRED)
```
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

#### 3.2 How to run

```shell
# open one terminal and run the server
./tm1638_server 
```
```shell
# open another terminal and sent the command
./tm1638 xxx xxx xxx ...
```

#### 3.3 Command Example

```shell
./tm1638 -i

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
./tm1638 -p

tm1638: SPI interface SCK connected to GPIO11(BCM).
tm1638: SPI interface MOMI connected to GPIO10(BCM).
tm1638: SPI interface CS connected to GPIO8(BCM).
```

```shell
./tm1638 -t write

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
./tm1638 -t read --times=3

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
./tm1638 -e init

tm1638: init.
```

```shell
./tm1638 -e read

tm1638: segk[0]: 0x01.
tm1638: segk[1]: 0x00.
tm1638: segk[2]: 0x00.
tm1638: segk[3]: 0x00.
```

```shell
./tm1638 -e write --addr=0 --num=0

tm1638: write address 0 number 0.
```
```shell
./tm1638 -e on

tm1638: display on.
```
```
./tm1638 -e off

tm1638: display off.
```
```shell
./tm1638 -e deinit

tm1638: deinit.
```
```shell
./tm1638 -h

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
