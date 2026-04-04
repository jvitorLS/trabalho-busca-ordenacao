import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import os

CSV_FILE = "ex3/resultados.csv"
PDF_FILE = "ex3/relatorio.pdf"
GRAFICOS_DIR = "ex3/graficos"

os.makedirs(GRAFICOS_DIR, exist_ok=True)

# =========================
# Ler CSV
# =========================
df = pd.read_csv(CSV_FILE, sep=";")

ordenado = df[df["Caso"] == "Ordenado"].copy()
invertido = df[df["Caso"] == "Invertido"].copy()

# =========================
# Gerar gráficos (PNG)
# =========================
def gerar_grafico(df_plot, titulo, arquivo_saida, col1, col2, label1, label2):
    plt.figure(figsize=(10, 6))
    plt.plot(df_plot["Tamanho"], df_plot[col1], marker="o", label=label1)
    plt.plot(df_plot["Tamanho"], df_plot[col2], marker="o", label=label2)
    plt.title(titulo)
    plt.xlabel("Tamanho do vetor (n)")
    plt.ylabel("Tempo (microsegundos)")
    plt.grid(True)
    plt.legend()
    plt.savefig(arquivo_saida)
    plt.close()

# Gráfico Ordenado
gerar_grafico(
    ordenado,
    "Tempo de Ordenação - Dados Ordenados",
    f"{GRAFICOS_DIR}/grafico_ordenado.png",
    "InsertSort(us)",
    "QuickSort(us)",
    "InsertSort",
    "QuickSort"
)

# Gráfico Invertido
gerar_grafico(
    invertido,
    "Tempo de Ordenação - Dados Invertidos",
    f"{GRAFICOS_DIR}/grafico_invertido.png",
    "InsertSort(us)",
    "QuickSort(us)",
    "InsertSort",
    "QuickSort"
)

# InsertSort comparando
plt.figure(figsize=(10, 6))
plt.plot(ordenado["Tamanho"], ordenado["InsertSort(us)"], marker="o", label="InsertSort Ordenado")
plt.plot(invertido["Tamanho"], invertido["InsertSort(us)"], marker="o", label="InsertSort Invertido")
plt.title("InsertSort - Comparação Ordenado vs Invertido")
plt.xlabel("Tamanho do vetor (n)")
plt.ylabel("Tempo (microsegundos)")
plt.grid(True)
plt.legend()
plt.savefig(f"{GRAFICOS_DIR}/grafico_insertsort.png")
plt.close()

# QuickSort comparando
plt.figure(figsize=(10, 6))
plt.plot(ordenado["Tamanho"], ordenado["QuickSort(us)"], marker="o", label="QuickSort Ordenado")
plt.plot(invertido["Tamanho"], invertido["QuickSort(us)"], marker="o", label="QuickSort Invertido")
plt.title("QuickSort - Comparação Ordenado vs Invertido")
plt.xlabel("Tamanho do vetor (n)")
plt.ylabel("Tempo (microsegundos)")
plt.grid(True)
plt.legend()
plt.savefig(f"{GRAFICOS_DIR}/grafico_quicksort.png")
plt.close()

# =========================
# Função para inserir imagem no PDF
# =========================
def inserir_imagem_pdf(pdf, caminho_imagem, titulo):
    img = plt.imread(caminho_imagem)

    fig = plt.figure(figsize=(11, 8.5))
    plt.imshow(img)
    plt.axis("off")
    plt.title(titulo, fontsize=16)
    pdf.savefig(fig)
    plt.close()

