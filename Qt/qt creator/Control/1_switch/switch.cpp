#include "switch.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QDebug>

static const qint8 c_delta1 = 1;
static const qint8 c_delta2 = 3;
static const double c_ratio = 0.5;
static const QColor c_uncheck_color(Qt::gray);
static const qint32 c_duration = 300;

CSwitch::CSwitch(QWidget *parent)
    : QWidget(parent),
      m_check_state(false),
      m_color(c_uncheck_color),
      m_p_animation1(nullptr),
      m_p_animation2(nullptr)
{
    m_p_animation1 = new QPropertyAnimation(this, "bkg_color");
    m_p_animation1->setDuration(c_duration);

    m_p_animation2 = new QPropertyAnimation(this, "pt_pos");
    m_p_animation2->setDuration(c_duration);

    m_p_animation_group = new QParallelAnimationGroup;
    m_p_animation_group->addAnimation(m_p_animation1);
    m_p_animation_group->addAnimation(m_p_animation2);

    init_property();
}

void CSwitch::init_property()
{
    m_properties["slider_color"] = QColor(Qt::white);
    m_properties["slider_disable_color"] = QColor(150,150,150);
    m_properties["bkg_checked_color"] = QColor(254, 44, 85);
    m_properties["bkg_checked_disable_color"] = QColor(70, 70, 70);
    m_properties["bkg_unchecked_color"] = QColor(Qt::gray);
    m_properties["bkg_unchecked_disable_color"] = QColor(70, 70, 70);
}

void CSwitch::set_color(QColor color)
{
    m_color = color;
    update();
}

void CSwitch::set_pos(QPointF pt)
{
    m_pt_pos = pt;
    update();
}

void CSwitch::get_point(QPointF &pt1, QPointF &pt2)
{
    qint32 w = width();
    qint32 w_ = w * c_ratio;

    pt1 = QPointF(c_delta1 + c_delta2, c_delta1 + c_delta2);
    pt2 = QPointF(w - w_ - (c_delta1 + c_delta2), (c_delta1 + c_delta2));
}

void CSwitch::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    qint32 w = width();
    qint32 h = height();
    qint32 w_ = w * c_ratio;
    qint32 h_ = h - 2 * (c_delta1 + c_delta2);
    QColor slider_color = isEnabled() ? get_property<QColor>("slider_color") :
                                        get_property<QColor>("slider_disable_color");
    if (m_p_animation_group->state() != QAbstractAnimation::Running) {
        if (m_check_state) {
            m_color = isEnabled() ? get_property<QColor>("bkg_checked_color") :
                                     get_property<QColor>("bkg_checked_disable_color");
        } else {
            m_color = isEnabled() ? get_property<QColor>("bkg_unchecked_color") :
                                     get_property<QColor>("bkg_unchecked_disable_color");
        }
    }

    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(m_color);

    painter.drawRoundedRect(c_delta1, c_delta1, w-2*c_delta1, h-2*c_delta1, h/2-c_delta1, h/2-c_delta1);
    painter.setBrush(slider_color);
    painter.drawRoundedRect(m_pt_pos.x(), m_pt_pos.y(), w_, h_, h_/2, h_/2);

}

void CSwitch::mousePressEvent(QMouseEvent *)
{
    QPointF pt1, pt2;
    get_point(pt1, pt2);

    if (m_p_animation_group->state() == QAbstractAnimation::Running) {
        return;
    }

    m_check_state = !m_check_state;

    if (m_check_state) {
        m_p_animation1->setStartValue(get_property<QColor>("bkg_unchecked_color"));
        m_p_animation1->setEndValue(get_property<QColor>("bkg_checked_color"));
        m_p_animation2->setStartValue(pt1);
        m_p_animation2->setEndValue(pt2);
    } else {
        m_p_animation1->setStartValue(get_property<QColor>("bkg_checked_color"));
        m_p_animation1->setEndValue(get_property<QColor>("bkg_unchecked_color"));
        m_p_animation2->setStartValue(pt2);
        m_p_animation2->setEndValue(pt1);
    }
    m_p_animation_group->start();
}

void CSwitch::resizeEvent(QResizeEvent *)
{
    QPointF pt1, pt2;
    get_point(pt1, pt2);

    m_pt_pos = m_check_state ? pt2 : pt1;
}
