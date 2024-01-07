#include "hardware/dma.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/dma.h"
#include <stdlib.h>

// ST7735 general purpose
#define ST7735_NOP     0x00 /**< Non operation */
#define ST7735_SWRESET 0x01 /**< Soft Reset */
#define ST7735_RDDID   0x04 /**< Read Display ID*/
#define ST7735_RDDST   0x09 /**< Read Display Status*/

// ST7735 Modes
#define ST7735_SLPIN   0x10 /**< Sleep ON */
#define ST7735_SLPOUT  0x11 /**< Sleep OFF */
#define ST7735_PTLON   0x12 /**< Partial mode */
#define ST7735_NORON   0x13 /**< Normal Display */
#define ST7735_INVOFF  0x20 /**< Display invert off */
#define ST7735_INVON   0x21 /**< Display Invert on */
#define ST7735_DISPOFF 0x28 /**< Display off */
#define ST7735_DISPON  0x29 /**< Display on */
#define ST7735_TFT_Idle_modeON 0x39 /**< Idle Mode ON */
#define ST7735_TFT_Idle_modeOF  0x38 /**< Idle Mode OFF */

// ST7735 Addressing 
#define ST7735_CASET   0x2A /**< Column address set */
#define ST7735_RASET   0x2B /**<  Page address set */
#define ST7735_RAMWR   0x2C /**< Memory write */
#define ST7735_RAMRD   0x2E /**< Memory read */
#define ST7735_PTLAR   0x30 /**< Partial Area */
#define ST7735_VSCRDEF 0x33 /**< Vertical scroll def */
#define ST7735_COLMOD  0x3A /**< Interface Pixel Format */
#define ST7735_MADCTL  0x36 /**< Memory Access Control */
#define ST7735_VSCRSADD 0x37 /**< Vertical Access Control */

// Frame Rate Control
#define ST7735_FRMCTR1 0xB1 /**< Normal */
#define ST7735_FRMCTR2 0xB2 /**< idle */
#define ST7735_FRMCTR3 0xB3 /**< Partial */

#define ST7735_INVCTR  0xB4 /**< Display Inversion control */
#define ST7735_DISSET5 0xB6 /**< Display Function set */

// ST7735 Power_Control
#define ST7735_PWCTR1  0xC0 /**< Power_Control VRH: Set the GVDD voltage */
#define ST7735_PWCTR2  0xC1 /**< Power_Control BT: set VGH/ VGL voltage */
#define ST7735_PWCTR3  0xC2 /**< Power_Control APA: adjust op amp & DCA: boost Voltage */
#define ST7735_PWCTR4  0xC3 /**< Power_Control APB: adjust op amp & DCB: boost Voltage */
#define ST7735_PWCTR5  0xC4 /**< Power_Control APC: adjust op amp & DCC: boost Voltage */
#define ST7735_PWCTR6  0xFC /**< Power_Control In partial mode + Idle */

#define ST7735_VMCTR1  0xC5 /**< VCOM_Control 1 */

#define ST7735_RDID1   0xDA /**< read ID1 */
#define ST7735_RDID2   0xDB /**< read ID2  */
#define ST7735_RDID3   0xDC /**< read ID3  */
#define ST7735_RDID4   0xDD /**< read ID4  */

// ST7735 color control
#define ST7735_GMCTRP1 0xE0 /**< Positive Gamma Correction Setting */
#define ST7735_GMCTRN1 0xE1 /**< Negative Gamma Correction Setting */

// Memory Access Data Control  Register 
#define ST7735_MADCTL_MY 0x80 /**< Row Address Order */
#define ST7735_MADCTL_MX 0x40 /**< Column Address Order */
#define ST7735_MADCTL_MV 0x20 /**< Row/Column Order (MV) */
#define ST7735_MADCTL_ML 0x10 /**< Vertical Refresh Order */
#define ST7735_MADCTL_RGB 0x00 /**< RGB order */
#define ST7735_MADCTL_BGR 0x08 /**< BGR order */
#define ST7735_MADCTL_MH 0x04  /**< Horizontal Refresh Order */

#define DC_TFT 0

void st7735_init(uint16_t *, size_t);

void st7735_redraw();