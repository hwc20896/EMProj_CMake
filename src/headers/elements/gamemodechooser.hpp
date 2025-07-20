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

        // Stylesheet
        static constexpr QString STYLESHEET = R"(
            QComboBox {
                background-color: #f0f0f0;
                border: 1px solid #ccc;
                border-radius: 4px;
                padding: 5px;
            }
            QComboBox::drop-down {
                subcontrol-origin: padding;
                subcontrol-position: top right;
                width: 20px;
            }
            QComboBox::down-arrow {
                image: url(:/Drawables/drawables/down_arrow.png);
            }
        )";
};

#endif
