[![Best](https://img.shields.io/badge/The%20best%20TRANSLATOR-GO-blue)](https://github.com/VasilevMaxim/TranslatorGo)
![C++](https://img.shields.io/badge/Code%20-C++-blue)
[![C#](https://img.shields.io/badge/Code%20Style-C%23-blueviolet)](https://docs.microsoft.com/en-us/dotnet/standard/design-guidelines/index?redirectedfrom=MSDN)

# Translator from Go to Assembler language.   


![Translator](https://sun9-37.userapi.com/c858032/v858032731/1890f7/F0RMRY0Npr4.jpg "GO")
Consists of 4 main stages.     

:arrow_forward: Token splitting. (Lexer)   
:arrow_forward: Tree building. (Parser)    
:arrow_forward: Semantic analyzer. (Ast)   
:arrow_forward: Code generation in Assembler. (Asm)   
      
The new parsing system is based on the recursion process. It is more acceptable, because it allows you to split the entire syntax into separate components, component parts.    

In order to translate the code, specify the path to the file in the main function.

## Already done.
:white_check_mark: Lexer    
:white_check_mark: Parser    
:white_check_mark: Semantic analyzer   
:white_check_mark: Code generation in Assembler   

Based on an article from Habr: https://habr.com/en/post/133780/     
Thanks so much for helping Peter, I582: https://github.com/i582
