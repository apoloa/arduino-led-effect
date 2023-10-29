#include "Oled.h"

void OledManager::init(const char* title_name) {
    _OLED.begin();
    _OLED.display();
    _OLED.setFont(u8g2_font_profont10_tf);
    this->g_lineHeight = _OLED.getFontAscent();
    this->_displayWidth = _OLED.getDisplayWidth();
    this->_titleName = title_name;
    print();
}

void OledManager::showIP(const String ip) {
    this->_ip = ip;
    print();
}

void OledManager::showEffect(const String effect) {
    this->_effect = effect;
    print();
    
}

void OledManager::print() {
    _OLED.clear();
    _OLED.setCursor(0, g_lineHeight);
    _OLED.print(_titleName);
    int separatorLine = this->g_lineHeight + 4;
    _OLED.setCursor(0, separatorLine);
    _OLED.drawLine(0, separatorLine, _displayWidth, separatorLine);
    int ipLine = separatorLine * 2;
    _OLED.setCursor(0, ipLine);
    _OLED.print("Local IP: " + _ip);
    int effectLine = separatorLine * 3;
    _OLED.setCursor(0, effectLine);
    _OLED.print("Effect: " + _effect);
    _OLED.sendBuffer();
}