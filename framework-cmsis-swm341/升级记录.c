2022/04/22
CSL\SWM341_StdPeriph_Driver\SWM341_flash.c 文件中，FLASH_Erase()、FLASH_Write() 改用 IAP 实现

2022/04/26
CSL\CMSIS\DeviceSupport\SWM341.h 文件中，TIMR_TypeDef 定义中，修正 PREDIV 寄存器位置错误，导致定时器预分频不起作用问题

2022/04/28
CSL\CMSIS\DeviceSupport\SWM341.h 文件中，UART_TypeDef 定义中，删除旧的 BRK 发送/检测功能寄存器

2022/05/10
CSL\SWM341_StdPeriph_Driver\SWM341_sdio.c 文件中，parseCSD() 定义中，将：
SD_cardInfo.CardCapacity = (SD_cardInfo.SD_csd.DeviceSize + 1) * 512 * 1024;
修正为：
SD_cardInfo.CardCapacity = (uint64_t)(SD_cardInfo.SD_csd.DeviceSize + 1) * 512 * 1024;

2022/05/11
CSL\SWM341_StdPeriph_Driver\SWM341_usbh.c 文件中，USBH_HW_Init() 定义中，将：
	USBD->DEVCR = (0 << USBD_DEVCR_DEVICE_Pos) |	// 主机模式
				  (1 << USBD_DEVCR_CSRDONE_Pos);
修改为：
	USBD->DEVCR = (0 << USBD_DEVCR_DEVICE_Pos) |	// 主机模式
				  (3 << USBD_DEVCR_SPEED_Pos)  |
				  (1 << USBD_DEVCR_CSRDONE_Pos);
同时删除 USBH_GetDeviceSpeed() 中对 USBD->DEVCR 的修改，解决上电时 USB Host 错误识别到 USB Device 插入的问题。

2022/05/24
CSL\SWM341_StdPeriph_Driver\SWM341_port.h 文件中，添加定义：
#define PORTA_PIN6_XTAL32_OUT   15
#define PORTA_PIN7_XTAL32_IN	15

CSL\CMSIS\DeviceSupport\SWM341.h 文件中，SYS->HRCCR 寄存器删除 LDOON 位定义

2022/05/31
CSL\SWM341_StdPeriph_Driver\SWM341_can.c 文件中，CAN_SetBaudrate() 定义中，将：
uint32_t brp = SystemCoreClock/2/baudrate/(1 + (CAN_bs1 + 1) + (CAN_bs2 + 1)) - 1;
修正为：
uint32_t brp = (SystemCoreClock/2)/2/baudrate/(1 + (CAN_bs1 + 1) + (CAN_bs2 + 1)) - 1;
