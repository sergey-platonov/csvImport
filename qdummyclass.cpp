#include "qdummyclass.h"

QDummyClass::QDummyClass(QObject *parent) : QObject(parent)
{

}

QDummyClass::~QDummyClass()
{

}

QString QDummyClass::field() const
{
    return m_field;
}

void QDummyClass::setField(QString arg)
{
    m_field = arg;
}

