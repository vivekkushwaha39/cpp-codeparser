#include "logging.h"
#include "FileParser.h"
#include "string_wrapper.h"
#include "FunctionProcessor.h"
using namespace std;

bool parser::FileParser::parseFile(string fileName)
{
    bool ret = false;
    do
    {
        this->index = clang_createIndex(0, 0);
        if ( this->index == nullptr )
        {
            logd("Index is null");
            break;
        }
        this->tu = clang_parseTranslationUnit(index, CSTR(fileName),
            nullptr, 0, nullptr, 0, CXTranslationUnit_None);
        if ( this->tu == nullptr )
        {
            logd("Tu is nnull");
            break;
        }
        initProcessors();
        ret = true;
    }while(false);
    return ret;
}

parser::ParserStat parser::FileParser::getState()
{
    return state;
}
void parser::FileParser::setState(parser::ParserStat st)
{
    state = st;
}
parser::FileParser::~FileParser()
{
    destroyProcessors();
    clang_disposeTranslationUnit(this->tu);
    clang_disposeIndex(this->index);
}

void parser::FileParser::initProcessors()
{
    processorList[CXCursorKind::CXCursor_FunctionDecl] = new FunctionProcessor();
    processorList[CXCursorKind::CXCursor_CXXMethod] = new FunctionProcessor();
}

ITokenProcessor * parser::FileParser::getProcessor(CXCursorKind kind)
{
    ITokenProcessor * ret = nullptr;
    if ( 1 == processorList.count(kind) )
    {
        ret = processorList[kind];
    }
    return ret;
}

void parser::FileParser::destroyProcessors()
{
    logd("Destroying the processors\n");
    for ( map<CXCursorKind, ITokenProcessor*>::iterator it = processorList.begin();
        it != processorList.end(); it++ )
    {
        delete it->second;
    }
}

void parser::FileParser::genTokens()
{
    CXCursor cursor = clang_getTranslationUnitCursor(this->tu);
    clang_visitChildren(
        cursor,
        [](CXCursor c, CXCursor parent, CXClientData client_data)
        {
            logd("Tu is %s", clang_getCString(clang_getCursorSpelling(c)));
            FileParser* self = reinterpret_cast<FileParser*>(client_data);
            ITokenProcessor *pro = nullptr;
            ProcessorData res("default");
            pro = self->getProcessor(clang_getCursorKind(c) );
            if ( pro != nullptr )
            {
                res = pro->process(c);
            }
            if ( res.getResult() == ProcessorResult::PARTIALLY_PROCESSED )
            {
                return CXChildVisit_Recurse;
            }
            else
            {
                logd("breaking no need to parser rec");
                return CXChildVisit_Continue;
            }
        },
        this);

    logd("END of gettoken");
}

