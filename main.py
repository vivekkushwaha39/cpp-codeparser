#!/usr/bin/python
from modules import MainParser
import argparse
def parseArg():
    parser = argparse.ArgumentParser(description="Enter file name to parse")
    parser.add_argument('--infile', help='File name to parse', required=True)
    args = parser.parse_args()
    return args

if __name__ == '__main__':
    args = parseArg()
    print("Program started ")
    objMainParser = MainParser.FileParser(args.infile)
    objMainParser.parseFile()
    objMainParser.generateTokenLists()
    res = objMainParser.getEntities()
    print(res)
