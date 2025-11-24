import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# ================================
# 1) CARREGAR DADOS DE AQUISICAO
# ================================
file_path = "data/dados_motor.csv"

data = pd.read_csv(file_path, header=None, names=["t_ms", "pwmA", "rpmA", "pwmB", "rpmB"])
data["t"] = data["t_ms"] / 1000.0  # converter ms para segundos

# ================================
# 2) DETECTAR MUDANCA DE DEGRAU
# ================================
pwm_diff = data["pwm"].diff()
step_index = pwm_diff.abs().idxmax()     # primeira mudanca de PWM
t0 = data["t"].iloc[step_index]          # tempo da mudanca
u_step = data["pwm"].iloc[step_index]    # valor do degrau

print("Degrau detectado em t =", t0, "s | PWM =", u_step)

# ================================
# 3) AJUSTAR MODELO DE 1a ORDEM
# ================================
# valor final = media dos ultimos 20% dos dados
final_values = data["rpm"].iloc[int(len(data)*0.8):]
rpm_final = final_values.mean()

K = rpm_final / u_step   # ganho estatico

# achar ponto onde rpm atingiu 63.2% do valor final:
target_value = 0.632 * rpm_final
idx_tau = (data["rpm"] - target_value).abs().idxmin()
tau = data["t"].iloc[idx_tau] - t0     # tempo desde t0

print("\n===== RESULTADOS =====")
print("Ganho K =", round(K, 4))
print("Constante de tempo τ =", round(tau, 4), "s")
print("Modelo estimado:  G(s) = K / (τ·s + 1)")

# ================================
# 4) PLOT PARA VALIDAR VISUALMENTE
# ================================
t_model = np.linspace(0, 5, 500)
rpm_model = rpm_final * (1 - np.exp(-t_model / tau))

plt.plot(data["t"], data["rpm"], label="Dados reais")
plt.plot(t0 + t_model, rpm_model, "--", label="Modelo 1a ordem")
plt.xlabel("tempo (s)")
plt.ylabel("RPM")
plt.title("Ajuste de sistema de 1a ordem")
plt.legend()
plt.grid()
plt.show()
