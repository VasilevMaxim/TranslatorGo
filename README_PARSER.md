
[![LEXER](https://img.shields.io/badge/<<%20LEXER-9cf)](https://github.com/VasilevMaxim/TranslatorGo)
[![AST](https://img.shields.io/badge/AST%20>>-9cf)](https://github.com/VasilevMaxim/TranslatorGo)  


[![Best](https://img.shields.io/badge/The%20best%20TRANSLATOR-GO-blue)](https://github.com/VasilevMaxim/TranslatorGo)
![C++](https://img.shields.io/badge/Code%20-C++-blue)
[![C#](https://img.shields.io/badge/Code%20Style-C%23-blueviolet)](https://docs.microsoft.com/en-us/dotnet/standard/design-guidelines/index?redirectedfrom=MSDN)

# Translator from Go to Assembler language.   


![Translator](https://sun9-37.userapi.com/c858032/v858032731/1890f7/F0RMRY0Npr4.jpg "GO")


## Парсер? Вы что с ума сошли? Зачем все так сложно?

Парсер — это одна из важнейших частей транслятора / компилятора. Он отвечает за то, чтобы построить дерево Ast, по готовым токенам из лексера. И в случаи, если этого сделать не получится, то необходимо вывести ошибку почему это не получается.

### Ошибки

Если Вы собрались самостоятельно писать транслятор, настоятельно рекомендую создать свою оболочку для вывода ошибок. Например, в коде, написанном мною, система ошибок построена следующим образом: парсер понимает, что в дереве ошибка -> создает объект класса Error или производную от него -> передает номер ошибки в конструктор класса -> по номеру из файла достается информация о том, какую ошибку допустил пользователь - программист языка. Таким образом мы можем более детально разбить каждую ошибку, обработать её, написать способы по её исправлению и более того, с легкостью по номерам ошибок написать, к примеру, в документации на сайте возможные способы по её исправлению.



У меня не было цели обработать все возможные ошибки, или написать все возможные языковые комбинации, или некоторые конструкции. Самое важное было - понять принцип работы. 

## Уже готово:
:white_check_mark: expr       
:white_check_mark: function       
:white_check_mark: function (args)      
:white_check_mark: func (args arrays)        
:white_check_mark: func return   
:white_check_mark: if   
:white_check_mark: else   
:white_check_mark: else if    
:white_check_mark: for (multi)    
:white_check_mark: error in tree    
:white_check_mark: comments       
:white_check_mark: comparisons operator  

:white_check_mark: var (multi)         
:white_check_mark: var (,)     

:white_check_mark: array    
:white_check_mark: array(expr)     
:white_check_mark: accessing a element array     
       
:white_check_mark: editing code building tree 

:white_check_mark: function call   

## Нужно сделать:
   
:black_square_button: editing code in classes          

 
____

Based on an article from Habr: https://habr.com/en/post/133780/     
Thanks so much for helping Peter, I582: https://github.com/i582      
    
[![ENG](https://img.shields.io/badge/ENG%20>>-9cf)](https://github.com/VasilevMaxim/TranslatorGo)
