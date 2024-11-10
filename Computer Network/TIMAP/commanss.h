#ifndef COMMANSS_H
#define COMMANSS_H
#include <QObject>
#include <QString>
using namespace std;
class commanss : public QObject
{
    Q_OBJECT
public:
    explicit commanss(QObject *parent = nullptr);

signals:
};

#endif // COMMANSS_H
