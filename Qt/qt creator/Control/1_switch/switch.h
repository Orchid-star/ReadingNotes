#pragma once

#include <QWidget>
#include <QColor>
#include <QMap>
#include <QVariant>
#include <QDebug>

class QPaintEvent;
class QPropertyAnimation;
class QParallelAnimationGroup;

#define SET_PROPERTY(type, name) \
    Q_PROPERTY(type name WRITE set_##name) \
    void set_##name(type val) { \
         m_properties[#name] = val; \
         update();\
    }

class CSwitch : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor bkg_color WRITE set_color)
    Q_PROPERTY(QPointF pt_pos WRITE set_pos)

public:
    SET_PROPERTY(QColor, slider_color)
    SET_PROPERTY(QColor, slider_disable_color)
    SET_PROPERTY(QColor, bkg_checked_color)
    SET_PROPERTY(QColor, bkg_checked_disable_color)
    SET_PROPERTY(QColor, bkg_unchecked_color)
    SET_PROPERTY(QColor, bkg_unchecked_disable_color)

    explicit CSwitch(QWidget *parent = nullptr);
    void set_checked(bool flag) {m_check_state = flag; update();}

private:
    void init_property();
    void set_color(QColor color);
    void set_pos(QPointF pt);
    void get_point(QPointF &pt1, QPointF &pt2);
    template<typename T>
    T get_property(QString property) {
        return m_properties[property].value<T>();
    }
    bool m_check_state;
    QColor m_color;
    QPointF m_pt_pos;
    QPropertyAnimation *m_p_animation1;
    QPropertyAnimation *m_p_animation2;
    QParallelAnimationGroup *m_p_animation_group;
    QMap<QString, QVariant> m_properties;

protected:
    void paintEvent(QPaintEvent *p_event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};

