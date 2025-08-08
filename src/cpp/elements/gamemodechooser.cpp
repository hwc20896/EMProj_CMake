#include "elements/gamemodechooser.hpp"
#include "templatewidget.hpp"

GamemodeChooser::GamemodeChooser(const int currentMode, QWidget* parent) : QComboBox(parent) {
    this->gamemodeList_ = {"所有題目", "只有憲法", "只有基本法"};
    this->addItems(this->gamemodeList_);
    this->setCurrentIndex(currentMode);

    this->setStyleSheet(STYLESHEET);

    this->setFont({"Microsoft JhengHei", 18});
}

int GamemodeChooser::getCurrentMode() const {
    return this->currentIndex();
}