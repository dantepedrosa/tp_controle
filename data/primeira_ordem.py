import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import os

# ======== IMPORT CSV ========
file = "data/primeira_ordem/bateria fraca/dados_motor.csv"
df = pd.read_csv(file)

# ======== ESCOLHER MOTOR ========
motor = "B"          # trocar para "B" para analisar o outro
output_dir = f"data/primeira_ordem/bateria fraca/motor{motor}/"
os.makedirs(output_dir, exist_ok=True)

df = df[df['motor'] == motor]

# detectar mudança de degrau automaticamente
df['step_change'] = df['pwm'].diff().fillna(0) != 0
df['step_id'] = df['step_change'].cumsum()

# ======= modelo de 1ª ordem =======
def first_order(t, K, tau):
    return K * (1 - np.exp(-t / tau))

def estimate_step(step_df):
    t = step_df['time_ms'].values / 1000.0
    y = step_df[f'speed{motor}'].values

    t = t - t[0]                # zerar tempo inicial

    K_guess = np.mean(y[-20:]) # chute inicial para K
    tau_guess = 0.5            # chute inicial para tau

    popt, _ = curve_fit(first_order, t, y, p0=[K_guess, tau_guess])
    K, tau = popt
    return K, tau, t, y

# ======= ANALISE POR DEGRAU =======
result_lines = []      # para output.txt
results = []

for step in df['step_id'].unique():
    step_df = df[df['step_id'] == step]
    if len(step_df) < 20:
        continue

    K, tau, t, y = estimate_step(step_df)
    results.append((step_df['pwm'].iloc[0], K, tau))

    t_fit = np.linspace(0, t.max(), 200)
    y_fit = first_order(t_fit, K, tau)

    # ======= SALVAR FIGURA =======
    plt.figure()
    plt.plot(t, y, 'o', label='experimental')
    plt.plot(t_fit, y_fit, label='ajuste')
    plt.title(f"PWM={step_df['pwm'].iloc[0]} -> K={K:.2f}, tau={tau:.2f}s")
    plt.xlabel("Tempo (s)")
    plt.ylabel(f"Pulsos/Ts (motor {motor})")
    plt.legend()
    fig_path = os.path.join(output_dir, f"pwm_{step_df['pwm'].iloc[0]}.png")
    plt.savefig(fig_path, dpi=300)
    plt.close()

# ======= SALVAR RESULTADO EM TXT =======
output_file = os.path.join(output_dir, "output.txt")
with open(output_file, "w") as f:
    f.write("MODELOS DE 1a ORDEM\n")
    f.write(f"Motor analisado: {motor}\n\n")
    for pwm, K, tau in results:
        line = f"PWM {pwm:>3}:   G(s) = {K:.3f} / ({tau:.3f}s + 1)"
        f.write(line + "\n")

print("\nRESULTADO FINAL - MODELOS DE 1ª ORDEM:")
for pwm, K, tau in results:
    print(f"PWM {pwm:>3}:   G(s) = {K:.3f} / ({tau:.3f}s + 1)")

print(f"\n✔ Todos os resultados salvos em: {output_dir}")
print(f"✔ Arquivo de texto: {output_file}")
