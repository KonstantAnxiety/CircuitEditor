#include "component.h"

Component::Component()
{

}

bool Component::hover(double x, double y) const { // ROTATION
    QTransform t;
    t.translate(ex(), ey());
    t.rotate(r());
    t.translate(-ex(), -ey());
    QVector<QPoint> points;
    points.push_back(QPoint(ex()-w(), ey()-h()/2));
    points.push_back(QPoint(ex()-w(), ey()+h()/2));
    points.push_back(QPoint(ex(), ey()+h()/2));
    points.push_back(QPoint(ex(), ey()-h()/2));
    QPolygonF border = QPolygonF(points);
    border = t.map(border);
    return (border.containsPoint(QPointF(x, y), Qt::OddEvenFill));
}

void Component::write(std::ostream &out) const {
    out << id() << " " << ex() << " " << ey() << " "
        << r() << " " <<  w() << " " << h() << " " << getText().toStdString();
}

void Component::writeBinary(std::ostream &out) const {
    out.write((char*)&m_ex, sizeof(double));
    out.write((char*)&m_ey, sizeof(double));
    out.write((char*)&m_r, sizeof(double));
    out.write((char*)&m_w, sizeof(double));
    out.write((char*)&m_h, sizeof(double));
    std::string s = m_text.toStdString();
    out << s << '\n';
}

void Component::readBinary(std::istream &out) {
    out.read((char*)&m_ex, sizeof(double));
    out.read((char*)&m_ey, sizeof(double));
    out.read((char*)&m_r, sizeof(double));
    out.read((char*)&m_w, sizeof(double));
    out.read((char*)&m_h, sizeof(double));
    std::string s;
    getline(out, s);
    m_text = QString::fromStdString(s);
}
