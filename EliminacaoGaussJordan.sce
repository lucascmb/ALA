//Eliminação Gaussiana:
//Implementação destinada à resolução de um sistema linear Ax=b.
//Entrada: A (matriz mxn), b (vetor mx1)

clear //limpa a memoria do scilab
clc //limpa a tela do console

//A = [1 0 -1; 0 3 7; 5 -2 1]; //linhas espaçadas por ponto e vírgula
b = [0;7;6];                 //e colunas separadas por espaços ou vírgulas
//A = [0 0 -2; 2 4 -10; 2 5 1];
A = [0 3 1; 2 -2 1; 1 5 5/2];

//A = input('Entre com a matriz A')
//b = input('Entre com o vetor b')



[m,n] = size(A); //m -> nº linhas; n -> nº colunas

lnn = m; //numero de linhas não nulas

for p = 1:lnn
    //localizar o próximo pivo
    disp([A])
    linhap = m
    colunap = n
    for r = p:lnn
        c=1
        while (c <= n) & (A(r,c) == 0)
            c = c + 1
        end
        
        //verificando se r é linha nula (trocar linha r por linha lnn em A e em b)
        if c == n+1 then
            if b(r) ~= 0 then
                error('Sistema Impossível!')
            end
            
        
            
            for q = 1:n
                aux = A(r,q)
                A(r,q) = A(lnn,q)
                A(lnn,q) = aux
            end
            aux = b(r)
            b(r) = b(lnn)
            b(lnn) = aux
            lnn = lnn - 1
        end
        //atualizando caso o candidato a pivô da linha r seja o mais à esquerda
        if c < colunap then
            colunap = c
            linhap = r
        end
    end
    disp([b])
    //trocar linha "p" com linha "linhap"
    if p ~= linhap then
        for r = 1:n
            aux = A(p,r)
            A(p,r) = A(linhap,r)
            A(linhap,r) = aux
        end
        aux = b(p)
        b(p) = b(linhap)
        b(linhap) = aux
    end
    pivo = A(p,colunap)
        disp([b])
    //dividir a linha do pivo pelo valor do pivo (transformar pivo em 1)
    for q = colunap:n
        A(p,q) = A(p,q)/pivo
    end
    b(p) = b(p)/pivo
        disp([b])
    //zerando os elementos abaixo do pivô (linhas p+1 até lnn)
    for r = (p+1):lnn
        mult = A(r,colunap)
        for q = colunap:n
            A(r,q) = A(r,q) - mult*A(p,q)
        end
        b(r) = b(r) - mult*b(p)
    end
        disp([b])
    //zerando os elementos acima do pivô (linhas 1 até p-1)
    if p > 1 then
        for r = 1:(p-1)
            mult = A(r,colunap)
            for q = colunap:n
                A(r,q) = A(r,q) - mult*A(p,q)
            end
            b(r) = b(r) - mult*b(p)
        end
    end
        disp([b])
    
    //disp([b])
end


//disp('Matriz Final Aumentada: ')
//disp([A b])



