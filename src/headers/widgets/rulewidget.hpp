#pragma once
#ifndef RULEWIDGET_HPP
#define RULEWIDGET_HPP
#include <QWidget>
#include <QSoundEffect>

//  PIMPL pattern
namespace Ui {
    class RuleWidget;
}

class RuleWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit RuleWidget(QWidget* parent = nullptr);
        void setRuleText(const std::string& blockText, int displayQuantity) const;
        ~RuleWidget() override;
    private:
        Ui::RuleWidget* ui_;

#ifndef NO_SOUND_EFFECT_PREVIEW
        QSoundEffect* corrSound_, * incorrSound_;
#endif

        //  Rule text
        static constexpr auto ruleText = R"(（遊戲以程序檔(.exe)呈現）

玩法：{0}
每輪遊戲可選擇不同模式（全部題目、僅基本法、僅憲法），系統會隨機抽取{1}題。
玩家需依次作答，答對可進入下一題並播放恭喜音效，答錯則顯示正確答案並播放鼓勵音效。
基本法題庫共{2}題，憲法題庫共{3}題，每輪將隨機抽出{1}題進行遊戲。

等級劃分：（正確率）
80% ~ 100%  -> S
55% ~ 80%   -> A
30% ~ 55%   -> B
0% ~  30%   -> C
        )";
    signals:
        void returnToIntro();
};


#endif