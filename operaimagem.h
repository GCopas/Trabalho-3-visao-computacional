#pragma once 
#include "CImg.h"
#include <iostream>
#include <vector>
#include <filesystem>
using namespace cimg_library;
using namespace std;


int tamanhoFoto(const char* imagem);

CImg<unsigned char> inverteVertical(const CImg<unsigned char>& imagem);

CImg<unsigned char> inverteHorizontal(const CImg<unsigned char>& imagem);

CImg <unsigned char> convertePretoBranco(const CImg <unsigned char>& imagem);

CImg<unsigned char> quantizaImagem(const CImg<unsigned char>& imagem, int n);