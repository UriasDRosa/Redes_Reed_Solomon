#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// Fun��o para multiplicar polin�mios
std::vector<int> multiplyPolynomials(const std::vector<int>& poly1, const std::vector<int>& poly2)
{
    int m = poly1.size();
    int n = poly2.size();
    std::vector<int> result(m + n - 1, 0);

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            result[i + j] ^= poly1[i] * poly2[j];
        }
    }

    return result;
}

// Fun��o para realizar a divis�o de polin�mios (XOR)
std::vector<int> dividePolynomials(const std::vector<int>& dividend, const std::vector<int>& divisor)
{
    std::vector<int> remainder = dividend;
    int dividendSize = dividend.size();
    int divisorSize = divisor.size();

    for (int i = 0; i <= dividendSize - divisorSize; ++i)
    {
        if (remainder[i] != 0)
        {
            for (int j = 0; j < divisorSize; ++j)
            {
                remainder[i + j] ^= divisor[j];
            }
        }
    }

    return remainder;
}

// Fun��o para decodificar os dados utilizando Reed-Solomon
std::vector<int> decodeReedSolomon(std::vector<int> receivedData, int numECC)
{
    std::vector<int> syndrome(numECC, 0);

    for (int i = 0; i < receivedData.size() - numECC; ++i)
    {
        int factor = receivedData[i];
        std::vector<int> product = multiplyPolynomials(syndrome, std::vector<int> { factor });
        syndrome.insert(syndrome.begin(), product.begin(), product.end());
        syndrome[numECC - 1] ^= factor;
    }

    std::vector<int> divisor(numECC + 1, 0);
    divisor[0] = 1;

    std::vector<int> remainder = dividePolynomials(syndrome, divisor);
    int remainderSize = remainder.size();

   /* if (remainderSize > 0)
    {
        std::cout << "Erro detectado!" << std::endl;
        // Fa�a a corre��o dos erros aqui, se necess�rio
    }
    else
    {
        std::cout << "Nenhum erro detectado." << std::endl;
    }

    // Retorne apenas os dados originais (descarte os bytes de redund�ncia)*/
    return std::vector<int>(receivedData.begin(), receivedData.end() - numECC);
}
std::string binaryToString(const std::string& binary) {
    std::string result;
    for (size_t i = 0; i < binary.length(); i += 8) {
        std::string segment = binary.substr(i, 8);
        int decimal = std::stoi(segment, nullptr, 2);
        result += static_cast<char>(decimal);
    }
    return result;
}
int main()
{
    std::string inputStr;

    while(std::cin >> inputStr){

    std::vector<int> receivedData;
    for (char c : inputStr)
    {
        receivedData.push_back(c - '0');
    }

    int numECC = 2;  // N�mero de bytes de redund�ncia (erro-correction code)

    std::vector<int> decodedData = decodeReedSolomon(receivedData, numECC);
    std::string vetor = "";
    for (int val : decodedData)
    {
        vetor += std::to_string(val);
    }
    std::cout << std::endl;
    std::string str = binaryToString(vetor); // Converter para string

    std::cout << str << std::endl;
    std::cout << std::endl;

    }
    return 0;
}