# =========================
# Gerar PDF completo
# =========================
with PdfPages(PDF_FILE) as pdf:

    # ---------- Página 1: Capa ----------
    fig = plt.figure(figsize=(11, 8.5))
    plt.axis("off")

    plt.text(0.5, 0.8, "Relatório de Desempenho", fontsize=24, ha="center")
    plt.text(0.5, 0.72, "Comparação: InsertSort vs QuickSort", fontsize=18, ha="center")
    plt.text(0.5, 0.62, "Testes com Vetores Ordenados e Invertidos", fontsize=14, ha="center")

    plt.text(0.5, 0.55, "Aluno: João Vitor Nunes Lopes", fontsize=12, ha="center")
    plt.text(0.5, 0.50, "Github: https://github.com/jvitorLS/trabs-complexidade-algoritmo", fontsize=12, ha="center")
    plt.text(0.5, 0.45, "Professor: Elgio Schlemer", fontsize=12, ha="center")
    plt.text(0.5, 0.40, "Disciplina: Complexidade e Avaliação de Desempenho", fontsize=12, ha="center")
    plt.text(0.5, 0.35, "Linguagem: C", fontsize=12, ha="center")

    pdf.savefig(fig)
    plt.close()

    # ---------- Página 2: Tabela ----------
    fig = plt.figure(figsize=(11, 8.5))
    plt.axis("off")

    plt.text(0.5, 0.95, "Tabela de Resultados", fontsize=18, ha="center")

    tabela_df = df.copy()
    tabela_df.columns = ["Tamanho", "Caso", "InsertSort (us)", "QuickSort (us)"]

    tabela = plt.table(
        cellText=tabela_df.values,
        colLabels=tabela_df.columns,
        loc="center",
        cellLoc="center"
    )

    tabela.auto_set_font_size(False)
    tabela.set_fontsize(10)
    tabela.scale(1, 1.5)

    pdf.savefig(fig)
    plt.close()

    # ---------- Página 3: Análise ----------
    fig = plt.figure(figsize=(11, 8.5))
    plt.axis("off")

    texto = (
        "Análise dos Resultados\n\n"
        "Os testes mostram claramente o impacto da complexidade assintótica no tempo de execução.\n\n"
        "1) InsertSort\n"
        "- Quando os dados já estão ordenados, o InsertSort praticamente não realiza trocas, operando próximo do melhor caso O(n).\n"
        "- Quando os dados estão invertidos, o algoritmo precisa deslocar muitos elementos a cada inserção, resultando no pior caso O(n²).\n"
        "- Isso explica o crescimento muito rápido do tempo no cenário invertido.\n\n"
        "2) QuickSort\n"
        "- O QuickSort apresentou crescimento mais controlado, compatível com o caso médio O(n log n).\n"
        "- Porém, dependendo da escolha do pivô, ele pode ter desempenho pior em vetores já ordenados, aproximando-se de O(n²).\n\n"
        "3) Comparação Geral\n"
        "- Para dados já ordenados, o InsertSort foi o mais rápido.\n"
        "- Para dados invertidos e tamanhos maiores, o QuickSort foi significativamente mais eficiente.\n\n"
        "Conclusão: InsertSort é adequado apenas para vetores pequenos ou quase ordenados, enquanto QuickSort é mais indicado\n"
        "para grandes volumes de dados e casos gerais, mas pode degradar se o pivô não for escolhido adequadamente.\n"
    )

    fig.text(0.05, 0.95, texto, fontsize=14, va="top", ha="left", wrap=True)
    pdf.savefig(fig)
    plt.close()

    # ---------- Gráficos ----------
    inserir_imagem_pdf(pdf, f"{GRAFICOS_DIR}/grafico_ordenado.png", "Gráfico 1 - Ordenação com Dados Ordenados")
    inserir_imagem_pdf(pdf, f"{GRAFICOS_DIR}/grafico_invertido.png", "Gráfico 2 - Ordenação com Dados Invertidos")
    inserir_imagem_pdf(pdf, f"{GRAFICOS_DIR}/grafico_insertsort.png", "Gráfico 3 - InsertSort (Ordenado vs Invertido)")
    inserir_imagem_pdf(pdf, f"{GRAFICOS_DIR}/grafico_quicksort.png", "Gráfico 4 - QuickSort (Ordenado vs Invertido)")

print("Relatório gerado com sucesso!")
print(f"- PDF: {PDF_FILE}")
print(f"- Gráficos: pasta '{GRAFICOS_DIR}/'")