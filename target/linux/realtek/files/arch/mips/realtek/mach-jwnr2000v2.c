/*
 *  Netgear JVNR2000 v2 board support
 *
 *  Copyright (C) 2018 Serg Studzinski <serguzhg@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/platform_device.h>

#include <asm/mach-realtek/realtek.h>
#include <asm/mach-realtek/platform.h>

#include "machtypes.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-m25p80.h"
#include "dev-eth.h"
#include "gpio.h"

#define NG_GPIO_LED_WPS_GREEN		4
#define NG_GPIO_LED_STATUS		6

#define NG_GPIO_BTN_WPS			3
#define NG_GPIO_BTN_RESET		5

#define NG_KEYS_POLL_INTERVAL		20	/* msecs */
#define NG_KEYS_DEBOUNCE_INTERVAL	(3 * NG_KEYS_POLL_INTERVAL)

static struct gpio_led ng_leds_gpio[] __initdata = {
	{
		.name		= "ng:green:wps",
		.gpio		= NG_GPIO_LED_WPS_GREEN,
		.active_low	= 1,
	}, {
		.name		= "ng:green:status",
		.gpio		= NG_GPIO_LED_STATUS,
		.active_low	= 1,
	},
};

static struct gpio_keys_button ng_gpio_keys[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = NG_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= NG_GPIO_BTN_RESET,
		.active_low	= 1,
	} , {
		.desc		= "wps",
		.type		= EV_KEY,
		.code		= KEY_WPS_BUTTON,
		.debounce_interval = NG_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= NG_GPIO_BTN_WPS,
		.active_low	= 1,
	}
};

static void __init jwnr2000v2_init(void)
{
//	u8 *ee = (u8 *) KSEG1ADDR(0x1fc06000);
	u8 *mac = (u8 *) KSEG1ADDR(0x1fc06007);

	realtek_register_leds_gpio(-1, ARRAY_SIZE(ng_leds_gpio),
				 ng_leds_gpio);
	realtek_register_gpio_keys_polled(-1, NG_KEYS_POLL_INTERVAL,
					ARRAY_SIZE(ng_gpio_keys),
					ng_gpio_keys);

	realtek_register_m25p80(NULL);
	realtek_init_mac(re865x_data.mac_addr, mac, 0);

	realtek_register_eth();

	realtek_set_gpio_control(NG_GPIO_LED_WPS_GREEN, true);
	realtek_set_gpio_control(NG_GPIO_LED_STATUS, true);
	realtek_set_gpio_control(NG_GPIO_BTN_WPS, true);
	realtek_set_gpio_control(NG_GPIO_BTN_RESET, true);

	realtek_set_gpio_mux(
		RTL8196C_GPIO_MUX_PCIE_RST |
/*
    Bord LEDs D9-D13 and D5-D8,D3 are MUXed by GPIOC0, so to use it
    have to clear GPIOC0 and PORT0-PORT5 here and write simple mux driver
*/
		(RTL8196C_GPIO_MUX_PORT0_MASK << RTL8196C_GPIO_MUX_PORT0_SHIFT) |
		(RTL8196C_GPIO_MUX_PORT1_MASK << RTL8196C_GPIO_MUX_PORT1_SHIFT) |
		(RTL8196C_GPIO_MUX_PORT2_MASK << RTL8196C_GPIO_MUX_PORT2_SHIFT) |
		(RTL8196C_GPIO_MUX_PORT3_MASK << RTL8196C_GPIO_MUX_PORT3_SHIFT) |
		(RTL8196C_GPIO_MUX_PORT4_MASK << RTL8196C_GPIO_MUX_PORT4_SHIFT) |
		(RTL8196C_GPIO_MUX_GPIOC0_MASK << RTL8196C_GPIO_MUX_GPIOC0_SHIFT) ,
		(RTL8196C_GPIO_MUX_RESET_MASK << RTL8196C_GPIO_MUX_RESET_SHIFT) |
		(RTL8196C_GPIO_MUX_JTAG_MASK << RTL8196C_GPIO_MUX_JTAG_SHIFT));
}

MIPS_MACHINE(REALTEK_MACH_JWNR2000_V2, "JWNR2000V2", "Netgear JWNR2000 v2",
	     jwnr2000v2_init);
