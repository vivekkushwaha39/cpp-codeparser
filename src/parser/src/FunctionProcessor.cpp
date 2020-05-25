#include "FunctionProcessor.h"
#include "logging.h"
ProcessorData FunctionProcessor::process(CXCursor  &node)
{
    ProcessorData res("Default data");
    res.setResult(ProcessorResult::PROCESSED);
    return res;
}