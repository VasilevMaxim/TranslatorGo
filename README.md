[![Best](https://img.shields.io/badge/The%20best%20TRANSLATOR-GO-blue)](https://github.com/VasilevMaxim/TranslatorGo)
[![C#](https://img.shields.io/badge/Code%20Style-C%23-blueviolet)](https://docs.microsoft.com/en-us/dotnet/standard/design-guidelines/index?redirectedfrom=MSDN)
# Translator from Go to Assembler language.   


![Translator](https://sun9-37.userapi.com/c858032/v858032731/1890f7/F0RMRY0Npr4.jpg "GO")
Consists of 4 main stages.    

:arrow_forward: Token splitting.   
:arrow_forward: Tree building.    
:arrow_forward: Syntactic analyzer.   
:arrow_forward: Code generation in Assembler.   

In order to translate the code, specify the path to the file in the main function.

## Already done.
:white_check_mark: if   
:white_check_mark: else   
:white_check_mark: else if    
:white_check_mark: for (multi)    
:white_check_mark: var (multi)         
:white_check_mark: var (,)     
:white_check_mark: error in tree    
:white_check_mark: array    
:white_check_mark: array(expr)
:white_check_mark: accessing a element array
:white_check_mark: comments    
:white_check_mark: comparisons operator    

## Need to do.
:black_square_button: function    
:black_square_button: function (args)      
:black_square_button: editing code building tree     

Based on an article from Habr: https://habr.com/en/post/133780/     
Thanks so much for helping Peter, i582: https://github.com/i582
