# EP2_NasAlturas

Relatório :

1) Descrição das estruturas : 

⭐Eu utilizei o template fornecido pelo professor, mas no caso fiz uma alteração na arvore AVL pois achei mais facil de entender.

As estruturas criadas foram :

-- bstCalculaAltura ➡️ que recebe a raiz para calcular e retornar a altura da BST.
-- alturaDaAvl ➡️ tambem recebe a raiz e retorna a altura da AVL.
-- rotacaoDireita ➡️ utilizada para fazer a rotação quando necessario para a direita.
-- geraNumerosAleatorios ➡️ gera números aleatórios que não se repetem para preencher a arvore.

2) Geração dos elementos das árvores : 

Criando uma variavel "igual" definada com 0 só que ao passar por um laço for que verifica se "numerosAleatorios[j] == numerosAleatorios[i]" caso dar verdadeiro então "igual" passa a ser 1 com isso não somando i(i++) e mantendo o do while.
 
3) Interpretação :

Eu percebi que com poucos nós as amostras ficam com uma média bem proxima, mas ao inserir uma quantidade maior de nós se percebe uma diferença grande entre as médias da BST e da AVL.

