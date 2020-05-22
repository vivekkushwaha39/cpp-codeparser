import clang.cindex
from  modules.processors.baseProcessor import BaseProcessor
class FunctionProcessor(BaseProcessor):


    @classmethod
    def process(cls, node):
        data = []
        hasBody, block = cls.hasFunctionBody(node)

        if hasBody:
            data = [node.location.line, node.location.column, block]
        else:
            data = [node.location.line, node.location.column]
        return (cls.PROCESSED,data)
    
    @classmethod
    def hasFunctionBody(cls, node: clang.cindex.Cursor) -> bool:
        hasBody = False
        bodyPos = []
        for i in node.get_children():
            if i.kind == clang.cindex.CursorKind.COMPOUND_STMT:
                hasBody = True
                bodyPos = [i.location.line,i.location.column]
                break
        return (hasBody,bodyPos)
