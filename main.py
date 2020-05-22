from modules import MainParser
if __name__ == '__main__':
    print ("Program started ")
    objMainParser = MainParser.FileParser("example/main.cpp")
    objMainParser.parseFile()
    objMainParser.generateTokenLists()