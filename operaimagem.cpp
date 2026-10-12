#include "CImg.h"
#include <iostream>
#include <vector>
#include <filesystem>
#include <cstring>
using namespace cimg_library;
using namespace std;


int tamanhoFoto(const char* imagem){
    return std:: filesystem :: file_size(imagem);
}

CImg<unsigned char> inverteVertical(const CImg<unsigned char>& imagem){
    int altura  = imagem.height();
    int largura = imagem.width();
    int quantidadeCores  = imagem.spectrum();

    CImg<unsigned char> imagemDeSaida(largura, altura, 1, quantidadeCores);

    for(int c = 0; c < quantidadeCores; c++){
        for(int y = 0; y < altura; y++){
            memcpy(imagemDeSaida.data(0, y, 0, c), imagem.data(0, altura - 1 - y, 0, c), largura);
        }
    }
    return imagemDeSaida;
}

CImg<unsigned char> inverteHorizontal(const CImg<unsigned char>& imagem){
    int altura  = imagem.height();
    int largura = imagem.width();
    int quantidadeCores  = imagem.spectrum();

    CImg<unsigned char> imagemDeSaida(largura, altura, 1, quantidadeCores);

    for(int c = 0; c < quantidadeCores; c++){
        for(int y = 0; y < altura; y++){
            for(int x = 0; x < largura; x++){
                imagemDeSaida(x,y,0,c) = imagem(largura-1-x,y,0,c);
            }
        }
    }
    
    return imagemDeSaida;
}

CImg <unsigned char> convertePretoBranco(const CImg <unsigned char>& imagem){
    int altura  = imagem.height();
    int largura = imagem.width();
    int quantidadeCores  = imagem.spectrum();
    
    CImg<unsigned char> imagemDeSaida(largura, altura, 1, quantidadeCores);

    for(int x = 0; x < largura; x++){
        for(int y = 0; y < altura; y++){
            int li = imagem(x,y,0,0)*0.299 + imagem(x,y,0,1)*0.587 + imagem(x,y,0,2)*0.114;
            imagemDeSaida(x,y,0,0) = imagemDeSaida(x,y,0,1) = imagemDeSaida(x,y,0,2) = li;           
        }
    }
    return imagemDeSaida;
}
CImg<unsigned char> quantizaImagem(const CImg<unsigned char>& imagem, int n){
    int altura  = imagem.height();
    int largura = imagem.width();
    int quantidadeCores  = imagem.spectrum();
    
    CImg<unsigned char> imagemDeSaida(largura, altura, 1, 1);
    
    float t_alto = 0;
    float t_baixo = 255;
    float tam_int = 0;

    for(int x = 0; x < largura; x++){
        for(int y = 0; y < altura; y++){
            if(imagem(x,y,0,0)>t_alto){
                t_alto = imagem(x,y,0,0);
            }
            if(imagem(x,y,0,0)<t_baixo){
                t_baixo = imagem(x,y,0,0);
            }
        }
    }
    tam_int = t_alto - t_baixo + 1;
    if(n >= tam_int){
        return imagem;
    }

    std::vector<int> tom(n, 0);
    int centroInt = 0;
    float intervalo = tam_int / n;
    float intervaloMenor = 0;
    float centro;
    for(int i = 0; i < n; i++){
        intervaloMenor = t_baixo - 0.5f + intervalo * i;   
        centro = intervaloMenor + intervalo / 2.0f;
        centroInt = (int)(centro + 0.5f);
        tom[i] = centroInt;
    }

    int posicao = 0;
    for(int x = 0; x < largura; x++){
        for(int y = 0; y < altura; y++){
            posicao = (int)((imagem(x,y,0,0) - t_baixo - 0.5f) / intervalo);
            if (posicao >= n) posicao = n - 1;   
            if (posicao < 0) posicao = 0;         
            imagemDeSaida(x,y,0,0) = tom[posicao];
        }
    }

    return imagemDeSaida;   
}