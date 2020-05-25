#ifndef _ITOKE_PROCESSOR_H_
#define _ITOKE_PROCESSOR_H_
#include <clang-c/Index.h>
#include "ProcessorData.h"
class ITokenProcessor
{
    public:
        virtual ProcessorData process(CXCursor &node){ return ProcessorData("default"); }
};

#endif

