#include <iostream>
#include <vector>
#include <string>
#include <bitset>

// Função para multiplicar polinômios
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

// Função para realizar a divisão de polinômios (XOR)
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

// Função para codificar os dados utilizando Reed-Solomon
std::vector<int> encodeReedSolomon(const std::vector<int>& data, int numECC)
{
    int dataSize = data.size();
    std::vector<int> generator(numECC + 1, 0);
    generator[0] = 1;

    std::vector<int> encodedData(dataSize + numECC, 0);

    for (int i = 0; i < dataSize; ++i)
    {
        int factor = data[i] ^ encodedData[i];
        std::vector<int> product = multiplyPolynomials(generator, std::vector<int> { factor });
        encodedData[i] ^= product[0];
    }

    return encodedData;
}
std::string stringToBinary(const std::string& text)
{
    std::string binary;

    for (char c : text)
    {
        std::bitset<8> bits(c);
        binary += bits.to_string();
    }

    return binary;
}
int main()
{
    std::string linha;

    while(std::getline(std::cin, linha))
    {
        std::string text = linha;
        std::string binary = stringToBinary(text);
        int soma = 0;

        std::vector<int> vetor;

        for(int i=0; i< binary.size(); i++){
            if(binary[i] == '0'){
                vetor.push_back(0);
            }
            else if(binary[i] == '1'){
                vetor.push_back(1);
            }
        }
        std::vector<int> data;
        for (int c : vetor)
        {
            data.push_back(c);
        }

        int numECC = 2;  // Número de bytes de redundância (erro-correction code)

        std::vector<int> encodedData = encodeReedSolomon(data, numECC);
        for (int val : encodedData)
        {
            std::cout << val;
        }
        std::cout << std::endl;
    }
    return 0;
}
