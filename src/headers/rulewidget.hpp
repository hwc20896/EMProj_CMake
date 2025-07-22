#pragma once
#ifndef RULEWIDGET_HPP
#define RULEWIDGET_HPP
#include "ui_rulewidget.h"
#include <QSoundEffect>
#include <format>

class RuleWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit RuleWidget(QWidget* parent = nullptr);
        void setRuleText(int questionCount, int totalQuestions) const;
        ~RuleWidget() override;
    private:
        Ui::RuleWidget* ui_;
        QSoundEffect* corrSound_, * incorrSound_;

        //  Rule text
        static constexpr auto ruleText = R"(（遊戲以程序檔(.exe)呈現）

玩法：
在按開始遊戲後，玩家共需回答{0}條問題。
答對了（選擇正確答案）可直接進入下一題，並獲得甜美的恭喜音效。
答錯（選擇錯誤答案）則自動出現正確答案，並獲得甜美的鼓勵音效。
答題庫共有{1}條，每輪遊戲會隨機抽出{0}題進行遊戲。

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