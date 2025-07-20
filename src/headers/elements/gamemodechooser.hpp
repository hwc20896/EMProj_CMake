#pragma once
#ifndef GAMEMODECHOOSER_HPP
#define GAMEMODECHOOSER_HPP
#include <QComboBox>

class GamemodeChooser final : public QComboBox {
    Q_OBJECT
    public:
        explicit GamemodeChooser(int currentMode, QWidget* parent = nullptr);

        [[nodiscard]] int getCurrentMode() const;
    private:
        QStringList gamemodeList_;
};

#endif
