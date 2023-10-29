#include <U8g2lib.h>

#ifndef OLED_H
#define OLED_H

#define OLED_CLOCK 15           // Pins for the oled display
#define OLED_DATA 4
#define OLED_RESET 16

class OledManager {
    private:
        U8G2_SSD1306_128X64_NONAME_F_SW_I2C _OLED = U8G2_SSD1306_128X64_NONAME_F_SW_I2C(U8G2_R2, OLED_CLOCK, OLED_DATA, OLED_RESET);
        int g_lineHeight = 0;
        int _displayWidth = 0;
        String _titleName; 
        String _ip;
        String _effect;
        void print();
    public: 
        void init(const char* title_name);
        void showIP(const String ip);
        void showEffect(const String effect);
};

#endif