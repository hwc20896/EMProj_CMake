#pragma once
#ifndef MANAGEMENTWIDGET_HPP
#define MANAGEMENTWIDGET_HPP
#include <QWidget>
#include "templatewidget.hpp"

class ManagementWidget final : public QWidget {
    Q_OBJECT
    public:
        explicit ManagementWidget(QWidget* parent = nullptr);
};

#endif
