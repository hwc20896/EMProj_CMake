#pragma once

#include <QComboBox>

class GamemodeChooser final : public QComboBox {
    Q_OBJECT
    public:
        explicit GamemodeChooser(int currentMode = 0, QWidget* parent = nullptr);

        [[nodiscard]] int getCurrentMode() const;
    private:
        QStringList gamemodeList_;

        // Stylesheet
        static constexpr auto STYLESHEET = R"(
QComboBox{
    border: 1px solid black;
    border-radius: 3px;
    padding-left: 8px;
    background-color: #f0f0f0;
}

QComboBox:hover{
    background-color: #e3e3e3;
}

QComboBox::down-arrow{
    image: url(:/Drawables/drawables/arrow_down.png);
    width: 10;
    height: 10;
}

QComboBox::drop-down{
    border: none;
}
        )";
};

