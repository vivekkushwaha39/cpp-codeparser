#include <iostream>
#include <argp.h>
#include <vector>
#include <string>
#include <clang/Parse/Parser.h>
#include "FileParser.h"
#include "logging.h"
#include "string_wrapper.h"

static argp optionParser;
std::vector<argp_option> options;
void prepareArgParser();
void addOptions(const char *, int , const char *, int , const char *);
error_t parse_opt (int key, char *arg, struct argp_state *state);
struct ProgramArgs
{
    std::string fileName;
    ProgramArgs(){fileName = "";}
}pArgs;
int main(int ac, char **av)
{
    logd("Program started");
    int ret = 0;
    prepareArgParser(); 
    ret = argp_parse(&optionParser, ac, av,0, NULL, NULL);
    std::cout<<"Parsing result " << ret <<std::endl;
    if ( ret == 0 && pArgs.fileName.empty() == false )
    {
        parser::FileParser fileParser;
        if ( fileParser.parseFile(pArgs.fileName) == false )
        {
            logd("Parsing failed for %s", CSTR(pArgs.fileName));
            return -1;
        }
        logd("Parsing success");
        fileParser.genTokens();
    }
    return ret;
}

void prepareArgParser()
{
    addOptions("infile", 'i', "file name", 0, "The file which needs to be processed");
    addOptions(NULL, 0, NULL, 0, NULL);
    optionParser.options = &options[0];
    optionParser.parser = parse_opt;
}
void addOptions(const char *longName, int shortName, const char *desc, int flag, const char *doc)
{
    argp_option opt;
    opt.doc = doc;
    opt.name = longName;
    opt.key = shortName;
    opt.flags = flag;
    opt.group = 0;
    opt.arg = desc;
    options.push_back(opt);
}

error_t parse_opt (int key, char *arg, struct argp_state *state)
{
    switch ((key))
    {
    case 'i':
        std::cout<< "Got file name " << arg << std::endl;
        pArgs.fileName.assign(std::string(arg));
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}