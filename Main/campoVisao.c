//sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - (2*fase.chave.coordenadas.x + 2.5*fase.chave.textura.width)/2, 2)
                //+ pow((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - (2*fase.chave.coordenadas.y + 2.5*fase.chave.textura.height)/2, 2));
                float distCampoVisaoBateria1 = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - fase.chave.coordenadas.x, 2) +
                pow(((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - fase.chave.coordenadas.y), 2));
                float distCampoVisaoBateria2 = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - fase.chave.coordenadas.x + 2.5*fase.chave.textura.width, 2) +
                pow(((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - fase.chave.coordenadas.y + 2.5*fase.chave.textura.height), 2));
