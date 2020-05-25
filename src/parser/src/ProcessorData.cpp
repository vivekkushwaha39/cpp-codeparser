#include "ProcessorData.h"
using namespace std;
ProcessorData::ProcessorData(string type): row(-1),col(-1), resultType(type)
{
    this->result = ProcessorResult::PARTIALLY_PROCESSED;
}

ProcessorResult ProcessorData::getResult()
{
    return this->result;
}

void ProcessorData::setResult(ProcessorResult res)
{
    this->result = res;
}



