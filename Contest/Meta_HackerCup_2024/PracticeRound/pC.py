import sys
import threading
import random

def main():
    import sys
    import random
    sys.setrecursionlimit(1 << 25)
    T = int(sys.stdin.readline())
    for case_num in range(1, T + 1):
        N = int(sys.stdin.readline())
        points = []
        for _ in range(N):
            x_str, y_str = sys.stdin.readline().split()
            x, y = int(x_str), int(y_str)
            points.append((x, y))
        max_estimated_N_line = 0
        M = min(N, 1000)  # Adjusted sample size
        K = min(5000, 50000000 // M)  # Adjusted number of iterations to limit total operations
        sampled_indices = [random.randint(0, N - 1) for _ in range(M)]
        for _ in range(K):
            i = random.randint(0, N - 1)
            j = random.randint(0, N - 1)
            while j == i:
                j = random.randint(0, N - 1)
            x1, y1 = points[i]
            x2, y2 = points[j]
            dx = x2 - x1
            dy = y2 - y1
            count = 0
            for k in sampled_indices:
                xk, yk = points[k]
                cross = (xk - x1) * dy - (yk - y1) * dx
                if cross == 0:
                    count += 1
            # Estimate N_line_estimated using integer arithmetic to avoid floating-point errors
            numerator = N * count + M // 2  # Adding M // 2 for rounding
            N_line_estimated = numerator // M
            if N_line_estimated > max_estimated_N_line:
                max_estimated_N_line = N_line_estimated
        M_final = N - max_estimated_N_line
        print(f"Case #{case_num}: {M_final}")

threading.Thread(target=main).start()
