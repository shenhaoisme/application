/*
pinBase is the base pin that you want your shift registers to appear at. The example below uses 100.
595扩展之后，多出来8个额外的pin，编号的话从100开始。 树莓派一共 40pins

numPins here can be from 1 to 32 – 8 pins per 74×585.

The dataPin is connected to the DS pin (14), 0   wiring  SER
 the clockPin is connected to the SHCP pin (11)  1  wiring  SPCLK
 the latchPin is connected to the STCP pin (12). 2 wiring RCLK
是说怎么连线


If connecting more 74×595’s together then you connect the SHCP and STCP pins together and the Q7S output pin (9) to the DS pin on the next one up the line. Data bit zero is Q0 on the first 74×595.

Pins MR (10) should be connected to Vcc,  QH
OE (13) connected to 0v   
Pin 16 is Vcc and 8 is 0v/Ground.

The following diagram gives an example with 2 74×595’s connected to 10 LEDs:

如果将更多74×595连接在一起，则将SHCP和STCP引脚连接在一起，将Q7S输出引脚（9）连接到线路上的下一个DS引脚。数据位0在第一个74×595上为Q0。

引脚MR（10）应连接到Vcc，QH
OE（13）连接到0v
引脚16是Vcc，8是0v /地。

下图给出了一个示例，其中2个74×595连接到10个LED：

When first powering up, the 74×595 will be in a random state – it may not be wise to rely on any particular setting 
and so explicitly setting all outputs to zero, or whatever value is needed might be wise.
The sr595 module takes care of doing all the shifting and remembering which bits are already set an which are clear for you.

 You just use digitalWrite() as before. (Calls to pinMode(), etc. have no effect)
 首次启动时，74×595将处于随机状态 - 依赖任何特定设置可能不明智
因此明确地将所有输出设置为零，或者所需的任何值都可能是明智的。
sr595模块负责完成所有的移位并记住哪些位已经设置，这对您来说很清楚。
你只需要像之前一样去调用这个函数，不用再重新的去初始化，就是因为它牛逼的可以记住寄存器的状态，即使掉电。

sr595Setup() calls pinMode() and digitalWrite() on the 3 pins supplied. These pins must be output capable, but can be any 3 
pins – e.g. the Pi’s on-board GPIO or additional GPIO provided via expansion modules. You can even use an existing registered
关于使用哪些pin，没有限制，只要注册过就行。意思是扩展出来的pin也可以控制595

sr595 instance to drive additional chains, although it’s not recommended!
Each call to digitalWrite() will do a complete shift of all bits out through the shift-register. 
If the 74×595 is directly connected to the Pi’s GPIO then each bit write takes 2µS plus an additional 2µS per latch.
 sr595实例驱动额外的链，虽然不推荐！
每次调用digitalWrite（）都会通过移位寄存器完成所有位的移位。
如果74×595直接连接到Pi的GPIO，那么每个位写入需要2μS加上每个锁存器额外的2μS。

 It should be “fast enough”, but do bear this in-mind when shifting out big strings of bits – ie. 
 4 daisy chained together into a 32-bit register will take 32 x 2 + 2 = 66µS per update. It may be slightly slower 
 它应该“足够快”，但在移出大量的比特时也要考虑到这一点 - 即。
 4菊花链接在一起成为32位寄存器，每次更新需要32 x 2 + 2 =66μS。它可能会稍慢
daisy 这个菊花是什么东东?
 if you connect the 74×595’s to another GPIO expander.
You can power the 74×595 from 5v rather than 3.3v if required. There are no inputs back to the Pi so it should be fine.
如果你连接到另一个GPIO扩展器。
如果需要，您可以从5v而不是3.3v为74×595供电。没有输入回Pi，所以应该没问题。

*/


#include <stdio.h>
#include <wiringPi.h>
#include <sr595.h>

int main (void)
{
  int i, bit ;

  wiringPiSetup () ;

// Pin base 100 for 10 pins.
//    Use wiringPi pins 0, 1 & 2 for data, clock and latch
  sr595Setup (100, 8, 0, 1, 2) ;

  printf ("Raspberry Pi - Shift Register Test\n") ;
/*
  for (;;)
  {
    for (i = 0 ; i < 1024 ; ++i)
    {
      for (bit = 0 ; bit < 8 ; ++bit)
        digitalWrite (100 + bit, i & (1 << bit)) ;
      delay (5) ;
    }
  }
*/

        digitalWrite (100,1) ;

  return 0 ;
}