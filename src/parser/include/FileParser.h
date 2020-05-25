#ifndef _FILE_PARSER_H_
#define _FILE_PARSER_H_
#include <clang-c/Index.h>
#include <string>
#include <map>
#include "ITokenProcessor.h"
namespace parser
{

enum ParserStat
{
    NO_INIT = 1,
    TU_GENERATED,
    INDEX_GENERATED
    
};
class FileParser
{
    protected:
        ParserStat state;
        std::string fileName;
        CXIndex index;
        CXTranslationUnit tu;
        void setState(ParserStat );
        void initProcessors();
        void destroyProcessors();
        std::map<CXCursorKind, ITokenProcessor *> processorList;
    public:
        bool parseFile(std::string );
        ParserStat getState();
        virtual ~FileParser();
        void genTokens();
        ITokenProcessor * getProcessor(CXCursorKind);

};

} // END parser namespace
#endif