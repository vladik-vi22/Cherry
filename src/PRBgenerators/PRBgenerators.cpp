#include "PRBgenerators.h"

PRBgenerators::PRBgenerators(QObject* parent): QObject(parent)
{
    m_generatedByBuiltInCPP = 0;
}

PRBgenerators::~PRBgenerators()
{
}

void PRBgenerators::generateBuiltInCPP(const uint32_t& numberOfBit)
{
    std::vector<uint16_t> bigNumberStdVectorUint16_t;
    srand(time(NULL));
    for(uint32_t indexBigNumberStdVectorUint16_t = 0; indexBigNumberStdVectorUint16_t < numberOfBit / 16 + (numberOfBit % 16 == 0 ? 0 : 1); ++indexBigNumberStdVectorUint16_t)
    {
        bigNumberStdVectorUint16_t.push_back(rand());
    }
    m_generatedByBuiltInCPP = bigNumberStdVectorUint16_t;
}
