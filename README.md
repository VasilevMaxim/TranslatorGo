[![Best](https://img.shields.io/badge/The%20best%20TRANSLATOR-GO-blue)](https://github.com/VasilevMaxim/TranslatorGo)
[![C#](https://img.shields.io/badge/Code%20Style-C%23-blueviolet)](https://docs.microsoft.com/en-us/dotnet/standard/design-guidelines/index?redirectedfrom=MSDN)
# Translator from Go to Assembler language.   


![Translator](https://sun9-37.userapi.com/c858032/v858032731/1890f7/F0RMRY0Npr4.jpg "GO")
Consists of 4 main stages.     

:arrow_forward: Token splitting.   
:arrow_forward: Tree building.    
:arrow_forward: Syntactic analyzer.   
:arrow_forward: Code generation in Assembler.   
      
The new parsing system is based on the recursion process. It is more acceptable, because it allows you to split the entire syntax into separate components, component parts.    

In order to translate the code, specify the path to the file in the main function.

## Already done.
:white_check_mark: expr       
:white_check_mark: func

## Need to do.

:black_square_button: if   
:black_square_button: else   
:black_square_button: else if    
:black_square_button: for (multi)    
:black_square_button: var (multi)         
:black_square_button: var (,)     
:black_square_button: error in tree    
:black_square_button: array    
:black_square_button: array(expr)     
:black_square_button: accessing a element array     
:black_square_button: comments       
:black_square_button: comparisons operator      
:black_square_button: function       
:black_square_button: function (args)      
:black_square_button: func (args arrays)       
:black_square_button: func return    
:black_square_button: editing code building tree in https://golang.org/ref/spec           
:black_square_button: editing code in classes           

Based on an article from Habr: https://habr.com/en/post/133780/     
Thanks so much for helping Peter, I582: https://github.com/i582
