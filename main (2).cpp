#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// Dados das contas
const int MAX_CONTAS = 100;
int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];
int quantidadeContas = 0;

// Historico de movimentacoes
const int MAX_MOVIMENTACOES = 500;
int contaMovimentacao[MAX_MOVIMENTACOES];
char tipoMovimentacao[MAX_MOVIMENTACOES];
double valorMovimentacao[MAX_MOVIMENTACOES];
int quantidadeMovimentacoes = 0;

// Pega o texto ate o proximo ';' e tira ele da linha
string pegarCampo(string &linha) {
    string campo;
    int pos = linha.find(";");
    if (pos == -1) {
        campo = linha;
        linha = "";
    } else {
        campo = linha.substr(0, pos);
        linha = linha.substr(pos + 1);
    }
    return campo;
}

void carregarContas() {
    ifstream arquivo("contas.txt");
    if (!arquivo.is_open()) {
        // primeira execucao, ainda nao existe arquivo
        return;
    }

    string linha;
    while (getline(arquivo, linha) && quantidadeContas < MAX_CONTAS) {
        if (linha == "") continue;

        numeroConta[quantidadeContas] = stoi(pegarCampo(linha));
        nomeCliente[quantidadeContas] = pegarCampo(linha);
        cpf[quantidadeContas] = pegarCampo(linha);
        tipoConta[quantidadeContas] = stoi(pegarCampo(linha));
        saldo[quantidadeContas] = stod(pegarCampo(linha));
        contaAtiva[quantidadeContas] = (pegarCampo(linha) == "1");
        quantidadeContas++;
    }
    arquivo.close();
}

