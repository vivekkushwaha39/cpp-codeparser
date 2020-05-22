
class BaseProcessor:
    PROCESSED = 1
    PARTIALLY_PROCESSED = 2
    
    @classmethod
    def process(cls, node):
        return ( cls.PROCESSED, [])