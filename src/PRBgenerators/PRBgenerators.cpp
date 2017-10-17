#include "PRBgenerators.h"

PRBgenerators::PRBgenerators(QObject* parent): QObject(parent)
{
}

PRBgenerators::~PRBgenerators()
{
}

QBitArray PRBgenerators::getNumberBitArr() const
{
    return m_number_bit_arr;
}

QByteArray PRBgenerators::getNumberByteArr() const
{
    return m_number_byte_arr;
}

QString PRBgenerators::getNumberStr() const
{
    return m_number_str;
}

QList<qint16> PRBgenerators::getNumberListInt() const
{
    return m_number_list_int;
}

void PRBgenerators::setNumberBitArr(const QBitArray &new_number_bit_arr)
{
    if(m_number_bit_arr != new_number_bit_arr)
    {
        m_number_bit_arr = new_number_bit_arr;
        emit numberBitArrChanged();
    }
}

void PRBgenerators::setNumberByteArr(const QByteArray &new_number_byte_arr)
{
    if(m_number_byte_arr != new_number_byte_arr)
    {
        m_number_byte_arr = new_number_byte_arr;
        emit numberByteArrChanged();
    }
}

void PRBgenerators::setNumberStr(const QString &new_number_str)
{
    if(m_number_str != new_number_str)
    {
        m_number_str = new_number_str;
        emit numberStrChanged();
    }
}

void PRBgenerators::setNumberListInt(const QList<qint16> &new_number_list_int)
{
    if(m_number_list_int != new_number_list_int)
    {
        m_number_list_int = new_number_list_int;
        emit numberListIntChanged();
    }
}
