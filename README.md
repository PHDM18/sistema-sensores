Este projeto contém três programas em C para manipulação de leituras de sensores em uma planta industrial inteligente.

#programa1.c – Organização dos Dados

- Lê um arquivo com leituras no formato `<timestamp> <ID_SENSOR> <valor>`.
- Separa as leituras por sensor em arquivos separados.
- Ordena os dados por timestamp.

programa2.c – Consulta por Instante

- Recebe o nome de um sensor e um timestamp como argumentos.
- Faz busca binária no arquivo do sensor para retornar a leitura mais próxima daquele instante.

programa3.c – Geração de Arquivo de Teste

- Gera um arquivo com 2000 leituras para cada sensor.
- Cada leitura tem timestamp aleatório entre duas datas e valor conforme tipo.

Como compilar

Use `gcc`:
```
gcc programa1.c -o organizar
gcc programa2.c -o buscar
gcc programa3.c -o gerar
```

Como usar

Gerar arquivo de teste
./gerar

# Organizar dados

./organizar leituras.txt


# Buscar valor mais próximo

./buscar temp 1672531200

