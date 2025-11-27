import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# ======== IMPORT CSV ========
file = "dados_motor.csv"
df = pd.read_csv(file)

# usar somente motor A
df = df[df['motor'] == 'A']

# detectar mudança de degrau automaticamente
df['step_change'] = df['pwm'].diff().fillna(0) != 0
df['step_id'] = df['step_change'].cumsum()

# ======= modelo de 1ª ordem =======
def first_order(t, K, tau):
    return K * (1 - np.exp(-t / tau))

def estimate_step(step_df):
    t = step_df['time_ms'].values / 1000.0
    y = step_df['speedA'].values

    # remover inicio antes da subida
    t = t - t[0]

    K_guess = np.mean(y[-20:])     # valor final ~ ganho
    tau_guess = 0.5                # chute inicial

    popt, _ = curve_fit(first_order, t, y, p0=[K_guess, tau_guess])
    K, tau = popt
    return K, tau, t, y

# ======= ANALISE POR DEGRAU =======
results = []
for step in df['step_id'].unique():
    step_df = df[df['step_id'] == step]
    if len(step_df) < 20:     # ignora trechos curtos
        continue

    K, tau, t, y = estimate_step(step_df)
    results.append((step_df['pwm'].iloc[0], K, tau))

    # PLOT para cada degrau
    t_fit = np.linspace(0, t.max(), 200)
    y_fit = first_order(t_fit, K, tau)

    plt.plot(t, y, 'o', label='experimental')
    plt.plot(t_fit, y_fit, label='ajuste')
    plt.title(f"PWM={step_df['pwm'].iloc[0]}  ->  K={K:.2f}, tau={tau:.2f}s")
    plt.xlabel("Tempo (s)")
    plt.ylabel("Pulsos/Ts")
    plt.legend()
    plt.show()

# ======= MOSTRA RESULTADO FINAL =======
print("\nRESULTADO FINAL - MODELOS DE 1ª ORDEM:")
for pwm, K, tau in results:
    print(f"PWM {pwm:>3}:   G(s) = {K:.3f} / ({tau:.3f}s + 1)")
