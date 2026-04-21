import numpy as np
import matplotlib.pyplot as plt

data1 = np.genfromtxt('linelist_data.csv', delimiter=';', skip_header=1, encoding='utf-8-sig')
n1 = data1[:, 0]
time1 = data1[:, 2]

data2 = np.genfromtxt('array_data.csv', delimiter=';', skip_header=1, encoding='utf-8-sig')
n2 = data2[:, 0]
time2 = data2[:, 2]

coeffs1 = np.polyfit(n1, time1, 1)
poly1 = np.poly1d(coeffs1)

coeffs2 = np.polyfit(n2, time2, 2)
poly2 = np.poly1d(coeffs2)

n_pred1 = np.linspace(max(n1), 2_000_000, 100)
time_pred1 = poly1(n_pred1)

n_pred2 = np.linspace(max(n2), 2_000_000, 100)
time_pred2 = poly2(n_pred2)

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))

ax1.plot(n1, time1, 'o-', label='Реальные данные', linewidth=2, markersize=6)
ax1.plot(n1, poly1(n1), 's-', label='МНК (линейная)', linewidth=2, markersize=4)
ax1.plot(n_pred1, time_pred1, '--', label='Прогноз', linewidth=2)
ax1.set_xlabel('N')
ax1.set_ylabel('Время расчета (сек)')
ax1.set_title('LineList')
ax1.legend()
ax1.grid(True, linestyle=':', alpha=0.7)

ax2.plot(n2, time2, 'o-', label='Реальные данные', linewidth=2, markersize=6)
ax2.plot(n2, poly2(n2), 's-', label='МНК (квадратичная)', linewidth=2, markersize=4)
ax2.plot(n_pred2, time_pred2, '--', label='Прогноз', linewidth=2)
ax2.set_xlabel('N')
ax2.set_ylabel('Время расчета (сек)')
ax2.set_title('Array')
ax2.legend()
ax2.grid(True, linestyle=':', alpha=0.7)

plt.tight_layout()
plt.show()