#include <QFile>
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QtGlobal>
#include <QStandardItem>
#include <QDebug>
#include "qcsvmodel.h"

QCSVModel::QCSVModel(QObject *parent) : QStandardItemModel(parent)
{
    m_object = 0;
    m_firstColNames = false;
    m_separator = ';';
    m_lineNumber = -1;
}

QCSVModel::~QCSVModel()
{
}

bool QCSVModel::parse()
{
    QFile file(filename());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    for ( m_lineNumber = 1 ; !file.atEnd() ; m_lineNumber++ ) {
        QByteArray line = file.readLine();
        if (!processLine(line))
            return false;
    }
    return true;
}

void QCSVModel::setFilename(const QString &filename)
{
    m_filename = filename;
}

bool QCSVModel::processLine(const QString &line)
{
    Q_ASSERT(object());
    if (line.isEmpty())
        return false;

    const QMetaObject *meta = object()->metaObject();
    Q_ASSERT(meta);
#ifndef WRITEABLE_OBJECT
    QObject *obj = meta->newInstance(this);
    m_objects.push_back(newObject);
#else
    QObject *obj = object();
#endif
    QStringList lst = line.split( separator() );
    if (lst.size() != m_properties.size()) {
        emit error(QString("Error: wrong number of columns at line %1").arg(m_lineNumber));
        return false;
    }
    int row = m_lineNumber - 1;
    if (m_firstColNames)
        row--;

    for ( int i = 0 ; i < lst.size() ; i++ ) {
        int propNumber = m_properties[i];
        QVariant var(lst.at(i));
        QMetaProperty property = meta->property( propNumber );
        if (!var.canConvert(property.type()))
        {
            emit error(QString("Error: wrong field format at line %1 column %2").arg(m_lineNumber).arg(i+1));
            return false;
        };
        var.convert(property.type());
        qDebug() << property.typeName() << " " << property.name() << " = " << var.typeName();
        if (!property.write(obj, var)) {
            emit error(QString("Error: wrong field format at line %1 column %2").arg(m_lineNumber).arg(i+1));
            return false;
        }
        QStandardItem *item = new QStandardItem(lst.at(i));
        setItem(row, i, item);
    }
    return true;
}

void QCSVModel::setProperties(const QVector<int> &properties)
{
    Q_ASSERT(object());
    m_properties = properties;

    const QMetaObject *meta = object()->metaObject();
    Q_ASSERT(meta);

    QStringList labels;
    for (int i: m_properties)
        labels.push_back(meta->property(i).name());

    setHorizontalHeaderLabels(labels);
}


QObject *QCSVModel::object() const
{
    return m_object;
}

void QCSVModel::setDefaultPropertiesOrder()
{
    Q_ASSERT(object());
    // by default, there is direct order of properties in line, property "name" excluded
    const QMetaObject *meta = object()->metaObject();

    Q_ASSERT(meta);
    QVector<int> properties(meta->propertyCount() - 1);
    for ( int i = 0 ; i < properties.size() ; i++ )
        properties[i] = i + 1;

    setProperties(properties);
}
QChar QCSVModel::separator() const
{
    return m_separator;
}

void QCSVModel::setSeparator(QChar separator)
{
    m_separator = separator;
}


void QCSVModel::setObject(QObject *object)
{
    Q_ASSERT(object);
    m_object = object;
    setDefaultPropertiesOrder();
}


QString QCSVModel::filename() const
{
    return m_filename;
}

bool QCSVModel::firstColNames() const
{
    return m_firstColNames;
}

void QCSVModel::setFirstColNames(bool value)
{
    m_firstColNames = value;
}
