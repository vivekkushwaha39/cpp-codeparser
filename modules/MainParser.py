import sys
import clang.cindex
from modules.processors.functionProcessor import FunctionProcessor
from modules.processors.baseProcessor import BaseProcessor
class FileParser:
    functionList = []
    processors = {}

    def __init__(self, _fileName):
        self.fileName = _fileName
        self.initProcessors()

    def initProcessors(self):
        self.processors[clang.cindex.CursorKind.FUNCTION_DECL] = FunctionProcessor
        self.processors[clang.cindex.CursorKind.CXX_METHOD] = FunctionProcessor
    
    def parseFile(self):
        if (self.fileName is None):
            return -1
        self.fileIndex = clang.cindex.Index.create()
        self.tu = self.fileIndex.parse(self.fileName)
        print("Translation Unit is ", self.tu.spelling)

    def generateTokenLists(self):
        cursor = self.tu.cursor
        self.recParse(cursor)

    def recParse(self, node: clang.cindex.Cursor):
        currProccessor = self.getProcessor(node.kind)
        processState = BaseProcessor.PARTIALLY_PROCESSED
        if currProccessor is not None:
            print('Processors registered for ', node.kind)     
            processState, data = currProccessor.process(node)
            self.functionList.append(data)

        if processState is not BaseProcessor.PROCESSED:
            for i in node.get_children():
                self.recParse(i)

    def getEntities(self):
        return self.functionList

    def getProcessor(self, processorName):
        if processorName in self.processors:
            return self.processors[processorName]
        else:
            return None
