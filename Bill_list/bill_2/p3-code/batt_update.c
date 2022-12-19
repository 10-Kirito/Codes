#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batt.h"

struct p_bin_num {
    int min, max;
    int bin_str;
} p_bin[6] = {
    {0,     4,      0b00000000},
    {5,     29,     0b00000001},
    {30,    49,     0b00000011},
    {50,    69,     0b00000111},
    {70,    89,     0b00001111},
    {90,    100,    0b00011111},
};

struct v_bin_num {
    int num;
    int bin_str;
} v_bin[11] = {
    {0, 0b0111111},
    {1, 0b0000110},
    {2, 0b1011011},
    {3, 0b1001111},
    {4, 0b1100110},
    {5, 0b1101101},
    {6, 0b1111101},
    {7, 0b0000111},
    {8, 0b1111111},
    {9, 0b1101111},
    {10, 0b1000000},
};

int find_p_bin_str(int p)
{
    int i;

    for (i = 0; i < 6; i++) {
        if (p >= p_bin[i].min && p <= p_bin[i].max) {
            return p_bin[i].bin_str;
        }
    }

    return 0;
}

int set_batt_from_ports(batt_t *batt)
{
    //printf("BATT_STATUS_PORT 0x%x\n", BATT_STATUS_PORT);
    //printf("BATT_DISPLAY_PORT 0x%x\n", BATT_DISPLAY_PORT);
    //printf("BATT_VOLTAGE_PORT 0x%x\n", BATT_VOLTAGE_PORT);
    int ret = 0;

    if (BATT_STATUS_PORT & 0x10) {
        batt->mode = 1;//P
    } else {
        batt->mode = 2;//V
    }

    if (BATT_VOLTAGE_PORT) {
        if (BATT_VOLTAGE_PORT > 0) {
            batt->mlvolts = BATT_VOLTAGE_PORT >> 1;
        } else {
            batt->mlvolts = 0;
            if (batt->mode == 2) {
                batt->mode = 0;
                ret = 1;
            }
        }
        if (batt->mlvolts >= 3000) {
            batt->percent = (batt->mlvolts - 3000) / 8;
        } else {
            batt->percent = 0;
            if (batt->mode == 1) {
                batt->mode = 0;
                ret = 1;
            }
        }
        if (batt->percent > 100) {
            batt->percent = 100;
        }
    } else {
        batt->mlvolts = 0;
        batt->percent = 0;
    }
    return ret;
}

// int set_display_from_batt(batt_t batt, int *display)
// {
//     int fmt_bits = 0, i;
//     int mode, value, tmp, tmp_bin;
//     if (batt.mode == 0) {
//         printf("batt.mode 0\n");
//         *display = fmt_bits;
//         return -1;
//     }

//     if (batt.mode == 2 && batt.mlvolts == 0) {
//         *display = 0b00000000011111101111110111111110;
//         return 0;
//     }

//     if (batt.mode == 1 && batt.percent == 0) {
//         *display = 0b00000000000000000000000111111001;
//         return 0;
//     }

//     if (batt.mode == 1 && batt.percent == 100) {
//         *display = 0b00011111000011001111110111111001;
//         return 0;
//     }

//     if (batt.mode == 1) {//p
//         fmt_bits |= 0x01; // bit0 --> 0001

//         mode = 10;
//         tmp = batt.percent;
//         for (i = 1; i >= 0; i--) {
//             value = tmp / mode;
//             if (value != 0 || (value == 0 && i == 0)) {
//                 tmp_bin = v_bin[value].bin_str;
//                 fmt_bits |= (tmp_bin << (i * 7 + 3));
//                 //printf("value %d, tmp_bin 0x%x, fmt_bits 0x%x\n", value, tmp_bin, fmt_bits);
//             }

//             tmp = tmp % mode;
//             mode /= 10;
//         }
//     } else {//v
//         fmt_bits |= 0x06; //bit 1-2 --> 0110

//         mode = 1000;
//         tmp = batt.mlvolts;
//         for (i = 2; i >= 0; i--) {
//             value = tmp / mode;
//             //printf("value %d = tmp %d / mode %d\n", value, tmp, mode);

//             if (i == 0) {
//                 if (tmp % mode > 5) {
//                     value++;
//                 }
//             }
//             tmp_bin = v_bin[value].bin_str;
//             fmt_bits |= (tmp_bin << (i * 7 + 3));
//             //printf("value %d, tmp_bin 0x%x, fmt_bits 0x%x\n", value, tmp_bin, fmt_bits);
//             tmp = tmp % mode;
//             mode /= 10;
//         }
//     }

//     tmp_bin = find_p_bin_str(batt.percent);
//     fmt_bits |= (tmp_bin << 24);
//     *display = fmt_bits;

//     return 0;
// }

int batt_update()
{
    int ret;

    batt_t batt;
    ret = set_batt_from_ports(&batt);
    if (ret == 1) {
        return ret;
    }
    ret = set_display_from_batt(batt, &BATT_DISPLAY_PORT);

    return ret;
}    

