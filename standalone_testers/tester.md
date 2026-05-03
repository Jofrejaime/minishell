# Standalone Testers

Aqui nos colocamos os nossos testes individuias, neste diretorio, o que permite que sejam testados de forma isolada, sem a necessidade de rodar o projeto inteiro.

ex: tester para o lexer, para o parser, etc.

isso permite analizar o comportamento de cada componente do projeto, e identificar possíveis erros ou melhorias de forma mais rápida e eficiente.

faz isso mano Lucio: 

Cria um pasta neste diretorio chamada "lexer_tester", e dentro dela cria um arquivo chamado "test_lexer.c", main para o teste de lexer. este directorio não deve conter arquivos relacionados a outros componentes do projeto, apenas o teste do lexer, e parser, execve antes de serem compilados.

para teste, deve se criar o binario dentro da pasta standalone_testers, e rodar o teste a partir do terminal, para garantir que o teste seja executado de forma isolada, sem interferencia de outros componentes do projeto.

colocar o comando no header do arquivo de teste(o arquivo ".c"), para facilitar a execução do teste, e garantir que o teste seja executado de forma correta.

apenas um aquivo de teste por componente, para evitar confusão e garantir que o teste seja executado de forma correta.