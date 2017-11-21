#include "BigIntCalculator.h"

BigIntCalculator::BigIntCalculator(QObject* parent): QObject(parent), BigInt()
{
    m_baseInput = 10;
    m_baseOutput = 10;
}

BigIntCalculator::~BigIntCalculator()
{

}

int BigIntCalculator::getBaseInput() const
{
    return m_baseInput;
}

int BigIntCalculator::getBaseOutput() const
{
    return m_baseOutput;
}

QString BigIntCalculator::getBigNumber1() const
{
    return QString::fromStdString(m_bigNumber1.toStdString(m_baseInput));
}

QString BigIntCalculator::getBigNumber2() const
{
    return QString::fromStdString(m_bigNumber2.toStdString(m_baseInput));
}

QString BigIntCalculator::getCalculationsResult() const
{
    return QString::fromStdString(m_calculationsResult.toStdString(m_baseOutput));
}

void BigIntCalculator::setBaseInput(const int &new_baseInput)
{
    if(m_baseInput != new_baseInput)
    {
        m_baseInput = new_baseInput;
        emit baseInputChanged();
    }
}

void BigIntCalculator::setBaseOutput(const int &new_baseOutput)
{
    if(m_baseOutput != new_baseOutput)
    {
        m_baseOutput = new_baseOutput;
        emit baseOutputChanged();
    }
}

void BigIntCalculator::setBigNumber1(const QString &new_bigNumber1)
{
    if(m_bigNumber1.toStdString(m_baseInput) != new_bigNumber1.toStdString())
    {
        m_bigNumber1 = BigInt(new_bigNumber1.toStdString(), m_baseInput);
        emit bigNumber1Changed();
    }
}

void BigIntCalculator::setBigNumber2(const QString &new_bigNumber2)
{
    if(m_bigNumber2.toStdString(m_baseInput) != new_bigNumber2.toStdString())
    {
        m_bigNumber2 = BigInt(new_bigNumber2.toStdString(), m_baseInput);
        emit bigNumber2Changed();
    }
}

void BigIntCalculator::setCalculationsResult(const QString &new_calculationResult)
{
    if(m_calculationsResult.toStdString(m_baseOutput) != new_calculationResult.toStdString())
    {
        m_calculationsResult = BigInt(new_calculationResult.toStdString(), m_baseOutput);
        emit calculationsResultChanged();
    }
}

void BigIntCalculator::calculate(const QString& operation)
{
    if(operation == "+")
    {
        setCalculationsResult(QString::fromStdString((m_bigNumber1 + m_bigNumber2).toStdString(m_baseOutput)));
    }
    else if(operation == "-")
    {
        setCalculationsResult(QString::fromStdString((m_bigNumber1 - m_bigNumber2).toStdString(m_baseOutput)));
    }
    else if(operation == "*")
    {
        setCalculationsResult(QString::fromStdString((m_bigNumber1 * m_bigNumber2).toStdString(m_baseOutput)));
    }
    else if(operation == "/")
    {
        setCalculationsResult(QString::fromStdString((m_bigNumber1 / m_bigNumber2).toStdString(m_baseOutput)));
    }
    else if(operation == "%")
    {
        setCalculationsResult(QString::fromStdString((m_bigNumber1 % m_bigNumber2).toStdString(m_baseOutput)));
    }
    else if(operation == "pow")
    {
        setCalculationsResult(QString::fromStdString(pow(m_bigNumber1, m_bigNumber2).toStdString(m_baseOutput)));
    }
    else if(operation == "~")
    {
        setCalculationsResult(QString::fromStdString((~m_bigNumber1).toStdString(m_baseOutput)));
    }
    else if(operation == "&&")
    {
        setCalculationsResult(QString::fromStdString((m_bigNumber1 & m_bigNumber2).toStdString(m_baseOutput)));
    }
    else if(operation == "|")
    {
        setCalculationsResult(QString::fromStdString((m_bigNumber1 | m_bigNumber2).toStdString(m_baseOutput)));
    }
    else if(operation == "^")
    {
        setCalculationsResult(QString::fromStdString((m_bigNumber1 ^ m_bigNumber2).toStdString(m_baseOutput)));
    }
    else if(operation == "<<")
    {
        setCalculationsResult(QString::fromStdString((m_bigNumber1 << m_bigNumber2.toUint32_t()).toStdString(m_baseOutput)));
    }
    else if(operation == ">>")
    {
        setCalculationsResult(QString::fromStdString((m_bigNumber1 >> m_bigNumber2.toUint32_t()).toStdString(m_baseOutput)));
    }
    else if(operation == "gcd")
    {
        setCalculationsResult(QString::fromStdString(gcd(m_bigNumber1, m_bigNumber2).toStdString(m_baseOutput)));
    }
    else if(operation == "lcm")
    {
        setCalculationsResult(QString::fromStdString(lcm(m_bigNumber1, m_bigNumber2).toStdString(m_baseOutput)));
    }
    else
    {
        setCalculationsResult("0");
    }
}
