//Eliminação Gaussiana:
//Implementação destinada à resolução de um sistema linear Ax=b.
//Entrada: A (matriz mxn), b (vetor mx1)

clear //limpa a memoria do scilab
clc //limpa a tela do console

//A = [1 0 -1; 0 3 7; 5 -2 1]; //linhas espaçadas por ponto e vírgula
A = [0 0 -2; 2 4 -10; 2 5 1];
//A = [0 3 1; 2 -2 1; 1 5 5/2];
//A = [2, 5, 8 ; 5 11/2 6 ; 0 1 5/7]

//A = input('Entre com a matriz A')
//b = input('Entre com o vetor b')



[m,n] = size(A); //m -> nº linhas; n -> nº colunas
I = zeros(m,n);

//transforma matriz de zeros em identidade
for p = 1:m
    for j = 1:n
        if p == j
            I(p,j) = 1;
        end   
    end
end

if det(A) == 0 then
    error('Não há inversa')
end

mPivo = I;
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
                //troco as linhas da inversa
                auxInversa = I(r,q)
                I(r,q) = I(lnn,q)
                I(lnn,q) = auxInversa
                //troca as linhas da pivo
                auxPivo = mPivo(r,q)
                mPivo(r,q) = mPivo(lnn,q)
                mPivo(lnn,q) = auxPivo
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
            //troco as linhas da inversa
            auxInversa = I(p,r)
            I(p,r) = I(linhap,r)
            I(linhap,r) = auxInversa
            //troca as linhas da pivo
            auxPivo = mPivo(p,r)
            mPivo(p,r) = mPivo(linhap,r)
            mPivo(linhap,r) = auxPivo
        end
    end
    pivo = A(p,colunap)
    //dividir a linha do pivo pelo valor do pivo (transformar pivo em 1)
    for q = colunap:n
        A(p,q) = A(p,q)/pivo
    end
    for w = 1:n
         I(p,w) = I(p,w)/pivo
    end
    //zerando os elementos abaixo do pivô (linhas p+1 até lnn)
    for r = (p+1):lnn
        mult = A(r,colunap)
        for q = colunap:n
            A(r,q) = A(r,q) - mult*A(p,q)
        end
        for w = 1:n
            I(r,w) = I(r,w) - mult*I(p,w)
        end
    end
    //zerando os elementos acima do pivô (linhas 1 até p-1)
    if p > 1 then
        for r = 1:(p-1)
            mult = A(r,colunap)
            for q = colunap:n
                A(r,q) = A(r,q) - mult*A(p,q)
            end
            for w = 1:n
                I(r,w) = I(r,w) - mult*I(p,w)
            end
        end
    end
end

Final = I * saveA;


disp('Matriz Inversa: ')
disp([I])
disp([Final])
//disp([mPivo])