void salvarContas() {
    ofstream arquivo("contas.txt");
    if (arquivo.is_open()) {
        arquivo << fixed << setprecision(2);
        for (int i = 0; i < quantidadeContas; i++) {
            arquivo << numeroConta[i] << ";"
                    << nomeCliente[i] << ";"
                    << cpf[i] << ";"
                    << tipoConta[i] << ";"
                    << saldo[i] << ";"
                    << contaAtiva[i] << endl;
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir contas.txt para gravar." << endl;
    }
}

void carregarMovimentacoes() {
    ifstream arquivo("movimentacoes.txt");
    if (!arquivo.is_open()) {
        // primeira execucao, ainda nao existe arquivo
        return;
    }

    string linha;
    while (getline(arquivo, linha) && quantidadeMovimentacoes < MAX_MOVIMENTACOES) {
        if (linha == "") continue;

        contaMovimentacao[quantidadeMovimentacoes] = stoi(pegarCampo(linha));
        tipoMovimentacao[quantidadeMovimentacoes] = pegarCampo(linha)[0];
        valorMovimentacao[quantidadeMovimentacoes] = stod(pegarCampo(linha));
        quantidadeMovimentacoes++;
    }
    arquivo.close();
}

void salvarMovimentacoes() {
    ofstream arquivo("movimentacoes.txt");
    if (arquivo.is_open()) {
        arquivo << fixed << setprecision(2);
        for (int i = 0; i < quantidadeMovimentacoes; i++) {
            arquivo << contaMovimentacao[i] << ";"
                    << tipoMovimentacao[i] << ";"
                    << valorMovimentacao[i] << endl;
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir movimentacoes.txt para gravar." << endl;
    }
}

int main() {
    // Recupera o que foi salvo na ultima execucao
    carregarContas();
    carregarMovimentacoes();

    int opcao;

    do {
        cout << "=====================" << endl;
        cout << "-----BANCO DO IAN-----" << endl;
        cout << "=====================" << endl;
        cout << "_____________________" << endl;

        cout << "\n1 - Cadastrar conta" << endl;
        cout << "2 - Listar contas" << endl;
        cout << "3 - Consultar conta" << endl;
        cout << "4 - Depositar" << endl;
        cout << "5 - Sacar" << endl;
        cout << "6 - Transferir" << endl;
        cout << "7 - Extrato" << endl;
        cout << "0 - Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {

        case 1: { // Cadastrar
            if (quantidadeContas >= MAX_CONTAS) {
                cout << "Limite de contas atingido." << endl;
                break;
            }
            cout << "Numero da conta: ";
            cin >> numeroConta[quantidadeContas];
            cin.ignore();
            cout << "Nome: ";
            getline(cin, nomeCliente[quantidadeContas]);
            cout << "CPF: ";
            getline(cin, cpf[quantidadeContas]);
            cout << "Tipo da conta (1-Corrente, 2-Poupanca): ";
            cin >> tipoConta[quantidadeContas];
            cout << "Saldo inicial: ";
            cin >> saldo[quantidadeContas];
            contaAtiva[quantidadeContas] = true;
            quantidadeContas++;
            salvarContas();
            cout << "Conta cadastrada." << endl;
            break;
        }

        case 2: { // Listar
            for (int i = 0; i < quantidadeContas; i++) {
                cout << numeroConta[i] << " | " << nomeCliente[i] << " | " << cpf[i]
                     << " | Tipo " << tipoConta[i] << " | Saldo: R$ " << saldo[i] << endl;
            }
            break;
        }

        case 3: { // Consultar
            int numero, indice = -1;
            cout << "Numero da conta: ";
            cin >> numero;
            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == numero) indice = i;
            }
            if (indice == -1) {
                cout << "Conta nao encontrada." << endl;
            } else {
                cout << numeroConta[indice] << " | " << nomeCliente[indice] << " | " << cpf[indice]
                     << " | Tipo " << tipoConta[indice] << " | Saldo: R$ " << saldo[indice] << endl;
            }
            break;
        }

        case 4: { // Depositar
            int numero, indice = -1;
            double valor;
            cout << "Numero da conta: ";
            cin >> numero;
            cout << "Valor: ";
            cin >> valor;
            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == numero) indice = i;
            }
            if (indice == -1) {
                cout << "Conta nao encontrada." << endl;
            } else {
                saldo[indice] = saldo[indice] + valor;
                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                valorMovimentacao[quantidadeMovimentacoes] = valor;
                quantidadeMovimentacoes++;
                salvarContas();
                salvarMovimentacoes();
                cout << "Deposito realizado." << endl;
            }
            break;
        }

        case 5: { // Sacar
            int numero, indice = -1;
            double valor;
            cout << "Numero da conta: ";
            cin >> numero;
            cout << "Valor: ";
            cin >> valor;
            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == numero) indice = i;
            }
            if (indice == -1) {
                cout << "Conta nao encontrada." << endl;
            } else if (saldo[indice] < valor) {
                cout << "Saldo insuficiente." << endl;
            } else {
                saldo[indice] = saldo[indice] - valor;
                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                valorMovimentacao[quantidadeMovimentacoes] = valor;
                quantidadeMovimentacoes++;
                salvarContas();
                salvarMovimentacoes();
                cout << "Saque realizado." << endl;
            }
            break;
        }

        case 6: { // Transferir
            int numeroOrigem, numeroDestino;
            int indiceOrigem = -1, indiceDestino = -1;
            double valor;
            cout << "Conta de origem: ";
            cin >> numeroOrigem;
            cout << "Conta de destino: ";
            cin >> numeroDestino;
            cout << "Valor: ";
            cin >> valor;
            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == numeroOrigem) indiceOrigem = i;
                if (numeroConta[i] == numeroDestino) indiceDestino = i;
            }
            if (indiceOrigem == -1 || indiceDestino == -1) {
                cout << "Conta nao encontrada." << endl;
            } else if (!contaAtiva[indiceOrigem] || !contaAtiva[indiceDestino]) {
                cout << "Conta inativa." << endl;
            } else if (valor <= 0) {
                cout << "O valor deve ser positivo." << endl;
            } else if (saldo[indiceOrigem] < valor) {
                cout << "Saldo insuficiente." << endl;
            } else if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
                cout << "Sem espaco no historico." << endl;
            } else {
                saldo[indiceOrigem] = saldo[indiceOrigem] - valor;
                saldo[indiceDestino] = saldo[indiceDestino] + valor;

                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceOrigem];
                tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                valorMovimentacao[quantidadeMovimentacoes] = valor;
                quantidadeMovimentacoes++;

                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceDestino];
                tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                valorMovimentacao[quantidadeMovimentacoes] = valor;
                quantidadeMovimentacoes++;

                salvarContas();
                salvarMovimentacoes();
                cout << "Transferencia realizada." << endl;
            }
            break;
        }

        case 7: { // Extrato
            int numero, indice = -1;
            cout << "Numero da conta: ";
            cin >> numero;
            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == numero) indice = i;
            }
            if (indice == -1) {
                cout << "Conta nao encontrada." << endl;
            } else {
                for (int i = 0; i < quantidadeMovimentacoes; i++) {
                    if (contaMovimentacao[i] == numero) {
                        if (tipoMovimentacao[i] == 'D') {
                            cout << "Deposito: R$ " << valorMovimentacao[i] << endl;
                        }
                        else if (tipoMovimentacao[i] == 'S') {
                            cout << "Saque: R$ " << valorMovimentacao[i] << endl;
                        }
                    }
                }
            }
            break;
        }

        case 0:
            cout << "Encerrando." << endl;
            break;

        default:
            cout << "Opcao invalida." << endl;
        }

    } while (opcao != 0);

    return 0;
}