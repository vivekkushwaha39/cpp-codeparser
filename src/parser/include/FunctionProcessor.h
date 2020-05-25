#ifndef _FUNCTION_PROCESSOR_H_
#define _FUNCTION_PROCESSOR_H_

#include "ITokenProcessor.h"
class FunctionProcessor: public ITokenProcessor
{
    virtual ProcessorData process(CXCursor& );
};

#endif