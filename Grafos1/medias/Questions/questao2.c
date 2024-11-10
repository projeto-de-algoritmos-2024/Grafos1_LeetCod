int largestCombination(int* candidates, int candidatesSize) {
    int ans = 0;

    // Itera sobre 24 bits (suficiente para representar números até 2^24)
    for (int i = 0; i < 24; i++) {
        int mask = 1 << i; // Cria uma máscara com o bit `i` ativado
        int count = 0;

        // Verifica quantos números no array possuem o bit `i` ativado
        for (int j = 0; j < candidatesSize; j++) {
            if (candidates[j] & mask) {
                count++; // Incrementa o contador se o bit estiver ativado
            }
        }

        // Atualiza o resultado com o maior valor encontrado
        if (count > ans) {
            ans = count;
        }
    }

    return ans;
}
