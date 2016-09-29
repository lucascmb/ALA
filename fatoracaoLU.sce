//Eliminação Gaussiana:
//Implementação destinada à resolução de um sistema linear Ax=b.
//Entrada: A (matriz mxn), b (vetor mx1)

clear //limpa a memoria do scilab
clc //limpa a tela do console

//A = [1 0 -1; 0 3 7; 5 -2 1]; //linhas espaçadas por ponto e vírgula
//A = [0 0 -2; 2 4 -10; 2 5 1];
//A = [0 3 1; 2 -2 1; 1 5 5/2];
A = [2, 5, 8 ; 5 11/2 6 ; 0 1 5/7]
U = [];

//A = input('Entre com a matriz A')
//b = input('Entre com o vetor b')



[m,n] = size(A); //m -> nº linhas; n -> nº colunas
L = zeros(m,n);
E = eye(m,n);
saveA = A;

lnn = m; //numero de linhas não nulas

for p = 1:lnn
    //localizar o próximo pivo
    linhap = m
    colunap = n
    for r = p:lnn
        c=1
        while (c <= n) & (A(r,c) == 0)
            c = c + 1
        end
        //verificando se r é linha nula (trocar linha r por linha lnn em A e em b)
        if c == n+1 then
            for q = 1:n
                aux = A(r,q)
                A(r,q) = A(lnn,q)
                A(lnn,q) = aux
                auxLower = L(r,q)
                L(r,q) = L(lnn,q)
                L(lnn,q) = auxLower
                auxE = E(r,q)
                E(r,q) = E(lnn,q)
                E(lnn,q) = auxE
            end
            lnn = lnn - 1
        end
        //atualizando caso o candidato a pivô da linha r seja o mais à esquerda
        if c < colunap then
            colunap = c
            linhap = r
        end
    end
    //trocar linha "p" com linha "linhap"
    if p ~= linhap then
        for r = 1:n
            aux = A(p,r)
            A(p,r) = A(linhap,r)
            A(linhap,r) = aux
            auxLower = L(p,r)
            L(p,r) = L(linhap,r)
            L(linhap,r) = auxLower
            auxE = E(p,r)
            E(p,r) = E(linhap,r)
            E(linhap,r) = auxE
        end
    end
    pivo = A(p,colunap)
    L(p,p) = pivo
    //dividir a linha do pivo pelo valor do pivo (transformar pivo em 1)
    for q = colunap:n
        if pivo ~= 0 then
            A(p,q) = A(p,q)/pivo
        end
    end
    //zerando os elementos abaixo do pivô (linhas p+1 até lnn)
    for r = (p+1):lnn
        mult = A(r,colunap)
        L(r, colunap) = A(r,colunap)
        for q = colunap:n
            A(r,q) = A(r,q) - mult*A(p,q)
        end
    end
end

U = A;

matrizLU = L * U;
Final = E * saveA;

disp('Matriz L: ')
disp([L])
disp('Matriz U: ')
disp([U])
disp('MATRIZ LU: ')
disp([matrizLU])
disp('P * A: ')
disp([Final])
