import sys
import clang.cindex

class FileParser:
    fileName = None
    fileIndex = None
    tu = None
    functionDefList = []
    functionDecList = []
    def __init__(self, _fileName):
        self.fileName = _fileName
    
    def parseFile(self):
        if ( self.fileName is None ):
            return -1;
        self.fileIndex = clang.cindex.Index.create()
        self.tu = self.fileIndex.parse(self.fileName)
        print ("Translation Unit is ", self.tu.spelling)
    
    def generateTokenLists(self):
        cursor = self.tu.cursor
        self.recParse(cursor)


    def recParse(self, node):
        if node.kind == clang.cindex.CursorKind.FUNCTION_DECL :
            if  self.hasFunctionBody(node) == True :
                self.functionDefList.append( [node.spelling,node.location.line, node.location.column] )
            else :
                self.functionDecList.append( [node.spelling,node.location.line, node.location.column] )
            return
        for i in node.get_children():
            self.recParse(i)

    def hasFunctionBody(self, node):
        
        hasBody = False
        for i in node.get_children() :
            if i.kind == clang.cindex.CursorKind.COMPOUND_STMT:
                hasBody = True
                break
        if hasBody == True:
            print ("Function name with body is ", node.spelling)
        else:
             print ("Function name without body is ", node.spelling)
        return hasBody