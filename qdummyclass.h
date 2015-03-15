#ifndef QDUMMYCLASS_H
#define QDUMMYCLASS_H

#include <QObject>

class QDummyClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString field READ field WRITE setField)
    QString m_field;

public:
    explicit QDummyClass(QObject *parent = 0);
    ~QDummyClass();

QString field() const;

signals:

public slots:
void setField(QString arg);
};

#endif // QDUMMYCLASS_H
