#ifndef _PROCESSOR_DATA_H_
#define _PROCESSOR_DATA_H_
#include <string>
#include <map>
#include <any>
enum ProcessorResult
{
    PROCESSED = 1,
    PARTIALLY_PROCESSED
};

class ProcessorData
{
private:
    ProcessorResult result;
    std::string resultType;
    int row,col;
    std::map<std::string, void*> props;
public:
    ProcessorData(std::string);
    ProcessorResult getResult();
    void setResult(ProcessorResult );
};

#endif
