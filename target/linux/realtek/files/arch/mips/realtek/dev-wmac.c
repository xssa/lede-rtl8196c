/*
 *  Realtek RLX based SoC built-in WMAC
 *
 *  Copyright (C) 2018 Serg Studzinski <serguzhg@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include "dev-wmac.h"

static u8 rtl_wmac_macp[ETH_ALEN];

void __init realtek_register_wmac(u8 *cal_data, u8 *mac_addr)
{
/*        if (soc_is_ar913x())
                ar913x_wmac_setup();
        else if (soc_is_ar933x())
                ar933x_wmac_setup();
        else if (soc_is_ar934x())
                ar934x_wmac_setup();
        else if (soc_is_qca953x())
                qca953x_wmac_setup();
        else if (soc_is_qca955x())
                qca955x_wmac_setup();
        else if (soc_is_qca956x() || soc_is_tp9343())
                qca956x_wmac_setup();
        else
                BUG();
*/
        if (cal_data)
                memcpy(rtl_wmac_data.eeprom_data, cal_data,
                       sizeof(rtl_wmac_data.eeprom_data));

        if (mac_addr) {
                memcpy(rtl_wmac_mac, mac_addr, sizeof(rtl_wmac_mac));
                ath79_wmac_data.macaddr = rtl_wmac_mac;
        }

        platform_device_register(&ath79_wmac_device);
}
