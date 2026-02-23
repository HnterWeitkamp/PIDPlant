import matplotlib.pyplot as plt
import numpy as np

A = np.array([[1,1],[0,1]])
B = np.array([[0.5],[1]])
H = np.array([[1,0]])
Q = 0.01 * np.eye(2)
R = np.array([[0.1]])
x_est = np.zeros((2,1))
P = np.eye(2)

def predict(x, P, u):
    x_pred = A @ x + B @ u
    P_pred = A @ P @ A.T + Q
    return x_pred, P_pred

def update(x_pred, P_pred, z):
    S = H @ P_pred @ H.T + R
    K = P_pred @ H.T @ np.linalg.inv(S)
    x_upd = x_pred + K @ (z - H @ x_pred)
    P_upd = (np.eye(K.shape[0]) - K @ H) @ P_pred
    return x_upd, P_upd


estimates = []
for k in range(N):
    x_pred, P_pred = predict(x_est, P, u[k])
    x_est, P = update(x_pred, P_pred, z[k])
    estimates.append(x_est[0,0])

plt.plot(estimates, label='Estimated State')
plt.plot(true_states, label='True State', alpha=0.5)
plt.legend(); plt.xlabel('Time'); plt.ylabel('State')
plt.show()

errors = true_states - np.array(estimates)
plt.plot(errors)
plt.title('Estimation Error Over Time')
plt.xlabel('Time'); plt.ylabel('Error')