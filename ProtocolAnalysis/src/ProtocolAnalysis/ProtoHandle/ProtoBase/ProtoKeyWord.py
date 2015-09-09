#-*- encoding=utf-8 -*-


# Proto 的关键字
class ProtoKeyWord(object):
    ePackage = "package"
    eMessage = "message"
    eEnum = "enum"
    eHeader = "header"
    eImport = "import"
    eSingleLineComment = "//"
    eMulLineCommentStart = "/**"
    eMulLineCommentEnd = "*/"
    
    #eOptional = "optional"
    #eRepeated = "repeated"
    
    eLeftBrace = "{"
    eRightBrace = "}"
    eSemicolon = ";"
    eRightBraceSemicolon = "};"
    eBase = "base"      # 说明是基类中的成员
    
    eUint32 = "uint32"
    eChar = "char"
    
    
    # 关键字分隔符
    sKeyWordDelimiter = ["package", "message", "enum", "header", "import"]
    

