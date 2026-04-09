#include "Transform.h"
#include <cmath>

// Aplica as transformações (escala, rotação e translação)
// a um ponto (x, y, z).
// Os parâmetros são passados por referência para que o valor original
// seja modificado diretamente.
void Transform::apply(double& x, double& y, double& z) const {
    // Multiplica cada eixo pelo fator de escala correspondente.
    // Isso aumenta ou diminui o tamanho do objeto.
    x *= scale.x;
    y *= scale.y;
    z *= scale.z;

    // As rotações são aplicadas na ordem: X -> Y -> Z.
    // Cada rotação usa matrizes de rotação clássicas.
    
    // Rotação em torno do eixo X. Afeta os eixos Y e Z
    double y1 = y * cos(rotation.x) - z * sin(rotation.x);
    double z1 = y * sin(rotation.x) + z * cos(rotation.x);
    y = y1; 
    z = z1;

    // Rotação em torno do eixo Y. Afeta os eixos X e Z
    double x1 = x * cos(rotation.y) + z * sin(rotation.y);
    z1 = -x * sin(rotation.y) + z * cos(rotation.y);
    x = x1; 
    z = z1;
    
    // Rotação em torno do eixo Z. Afeta os eixos X e Y
    x1 = x * cos(rotation.z) - y * sin(rotation.z);
    y1 = x * sin(rotation.z) + y * cos(rotation.z);
    x = x1; 
    y = y1;

    // Move o ponto no espaço somando a posição do objeto.
    x += position.x;
    y += position.y;
    z += position.z;
}

